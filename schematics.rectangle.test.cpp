#ifndef SCHEMATICS_RECTANGLE_H
#include "schematics.rectangle.h"
#endif

#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef    double float_type;
typedef svg_shape<float_type> svg_t;
typedef rectangle<float_type> rectangle_t;

// std::ostream& operator<<(std::ostream& o, Cmp& cmp) {

using namespace std;

int main()
{
  // rectangle_t * ptr = new rectangle_t(60,30, 25, 25);

  vector<const svg_t*> v{
    new rectangle_t(60,30,  25,25),
    new rectangle_t(60,30, 100,25, 4),
    new rectangle_t(60,30, 140,40, 8, 4) };
  string yellow_fill{"fill=\"yellow\""};

// open file "test-rectangle.html" to hold an SVG element:
  ofstream ofs("test-rectangle.html");
  ofs << "<!DOCTYPE html>\n";
  ofs << "<html>\n<body>\n";
  ofs << "<p>Some SVG for testing</p>";
  ofs << "<pre>virtual rectangle::add_svg_unclosed(<var>OSTREAM</var>, <var>ATTRS</var>)</pre>\n";
  ofs << "<p>through a reference of type <code>const svg_shape&lt;F&gt;*</code>:</p>\n";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.5);
      for(const auto p : v)
        p->add_svg(ofs, yellow_fill);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
