#include <QApplication>
#include "mainwindow.h"
#include "gmp/gmp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *window = new MainWindow;
    window->show();
    return a.exec();
}

void init_gmp(){
    //=====================mpf
    //初始化
//    mpf_t mp_float;
//    //初始化
//    mpf_init(mp_float);
//    mpf_init2 (mp_float, 1024);
//    mpf_set_prec(mp_float, 6);
//    //初始化
//    mpf_init_set_str(mp_float, "111222333444111222333444111222333444111222333444.111222333444111222333444", 10);
//    //初始化
//    mpf_init_set_d(mp_float, 111222333444111222333444.111222333444111222333444);
//    //加法
//    mpf_add(mp_float, mp_float, mp_float);
//    //获取
//    qDebug(std::to_string(mpf_get_d(mp_float)).c_str());
//    mp_exp_t exponent;
//    char *sss = mpf_get_str(nullptr, &exponent, 10, 1000, mp_float);
//    qDebug(sss);
    //=====================mpz
//     mpz_t mp_int;
//     mpz_init(mp_int);
//     mpz_init_set_str(mp_int, "111222333444111222333444111222333444111222333444", 10);
//     mpz_add(mp_int, mp_int, mp_int);
//     qDebug(std::to_string(mpz_get_d(mp_int)).c_str());
//     char *sss = mpz_get_str(nullptr, 10 ,mp_int);
//     qDebug(sss);
     //=====================mpq
//       mpq_t mp_qua;
//       mpq_init(mp_qua);
//       mpq_set_str(mp_qua, "1.1/2.2", 10);
//       qDebug(std::to_string(mpq_get_d(mp_qua)).c_str());
//       char *sss = mpq_get_str(nullptr, 10 ,mp_qua);
//       qDebug(sss);
}
