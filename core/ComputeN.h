#ifndef COMPUTEN_H
#define COMPUTEN_H

#include <iostream>
#include <stdio.h>
#include <cmath>
#include "XYModel.h"

class ComputeN
{
public:
    void init(long double R, long double P, long double T);
    long double compute_n();

private:
    long double m_R = 0;//常量
    long double m_P = 0;//压强
    long double m_T = 0;//温度
//    long double m_V = 0;//体积
};

#endif // COMPUTEN_H
