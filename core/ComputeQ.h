#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>
#include "XYModel.h"
#include "DecimalUtils.h"
#include "LongDouble.h"

class ComputeQ
{
public:
  void init(vector<VJModel> vec_x, long double h, long double c, long double KTex, long double KTvib, long double KTrot, int gne, int gno, long double gbase);
  long double sumQ();

private:
  vector<VJModel> m_vec_x;
  vector<VJModel> m_vec_Te;
  vector<VJModel> m_vec_Gv;
  vector<VJModel> m_vec_Fj;
  long double const_h = 0;
  long double const_c = 0;
  long double const_KTex = 0;
  long double sumQe();
  long double const_KTvib = 0;
  long double sumQv();
  long double const_KTrot = 0;
  long double sumQj(float v);
  long double const_gne = 0;
  long double const_gno = 0;
  long double const_gbase = 1;
  long double sumgj(float j);
};