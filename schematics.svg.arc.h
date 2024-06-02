#ifndef SCHEMATICS_SVG_H
#include "schematics.svg.h"
#endif

/* TODOs:
 (1) arcs by (rx,ry, r, beg_angle,end_angle)
     output a <path d="M rx ry a ..." />
 *
 *
 */
template<typename F = double>
class svg_arc {
public:
  F bx, by;
  F rx, ry; // radii
  F ex, ey; // end point
  bool clockwise;           // 1 means clockwise and 0 means counter-clockwise.
  bool x_axis_rotation; // rotates the ellipse around its x, or horizontal, axis.
                        // to tilt an ellipse, just code an <ellipse/>
  bool large_arc;
  // constructor
  svg_arc(F _bx, F _by, F _rx, F _ry, F _ex, F _ey,
          bool swp = false, bool xar=false, bool la=false) :
          bx(_bx), by(_by), rx(_rx), ry(_ry), ex(_ex), ey(_ey), clockwise(swp), x_axis_rotation(xar), large_arc(la)
    {};
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_to_svg_path(const svg_arc<F>& a, OUT& o = std::cout) {
  // skip moving: A bx by
  o << "A " << a.rx << ' ' << a.ry << "  ";
  o << a.x_axis_rotation << ' ' << std::noboolalpha << a.large_arc << ' ' << a.clockwise << "  ";
  o         << a.ex << ' ' << a.ey << ' '; // do not close but add space
  return o;
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const svg_arc<F>& a, OUT& o = std::cout) {
  o << "<path d=\"";
  o << "M " << a.bx << ' ' << a.by << ' ';
  /*
  o << "A " << a.rx << ' ' << a.ry << ' ';
  o << std::noboolalpha << a.x_axis_rotation << ' ' << a.large_arc << ' ' << a.clockwise << ' ';
  o         << a.ex << ' ' << a.ey << '\"';
  */
  add_to_svg_path(a,o);
  o << '\"';
  return o;

};
