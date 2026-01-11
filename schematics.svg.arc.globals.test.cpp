#include "schematics.svg.arc.globals.h"
//#include "schematics.svg.h"

#include <fstream>

using namespace std;

typedef double  float_type;
typedef svg_arc<float_type> svg_arc_t;

int main() {

  ofstream ofs("test-arc-globals.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<h1>Some SVG arc(s)... (global functions version)</h1>\n";
  open_svg(ofs);

  svg_arc_t sa1(50,50, 33,33, 0,50, false, false, false);
  add_svg(sa1,ofs);

  close_svg(ofs);
  ofs << "</body></html>";
  ofs.close();

  return 0;
}
