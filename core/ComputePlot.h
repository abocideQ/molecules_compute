#ifndef COMPUTEPLOT_H
#define COMPUTEPLOT_H
#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "XYModel.h"
#include "DecimalUtils.h"
#include "LongDouble.h"

class ComputePlot
{
public:
    //设置区间
    void computPlots(float min_x, float max_x, float step, long double Q, long double N, vector<XModel> vec_x);
private:
    vector<XModel> computeBasic(float min_x, float max_x, vector<XModel> vec_x);
    vector<XModel> computeSinglePlot(vector<XModel> vec_x_basic);
};

#endif // COMPUTEPLOT_H
