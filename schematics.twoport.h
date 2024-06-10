#ifndef SCHEMATICS_TWOPORT_H
#define SCHEMATICS_TWOPORT_H

#ifndef SEGMENT_H
#include "segment.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

#ifndef SCHEMATICS_ROUND_H
#include "schematics.round.h"
#endif

#include <cmath> // for atan2(y,x), returning an angle in rads

/* Class twoport<FLOAT,POINT>
 * Draws a generic 2-port (electronics) component as a rectangle
 * Its constructor takes two points plus a relative half width argument to set 'rhw'
   (This third and last parameter defaults to 0.1.)
 * If you want to use absolute widths, call set_width(ABSOLUTE_WIDTH) after construction.
 */
template<typename FLOAT = double,
         typename POINT = point<FLOAT, 2, boost::geometry::cs::cartesian> >
class twoport : public segment<POINT> {
public:
  FLOAT rhw; // relative half-width
  typedef POINT point_t;
  typedef segment<POINT> segment_t;
  using segment_t::first, segment_t::second;
  // Get the coordinates of the initial ('first') and final ('second') points:
  FLOAT get_first_x() const {return get<0>(first);};
  FLOAT get_first_y() const {return get<1>(first);};
  FLOAT get_second_x() const {return get<0>(second);};
  FLOAT get_second_y() const {return get<1>(second);};
  // Get the x and y coordinates of each of the corners on the drawn rectangle:
  FLOAT get_ulx() const {return get<0>(first)  - rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_uly() const {return get<1>(first)  + rhw * ( get<0>(second) - get<0>(first));};
  FLOAT get_llx() const {return get<0>(first)  + rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_lly() const {return get<1>(first)  - rhw * ( get<0>(second) - get<0>(first));};
  FLOAT get_urx() const {return get<0>(second) - rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_ury() const {return get<1>(second) + rhw * ( get<0>(second) - get<0>(first));};
  FLOAT get_lrx() const {return get<0>(second) + rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_lry() const {return get<1>(second) - rhw * ( get<0>(second) - get<0>(first));};
  FLOAT get_length() const; // used by set_width(ABSOLUTE_WIDTH)
  FLOAT get_angle()  const; // provided for testing; is it useful at all?
  void set_width(FLOAT w) {rhw = 0.5 * (w / get_length());}; // 'w' is absolute, unlike 'rhw'
  // Constructors:
  twoport() = default;
  twoport(const POINT & p1, const POINT & p2, FLOAT relhw = 0.1) : segment_t(p1,p2), rhw(relhw) {};
};
template<typename FLOAT, typename POINT>
FLOAT twoport<FLOAT,POINT>::get_length() const {
  return sqrt( ( get<0>(second) - get<0>(first) ) *  ( get<0>(second) - get<0>(first) ) +
               ( get<1>(second) - get<1>(first) ) *  ( get<1>(second) - get<1>(first) ) );
};
template<typename FLOAT, typename POINT>
FLOAT twoport<FLOAT,POINT>::get_angle() const {
  return atan2(get<1>(second) - get<1>(first),
               get<0>(second) - get<0>(first));
};

template<typename FLOAT = double,
         typename POINT = point<FLOAT, 2, boost::geometry::cs::cartesian>,
         typename OUT = std::ostream>
OUT & add_svg_unclosed(const twoport<FLOAT,POINT>& tp, OUT& o = std::cout) {
  o << "<polygon points=\"";
  o << tp.get_ulx() << ' ' << tp.get_uly() << ' ' << tp.get_llx() << ' ' << tp.get_lly() << ' ';
  o << tp.get_lrx() << ' ' << tp.get_lry() << ' ' << tp.get_urx() << ' ' << tp.get_ury() << '\"';
  return o;
};

#endif
