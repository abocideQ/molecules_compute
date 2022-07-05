#include "ComputePlot.h"

std::vector<CoordinateModel> ComputePlot::computPlots(float min_x, float max_x, float step, float weight, float Trot, vector<XModel> vec_x)
{
    vector<CoordinateModel> vec_ret = vector<CoordinateModel>();
    //1. 初始化 展宽
    long double fWidth_D = 2 * (5.94 * pow(10, -6)) * sqrt(Trot / 296 / weight);
    long double fWidth_L = pow(2 * (296 / Trot), 0.5);
    long double fWidth_V = (0.5346 * fWidth_L) + sqrt((0.2166 * pow(fWidth_L, 2)) + pow(fWidth_D, 2));
    //2. 初始化 区间内 基准x
    vector<XModel> vec_x_basic = computeBasic(min_x, max_x, vec_x);
    //3. 初始化 区间内 所有x点 -> step计算 -> x = minx + n*step
    vector<long double> vec_x_plot = vector<long double>();
    for(float x = min_x; x <= max_x ; x += step){
        vec_x_plot.push_back(x);
    }
    //4. 计算
    for(size_t i = 0; i < vec_x_plot.size(); i++){
        for(size_t j = 0; j < vec_x_basic.size(); j++){
            CoordinateModel *coordinate = computeCoordinate(fWidth_L, fWidth_V, vec_x_basic[j], vec_x_plot[i]);
            if(i == vec_ret.size()){
                vec_ret.push_back(*coordinate);
            } else {
                vec_ret[i].y += coordinate->y;
            }
            delete coordinate;
        }
    }
    return vec_ret;
}

vector<CoordinateModel> ComputePlot::computBasicPlots(vector<XModel> vec_x)
{
    vector<CoordinateModel> vec_ret = vector<CoordinateModel>();
    for(size_t i = 0; i < vec_x.size(); i++){
        CoordinateModel coordinate = CoordinateModel();
        coordinate.x = vec_x[i].x;
        coordinate.y = vec_x[i].y;
        vec_ret.push_back(coordinate);
    }
    return vec_ret;
}

