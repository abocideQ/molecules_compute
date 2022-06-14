#include "brigde.h"

void Brigde::set_x_a_info(string _g_1, float _t_1, char *_pUrl_1, string _g_2, float _t_2, char *_pUrl_2, char *_pUrl_a)
{
    m_1_g = _g_1;
    m_1_t = _t_1;
    m_1_pUrl = _pUrl_1;
    m_2_g = _g_2;
    m_2_t = _t_2;
    m_2_pUrl = _pUrl_2;
    m_a_pUrl = _pUrl_a;
}

void Brigde::set_q_info(char *_pUrl_q, string g, long double h, long double c, long double k, long double Tex, long double Tvib, long double Trot, int gne, int gno, long double gbase)
{
   m_q_pUrl = _pUrl_q;
   m_q_g = g;
   m_q_h = h;
   m_q_c = c;
   m_q_K= k;
   m_q_Tex = Tex;
   m_q_Tvib = Tvib;
   m_q_Trot = Trot;
   m_q_gne = gne;
   m_q_gno = gno;
   m_q_gbase = gbase;
}

std::vector<XModel> Brigde::compute_x_a()
{
    return m_pMergeXA->Merge(m_pParseX->XVector(m_1_g, m_1_t, m_1_pUrl, m_2_g, m_2_t, m_2_pUrl), m_pParseA->AVector(m_a_pUrl));
}

long double Brigde::compute_q()
{
     m_pComputeQ->init(m_pParseX->ParseStr2VJ(m_q_g, m_q_t, m_q_pUrl), m_q_h, m_q_c, m_q_K * m_q_Tex, m_q_K * m_q_Tvib, m_q_K * m_q_Trot, m_q_gne, m_q_gno, m_q_gbase);
     return m_pComputeQ->sumQ();
}
