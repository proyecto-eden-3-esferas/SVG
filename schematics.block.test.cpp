#include "schematics.rectangle.h"
#include "svg.h"

#define TEST_IC_PIN_LOCATION

#include <fstream>
using namespace std;

typedef  double float_type;
typedef block<float_type> block_t;

#ifdef DRAW_LINES
#include "schematics.line.h"
typedef twoline<float_type> line_t;
#endif

// std::ostream& operator<<(std::ostream& o, Cmp& cmp) {

int main()
{

  block_t bl1 (60,20, 0,0,  4, 3, 5, 2);
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
