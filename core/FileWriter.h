#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#ifndef _BASESFILEWRITER_H_
#define _BASESFILEWRITER_H_

void write(string ss)
{
  ofstream *p_oftream = new ofstream();
  p_oftream->open("C:\\ret_.txt", ios::out | ios::app);
  p_oftream->write(ss.c_str(), ss.length());
  p_oftream->close();
}
#endif