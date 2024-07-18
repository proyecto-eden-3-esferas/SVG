#include "schematics.line.h"

#define TEST_POLYLINE_POINT_LOCATIONS
#define TEST_IC_PIN_LOCATION

#include <fstream>
using namespace std;

typedef                       double float_type;
typedef polyline<             float_type>  polyline_t;
typedef polygon<             float_type>  polygon_t;
typedef               twoline<float_type>                  line_t;

typedef angle_addressable<float_type> cir_t;
float_type a10(cir_t::deg_to_rad(10));
float_type a15(cir_t::deg_to_rad(15));
float_type a22(cir_t::deg_to_rad(22));
float_type a30(cir_t::deg_to_rad(30));
float_type a45(cir_t::deg_to_rad(45));
float_type a60(cir_t::deg_to_rad(60));
float_type a80(cir_t::deg_to_rad(80));
float_type a225(cir_t::deg_to_rad(225));



// std::ostream& operator<<(std::ostream& o, Cmp& cmp) {

int main()
{

  cout << "Test twoline<>:\n";
  line_t l1( 100,25,300,25);
  line_t l1c(100,75,300,75);
  cout << "Interpolate components of l1(-100,25,100,25) for several \'k\':\n";
  cout << "For \'k\' = 0.25, components are: " << l1.get_x(0.25) << ", " << l1.get_y(0.25) << '\n';
  cout << "For \'k\' = 0.66, components are: " << l1.get_x(0.66) << ", " << l1.get_y(0.66) << '\n';
  line_t l11(l1.xperim(a45,20), l1.yperim(a45,20), l1.xperim(a225,20), l1.yperim(a225,20));
  line_t l2(-100,25, 100,0);
  cout << "Interpolate components of l2(-100,25, 100,0) for several \'k\':\n";
  cout << "For \'k\' = 0.25, components are: " << l2.get_x(0.25) << ", " << l2.get_y(0.25) << '\n';
  cout << "For \'k\' = 0.66, components are: " << l2.get_x(0.66) << ", " << l2.get_y(0.66) << '\n';
  // polyline_t pll1;
  polygon_t pll1;
  pll1.push_back( 100,  100);
  pll1.push_back(130, 110);
  pll1.push_back(130, 90);
  pll1.push_back( 100, 100);
#ifdef TEST_POLYLINE_POINT_LOCATIONS
  cout << "Output polyline_t \'pll1\' point locations:\n";
  for(auto pt : pll1.points)
    cout << "x=" << pt.first << ", y=" << pt.second << '\n';
#endif

  // open file "test-line.html" to hold an SVG element:
  ofstream ofs("test-line.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.5);

  // Keep adding components to the SVG file (handle='ofs')
      add_svg(l1,   ofs);
      add_svg(l1c,   ofs);
      l1c.add_circle_to_svg(ofs,22.0);
      //cout << "l1.xperim(0.0)=" << l1.xperim(0.0) << '\n';
      //add_svg(l2,   ofs);
      add_svg(l11,  ofs);
      add_svg(pll1, ofs);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();

  return 0;
}
