#ifndef XYMODEL
#define XYMODEL

#include <string>

using namespace std;

typedef struct _VJModel
{
    string g;//名称
    float v;
    float j;
    float e;
    float t;//跃迁
} VJModel;

typedef struct _AModel
{
    float v1;
    float j1;

    float v2;
    float j2;

    float ret_;
} AModel;

typedef struct _XModel
{
    string g1;//名称
    float v1;
    float j1;
    float e1;
    float t1;//跃迁

    string g2;//名称
    float v2;
    float j2;
    float e2;
    float t2;//跃迁

    float x;
    float a;
    long double Qevj;
} XModel;

typedef struct _YModel
{
    float y;
} YModel;

typedef struct _XAReq
{
    //x
    string g1;//名称
    string g2;//名称
    float Te1;//跃迁
    float Te2;//跃迁
    string url1;
    string url2;
    long double h;//常量
    long double c;//常量
    long double K;//常量
    long double Tex;//常量
    long double Tvib;//常量
    long double Trot;//常量
    int gne;//常量
    int gno;//常量
    int gbase;//常量
    //aul
    string urla;
} XAReq;

typedef struct _QReq
{
    string g;//名称
    float Te;//跃迁
    string url;
    long double h;//常量
    long double c;//常量
    long double K;//常量
    long double Tex;//常量
    long double Tvib;//常量
    long double Trot;//常量
    int gne;//常量
    int gno;//常量
    long double gbase;//常量
} QReq;

#endif
