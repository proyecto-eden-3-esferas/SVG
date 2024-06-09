#include "segment.h"

#include <iostream>
//#include <boost/geometry.hpp>
//#include <boost/geometry/geometries/geometries.hpp>

typedef point<double, 2, boost::geometry::cs::cartesian> point_t;
typedef segment<point_t> segment_t;

using namespace std;

int main()
{

  segment_t seg1;
  segment_t seg2(point_t(1.1, 2.2), point_t(3.3, 4.4));
  segment_t seg3{{0.0, 0.0}, {5.0, 5.0}};

  double x0 = get<0, 0>(seg2);
  double y0 = get<0, 1>(seg2);
  double x1 = get<1, 0>(seg2);
  double y1 = get<1, 1>(seg2);
  std::cout << x0 << ", " << y0 << ", " << x1 << ", " << y1 << std::endl;

  set<0, 0>(seg2, 1.0);
  set<0, 1>(seg2, 2.0);
  set<1, 0>(seg2, 3.0);
  set<1, 1>(seg2, 4.0);
  x0 = get<0, 0>(seg2);
  y0 = get<0, 1>(seg2);
  x1 = get<1, 0>(seg2);
  y1 = get<1, 1>(seg2);
  std::cout << "After setting: " << x0 << ", " << y0 << ", " << x1 << ", " << y1 << std::endl;



  return 0;
}
