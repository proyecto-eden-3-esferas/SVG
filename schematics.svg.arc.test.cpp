#include "schematics.svg.arc.h"
//#include "schematics.svg.h"

#include <fstream>

using namespace std;

typedef double  float_type;
typedef svg_shape<float_type> svg_t;
typedef svg_arc<float_type> svg_arc_t;

int main() {

  ofstream ofs("test-arc.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<h1>Some SVG arc(s) drawn through a pointer (<code>svg_t*</code>)</h1>\n";
  open_svg(ofs);
    svg_t * ptr = new svg_arc_t(50,50, 33,33, 0,50, false, false, false, svg_arc_t::move);
    ptr->add_svg(ofs);
  close_svg(ofs);
  ofs << "</body></html>";
  ofs.close();

  return 0;
}
