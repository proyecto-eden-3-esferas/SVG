#include "point_xyz.h"

#include <iostream>

using namespace std;

int main() {

  point_xyz p0, p2{4.04, 5.99, 333.0};
  // point_xyz p3{1.23, 2.34, 3.45};

  cout << "p2[2] = " << get<2>(p2) << '\n';
  set<2>(p2, 123.0);
  cout << "p2[2] = " << get<2>(p2) << '\n';

  return 0;
};
