#include "ComputeQevj.h"

vector<XModel> ComputeQevj::computeQevj_s(vector<XModel> vec_x,
                                          long double h, long double c, long double K,
                                          long double Tex, long double Tvib, long double Trot,
                                          float gne, float gno, float gbase)
{
    long double Gv = 0;
    for(size_t i = 0; i < vec_x.size(); i++){
        XModel *x_model = &vec_x[i];
        if(x_model->j2 == 0){
            Gv = x_model->e2;
        }
        x_model->Qevj = computeQevj(*x_model, Gv, h, c, K, Tex, Tvib, Trot, gne, gno, gbase);
    }
    return vec_x;
}

long double ComputeQevj::computeQevj(XModel x_model, long double Gv,
                                     long double h, long double c, long double K,
                                     long double Tex, long double Tvib, long double Trot,
                                     float gne, float gno, float gbase)
{
    long double ret_ =0;
    //G(v) = G(vn''j0''), F(j) = F(vn''jn'') - G(vn''j0'')
    long double Fj = x_model.e2 - Gv;
    long double gj = sumgj(x_model.j2, gne, gno, gbase);
    ret_ = DecimalUtils::exp_((-1 * (h * c / K)) * ((x_model.t2 / Tex) + (Gv / Tvib) + (Fj / Trot)));
    ret_ = ret_ * gj;
    return ret_;
}

long double ComputeQevj::sumgj(float j, float gne, float gno, float gbase)
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
