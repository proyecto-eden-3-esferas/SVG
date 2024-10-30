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

  cout << "p2.second = " << p2.second;
  cout << ", whereas for a given height (or depth) 1000, its invert is " << get_y_invert(p2,1000) << endl;

  return 0;
}
