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


template<typename FLOAT = double,
         typename POINT = point<FLOAT, 2, boost::geometry::cs::cartesian> >
class twoport : public segment<POINT> {
public:
  FLOAT rhw; // relative half-width
  typedef POINT point_t;
  typedef segment<POINT> segment_t;
  using segment_t::first, segment_t::second;
  FLOAT get_ulx() const {return get<0>(first)  - rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_uly() const {return get<1>(first)  + rhw * ( get<0>(second) - get<0>(first));};
  FLOAT get_llx() const {return get<0>(first)  + rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_lly() const {return get<1>(first)  - rhw * ( get<0>(second) - get<0>(first));};
  FLOAT get_urx() const {return get<0>(second) - rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_ury() const {return get<1>(second) + rhw * ( get<0>(second) - get<0>(first));};
  FLOAT get_lrx() const {return get<0>(second) + rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_lry() const {return get<1>(second) - rhw * ( get<0>(second) - get<0>(first));};
  void set_width(FLOAT w);
  // Constructors:
  twoport() = default;
  twoport(POINT const & p1, POINT const & p2, FLOAT relhw) : segment_t(p1,p2), rhw(relhw) {};
};
template<typename FLOAT, typename POINT>
void twoport<FLOAT,POINT>::set_width(FLOAT w) {
  // calculate the length of port axis:
  FLOAT len = sqrt( ( get<0>(second) - get<0>(first) ) *  ( get<0>(second) - get<0>(first) ) +
                    ( get<1>(second) - get<1>(first) ) *  ( get<1>(second) - get<1>(first) ) );
  rhw = 0.5 * (w / len);
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
