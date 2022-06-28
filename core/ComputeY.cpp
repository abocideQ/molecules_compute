#include "ComputeY.h"


void ComputeY::init(long double h, long double c, long double n, long double Q, vector<XModel> vec_x)
{
    const_h = h;
    const_c = c;
    m_n = n;
    m_Q = Q;
    m_vec_x = vec_x;
}

vector<XModel> ComputeY::compute_y()
{
    float pai = 3.1415926;
    for(size_t i = 0; i < m_vec_x.size(); i++){
        XModel *x_model = &m_vec_x[i];
        long double nu = m_n * (x_model->Qevj / m_Q);
        x_model->y = nu * ((const_h * const_c * x_model->a) / (4 * pai * x_model->x));
    }
    return m_vec_x;
}
