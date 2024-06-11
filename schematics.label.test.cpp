#ifndef SCHEMATICS_LABEL_H
#include "schematics.label.h"
#endif

#include <fstream>
using namespace std;

typedef       double float_type;
typedef label<float_type> label_t;

label_t lbl1(100.0, 100.0, "original");
label_t lbl2(200.0, 100.0, "rising", -45, label<float_type>::text_anchor::start);

int main() {

  // open file "test.html" to hold an SVG element:
  ofstream ofs("test.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.2);
      add_svg(lbl1, ofs);
      add_svg(lbl2, ofs);
      //add_svg(l80, ofs);

  // Keep adding components to the SVG file (handle='ofs')
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();



  return 0;
}
