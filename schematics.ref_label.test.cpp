/* Test classes label<> and multilabel<>
 * A vector of pointers to svg_shape<> is declared,
 * Then member add_svg(OSTREAM,ATTRS) is called on each reference
 * The result is shown in an HTML file.
 */

#ifndef SCHEMATICS_REF_LABEL_H
#include "schematics.ref_label.h"
#endif

#ifndef SCHEMATICS_REF_MULTILABEL_H
#include "schematics.ref_multilabel.h"
#endif

#include <fstream>
#include <vector>
using namespace std;

typedef    double      float_type;
typedef svg_shape<     float_type> svg_t;
typedef label_base<    float_type> label_base_t;
typedef ref_label<     float_type> ref_label_t;
typedef ref_multilabel<float_type> ref_multilabel_t;

float_type x1{100.0}, Y1{100.0}, deg1{  0};
float_type x2{200.0}, y2{100.0}, deg2{-45};
float_type x3{250.0}, y3{150.0}, r3{40.0}, deg3{ 10};
ref_label_t lbl1(x1, Y1, "original", deg1);
ref_label_t lbl2(x2, y2,   "rising", deg2,
                 label_base_t::text_anchor::start
            );
ref_multilabel_t::lines_t lines({"First line", "Second line", "Third line"});
ref_multilabel_t mlbl1(x3, y3, r3, lines, deg3,
                       label_base_t::text_anchor::middle,
                       20.0);
vector<svg_t*> vector_of_pointers{&lbl1,
                                  &lbl2,
                                  &mlbl1};

int main() {

  // open file "test-ref_label.html" to hold an SVG element:
  ofstream ofs("test-ref_label.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n";
  ofs << "<p>Testing objects of class <code>ref_label</code> and <code>ref_multilabel</code> through references. The radius of the inner circle is the <var>radius</var> parameter into the <code>ref_multilabel</code> constructor.</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.2);
      ofs << "<circle cx=\"" << x3 << "\" cy=\"" << y3 << "\" r=\"" << r3 + 15 << "\"/>\n";
      ofs << "<circle cx=\"" << x3 << "\" cy=\"" << y3 << "\" r=\"" << r3      << "\"/>\n";
      for(const auto& p : vector_of_pointers)
        p->add_svg(ofs, default_svg_text_std_attrs);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();

  return 0;
}
