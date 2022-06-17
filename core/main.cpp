#include <QCoreApplication>
#include "ParseX.h"
#include "ParseA.h"
#include "MergeXA.h"
#include "ComputeQevj.h"
#include "ComputeQ.h"
#include "QFile"


//科学计数法
long double ENumber(std::string num_str){
    long double ret_ = 0;
    int index_E_base = 1;
    int index_E = -1;
    if (num_str.find("E-") != num_str.npos) {
        index_E_base = -1;
        index_E = num_str.find("E-");
    } else if (num_str.find("E+") != num_str.npos){
        index_E_base = 1;
        index_E = num_str.find("E+");
    }
    if (index_E == -1){
        ret_ = std::stold(num_str);
        return ret_;
    }
    std::string num_a = num_str.substr(0, index_E);
    std::string num_b = num_str.substr(index_E + 2, num_str.length() - (index_E + 2));
    ret_ = std::stold(num_a) * (std::pow(10, index_E_base * std::stoi(num_b)));
    return ret_;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int type = 0;
    std::cout << "input number(1: x a Qevj , 2: Q):" << std::endl;
    std::cin >> type;
    if(type==1){
        //compute x & a & Qevj
        std::cout << std::endl << "input: file_deeper (example: C:/deeper.txt)" << std::endl;
        char x_a_1_url[1024] = "";
        std::cin >> x_a_1_url;
        std::cout << std::endl << "input: deeper_Te (example: 0)" << std::endl;
        char x_a_1_Te[1024] = "";
        std::cin >> x_a_1_Te;
        //x
        std::cout << std::endl << "input: file_higher (example: C:/higher.txt)" << std::endl;
        char x_a_2_url[1024] = "";
        std::cin >> x_a_2_url;
        std::cout << std::endl << "input: higher_Te (example: 15000)" << std::endl;
        char x_a_2_Te[1024] = "";
        std::cin >> x_a_2_Te;
        //a
        std::cout << std::endl << "input: file_Aul (example: C:/Aul.txt)" << std::endl;
        char x_a_a_url[1024] = "";
        std::cin >> x_a_a_url;
        //const
        std::cout << std::endl << "input: const h (example: 6.63E-34)" << std::endl;
        char const_h[1024] = "";
        std::cin >> const_h;
        std::cout << std::endl << "input: const c (example: 2.99792458E+10)" << std::endl;
        char const_c[1024] = "";
        std::cin >> const_c;
        std::cout << std::endl << "input: const K (example: 1.38E-23)" << std::endl;
        char const_K[1024] = "";
        std::cin >> const_K;
        std::cout << std::endl << "input: const Tex/Tvib/Tor (example: 15000)" << std::endl;
        char const_Tsss[1024] = "";
        std::cin >> const_Tsss;
        std::cout << std::endl << "input: const gne (example: 6)" << std::endl;
        char const_gne[1024] = "";
        std::cin >> const_gne;
        std::cout << std::endl << "input: const gno (example: 3)" << std::endl;
        char const_gno[1024] = "";
        std::cin >> const_gno;
        std::cout << std::endl << "input: const gbase (example: 1)" << std::endl;
        char const_gbase[1024] = "";
        std::cin >> const_gbase;
        //compute x & a & Qevj
        ComputeQevj m_pComputeQevj = ComputeQevj();
        m_pComputeQevj.init(MergeXA().Merge(ParseX().XVector("deeper", std::stof(std::string(x_a_1_Te)), x_a_1_url, "higher", std::stof(std::string(x_a_2_Te)), x_a_2_url), ParseA().AVector(x_a_a_url)),
                            ENumber(std::string(const_h)),          // h 常量
                            ENumber(std::string(const_c)),          // c 常量
                            ENumber(std::string(const_K)),          // K 常量
                            std::stof(std::string(const_Tsss)),     // Tex 常量
                            std::stof(std::string(const_Tsss)),     // Tvib 常量
                            std::stof(std::string(const_Tsss)),     // Trot 常量
                            std::stof(std::string(const_gne)),      // gne   偶数时的值
                            std::stof(std::string(const_gno)),      // gno   奇数时的值
                            std::stof(std::string(const_gbase)));
        //        m_pComputeQevj.init(MergeXA().Merge(ParseX().XVector("deeper", 0, x_a_1_url, "higher", 15000, x_a_2_url), ParseA().AVector(x_a_a_url)),
        //                            6.63 * pow(10, -34),               // h 常量
        //                            2.99792458 * pow(10, 10),          // c 常量
        //                            15000,                            // K 常量
        //                            (1.38 * pow(10, -23)),           // Tex 常量
        //                            (1.38 * pow(10, -23)),           // Tvib 常量
        //                            (1.38 * pow(10, -23)),           // Trot 常量
        //                            6,                               // gne   偶数时的值
        //                            3,                               // gno   奇数时的值
        //                            1);
        vector<XModel> vec_x = m_pComputeQevj.computeQevj_s();
        std::string tmp_str = "";
        for(size_t i = 0; i < vec_x.size(); i++){
            XModel x_model = vec_x[i];
            tmp_str += "g'=" + x_model.g1 + ", "
                    + "v'=" + std::to_string(x_model.v1) + " "
                    + "j'=" + std::to_string(x_model.j1) + " "
                    + "e'=" + std::to_string(x_model.e1) + " "
                    + "t'=" + std::to_string(x_model.t1) + " "
                    + " <<--->> "
                    + "g''=" + x_model.g2 + ", "
                    + "v''=" + std::to_string(x_model.v2) + " "
                    + "j''=" + std::to_string(x_model.j2) + " "
                    + "e''=" + std::to_string(x_model.e2) + " "
                    + "t''=" + std::to_string(x_model.t2) + " "
                    + " <<--->> "
                    + "x= " + std::to_string(x_model.x) + " "
                    + "a= " + std::to_string(x_model.a) + " "
                    + "Qvej= " + std::to_string(x_model.Qevj) + " \n";
            std::cout << "." << endl;
        }

        QFile file("./x_a_Qevj.txt");
        file.open(QIODevice::ReadWrite);
        file.write(tmp_str.c_str());
        file.close();
        std::cout << "./x_a_Qevj.txt" << endl;
    } else if(type == 2){
        // compute Q
        //q
        std::cout << "input: file (example: c:/xxx.txt)" << std::endl;
        char q_url[1024] = "";
        std::cin >> q_url;
        std::cout << std::endl << "input: Te (example: 15000)" << std::endl;
        char x_q_1_Te[1024] = "";
        std::cin >> x_q_1_Te;
        //const
        std::cout << std::endl << "input: const h (example: 6.63E-34)" << std::endl;
        char const_h[1024] = "";
        std::cin >> const_h;
        std::cout << std::endl << "input: const c (example: 2.99792458E+10)" << std::endl;
        char const_c[1024] = "";
        std::cin >> const_c;
        std::cout << std::endl << "input: const K (example: 1.38E-23)" << std::endl;
        char const_K[1024] = "";
        std::cin >> const_K;
        std::cout << std::endl << "input: const Tex/Tvib/Tor (example: 15000)" << std::endl;
        char const_Tsss[1024] = "";
        std::cin >> const_Tsss;
        std::cout << std::endl << "input: const gne (example: 6)" << std::endl;
        char const_gne[1024] = "";
        std::cin >> const_gne;
        std::cout << std::endl << "input: const gno (example: 3)" << std::endl;
        char const_gno[1024] = "";
        std::cin >> const_gno;
        std::cout << std::endl << "input: const gbase (example: 1)" << std::endl;
        char const_gbase[1024] = "";
        std::cin >> const_gbase;
        //compute Q
        ComputeQ m_qCompute = ComputeQ();
        m_qCompute.init(
                    ParseX().ParseStr2VJ("Q", std::stof(std::string(x_q_1_Te)), q_url), // q_name 名称, q_t 跃迁, q_url 文件
                    ENumber(std::string(const_h)),          // h 常量
                    ENumber(std::string(const_c)),          // c 常量
                    ENumber(std::string(const_K)),          // K 常量
                    std::stof(std::string(const_Tsss)),     // Tex 常量
                    std::stof(std::string(const_Tsss)),     // Tvib 常量
                    std::stof(std::string(const_Tsss)),     // Trot 常量
                    std::stof(std::string(const_gne)),      // gne   偶数时的值
                    std::stof(std::string(const_gno)),      // gno   奇数时的值
                    std::stof(std::string(const_gbase)));   // gbase 倍数
        //        m_qCompute.init(
        //                    ParseX().ParseStr2VJ("segma", 0, q_url), // q_name 名称, q_t 跃迁, q_url 文件
        //                    6.63 * pow(10, -34),                   // h 常量
        //                    2.99792458 * pow(10, 10),              // c 常量
        //                    15000,                            // K 常量
        //                    (1.38 * pow(10, -23)),           // Tex 常量
        //                    (1.38 * pow(10, -23)),           // Tvib 常量
        //                    (1.38 * pow(10, -23)),           // Trot 常量
        //                    6,                                     // gne   偶数时的值
        //                    3,                                     // gno   奇数时的值
        //                    1);                                    // gbase 倍数
        m_qCompute.sumQ();
        QFile file("./Q.txt");
        file.open(QIODevice::ReadWrite);
        file.write(m_qCompute.record_string.c_str());
        file.close();
        std::cout << "./Q.txt" << endl;
    }
    system("pause");
    return a.exec();
}
