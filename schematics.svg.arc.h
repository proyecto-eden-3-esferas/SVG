#ifndef SVG_ARC_H
#define SVG_ARC_H

#ifndef SVG_H
#include "svg.h"
#endif

/*
 * TODOs:
 [ ] class svg_rarc<F> for a relative arc
 [ ] svg_rarc(const svg_arc<F>& sa);
 */
template<typename F = double>
class svg_arc : public svg_shape<F> {
public:
  F bx, by; // begining point
  F rx, ry; // radii
  F ex, ey; // end point
  bool clockwise;       // 1 means clockwise and 0 means counter-clockwise.
  bool x_axis_rotation; // rotates the ellipse around its x, or horizontal, axis.
                        // to tilt an ellipse, just code an <ellipse/>
  bool large_arc;
  enum policy_enum {move, line, none}; //
  enum policy_enum policy;
  //
  void move_in_svg_path(std::ostream& o = std::cout) const {o << "M " << bx << ' ' << by << ' ';};
  void add_to_svg_path( std::ostream& o = std::cout) const;
  void add_svg_unclosed(std::ostream& o = std::cout, const std::string& attrs = "") const override;
  // constructor
  svg_arc(F _bx, F _by, F _rx, F _ry, F _ex, F _ey,
          bool swp = false, bool xar=false, bool la=false, policy_enum p = move) :
          bx(_bx), by(_by), rx(_rx), ry(_ry), ex(_ex), ey(_ey),
          clockwise(swp), x_axis_rotation(xar), large_arc(la),
          policy(p)
    {};
};
template<typename F>
void svg_arc<F>::add_to_svg_path( std::ostream& o) const {
  // skip moving: A bx by
  o << "A " << rx << ' ' << ry << "  ";
  o << x_axis_rotation << ' ' << std::noboolalpha << large_arc << ' ' << clockwise << "  ";
  o         << ex << ' ' << ey << ' '; // do not close but add space
};

template<typename F>
void svg_arc<F>::add_svg_unclosed(std::ostream& o, const std::string& attrs) const {
  o << "<path d=\"";
  switch (policy) {
    case move: o << "M " << bx << ' ' << by << ' ';
               break;
    case line: o << "L " << bx << ' ' << by << ' ';
               break;
    default:   break;
  }

  add_to_svg_path(o);
  o << '\"';
};

#endif

