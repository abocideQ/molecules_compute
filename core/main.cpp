#include <windows.h>
#include "ParseX.h"
#include "ParseA.h"
#include "MergeXA.h"
#include "ComputeQ.h"

int main()
{
    while (1)
    {
        // //基态
        // std::cout << "↓ 基态名称 G ↓" << std::endl;
        // string g_1 = "";
        // std::cin >> g_1;
        // std::cout << "↓ 基态温度 T ↓" << std::endl;
        // float t_1 = 0;
        // std::cin >> t_1;
        // std::cout << "↓ 基态数据 DATA ↓" << std::endl;
        // char pUrl_1[1024];
        // std::cin >> pUrl_1;

        // //激发态
        // std::cout << "↓ 激发态名称 G ↓" << std::endl;
        // string g_2 = "";
        // std::cin >> g_2;
        // std::cout << "↓ 激发态温度 T ↓" << std::endl;
        // float t_2 = 0;
        // std::cin >> t_2;
        // std::cout << "↓ 激发态数据 DATA ↓" << std::endl;
        // char pUrl_2[1024];
        // std::cin >> pUrl_2;

        // //数据Aul
        // std::cout << "↓ Aul数据 DATA ↓" << std::endl;
        // char aUrl[1024];
        // std::cin >> aUrl;

        // // merge X & Aul
        // ParseX m_xParse = ParseX();
        // ParseA m_aParse = ParseA();
        // MergeXA m_merge = MergeXA();
        // vector<XModel> vec_x = m_merge.Merge(m_xParse.XVector(g_1, t_1, pUrl_1, g_2, t_2, pUrl_2), m_aParse.AVector(aUrl));

        // compute Q
        char q_Url[1024] = "D:/Project_QT/github_admin/N2/document/z_data_sample/基态X1sigema振转能级.txt";
        ComputeQ m_qCompute = ComputeQ();
        m_qCompute.init(
            ParseX().ParseStr2VJ("x1segma", 15000, q_Url), // q_name 名称, q_t 温度, q_url 文件
            6.63 * pow(10, -34),                           // h 常量
            2.99792458 * pow(10, 10),                      // c 常量
            15000 * (1.38 * pow(10, -23)),                 // KTex 常量
            15000 * (1.38 * pow(10, -23)),                 // KTvib 常量
            15000 * (1.38 * pow(10, -23)),                 // KTrot 常量
            6,                                             // gne   偶数时的值
            3,                                             // gno   奇数时的值
            1);                                            // gbase 倍数
        m_qCompute.sumQ();
        std::cin >> q_Url;
    }
    system("pause");
    return 0;
}