#include "MergeXA.h"

vector<XModel> MergeXA::Merge(vector<XModel> x_vec, vector<AModel> a_vec)
{
  for (size_t i = 0; i < x_vec.size(); i++)
  {
    XModel *x_model = &x_vec[i];
    AModel a_model = FindA(*x_model, a_vec);
    x_model->a = a_model.ret_;
  }
  return x_vec;
}

AModel MergeXA::FindA(XModel x_model, vector<AModel> a_vec)
{
  for (size_t i = 0; i < a_vec.size(); i++)
  {
    AModel a_model = a_vec[i];
    if (a_model.v1 == x_model.v1 && a_model.v2 == x_model.v2 && a_model.j1 == x_model.j1 && a_model.j2 == x_model.j2)
    {
      return a_model;
    }
  }
  return AModel();
}
