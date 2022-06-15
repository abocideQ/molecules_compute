#ifndef BRIGDE_H
#define BRIGDE_H
#include "core/XYModel.h"
#include "core/ParseX.h"
#include "core/ParseA.h"
#include "core/MergeXA.h"
#include "core/ComputeQ.h"

class Brigde
{
public:
    void set_x_a_info(string _g_1, float _t_1, string _pUrl_1, string _g_2, float _t_2, string _pUrl_2, string _pUrl_a);
    void add_q_info(string _pUrl_q, float Te, string g, long double h, long double c, long double K, long double Tex, long double Tvib, long double Trot, int gne, int gno, long double gbase);
    //compute x & a
    std::vector<XModel> compute_x_a();
    //compute Q
    long double compute_q();

//private:
    //req
    XAReq *m_xaReq = new XAReq();
    vector<QReq> *m_qReq = new vector<QReq>();
    //ret
    vector<XModel> m_ret_vec_x = vector<XModel>();
    long double m_ret_Q = 0;
    //utils
    ParseX *m_pParseX = new ParseX();
    ParseA *m_pParseA = new ParseA();
    MergeXA *m_pMergeXA = new MergeXA();
    ComputeQ *m_pComputeQ = new ComputeQ();
    //    //x
    //    string m_1_g;
    //    string m_2_g;
    //    float m_1_t;//差值
    //    float m_2_t;//差值
    //    string m_1_pUrl;
    //    string m_2_pUrl;
    //    //aul
    //    string m_a_pUrl;
    //    //q
    //    string m_q_pUrl;
    //    string m_q_g;
    //    long double m_q_Te;//温度
    //    long double m_q_h;//常量
    //    long double m_q_c;//常量
    //    long double m_q_K;//常量
    //    long double m_q_Tex;//常量
    //    long double m_q_Tvib;//常量
    //    long double m_q_Trot;//常量
    //    int m_q_gne;//常量
    //    int m_q_gno;//常量
    //    long double m_q_gbase;//常量
};

#endif // BRIGDE_H
