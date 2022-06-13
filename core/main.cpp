#include <QCoreApplication>
#include "ParseX.h"
#include "ParseA.h"
#include "MergeXA.h"
#include "ComputeQ.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // compute Q
    std::cout << "input: name (example: x1segma)" << std::endl;
    string q_g = "x1segma";
    std::cin >> q_g;
    std::cout << "input: temperature (example: 15000)" << std::endl;
    float q_t = 15000;
    std::cin >> q_t;
    std::cout << "input: url (example: c:/xxx.txt)" << std::endl;
    char q_url[1024] = "D:/Project_QT/github_admin/N2/document/z_data_sample/基态X1sigema振转能级.txt";
    std::cin >> q_url;
    ComputeQ m_qCompute = ComputeQ();
    m_qCompute.init(
        ParseX().ParseStr2VJ(q_g, q_t, q_url), // q_name 名称, q_t 温度, q_url 文件
        6.63 * pow(10, -34),                   // h 常量
        2.99792458 * pow(10, 10),              // c 常量
        q_t * (1.38 * pow(10, -23)),           // KTex 常量
        q_t * (1.38 * pow(10, -23)),           // KTvib 常量
        q_t * (1.38 * pow(10, -23)),           // KTrot 常量
        6,                                     // gne   偶数时的值
        3,                                     // gno   奇数时的值
        1);                                    // gbase 倍数
    m_qCompute.sumQ();
    std::cin >> q_url;
    system("pause");
    return a.exec();
}
