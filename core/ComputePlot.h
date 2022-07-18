#ifndef COMPUTEPLOT_H
#define COMPUTEPLOT_H
#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "XYModel.h"
#include "DecimalUtils.h"

class ComputePlot
{
public:
    std::vector<CoordinateModel> computPlots(float min_x, float max_x, float step, float weight, float Trot, vector<XModel> vec_x);

    vector<CoordinateModel> computBasicPlots(vector<XModel> vec_x);

    void computTestPlots(float weight, float Trot, vector<CoordinateModel> *response);
private:
    vector<XModel> computeBasic(float min_x, float max_x, vector<XModel> vec_x);
    //=========method 0
    CoordinateModel *computeCoordinate(float weight, float Trot, XModel x_basic, long double x);
//    =========method 1
//    vector<CoordinateModel> computePlot(float Trot, float weight, vector<XModel> vec_x_basic, vector<long double> vec_plot_x);
//    //Trot:15000 weight:分子量
//    std::vector<CoordinateModel> computeCoordinate(float Trot, float weight, XModel x_basic, vector<long double> vec_plot_x);
//    //=========method 2
//    //高斯分布数据  1.μ=0 期望值/分布平均值/中心点, 2.σ=0.25 标准差/展宽
//    std::vector<CoordinateModel> compute_fai_gauss(XModel x_basic, vector<long double> vec_plot_x);
};

#endif // COMPUTEPLOT_H
