#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "XYModel.h"
#include "DecimalUtils.h"

class ComputeQ
{
public:
    long double sumQ(vector<VJModel> vec_vj,
                     long double h, long double c, long double K,
                     long double Tex, long double Tvib, long double Trot,
                     float gne, float gno, float gbase);
private:
    vector<VJModel> m_vec_Gv;
    vector<VJModel> m_vec_Fj;
    long double sumQe(vector<VJModel> vec_vj,
                      long double h, long double c, long double K,
                      long double Tex, long double Tvib, long double Trot,
                      float gne, float gno, float gbase);
    long double sumQv(vector<VJModel> vec_vj,
                      long double h, long double c, long double K,
                      long double Tex, long double Tvib, long double Trot,
                      float gne, float gno, float gbase);
    long double sumQj(float v,
                      vector<VJModel> vec_vj,
                      long double h, long double c, long double K,
                      long double Tex, long double Tvib, long double Trot,
                      float gne, float gno, float gbase);
    long double sumgj(float j, float gne, float gno, float gbase);
};
