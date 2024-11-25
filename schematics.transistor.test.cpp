#include "schematics.transistor.h"
#include "schematics.fet.h"

#ifndef SCHEMATICS_LABEL_H
#include "schematics.label.h"
#endif

#ifndef TR_RADIUS
#define TR_RADIUS 66.0
#endif

#include <fstream>
using namespace std;

typedef double float_type;
typedef transistor<float_type> transistor_t;
typedef        fet<float_type>        fet_t;

int main() {

  transistor_t tr1(TR_RADIUS, 1.5*TR_RADIUS, 1.5*TR_RADIUS);
  fet_t        ft1(TR_RADIUS, 1.5*TR_RADIUS, 1.5*TR_RADIUS);

  /*
  for(int i=0; i < 10; ++i) {
    cout << "point " << i << " is (" << tr1.x_of_pin(i) << ", " << tr1.y_of_pin(i) << ")\n";
  }
  for(int i=0; i < 10; ++i) {
    cout << "point " << i << " is (" << ft1.x_of_pin(i) << ", " << ft1.y_of_pin(i) << ")\n";
  }
  */


  // open file "test.transistor.html" to hold an SVG element:
  ofstream ofs("test.transistor.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Drawing transistors in SVG</p>\n";

    ofs << "<p>Draw a generic BJT:</p>";
    open_svg(ofs, 3*TR_RADIUS, 3*TR_RADIUS, "black", "gray", 0.2);
    add_svg(tr1, ofs);
    close_svg(ofs);

    ofs << "<p>Now draw a generic FET:</p>";
    open_svg(ofs, 3*TR_RADIUS, 3*TR_RADIUS, "black", "gray", 0.2);
    add_svg(ft1, ofs);
    close_svg(ofs);

  ofs << "</body>\n</html>";
  ofs.close();

  // Now write SVG files "bjt.svg" and "fet.svg":

  ofstream bjt_ofs("bjt.svg");
    open_svg(bjt_ofs, 3*TR_RADIUS, 3*TR_RADIUS, "black", "gray", 0.2);
    add_svg(tr1, bjt_ofs);
    close_svg(bjt_ofs);
  bjt_ofs.close();

  ofstream fet_ofs("fet.svg");
    open_svg(fet_ofs, 3*TR_RADIUS, 3*TR_RADIUS, "black", "gray", 0.2);
    add_svg(ft1, fet_ofs);
    close_svg(fet_ofs);
  fet_ofs.close();



  return 0;
}
