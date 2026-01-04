#include "schematics.rectangle.h"

#include <fstream>
using namespace std;

#ifndef SCHEMATICS_RECTANGLE_GLOBALS_H
#include "schematics.rectangle.globals.h"
#endif

typedef                       double float_type;
typedef rectangle<            float_type> rectangle_t;

// std::ostream& operator<<(std::ostream& o, Cmp& cmp) {

int main()
{

  rectangle_t rect1(60,30, 25, 25);

// open file "test-rectangle-globals.html" to hold an SVG element:
  ofstream ofs("test-rectangle-globals.html");
  ofs << "<!DOCTYPE html>\n";
  ofs << "<html>\n<body>\n";
  ofs << "<p>Some SVG for testing <code>add_svg_unclosed(<var>RECTANGLE</var>, <var>OSTREAM</var>)</code>:</p>\n";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.5);
      add_svg(rect1, ofs);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