void ComputePlot::computTestPlots(float weight, float Trot, vector<CoordinateModel> *response)
{
    long double fWidth_D = 2 * (5.94 * pow(10, -6)) * sqrt(Trot / 296 / weight);
    long double fWidth_L = pow(2 * (296 / Trot), 0.5);
    long double fWidth_V = (0.5346 * fWidth_L) + sqrt((0.2166 * pow(fWidth_L, 2)) + pow(fWidth_D, 2));
    vector<CoordinateModel> vec_ret = vector<CoordinateModel>();
    //?. 曲线测试
    vector<long double> vec_x_plot = vector<long double>();
    vec_x_plot.clear();
    for(float x = 0; x <= 40 ; x += 0.1){
        vec_x_plot.push_back(x);
    }
    XModel x_test = XModel();
    x_test.x = 10;
    x_test.y = 1;
    for(size_t i = 0; i < vec_x_plot.size(); i++){
        CoordinateModel *coordinate = computeCoordinate(fWidth_L, fWidth_V, x_test, vec_x_plot[i]);
        response->push_back(*coordinate);
        delete coordinate;
    }
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
    if(vec_ret.size() == 0){
        return vec_ret;
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

CoordinateModel *ComputePlot::computeCoordinate(long double fWidth_L, long double fWidth_V, XModel x_basic, long double x)
{
    CoordinateModel *model = new CoordinateModel();
    long double CSPRD = x - x_basic.x;
    if(CSPRD < 0){//绝对值
        CSPRD *= -1;
    }
    long double CSPRD1 = fWidth_L / fWidth_V;
    long double CSPRD2 = CSPRD / fWidth_V;
    long double GV = ((1.0 - CSPRD1) * DecimalUtils::exp_(-2.772 * pow(CSPRD2, 2))) +
            (CSPRD1 / (1 + (4 * pow(CSPRD2, 2)))) +
            ((0.016 * (1-CSPRD1) * CSPRD1) * (DecimalUtils::exp_(-0.4 * pow(CSPRD2, 2.25)) - (10 / (10 + pow(CSPRD2, 2.25)))));
    GV /= fWidth_V * (1.065 + (0.447 * CSPRD1) + (0.058 * pow(CSPRD1, 2)));
    //Coordinate
    model->xModel = x_basic;
    model->x = x;
    model->y = GV * x_basic.y;
    return model;
}

//vector<CoordinateModel> ComputePlot::computePlot(float Trot, float weight, vector<XModel> vec_x_basic, vector<long double> vec_plot_x)
//{
//    vector<CoordinateModel> vec_ret = vector<CoordinateModel>();
//    for(size_t i = 0; i < vec_plot_x.size(); i++){
//        vec_ret.push_back(CoordinateModel());
//    }
//    for(size_t i = 0; i < vec_x_basic.size(); i++){
//        vector<CoordinateModel> vec_coordinate = computeCoordinate(Trot, weight, vec_x_basic[i], vec_plot_x);
//        for(size_t j = 0; j < vec_plot_x.size(); j++){
//            CoordinateModel coordinate = vec_ret[j];
//            coordinate.xModel = vec_coordinate[j].xModel;
//            coordinate.x = vec_coordinate[j].x;
//            coordinate.y += vec_coordinate[j].y;
//        }
//    }
//    return vec_ret;
//}

//std::vector<CoordinateModel> ComputePlot::computeCoordinate(float Trot, float weight, XModel x_basic, vector<long double> vec_plot_x)
//{
//    std::vector<CoordinateModel> vec_ret = std::vector<CoordinateModel>();
//    long double fWidth_D = 2 * (5.94 * pow(10, -6)) * sqrt(Trot / 296 / weight);
//    long double fWidth_L = pow(2 * (296 / Trot), 0.5);
//    long double fWidth_V = (0.5346 * fWidth_L) + sqrt((0.2166 * pow(fWidth_L, 2)) + pow(fWidth_D, 2));
//    for(size_t i = 0; i < vec_plot_x.size(); i++){
//        CoordinateModel *model = new CoordinateModel();
//        long double CSPRD = vec_plot_x[i] - x_basic.x;
//        if(CSPRD < 0){//绝对值
//            CSPRD *= -1;
//        }
//        long double CSPRD1 = fWidth_L / fWidth_V;
//        long double CSPRD2 = CSPRD / fWidth_V;
//        long double GV = ((1.0 - CSPRD1) * DecimalUtils::exp_(-2.772 * pow(CSPRD2, 2))) +
//                (CSPRD1 / (1 + (4 * pow(CSPRD2, 2)))) +
//                ((0.016 * (1-CSPRD1) * CSPRD1) * (DecimalUtils::exp_(-0.4 * pow(CSPRD2, 2.25)) - (10 / (10 + pow(CSPRD2, 2.25)))));
//        GV /= fWidth_V * (1.065 + (0.447 * CSPRD1) + (0.058 * pow(CSPRD1, 2)));
//        //==========================
//        model->xModel = x_basic;
//        model->x = vec_plot_x[i];
//        model->y = GV * x_basic.y;
//        vec_ret.push_back(*model);
//    }
//    return vec_ret;
//}

////gauss分布
//std::vector<CoordinateModel> ComputePlot::compute_fai_gauss(XModel x_basic, vector<long double> vec_plot_x)
//{
//    //fai
//    float u = x_basic.x;//中心点
//    float o = 0.25;     //展宽
//    float pai = 3.1415926;//pai
//    std::vector<CoordinateModel> vec_fai = std::vector<CoordinateModel>();
//    for(size_t i = 0; i < vec_plot_x.size(); i++){
//        //        vec_fai[]
//        CoordinateModel *fai_model = new CoordinateModel();
//        fai_model->x = vec_plot_x[i];
//        fai_model->y = (1 / (o * sqrt(2 * pai))) * DecimalUtils::exp_(-1 * (pow(vec_plot_x[i] - u, 2)) / (2 * pow(o, 2)));
//        vec_fai.push_back(*fai_model);
//    }
//    return vec_fai;
//}
