#include "schematics.h"
#include "schematics.svg.h"

#define TEST_POLYLINE_POINT_LOCATIONS
#define TEST_IC_PIN_LOCATION

#include <fstream>
using namespace std;

typedef                       double float_type;
typedef          angle_addressable<   float_type> cir_t; // instead of former longish name 'component_t'
typedef circular<   float_type>    circular_component_t;
typedef rectangular<float_type> rectangular_component_t;
typedef rectangle<            float_type> rectangle_t;
typedef polyline<             float_type>  polyline_t;
typedef polygon<             float_type>  polygon_t;
typedef  elliptical<float_type>  elliptical_component_t;
typedef               twoline<float_type>                  line_t;

// std::ostream& operator<<(std::ostream& o, Cmp& cmp) {

int main()
{


  rectangle_t rect1(60,30, 25, 25);

// open file "test.html" to hold an SVG element:
  ofstream ofs("test.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.5);
      add_svg(rect1, ofs);

  cout << "Test twoline<>:\n";
  line_t l1(-100,25,100,25);
  cout << "Interpolate components of l1(-100,25,100,25) for several \'k\':\n";
  cout << "For \'k\' = 0.25, components are: " << l1.get_x(0.25) << ", " << l1.get_y(0.25) << '\n';
  cout << "For \'k\' = 0.66, components are: " << l1.get_x(0.66) << ", " << l1.get_y(0.66) << '\n';
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

  // Keep adding components to the SVG file (handle='ofs')
      add_svg(l1,ofs);
      add_svg(l2,ofs);
      add_svg(pll1, ofs);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
