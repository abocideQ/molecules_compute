#include "ComputeN.h"

void ComputeN::init(long double R, long double P, long double T)
{
    m_R = R;
    m_P = P;
    m_T = T;
}

long double ComputeN::compute_n()
{
    long double NV = (m_P) / (m_R * m_T);
    long double N = NV * ((6.12 * std::pow(10, 23)) / std::pow(100, 3));
    return N;
}
