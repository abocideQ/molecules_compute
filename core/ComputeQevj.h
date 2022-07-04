#ifndef COMPUTEQEVJ_H
#define COMPUTEQEVJ_H

#include <vector>
#include <iostream>
#include "XYModel.h"
#include "DecimalUtils.h"

class ComputeQevj
{
public:
    vector<XModel> computeQevj_s(vector<XModel> vec_x,
                                 long double h, long double c, long double K,
                                 long double Tex, long double Tvib, long double Trot,
                                 float gne, float gno, float gbase);

private:
    long double computeQevj(XModel x_model, long double Gv,
                            long double h, long double c, long double K,
                            long double Tex, long double Tvib, long double Trot,
                            float gne, float gno, float gbase);
    long double sumgj(float j, float gne, float gno, float gbase);
};

#endif // COMPUTEQEVJ_H
