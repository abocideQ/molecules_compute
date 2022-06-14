#ifndef COMPUTEQEVJ_H
#define COMPUTEQEVJ_H

#include <vector>
#include "XYModel.h"

class ComputeQevj
{
public:
    vector<XModel> computeQevj_s(vector<XModel> vec_x);

private:
    long double computeQevj(XModel);
};

#endif // COMPUTEQEVJ_H
