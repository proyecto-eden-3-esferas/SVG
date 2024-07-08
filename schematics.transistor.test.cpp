#include "schematics.transistor.h"

#ifndef SCHEMATICS_LABEL_H
#include "schematics.label.h"
#endif

#include <fstream>
using namespace std;

typedef double float_type;
typedef bjt<float_type> bjt_t;

int main() {

  bjt_t bjt1(50, 90, 90);

  // open file "test.transistor.html" to hold an SVG element:
  ofstream ofs("test.transistor.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.2);
    //add_svg(static_cast<circular<float_type>>(bjt1), ofs);
    add_svg(bjt1, ofs);

  // Keep adding components to the SVG file (handle='ofs')
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();



  return 0;
}
