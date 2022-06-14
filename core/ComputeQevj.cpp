#include "ComputeQevj.h"

vector<XModel> ComputeQevj::computeQevj_s(vector<XModel> vec_x)
{
    for(size_t i = 0; i < vec_x.size(); i++){
        XModel xmodel = vec_x[i];
        xmodel.Qevj = computeQevj(xmodel);
    }
    return vec_x;
}

long double ComputeQevj::computeQevj(XModel)
{
    long double ret_ =0;

    return ret_;
}
