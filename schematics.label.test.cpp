/* Test classes label<> and multilabel<>
 * A vector of pointers to svg_shape<> is declared,
 * Then member add_svg(OSTREAM,ATTRS) is called on each reference
 * The result is shown in an HTML file.
 */

#ifndef SCHEMATICS_LABEL_H
#include "schematics.label.h"
#endif

#include <fstream>
#include <vector>
using namespace std;

typedef       double float_type;
typedef svg_shape<float_type> svg_t;
typedef label_base<     float_type> label_base_t;
typedef label<     float_type> label_t;
typedef multilabel<float_type> multilabel_t;

label_t lbl1(100.0, 100.0, "original");
label_t lbl2(200.0, 100.0, "rising", -45,
             label_base_t::text_anchor::start
             );
multilabel_t::lines_t lines({"First line", "Second line", "Third line"});
multilabel_t mlbl1(200.0, 200.0, 40.0,
                   lines, 0.0//, //typename label_base_t::text_anchor::middle, 20.0
                  );

vector<svg_t*> vector_of_pointers{&lbl1, &lbl2, &mlbl1};

int main() {

  // open file "test-label.html" to hold an SVG element:
  ofstream ofs("test-label.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.2);
      for(const auto& p : vector_of_pointers)
        p->add_svg(ofs, default_svg_text_std_attrs);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();

  return 0;
}
