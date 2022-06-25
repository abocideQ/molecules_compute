#ifndef COMPUTEFAI_H
#define COMPUTEFAI_H

#include <math.h>
#include <iostream>

class ComputeFai
{
public:
    long double compute_fai();

private:
    long double compute_A(long double wV, long double t);
    long double compute_L(long double wV);
    long double compute_t(long double wL, long double wV);
    long double compute_wV(long double wL, long double wG);
};

#endif // COMPUTEFAI_H
