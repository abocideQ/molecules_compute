#ifndef COMPUTEFAI_H
#define COMPUTEFAI_H

#include <math.h>
#include <iostream>
#include <vector>
#include "XYModel.h"
#include "DecimalUtils.h"

class ComputeFai
{
public:
//    long double compute_fai();
    //高斯分布数据  1.μ=0 期望值/分布平均值/中心点, 2.σ=0.25 标准差/展宽
    std::vector<FaiModel> compute_fai_gauss(float u, float o, std::vector<long double> vec_x);

private:
//    long double compute_A(long double wV, long double t);
//    long double compute_L(long double wV);
//    long double compute_t(long double wL, long double wV);
//    long double compute_wV(long double wL, long double wG);
};

#endif // COMPUTEFAI_H
