#include "ComputeQ.h"

void ComputeQ::init(vector<VJModel> vec_x, long double h, long double c, long double KTex, long double KTvib, long double KTrot, int gne, int gno, long double gbase)
{
  m_vec_x = vec_x;
  const_h = h;
  const_c = c;
  const_KTex = KTex;
  const_KTvib = KTvib;
  const_KTrot = KTrot;
  const_gne = gne;
  const_gno = gno;
  const_gbase = gbase;
}

long double ComputeQ::sumQ()
{
  m_vec_Te = vector<VJModel>();
  m_vec_Gv = vector<VJModel>();
  m_vec_Fj = vector<VJModel>();
  m_vec_Te.push_back(m_vec_x[0]);
  for (size_t i = 0; i < m_vec_x.size(); i++)
  {
    if (m_vec_x[i].j > 0)
    {
      continue;
    }
    m_vec_Gv.push_back(m_vec_x[i]);
  }
  for (size_t i = 0; i < m_vec_x.size(); i++)
  {
    m_vec_Fj.push_back(m_vec_x[i]);
  }
  long double Q = sumQe();
  std::cout << "Q = " << Q << endl;
  return Q;
}

long double ComputeQ::sumQe()
{
  long double ret_Qe = 0;
  long double exp = DecimalUtils::exp_(-1 * ((const_h * const_c * m_vec_Te[0].t) / (const_KTex))) * sumQv();
  ret_Qe = DecimalUtils::sum_(ret_Qe, exp);
  std::cout << "Qe = " << ret_Qe << endl;
  return ret_Qe;
}

long double ComputeQ::sumQv()
{
  long double ret_Qv = 0;
  for (size_t i = 0; i < m_vec_Gv.size(); i++)
  {
    long double exp = DecimalUtils::exp_(-1 * ((const_h * const_c * m_vec_Gv[i].e) / (const_KTvib))) * sumQj(m_vec_Gv[i].v);
    ret_Qv = DecimalUtils::sum_(ret_Qv, exp);
    std::cout << "*** exp(hcG(v)/ktvib) = " << ret_Qv << endl;
  }
//  std::cout << "sumQv = " << ret_Qv << endl;
  return ret_Qv;
}

long double ComputeQ::sumQj(float v)
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
    long double exp = DecimalUtils::exp_(-1 * ((const_h * const_c * (m_vec_Fj[i].e - vnj0)) / (const_KTrot)));
    exp = sumgj(m_vec_Fj[i].j) * exp;
    ret_Qj = DecimalUtils::sum_(ret_Qj, exp);
    std::cout << "--- gjexp(hcF(j)/ktrot) = " << ret_Qj << endl;
  }
  return ret_Qj;
}

long double ComputeQ::sumgj(float j)
{
  // gj = gn * base * (2j +2) ;
  // gne 偶 gno 奇
  long double gj = 0;
  if (DecimalUtils::even_(j))
  { //偶
    gj = const_gne * const_gbase * ((2 * j) + 1);
  }
  else
  { //奇
    gj = const_gno * const_gbase * ((2 * j) + 1);
  }
  return gj;
}
