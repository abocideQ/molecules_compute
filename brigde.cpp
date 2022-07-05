#include "brigde.h"

void Brigde::add_q_info(string g, float Te, string _pUrl_q,
                        int gne, int gno, long double gbase)
{
    //    6.63 * pow(10, -34),                    // h 常量
    //    2.99792458 * pow(10, 10),               // c 常量
    //    (1.38 * pow(10, -23)),                  // K 常量
    QReq *qReq = new QReq();
    qReq->g = g;//名称
    qReq->Te = Te;//跃迁
    qReq->url = _pUrl_q;//文件地址
    qReq->h = m_req_h;//常量
    qReq->c = m_req_c;//常量
    qReq->K= m_req_K;//常量
    qReq->Tex = m_req_Tex;//常量
    qReq->Tvib = m_req_Tvib;//常量
    qReq->Trot = m_req_Trot;//常量
    qReq->gne = gne;//偶数时常量
    qReq->gno = gno;//奇数时常量
    qReq->gbase = gbase;//倍数
    m_req_Q->push_back(*qReq);
}

void Brigde::clear_q_info()
{
    std::vector<QReq>().swap(*m_req_Q);
}

void Brigde::set_x_a_info(string _g_1, float _Te1, string _pUrl_1, string _g_2, float _Te2, string _pUrl_2,
                          int gne, int gno, long double gbase,
                          string _pUrl_a)
{
    m_req_x_a->g1 = _g_1;//名称1
    m_req_x_a->Te1 = _Te1;//跃迁1
    m_req_x_a->url1 = _pUrl_1;//文件地址1
    m_req_x_a->g2 = _g_2;//名称2
    m_req_x_a->Te2 = _Te2;//跃迁2
    m_req_x_a->url2 = _pUrl_2;//文件地址2
    m_req_x_a->h = m_req_h;//常量
    m_req_x_a->c = m_req_c;//常量
    m_req_x_a->K = m_req_K;//常量
    m_req_x_a->Tex = m_req_Tex;//温度
    m_req_x_a->Tvib = m_req_Tvib;//温度
    m_req_x_a->Trot = m_req_Trot;//温度
    m_req_x_a->gne = gne;//偶时值
    m_req_x_a->gno = gno;//奇时值
    m_req_x_a->gbase = gbase;//倍数
    m_req_x_a->urla = _pUrl_a;//Aul
}

void Brigde::set_other_info(long double h, long double c, long double K, long double Tex, long double Tvib, long double Trot)
{
    m_req_h = h;//6.63 * pow(10, -34),
    m_req_c = c;//2.99792458 * pow(10, 10)
    m_req_K= K;//(1.38 * pow(10, -23))
    m_req_Tex = Tex;//温度
    m_req_Tvib = Tvib;//温度
    m_req_Trot = Trot;//温度
    //Q
    for(size_t i = 0; i < m_req_Q->size(); i++){
        m_req_Q->at(i).h = m_req_h;//6.63 * pow(10, -34),
        m_req_Q->at(i).c = m_req_c;//2.99792458 * pow(10, 10)
        m_req_Q->at(i).K = m_req_K;//(1.38 * pow(10, -23))
        m_req_Q->at(i).Tex = m_req_Tex;//温度
        m_req_Q->at(i).Tvib = m_req_Tvib;//温度
        m_req_Q->at(i).Trot = m_req_Trot;//温度
    }
    //x & a
    m_req_x_a->h = m_req_h;//6.63 * pow(10, -34),
    m_req_x_a->c = m_req_c;//2.99792458 * pow(10, 10)
    m_req_x_a->K = m_req_K;//(1.38 * pow(10, -23))
    m_req_x_a->Tex = m_req_Tex;//温度
    m_req_x_a->Tvib = m_req_Tvib;//温度
    m_req_x_a->Trot = m_req_Trot;//温度
}

std::vector<CoordinateModel> Brigde::compute(float min_x, float max_x, float step, float weight)
{
    std::vector<CoordinateModel>().swap(m_ret_vec_coordinate);
    compute_q();
    compute_x_a();
    compute_qevj();
    compute_n();
    compute_y();
    compute_plot(min_x, max_x, step, weight);
    //free
    delete(m_pParseX);
    delete(m_pParseA);
    delete(m_pMergeXA);
    delete(m_pComputeQevj);
    delete(m_pComputeQ);
    delete(m_pComputeN);
    delete(m_pComputeY);
    delete(m_pComputePlot);
    m_pParseX = new ParseX();//x
    m_pParseA = new ParseA();//a
    m_pMergeXA = new MergeXA();//x & a
    m_pComputeQevj = new ComputeQevj();//Qevj
    m_pComputeQ = new ComputeQ();//Q
    m_pComputeN = new ComputeN();//n
    m_pComputeY = new ComputeY();//y
    m_pComputePlot = new ComputePlot();//fai
    return m_ret_vec_coordinate;
}

std::vector<CoordinateModel> Brigde::getData()
{
    return m_ret_vec_coordinate;
}

std::vector<CoordinateModel> Brigde::getBasicData()
{
    return m_pComputePlot->computBasicPlots(m_ret_vec_xModel);
}

long double Brigde::compute_q()
{
    m_ret_Q = 0;
    for(size_t i = 0; i < m_req_Q->size(); i++){
        QReq *qReq = &m_req_Q->at(i);
        m_ret_Q += m_pComputeQ->sumQ(m_pParseX->ParseStr2VJ(qReq->g, qReq->Te, qReq->url),
                                     qReq->h, qReq->c, qReq->K,
                                     qReq->Tex, qReq->Tvib, qReq->Trot,
                                     qReq->gne, qReq->gno, qReq->gbase);
    }
    return m_ret_Q;
}

std::vector<XModel> Brigde::compute_x_a()
{
    m_ret_vec_xModel = m_pMergeXA->Merge(m_pParseX->XVector(m_req_x_a->g1, m_req_x_a->Te1, m_req_x_a->url1, m_req_x_a->g2, m_req_x_a->Te2, m_req_x_a->url2, m_req_x_a->h, m_req_x_a->c),
                                         m_pParseA->AVector(m_req_x_a->urla));
    return m_ret_vec_xModel;
}

std::vector<XModel> Brigde::compute_qevj()
{
    m_ret_vec_xModel = m_pComputeQevj->computeQevj_s(m_ret_vec_xModel, m_req_x_a->h,  m_req_x_a->c,  m_req_x_a->K,
                                                     m_req_x_a->Tex, m_req_x_a->Tvib, m_req_x_a->Trot,
                                                     m_req_x_a->gne, m_req_x_a->gno, m_req_x_a->gbase);
    return m_ret_vec_xModel;
}

long double Brigde::compute_n()
{
    //R=8.31 P=1.01*10^5 T=15000
    m_ret_n = m_pComputeN->compute_n(8.31, 1.01 * pow(10, 5), m_req_x_a->Tex);
    return m_ret_n;
}

std::vector<XModel> Brigde::compute_y()
{
    m_ret_vec_xModel = m_pComputeY->compute_y(m_req_x_a->h, m_req_x_a->c, m_ret_n, m_ret_Q, m_ret_vec_xModel);
    return m_ret_vec_xModel;
}

std::vector<CoordinateModel> Brigde::compute_plot(float min_x, float max_x, float step, float weight)
{
    m_ret_vec_coordinate = m_pComputePlot->computPlots(min_x, max_x, step, weight, m_req_x_a->Tex, m_ret_vec_xModel);
    return m_ret_vec_coordinate;
}
