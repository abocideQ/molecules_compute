#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#ifndef _BASEDECIMALUTILS_H_
#define _BASEDECIMALUTILS_H_

class DecimalUtils
{
public:
  // a + b
  static long double sum_(long double a, long double b)
  {
    return a + b;
  }

  // a * b
  static long double multiply_(long double a, long double b)
  {
    return a * b;
  }

  // eⁿ
  static long double exp_(long double n)
  {
    return exp(n);
  }

  //偶数?
  static bool even_(int n)
  {
    if (n % 2 == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};
#endif
