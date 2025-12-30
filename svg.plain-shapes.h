#ifndef SVG_PLAIN_SHAPES_H
#define SVG_PLAIN_SHAPES_H

/* Printing shapes to an outstream (default std::ostream)
 * Originally writing for mp_spline<> in "mp_spline.*"
 * General format:
     add_SHAPE_to_svg(OSTREAM&, PARAMS, NUM_DECIMALS=2, ATTR="")
 * ATTR is a string that gets included in the (stand-alone) tag
   and it just comprises attributes
 *
 * Some of the shapes:
   - circle
   - line
   etc.
 */

#include <iomanip> // for std::setprecision(INT)
#include <iostream>
#include <string>

template <typename F = double, typename OUT = std::ostream>
void add_circle_to_svg(OUT& o, F x, F y, F r, /*int decimals = 2, */const std::string& attr="") {
  o << "<circle ";
  if(attr.length() > 0)
    o << attr << ' ';
  //o << std::fixed << std::setprecision(decimals);
  o << "cx=\"" << x << "\" cy=\"" << y <<  "\" r=\"" << r <<"\"/>\n";
};
template <typename F = double, typename OUT = std::ostream>
void add_line_to_svg(OUT& o, F x1, F y1, F x2, F y2, /*int decimals = 2, */const std::string& attr="") {
  o << "<line ";
  if(attr.length() > 0)
    o << attr << ' ';
  //o << std::fixed << std::setprecision(decimals);
  o <<    "x1=\"" << x1 << "\" y1=\"" << y1;
  o << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\"/>\n";
};

#endif
