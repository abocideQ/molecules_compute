#ifndef COMPUTEY_H
#define COMPUTEY_H

#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "XYModel.h"
#include "DecimalUtils.h"
#include "LongDouble.h"

class ComputeY
{
public:
    void init(long double h, long double c, long double n, long double Q, vector<XModel> vec_x);
    vector<XModel> compute_y();
private:
    vector<XModel> m_vec_x;
    long double const_h = 0;
    long double const_c = 0;
    long double m_n = 0;
    long double m_Q = 0;
};

#endif // COMPUTEY_H
