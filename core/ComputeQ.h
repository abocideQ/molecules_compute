#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "XYModel.h"
#include "DecimalUtils.h"
#include "LongDouble.h"

class ComputeQ
{
public:
  void init(vector<VJModel> vec_x, long double h, long double c, long double K, long double Tex, long double Tvib, long double Trot, float gne, float gno, float gbase);
  long double sumQ();
  //
  string record_string;
private:
  vector<VJModel> m_vec_x;
  vector<VJModel> m_vec_Te;
  vector<VJModel> m_vec_Gv;
  vector<VJModel> m_vec_Fj;
  long double const_h = 0;
  long double const_c = 0;
  long double const_K = 0;
  long double const_Tex = 0;
  long double sumQe();
  long double const_Tvib = 0;
  long double sumQv();
  long double const_Trot = 0;
  long double sumQj(float v);
  float const_gne = 0;
  float const_gno = 0;
  float const_gbase = 1;
  long double sumgj(float j);
};
