#include "ComputePlot.h"

void ComputePlot::computPlots(float min_x, float max_x, float step, vector<XModel> vec_x)
{
    //[minx, max]间的x点 由step计算出 x = minx + n*step
    vector<long double> vec_plot_x = vector<long double>();
    //区间内 基准
    vector<XModel> vec_x_basic = computeBasic(min_x, max_x, vec_x);
    //plot
    //    vector<PlotModel> vec_plot1 = computeSinglePlot(vec_plot_x);
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

vector<PlotModel> ComputePlot::computeSinglePlot(vector<long double> vec_plot_x, XModel x_basic)
{
    vector<PlotModel> vec_ret = vector<PlotModel>();
    vector<FaiModel> vec_fai = compute_fai_gauss(x_basic, vec_plot_x);
    return vec_ret;
}

std::vector<FaiModel> ComputePlot::compute_fai_gauss(XModel x_basic, vector<long double> vec_plot_x)
{
    //fai
    float u = x_basic.x;//中心点
    float o = 0.25;     //展宽
    float pai = 3.1415926;//pai
    std::vector<FaiModel> vec_fai = std::vector<FaiModel>();
    for(size_t i = 0; i < vec_plot_x.size(); i++){
        //        vec_fai[]
        FaiModel *fai_model = new FaiModel();
        fai_model->x = vec_plot_x[i];
        fai_model->y = (1 / (o * sqrt(2 * pai))) * DecimalUtils::exp_(-1 * (pow(vec_plot_x[i] - u, 2)) / (2 * pow(o, 2)));
        vec_fai.push_back(*fai_model);
    }
    return vec_fai;
}

std::vector<FaiModel> ComputePlot::compute_fai(float Trot, float weight, XModel x_model, vector<long double> vec_plot_x)
{
    std::vector<FaiModel> vec_fai = std::vector<FaiModel>();
    long double fWidth_D = 2 * (5.94 * pow(10, -6)) * sqrt(Trot / 296 / weight);
    long double fWidth_L = pow(2 * (296 / Trot), 0.5);
    long double fWidth_V = (0.5346 * fWidth_L) + sqrt((0.2166 * pow(fWidth_L, 2)) + pow(fWidth_D, 2));
    for(size_t i = 0; i < vec_plot_x.size() - 1 ; i++){
        FaiModel *fai_model = new FaiModel();
        long double CSPRD = vec_plot_x[i] - x_model.x;
        if(CSPRD < 0){//绝对值
            CSPRD *= -1;
        }
        long double CSPRD1 = fWidth_L / fWidth_V;
        long double CSPRD2 = CSPRD / fWidth_V;
        long double GV = ((1.0 - CSPRD1) * DecimalUtils::exp_(-2.772 * pow(CSPRD2, 2))) +
                (CSPRD1 / (1 + (4 * pow(CSPRD2, 2)))) +
                ((0.016 * (1-CSPRD1) * CSPRD1) * (DecimalUtils::exp_(-0.4 * pow(CSPRD2, 2.25)) - (10 / (10 + pow(CSPRD2, 2.25)))));
        GV /= fWidth_V * (1.065 + (0.447 * CSPRD1) + (0.058 * pow(CSPRD1, 2)));
        //==========================
        fai_model->x = vec_plot_x[i];
        fai_model->y = GV;
        vec_fai.push_back(*fai_model);
    }
    return vec_fai;
}
