#include "point.h"

#include <iostream>

using namespace std;
typedef point<double,3> point3_type;
typedef point<double,2> point2_type;

int main() {

  point2_type p0, p1{3.3}, p2{4.04, 5.99};
  point3_type              p3{1.23, 2.34, 3.45};

  cout << "p3[2] = " << get<2>(p3) << '\n';
  set<2>(p3, 3.33);
  cout << "p3[2] = " << get<2>(p3) << '\n';

  //
  cout << "Now use point<>\'s member getters and setters.\n";

  cout << "After running \'p3.set<2>(4.44);\' we find that:\n";
  p3.set<2>(4.44);
  cout << "p3[2] = " << p3.get<2>() << '\n';

  cout << "After running \'p2.set<1>(3.14);\' we find that:\n";
  p2.set<1>(3.14);
  cout << "p2[1] = " << p2.get<1>() << '\n';

  return 0;
};
