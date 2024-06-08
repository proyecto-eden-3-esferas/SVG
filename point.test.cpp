#include "point.h"

#include <iostream>

using namespace std;

int main() {

  point p0, p1{3.3}, p2{4.04, 5.99}, p3{1.23, 2.34, 3.45};

  cout << "p3[2] = " << get<2>(p3) << '\n';
  set<2>(p3, 3.33);
  cout << "p3[2] = " << get<2>(p3) << '\n';

  return 0;
};
