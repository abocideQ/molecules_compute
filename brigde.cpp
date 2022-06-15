#include "brigde.h"

void Brigde::set_x_a_info(string _g_1, float _Te1, string _pUrl_1, string _g_2, float _Te2, string _pUrl_2, string _pUrl_a)
{
    m_xaReq->g1 = _g_1;//名称
    m_xaReq->Te1 = _Te1;//差值
    m_xaReq->url1 = _pUrl_1;//文件地址
    m_xaReq->g2 = _g_2;
    m_xaReq->Te2 = _Te2;
    m_xaReq->url2 = _pUrl_2;
    m_xaReq->urla = _pUrl_a;
}

void Brigde::add_q_info(string g, float Te, string _pUrl_q, long double h, long double c, long double K,  long double Tex, long double Tvib, long double Trot, int gne, int gno, long double gbase)
{
    QReq *qReq = new QReq();
    qReq->g = g;//名称
    qReq->Te = Te;//跃迁差值
    qReq->url = _pUrl_q;//文件地址
    qReq->h = h;//常量
    qReq->c = c;//常量
    qReq->K= K;//常量
    qReq->Tex = Tex;//常量
    qReq->Tvib = Tvib;//常量
    qReq->Trot = Trot;//常量
    qReq->gne = gne;//偶数时常量
    qReq->gno = gno;//奇数时常量
    qReq->gbase = gbase;//倍数
    m_qReq->push_back(*qReq);
}

std::vector<XModel> Brigde::compute_x_a()
{
    m_ret_vec_x = m_pMergeXA->Merge(m_pParseX->XVector(m_xaReq->g1, m_xaReq->Te1, m_xaReq->url1, m_xaReq->g2, m_xaReq->Te2, m_xaReq->url2),
                                    m_pParseA->AVector(m_xaReq->urla));
    return m_ret_vec_x;
}

long double Brigde::compute_q()
{
    m_ret_Q = 0;
    for(size_t i = 0; i < m_qReq->size(); i++){
        QReq *qReq = &m_qReq->at(i);
        m_pComputeQ->init(m_pParseX->ParseStr2VJ(qReq->g, qReq->Te, qReq->url),
                          qReq->h, qReq->c, (qReq->K * qReq->Tex), (qReq->K * qReq->Tvib), (qReq->K * qReq->Trot), qReq->gne, qReq->gno, qReq->gbase);
        m_ret_Q += m_pComputeQ->sumQ();
    }
    return m_ret_Q;
}
