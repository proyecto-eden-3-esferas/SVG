#include "schematics.h"
#include "schematics.svg.h"

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

  block<float_type> bl1 (60,20, 0,0,  4, 3, 5, 2);
  for(int i=0; i < 4; ++i)
    cout << "right side x="  << bl1.get_x_right(i) << ", y=" << bl1.get_y_right(i) << '\n';
  for(int i=0; i < 3; ++i)
    cout << "bottom side x="  << bl1.get_x_bottom(i) << ", y=" << bl1.get_y_bottom(i) << '\n';
  for(int i=0; i < 5; ++i)
    cout << "left side x="  << bl1.get_x_left(i) << ", y=" << bl1.get_y_left(i) << '\n';
  for(int i=0; i < 2; ++i)
    cout << "top side x="  << bl1.get_x_top(i) << ", y=" << bl1.get_y_top(i) << '\n';

  // open file "test.html" to hold an SVG element:
  ofstream ofs("test.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "yellow", 0.25);
  // Keep adding components to the SVG file (handle='ofs')
      add_svg(bl1,  ofs);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
