#include "pair-as-2D-point.h"

#include <iostream>
#include <iomanip>

#ifndef PRINT_PAIR_H
#include "print-pair.h"
#endif

using namespace std;

int main()
{
  pair<double,double> p1(100.33, 200.33), p2(p1), p3(25,50);
  p1 *= 2.0;
  cout << p1 << endl;

  p2 += p3;
  cout << p2 << endl;

  return 0;
}
