#include "ComputeY.h"

vector<XModel> ComputeY::compute_y(long double h, long double c, long double n, long double Q, vector<XModel> vec_x)
{
    float pai = 3.1415926;
    for(size_t i = 0; i < vec_x.size(); i++){
        XModel *x_model = &vec_x[i];
        long double nu = n * (x_model->Qevj / Q);
        x_model->y = nu * ((h * c * x_model->a) / (4 * pai * x_model->x));
    }
    return vec_x;
}
