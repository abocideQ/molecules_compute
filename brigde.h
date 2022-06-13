#ifndef BRIGDE_H
#define BRIGDE_H
#include "core/XYModel.h"
#include "core/ParseX.h"
#include "core/ParseA.h"
#include "core/ComputeQ.h"

class Brigde
{
public:
    //1.态名 2.温度 3.地址
    std::vector<VJModel> parse_2_vec_vj(string _g, float _t, char *_pUrl);
    std::vector<VJModel> parse_2_vec_x(string _g1, float _t1, char *_pUrl1, string _g2, float _t2, char *_pUrl2);
};

#endif // BRIGDE_H
