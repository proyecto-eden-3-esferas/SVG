#ifndef SCHEMATICS_RECTANGLE_GLOBALS_H
#define SCHEMATICS_RECTANGLE_GLOBALS_H

#ifndef SCHEMATICS_RECTANGLE_H
#include "schematics.rectangle.h"
#endif

// Partial specialization of add_svg_unclosed(RECTANGLE&,OUT&)
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const rectangle<F>& rct, OUT& o = std::cout) {
  o << "<rect x=\"" << rct.x     << "\" y=\""      << rct.y << "\" ";
  o <<   "width=\"" << rct.width << "\" height=\"" << rct.height << "\"";
  //return o; // void return type
};

#endif
