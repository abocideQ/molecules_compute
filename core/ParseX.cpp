/**
 * @file XAsis.cpp
 * @version 0.1
 * @date 2022-04-24
 * @details
 * X轴 = 某态数据(v'j') - 某态数据(v''j'') + T差值
 * (v0j0) - (v0j-1)
 * (v0j0) - (v0j 0)
 * (v0j0) - (v0j+1)
 */
#include "ParseX.h"
#include "XYModel.h"

vector<XModel> ParseX::XVector(string g1, float t1, char *pUrl1, string g2, float t2, char *pUrl2)
{
  vector<XModel> ret_ = vector<XModel>();
  vector<VJModel> vec_vj1 = ParseStr2VJ(g1, t1, pUrl1);
  vector<VJModel> vec_vj2 = ParseStr2VJ(g2, t2, pUrl2);
  for (size_t i = 0; i < vec_vj1.size(); i++)
  {
    if (i > vec_vj2.size() - 1)
    {
      break;
    }
    VJModel vj1 = vec_vj1[i];
    // j1 + j2 = -1/0/+1
    for (int j = -1; j < 2; j++)
    {
      if (i + j < 0)
      { //超上限
        continue;
      }
      else if (i + j > vec_vj2.size() - 1)
      { //超下限
        continue;
      }
      VJModel vj2 = vec_vj2[i + j];
      XModel x_model = XModel();
      // vj1
      x_model.g1 = g1;
      x_model.v1 = vj1.v;
      x_model.j1 = vj1.j;
      x_model.e1 = vj1.e;
      x_model.t1 = vj1.t;
      // vj2
      x_model.g2 = g2;
      x_model.v2 = vj2.v;
      x_model.j2 = vj2.j;
      x_model.e2 = vj2.e;
      x_model.t2 = vj2.t;
      // x
      x_model.x = x_model.e1 - x_model.e2 + (x_model.t1 - x_model.t2);
      ret_.push_back(x_model);

      // std::cout << x_model.g1 << " "
      //           << x_model.v1 << " "
      //           << x_model.j1 << " "
      //           << x_model.e1 << " "
      //           << x_model.t1 << " "
      //           << x_model.g2 << " "
      //           << x_model.v2 << " "
      //           << x_model.j2 << " "
      //           << x_model.e2 << " "
      //           << x_model.t2 << " "
      //           << " , x= " << x_model.x << " " << std::endl;
    }
  }
  return ret_;
}

vector<VJModel> ParseX::ParseStr2VJ(string g, float t, char *pUrl)
{
  vector<VJModel> ret_ = vector<VJModel>();
  FileUtils m_reader = FileUtils();
  std::vector<std::vector<float>> datas = m_reader.Load(pUrl);
  for (size_t i = 0; i < datas.size(); i++)
  {
    std::vector<float> data = datas[i];
    VJModel model = VJModel();
    model.g = g;
    model.v = data[0];
    model.j = data[1];
    model.e = data[2];
    model.t = t;
    ret_.push_back(model);
  }
  return ret_;
}
