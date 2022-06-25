#include "ComputeFai.h"

long double ComputeFai::compute_fai()
{
    long double fai = 0;
    long double A = compute_A(0, 0);//????
    long double L = compute_L(0);//????
    long double t = compute_t(0, 0);//????
    fai = (1 - t) * exp(-2.772 * pow(L, 2));
    fai = fai + (t / 1 + 4 * pow(L, 2));
    fai = fai + ((0.016) * (1 - t) * t * ((exp(-0.4 * pow(L, 2.25)))) - (10 / (10 + pow(L, 2.25))));
    return fai;
}

long double ComputeFai::compute_A(long double wV, long double t)
{
    long double A =  wV * (1.065 + (0.447 * t) + (0.056 * t * t));
    A = 1 / A;
    return A;
}

long double ComputeFai::compute_L(long double wV)
{
    long double L = 0;//????
    return L;
}

long double ComputeFai::compute_t(long double wL, long double wV)
{
    long double t = wL / wV;
    return t;
}

long double ComputeFai::compute_wV(long double wL, long double wG)
{
    long double wV = sqrt(pow(wL / 2, 2) + pow(wG, 2));
    wV = (wL / 2) + wV;
    return wV;
}
