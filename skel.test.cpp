#include "skel.h"

#include <iostream>

#ifndef SKEL_CPP
#include "skel.cpp"
#endif


typedef mechalink<double,3> mechalink_type;
typedef point<    double,3> point_type;
using namespace std;

int main() {

  point_type p0(1.1, 2.2, 3.3);
  mechalink_type m0(p0);
  mechalink_type & m1 = m0.grow();

  /*
  cout << "is \'m0\' initialized? "<< boolalpha << m0.is_initialized() << endl;
  cout << "is \'m1\' initialized? "<< boolalpha << m1.is_initialized() << endl;
  */

  return 0;
}
