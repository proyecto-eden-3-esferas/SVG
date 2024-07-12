#ifndef SCHEMATICS_RECTANGLE_H
#define SCHEMATICS_RECTANGLE_H

#include <iostream> // for std::size_t

/* rectangle<> has location (x,y) = upper left-hand corner
   and is very much modelled on svg::rect
 * It has sides parallel to X and Y axes.
 * Its child 'block' is meant to be used in block diagrammes
 */
template <typename FLOAT = double>
class rectangle {
public:
  typedef FLOAT float_t;
  float_t width, height;
  float_t x, y; // coordinates of upper left-hand corner
  rectangle(float_t w, float_t h, float_t lft=0, float_t uppr=0) : width(w), height(h), x(lft), y(uppr) {};
};

// Partial specialization of add_svg_unclosed(RECTANGLE&,OUT&)
#ifndef SVG_H
#include "svg.h"
#endif
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const rectangle<F>& rct, OUT& o = std::cout) {
  o << "<rect x=\"" << rct.x     << "\" y=\""      << rct.y << "\" ";
  o <<   "width=\"" << rct.width << "\" height=\"" << rct.height << "\"";
  //return o; // void return type
};

#endif
