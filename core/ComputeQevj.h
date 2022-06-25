#ifndef COMPUTEQEVJ_H
#define COMPUTEQEVJ_H

#include <vector>
#include <iostream>
#include "XYModel.h"
#include "DecimalUtils.h"

class ComputeQevj
{
public:
    void init(vector<XModel> vec_x, long double h, long double c, long double K, long double Tex, long double Tvib, long double Trot, float gne, float gno, float gbase);
    vector<XModel> computeQevj_s();

private:
    vector<XModel> m_vec_x;
    long double const_h = 0;
    long double const_c = 0;
    long double const_K = 0;
    long double const_Tex = 0;
    long double const_Tvib = 0;
    long double const_Trot = 0;
    float const_gne = 0;
    float const_gno = 0;
    float const_gbase = 1;
    long double computeQevj(XModel x_model, long double Gv);
    long double sumgj(float j);
};

#endif // COMPUTEQEVJ_H
