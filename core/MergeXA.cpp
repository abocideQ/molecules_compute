#include "MergeXA.h"

vector<XModel> MergeXA::Merge(vector<XModel> x_vec, vector<AModel> a_vec)
{
  std::cout << " === "
            << "x_vec.size="
            << x_vec.size()
            << " "
            << "a_vec.size="
            << a_vec.size() << " === " << std::endl;
  for (size_t i = 0; i < x_vec.size(); i++)
  {
    XModel x_model = x_vec[i];
    AModel a_model = FindA(x_model, a_vec);
    x_model.a = a_model.ret_;
    std::cout << "g'=" << x_model.g1 << " "
              << "v'=" << x_model.v1 << " "
              << "j'=" << x_model.j1 << " "
              << "e'=" << x_model.e1 << " "
              << "t'=" << x_model.t1 << " "
              << " --- "
              << "g''=" << x_model.g2 << " "
              << "v''=" << x_model.v2 << " "
              << "j''=" << x_model.j2 << " "
              << "e''=" << x_model.e2 << " "
              << "t''=" << x_model.t2 << " "
              << " --- "
              << "x= " << x_model.x << " "
              << "a= " << x_model.a << " " << std::endl;
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