#ifndef COMPUTEFAI_H
#define COMPUTEFAI_H
#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "XYModel.h"
#include "DecimalUtils.h"
#include "LongDouble.h"

class ComputeFai
{
public:
    vector<FaiModel> compute_fai(float Trve, float weight, XModel x_model, vector<long double> vec_plot_x);
private:

};

#endif // COMPUTEFAI_H
