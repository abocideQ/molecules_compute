#include "ComputePlot.h"


void ComputePlot::computPlots(float min_x, float max_x, float step, long double Q, long double N, vector<XModel> vec_x)
{
    vector<XModel> vec_x_basic = computeBasic(min_x, max_x, vec_x);
}

vector<XModel> ComputePlot::computeBasic(float min_x, float max_x, vector<XModel> vec_x)
{
    vector<XModel> vec_ret = vector<XModel>();
    //区间内 [x1,x2]
    for(size_t i = 0; i < vec_x.size(); i++){
        XModel *x_model = &vec_x[i];
        if(x_model->x > min_x && x_model->x < max_x){
            vec_ret.push_back(*x_model);
        }
    }
    //冒泡排序
    for(size_t i = 0; i < vec_ret.size() - 1; i++){
        for(size_t j = 0; j < vec_ret.size() - 1 - i; j++){
            if(vec_ret[j].x > vec_ret[j + 1].x){
                XModel *tmp = &vec_ret[j];
                vec_ret[j] = vec_ret[j+1];
                vec_ret[j+1] = *tmp;
            }
        }
    }
    //区间内 x0[x,x]x3
    int index_l = -1;
    int index_r = -1;
    for(size_t i = 0; i < vec_x.size(); i++){
        XModel *x_model = &vec_x[i];
        if(index_l == -1 && x_model->x < vec_ret[0].x){
            index_l = i;
        } else if(index_r == -1 && x_model->x < vec_ret[vec_ret.size()-1].x){
            index_r = i;
        } else if(index_l !=-1 && index_r !=-1){
            break;
        }
    }
    if(index_l != -1){
        vec_ret.insert(vec_ret.begin(), vec_x[index_l]);
    }
    if(index_r != -1){
        vec_ret.push_back(vec_x[index_r]);
    }
    return vec_ret;
}

vector<XModel> ComputePlot::computeSinglePlot(vector<XModel> vec_x_basic)
{
    vector<XModel> vec_ret = vector<XModel>();

    return vec_ret;
}
