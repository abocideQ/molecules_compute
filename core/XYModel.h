#ifndef XYMODEL
#define XYMODEL

#include <string>

using namespace std;

typedef struct _VJModel //v, j
{
    string g;//名称
    float v;
    float j;
    long double e;//
    long double t;//跃迁
} VJModel;

typedef struct _AModel //Aul
{
    float v1;
    float j1;

    float v2;
    float j2;

    long double ret_;//
} AModel;

typedef struct _XModel//基准 x, y
{
    string g1;//名称
    float v1;
    float j1;
    long double e1;//
    long double t1;//跃迁

    string g2;//名称
    float v2;
    float j2;
    long double e2;//
    long double t2;//跃迁

    long double x;
    long double a;
    long double Qevj;
    long double y;
} XModel;

typedef struct _XAReq
{
    //x
    string g1;//名称
    string g2;//名称
    long double Te1;//跃迁
    long double Te2;//跃迁
    string url1;
    string url2;
    long double h;//常量
    long double c;//常量
    long double K;//常量
    long double Tex;//常量
    long double Tvib;//常量
    long double Trot;//常量
    float gne;//常量
    float gno;//常量
    float gbase;//常量
    //aul
    string urla;
} XAReq;

typedef struct _QReq
{
    string g;//名称
    long double Te;//跃迁
    string url;
    long double h;//常量
    long double c;//常量
    long double K;//常量
    long double Tex;//常量
    long double Tvib;//常量
    long double Trot;//常量
    float gne;//常量
    float gno;//常量
    float gbase;//常量
} QReq;

typedef struct _NReq
{
    long double R;
    long double P;
    long double T;
    long double V;
} NReq;

#endif
