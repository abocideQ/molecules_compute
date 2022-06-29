#include "brigde.h"

void Brigde::add_q_info(string g, float Te, string _pUrl_q,
                        long double h, long double c, long double K,
                        long double Tex, long double Tvib, long double Trot, int gne, int gno, long double gbase)
{
//    6.63 * pow(10, -34),                    // h 常量
//    2.99792458 * pow(10, 10),               // c 常量
//    (1.38 * pow(10, -23)),                  // K 常量
    QReq *qReq = new QReq();
    qReq->g = g;//名称
    qReq->Te = Te;//跃迁
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
    m_req_Q->push_back(*qReq);
}

void Brigde::set_x_a_info(string _g_1, float _Te1, string _pUrl_1, string _g_2, float _Te2, string _pUrl_2,
                          long double h, long double c, long double K,
                          long double Tex, long double Tvib, long double Trot, int gne, int gno, long double gbase,
                          string _pUrl_a)
{
    m_req_x_a->g1 = _g_1;//名称1
    m_req_x_a->Te1 = _Te1;//跃迁1
    m_req_x_a->url1 = _pUrl_1;//文件地址1
    m_req_x_a->g2 = _g_2;//名称2
    m_req_x_a->Te2 = _Te2;//跃迁2
    m_req_x_a->url2 = _pUrl_2;//文件地址2
    m_req_x_a->h = h;//常量
    m_req_x_a->c = c;//常量
    m_req_x_a->K = K;//常量
    m_req_x_a->Tex = Tex;//温度
    m_req_x_a->Tvib = Tvib;//温度
    m_req_x_a->Trot = Trot;//温度
    m_req_x_a->gne = gne;//偶时值
    m_req_x_a->gno = gno;//奇时值
    m_req_x_a->gbase = gbase;//倍数
    m_req_x_a->urla = _pUrl_a;//Aul
}

long double Brigde::compute_q()
{
    m_ret_Q = 0;
    for(size_t i = 0; i < m_req_Q->size(); i++){
        QReq *qReq = &m_req_Q->at(i);
        m_pComputeQ->init(m_pParseX->ParseStr2VJ(qReq->g, qReq->Te, qReq->url),
                          qReq->h, qReq->c, qReq->K, qReq->Tex, qReq->Tvib, qReq->Trot, qReq->gne, qReq->gno, qReq->gbase);
        m_ret_Q += m_pComputeQ->sumQ();
    }
    return m_ret_Q;
}

std::vector<XModel> Brigde::compute_x_a()
{
    m_ret_vec_x = m_pMergeXA->Merge(m_pParseX->XVector(m_req_x_a->g1, m_req_x_a->Te1, m_req_x_a->url1, m_req_x_a->g2, m_req_x_a->Te2, m_req_x_a->url2, m_req_x_a->h, m_req_x_a->c),
                                    m_pParseA->AVector(m_req_x_a->urla));
    return m_ret_vec_x;
}

std::vector<XModel> Brigde::compute_qevj()
{
    m_pComputeQevj->init(m_ret_vec_x, m_req_x_a->h,  m_req_x_a->c,  m_req_x_a->K,
                         m_req_x_a->Tex, m_req_x_a->Tvib, m_req_x_a->Trot,
                         m_req_x_a->gne, m_req_x_a->gno, m_req_x_a->gbase);
    m_ret_vec_x = m_pComputeQevj->computeQevj_s();
    return m_ret_vec_x;
}

long double Brigde::compute_n()
{
    //R=8.31 P=1.01*10^5 T=15000
    m_pComputeN->init(8.31, 1.01 * pow(10, 5), 15000);
    m_ret_n = m_pComputeN->compute_n();
    return m_ret_n;
}

std::vector<FaiModel> Brigde::compute_fai(float u, float o, vector<long double> vec_x)
{
    return m_pComputeFai->compute_fai_gauss(u, o, vec_x);
}
