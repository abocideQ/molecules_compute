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

vector<XModel> ParseX::XVector(string g1, float t1,string pUrl1, string g2, float t2, string pUrl2, long double h, long double c)
{
    vector<XModel> ret_ = vector<XModel>();
    vector<VJModel> vec_vj1 = ParseStr2VJ(g1, t1, pUrl1);
    vector<VJModel> vec_vj2 = ParseStr2VJ(g2, t2, pUrl2);
    size_t index_next_vec_vj2 = 0;//记录上次遍历到的v=n位置, 不再从v=0遍历
    for (size_t i = 0; i < vec_vj1.size(); i++)
    {
        VJModel vj1 = vec_vj1[i];
        for (size_t j = index_next_vec_vj2; j < vec_vj2.size(); j++)
        {// j1 - j2 = -1/0/+1
            VJModel vj2 = vec_vj2[j];
            int index = -1;
            if(vj2.v > vj1.v){
                break;
            }
            else if (vj2.v < vj1.v)
            {
                continue;
            }
            else if (vj2.j - vj1.j > 1 || vj2.j - vj1.j < -1)
            {
                continue;
            }
            else if (index == -1 && vj2.v == vj1.v && j > 0){
                index = j - 1;
                index_next_vec_vj2 = index;
            }
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
            x_model.x = x_model.e2 - x_model.e1 + (x_model.t2 - x_model.t1);
            x_model.x = (h * c) / x_model.x;
            ret_.push_back(x_model);
        }
    }
    return ret_;
}

vector<VJModel> ParseX::ParseStr2VJ(string g, float t, string pUrl)
{
    vector<VJModel> ret_ = vector<VJModel>();
    FileUtils m_reader = FileUtils();
    std::vector<std::vector<long double>> datas = m_reader.Load(pUrl.data());
    for (size_t i = 0; i < datas.size(); i++)
    {
        std::vector<long double> data = datas[i];
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
