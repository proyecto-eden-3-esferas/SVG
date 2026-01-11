#ifndef SVG_ARC_GLOBALS_H
#define SVG_ARC_GLOBALS_H

#ifndef SVG_ARC_H
#include "schematics.svg.arc.h"
#endif


template<typename F = double, typename OUT = std::ostream>
void add_to_svg_path(const svg_arc<F>& a, OUT& o = std::cout) {
  // skip moving: A bx by
  o << "A " << a.rx << ' ' << a.ry << "  ";
  o << a.x_axis_rotation << ' ' << std::noboolalpha << a.large_arc << ' ' << a.clockwise << "  ";
  o         << a.ex << ' ' << a.ey << ' '; // do not close but add space
  //return o; // void return type
};
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const svg_arc<F>& a, OUT& o = std::cout) {
  o << "<path d=\"";
  o << "M " << a.bx << ' ' << a.by << ' ';
  add_to_svg_path(a,o);
  o << '\"';
  //return o; // void return type
};

#endif
