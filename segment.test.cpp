#include "segment.h"
#include "schematics.twoport.h"

#ifndef SVG_H
#include "svg.h"
#endif

#include <iostream>
#include <fstream>


typedef point<double, 2, boost::geometry::cs::cartesian> point_t;
typedef segment<point_t> segment_t;
typedef twoport<double> twoport_t;

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

  twoport_t tp1({100.0, 100.0}, {200.0, 100.0}, 0.1);
  twoport_t tp2({150.0, 150.0}, {400.0,  25.0}, 0.1);
  tp1.set_width(44.0);
  tp2.set_width(44.0);
  // open file "test.html" to hold an SVG element:
  ofstream ofs("test.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.2);
      add_svg(tp1, ofs);
      add_svg(tp2, ofs);
      //add_svg(l80, ofs);

  // Keep adding components to the SVG file (handle='ofs')
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
