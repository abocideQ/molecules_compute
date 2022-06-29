#ifndef BRIGDE_H
#define BRIGDE_H
#include "core/XYModel.h"
#include "core/ParseX.h"
#include "core/ParseA.h"
#include "core/MergeXA.h"
#include "core/ComputeQevj.h"
#include "core/ComputeQ.h"
#include "core/ComputeN.h"
#include "core/ComputeFai.h"

class Brigde
{
public:
    void add_q_info(string _pUrl_q, float Te, string g,
                    long double h, long double c, long double K,
                    long double Tex, long double Tvib, long double Trot, int gne, int gno, long double gbase);
    void set_x_a_info(string _g_1, float _t_1, string _pUrl_1, string _g_2, float _t_2, string _pUrl_2,
                      long double h, long double c, long double K,
                      long double Tex, long double Tvib, long double Trot, int gne, int gno, long double gbase,
                      string _pUrl_a);
    //1. compute Q
    long double compute_q();
    //2. compute x & a
    std::vector<XModel> compute_x_a();
    //3. compute Qevj
    std::vector<XModel> compute_qevj();
    //4. compute n
    long double compute_n();
    //5. compute fai
    std::vector<FaiModel> compute_fai(float u, float o, vector<long double> vec_x);
private:
    //Req 请求
    vector<QReq> *m_req_Q = new vector<QReq>();//Q
    XAReq *m_req_x_a = new XAReq();//x_a_Qevj
    //result 结果
    long double m_ret_Q = 0;
    long double m_ret_n = 0;
    vector<XModel> m_ret_vec_x = vector<XModel>();
    //utils 工具
    ParseX *m_pParseX = new ParseX();//x
    ParseA *m_pParseA = new ParseA();//a
    MergeXA *m_pMergeXA = new MergeXA();//x & a
    ComputeQevj *m_pComputeQevj = new ComputeQevj();//Qevj
    ComputeQ *m_pComputeQ = new ComputeQ();//Q
    ComputeN *m_pComputeN = new ComputeN();//n
    ComputeFai *m_pComputeFai = new ComputeFai();//fai 高斯分布
};

#endif // BRIGDE_H
