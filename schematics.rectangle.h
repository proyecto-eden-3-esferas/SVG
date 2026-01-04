#ifndef SCHEMATICS_RECTANGLE_H
#define SCHEMATICS_RECTANGLE_H

#include <iostream> // for std::size_t

#ifndef SVG_H
#include "svg.h"
#endif

/* rectangle<> has location (x,y) = upper left-hand corner
   and is very much modelled on svg::rect
 * It has sides parallel to X and Y axes.
 * Its child 'block' is meant to be used in block diagrammes
 */
template <typename FLOAT = double>
class rectangle : public svg_shape<FLOAT> {
public:
  typedef FLOAT float_t;
  float_t width, height;
  float_t x, y; // coordinates of upper left-hand corner
  //
  void add_svg_unclosed(   std::ostream& o = std::cout, const std::string& attrs = "") const override;
  rectangle(float_t w, float_t h, float_t lft=0, float_t uppr=0) : width(w), height(h), x(lft), y(uppr) {};
};
template <typename FLOAT>
void rectangle<FLOAT>::add_svg_unclosed(   std::ostream& o, const std::string& attrs) const {
  o << "<rect x=\"" << x     << "\" y=\""      << y << "\" ";
  o <<   "width=\"" << width << "\" height=\"" << height << "\"";
  if(attrs.length() > 0)
    o << ' ' << attrs;
};

#endif
