#include "schematics.transistor.h"
#include "schematics.fet.h"

#ifndef SCHEMATICS_LABEL_H
#include "schematics.label.h"
#endif

#include <fstream>
using namespace std;

typedef double float_type;
typedef transistor<float_type> transistor_t;
typedef        fet<float_type>        fet_t;

int main() {

  transistor_t tr1(40,  50, 50);
  fet_t        ft1(40, 150, 50);

  // open file "test.transistor.html" to hold an SVG element:
  ofstream ofs("test.transistor.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Drawing transistors in SVG</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.2);
    //add_svg(static_cast<circular<float_type>>(tr1), ofs);
    //add_svg(tr1, ofs);
    tr1.add_svg(ofs);
    ft1.add_svg(ofs);
    //ft1.add_emitter_to_svg(ofs);
    //ft1.add_collector_to_svg(ofs);

  // Keep adding components to the SVG file (handle='ofs')
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();



  return 0;
}
