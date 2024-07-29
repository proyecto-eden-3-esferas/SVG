#ifndef SCHEMATICS_LABEL_H
#include "schematics.label.h"
#endif

#include <fstream>
using namespace std;

typedef       double float_type;
typedef label<     float_type> label_t;
typedef multilabel<float_type> multilabel_t;

label_t lbl1(100.0, 100.0, "original");
label_t lbl2(200.0, 100.0, "rising", -45, text_anchor::start);
multilabel_t::lines_t lines({"First line", "Second line", "Third line"});
multilabel_t mlbl1(200.0, 200.0, 40.0, lines, 0.0, text_anchor::middle);

int main() {

  // open file "test-label.html" to hold an SVG element:
  ofstream ofs("test-label.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.2);
      add_svg(lbl1, ofs);
      add_svg(lbl2, ofs);
      //add_svg(l80, ofs);
      string undropped("undropped");
      string   dropped("dropped");
      // add_label_to_svg(X,Y,TEXT,DEGREES,TEXT_ANCHOR,OUT,BASELINE_DROP)
      add_label_to_svg(50.0,50.0, undropped, 0.0, text_anchor::middle, ofs,  0.0);
      add_label_to_svg(50.0,50.0,   dropped, 0.0, text_anchor::middle, ofs, 30.0);
      add_label_to_svg(50.0,50.0,   dropped, 0.0, text_anchor::middle, ofs, 60.0);

      add_label_to_svg(80.0,80.0, undropped, 45.0, text_anchor::middle, ofs,  0.0);
      add_label_to_svg(80.0,80.0,   dropped, 45.0, text_anchor::middle, ofs, 30.0);
      add_label_to_svg(80.0,80.0,   dropped, 45.0, text_anchor::middle, ofs, 60.0);

      add_svg(mlbl1, ofs);

  // Keep adding components to the SVG file (handle='ofs')
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();



  return 0;
}
