#include "ComputeY.h"


//void ComputeY::init(long double h, long double c, long double n, long double Q, vector<XModel> vec_x)
//{
//    const_h = h;
//    const_c = c;
//    m_n = n;
//    m_Q = Q;
//    m_vec_x = vec_x;
//}

vector<XModel> ComputeY::compute_y(long double h, long double c, long double n, long double Q, vector<XModel> vec_x)
{
    float pai = 3.1415926;
    for(size_t i = 0; i < vec_x.size(); i++){
        XModel *x_model = &vec_x[i];
        long double nu = n * (x_model->Qevj / Q);
        x_model->y = nu * ((h * c * x_model->a) / (4 * pai * x_model->x));
        x_model->y *= pow(10, 10);
    }
    return vec_x;
}
