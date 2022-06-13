#ifndef XYMODEL
#define XYMODEL

#include <string>

using namespace std;

typedef struct _VJModel
{
  string g;
  float v;
  float j;
  float e;
  float t;
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
  string g1;
  float v1;
  float j1;
  float e1;
  float t1;

  string g2;
  float v2;
  float j2;
  float e2;
  float t2;

  float x;
  float a;
} XModel;

typedef struct _QModel
{
  float ret_;
} QModel;

typedef struct _YModel
{
  float ret_;
} YModel;

#endif