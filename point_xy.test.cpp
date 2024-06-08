#include "point_xy.h"

#include <iostream>

using namespace std;

int main() {

  point_xy p0, p2{4.04, 5.99};
  // point_xyz p3{1.23, 2.34, 3.45};

  cout << "p2[1] = " << get<1>(p2) << '\n';
  set<1>(p2, 3.33);
  cout << "p2[1] = " << get<1>(p2) << '\n';

  return 0;
};
