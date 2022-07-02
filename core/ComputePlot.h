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
    //设置区间
    void computPlots(float min_x, float max_x, float step, vector<XModel> vec_x);
//private:
    vector<XModel> computeBasic(float min_x, float max_x, vector<XModel> vec_x);
    vector<PlotModel> computeSinglePlot(vector<long double> vec_plot_x, XModel x_basic);
    //高斯分布数据  1.μ=0 期望值/分布平均值/中心点, 2.σ=0.25 标准差/展宽
    std::vector<FaiModel> compute_fai_gauss(XModel x_basic, vector<long double> vec_plot_x);
    //Trot + 分子量
    std::vector<FaiModel> compute_fai(float Trot, float weight, XModel x_model, vector<long double> vec_plot_x);
};

#endif // COMPUTEPLOT_H
