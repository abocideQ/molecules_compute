#include "ComputeN.h"

long double ComputeN::compute_n(long double R, long double P, long double T)
{
    long double NV = (P) / (R * T);
    long double N = NV * ((6.12 * std::pow(10, 23)) / std::pow(100, 3));
    return N;
}
