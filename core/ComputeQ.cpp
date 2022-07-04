#include "ComputeQ.h"

long double ComputeQ::sumQ(vector<VJModel> vec_vj,
                           long double h, long double c, long double K,
                           long double Tex, long double Tvib, long double Trot,
                           float gne, float gno, float gbase)
{
    m_vec_Gv = vector<VJModel>();
    m_vec_Fj = vector<VJModel>();
    for (size_t i = 0; i < vec_vj.size(); i++)
    {
        if (vec_vj[i].j > 0)
        {
            continue;
        }
        m_vec_Gv.push_back(vec_vj[i]);
    }
    for (size_t i = 0; i < vec_vj.size(); i++)
    {
        m_vec_Fj.push_back(vec_vj[i]);
    }
    long double Q = sumQe(vec_vj,
                          h, c, K,
                          Tex, Tvib, Trot,
                          gne, gno, gbase);
    std::vector<VJModel>().swap(m_vec_Gv);
    std::vector<VJModel>().swap(m_vec_Fj);
    return Q;
}

long double ComputeQ::sumQe(vector<VJModel> vec_vj,
                            long double h, long double c, long double K,
                            long double Tex, long double Tvib, long double Trot,
                            float gne, float gno, float gbase)
{
    long double ret_Qe = 0;
    long double exp = DecimalUtils::exp_(-1 * ((h * c * vec_vj[0].t) / (K * Tex))) * sumQv(vec_vj,
                                                                                           h, c, K,
                                                                                           Tex, Tvib, Trot,
                                                                                           gne, gno, gbase);
    ret_Qe = DecimalUtils::sum_(ret_Qe, exp);
    return ret_Qe;
}

long double ComputeQ::sumQv(vector<VJModel> vec_vj,
                            long double h, long double c, long double K,
                            long double Tex, long double Tvib, long double Trot,
                            float gne, float gno, float gbase)
{
    long double ret_Qv = 0;
    for (size_t i = 0; i < m_vec_Gv.size(); i++)
    {
        long double exp = DecimalUtils::exp_(-1 * ((h * c * m_vec_Gv[i].e) / (K * Tvib))) * sumQj(m_vec_Gv[i].v,
                                                                                                  vec_vj,
                                                                                                  h, c, K,
                                                                                                  Tex, Tvib, Trot,
                                                                                                  gne, gno, gbase);
        ret_Qv = DecimalUtils::sum_(ret_Qv, exp);
    }
    return ret_Qv;
}

long double ComputeQ::sumQj(float v,
                            vector<VJModel> vec_vj,
                            long double h, long double c, long double K,
                            long double Tex, long double Tvib, long double Trot,
                            float gne, float gno, float gbase)
{
    long double ret_Qj = 0;
    long double vnj0 = 0;
    for (size_t i = 0; i < m_vec_Fj.size(); i++)
    {
        if (m_vec_Fj[i].v != v)
        {
            continue;
        }
        else if (m_vec_Fj[i].j == 0)
        {
            vnj0 = m_vec_Fj[i].e;
        }
        long double exp = DecimalUtils::exp_(-1 * ((h * c * (m_vec_Fj[i].e - vnj0)) / (K * Trot)));
        exp = sumgj(m_vec_Fj[i].j, gne, gno ,gbase) * exp;
        ret_Qj = DecimalUtils::sum_(ret_Qj, exp);
    }
    return ret_Qj;
}

long double ComputeQ::sumgj(float j, float gne, float gno, float gbase)
{
    // gj = gn * base * (2j +2) ;
    // gne 偶 gno 奇
    long double gj = 0;
    if (DecimalUtils::even_(j))
    { //偶
        gj = gne * gbase * ((2 * j) + 1);
    }
    else
    { //奇
        gj = gno * gbase * ((2 * j) + 1);
    }
    return gj;
}
