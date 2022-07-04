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
    vector<XModel> compute_y(long double h, long double c, long double n, long double Q, vector<XModel> vec_x);
};

#endif // COMPUTEY_H
