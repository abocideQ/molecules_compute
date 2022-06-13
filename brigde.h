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
    void set_x_a_info(string _g_1, float _t_1, char *_pUrl_1, string _g_2, float _t_2, char *_pUrl_2, char *_pUrl_a);
    void set_q_info(char *_pUrl_q, string g, long double h, long double c, long double KTex, long double KTvib, long double KTrot, int gne, int gno, long double gbase);
    //compute x & a
    std::vector<XModel> compute_x_a();
    //compute Q
    long double compute_q();

private:
    //x
    string m_1_g;
    string m_2_g;
    float m_1_t;
    float m_2_t;
    char *m_1_pUrl;
    char *m_2_pUrl;
    //aul
    char *m_a_pUrl;
    //q
    char *m_q_pUrl;
    string m_q_g;
    long double m_q_t;//温度
    long double m_q_h;//常量
    long double m_q_c;//常量
    long double m_q_KTex;//常量
    long double m_q_KTvib;//常量
    long double m_q_KTrot;//常量
    int m_q_gne;//常量
    int m_q_gno;//常量
    long double m_q_gbase;//常量
    //utils
    ParseX *m_pParseX = new ParseX();
    ParseA *m_pParseA = new ParseA();
    MergeXA *m_pMergeXA = new MergeXA();
    ComputeQ *m_pComputeQ = new ComputeQ();
};

#endif // BRIGDE_H
