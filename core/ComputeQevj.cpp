#include "ComputeQevj.h"

void ComputeQevj::init(vector<XModel> vec_x, long double h, long double c, long double K,
                       long double Tex, long double Tvib, long double Trot,
                       float gne, float gno, float gbase)
{
    m_vec_x = vec_x;
    const_h = h;
    const_c = c;
    const_K = K;
    const_Tex = Tex;
    const_Tvib = Tvib;
    const_Trot = Trot;
    const_gne = gne;
    const_gno = gno;
    const_gbase = gbase;
}

vector<XModel> ComputeQevj::computeQevj_s()
{
    long double Gv = 0;
    for(size_t i = 0; i < m_vec_x.size(); i++){
        XModel *x_model = &m_vec_x[i];
        if(x_model->j2 == 0){
            Gv = x_model->e2;
        }
        x_model->Qevj = computeQevj(*x_model, Gv);
//        std::cout << "g'=" << x_model->g1 << " "
//                  << "v'=" << x_model->v1 << " "
//                  << "j'=" << x_model->j1 << " "
//                  << "e'=" << x_model->e1 << " "
//                  << "t'=" << x_model->t1 << " "
//                  << " --- "
//                  << "g''=" << x_model->g2 << " "
//                  << "v''=" << x_model->v2 << " "
//                  << "j''=" << x_model->j2 << " "
//                  << "e''=" << x_model->e2 << " "
//                  << "t''=" << x_model->t2 << " "
//                  << " --- "
//                  << "x= " << x_model->x << " "
//                  << "a= " << x_model->a << " "
//                  << "Qvej= " << x_model->Qevj << " "<< std::endl;
    }
    return m_vec_x;
}

long double ComputeQevj::computeQevj(XModel x_model, long double Gv)
{
    long double ret_ =0;
    //G(v) = G(vn''j0''), F(j) = F(vn''jn'') - G(vn''j0'')
    long double Fj = x_model.e2 - Gv;
    long double gj = sumgj(x_model.j2);
    ret_ = DecimalUtils::exp_((-1 * (const_h * const_c / const_K)) * ((x_model.t2 / const_Tex) + (Gv / const_Tvib) + (Fj / const_Trot)));
    ret_ = ret_ * gj;
    return ret_;
}

long double ComputeQevj::sumgj(float j)
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
