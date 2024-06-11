#ifndef SCHEMATICS_TWOPORT_H
#define SCHEMATICS_TWOPORT_H

/* As a twoport<> is drawn as a long rectangle, the baseline of a label inside it
  must fall below is major axis so as to look right.
 * TWOPORT_BASELINE_K is a positive fractional number between 0 and 0.5,
   but it seems that 0.1 yields the best result.
 */
#ifndef TWOPORT_BASELINE_K
#define TWOPORT_BASELINE_K 0.1
#endif

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
#include <string>

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
  std::string caption;
  FLOAT rhw; // relative half-width
  typedef POINT point_t;
  typedef segment<POINT> segment_t;
  using segment_t::first, segment_t::second;
  // Get the coordinates of the initial ('first') and final ('second') points:
  inline FLOAT get_first_x() const {return get<0>(first);};
  inline FLOAT get_first_y() const {return get<1>(first);};
  inline FLOAT get_second_x() const {return get<0>(second);};
  inline FLOAT get_second_y() const {return get<1>(second);};
  // Get the x and y coordinates of each of the corners on the drawn rectangle:
  /*
  FLOAT get_ulx() const {return get<0>(first)  - rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_uly() const {return get<1>(first)  + rhw * ( get<0>(second) - get<0>(first));};
  FLOAT get_llx() const {return get<0>(first)  + rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_lly() const {return get<1>(first)  - rhw * ( get<0>(second) - get<0>(first));};
  FLOAT get_urx() const {return get<0>(second) - rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_ury() const {return get<1>(second) + rhw * ( get<0>(second) - get<0>(first));};
  FLOAT get_lrx() const {return get<0>(second) + rhw * ( get<1>(second) - get<1>(first));};
  FLOAT get_lry() const {return get<1>(second) - rhw * ( get<0>(second) - get<0>(first));};

  */
  inline FLOAT get_ulx() const {return get_first_x()  - rhw * ( get_second_y() - get_first_y());};
  inline FLOAT get_uly() const {return get_first_y()  + rhw * ( get_second_x() - get_first_x());};
  inline FLOAT get_llx() const {return get_first_x()  + rhw * ( get_second_y() - get_first_y());};
  inline FLOAT get_lly() const {return get_first_y()  - rhw * ( get_second_x() - get_first_x());};
  inline FLOAT get_urx() const {return get_second_x() - rhw * ( get_second_y() - get_first_y());};
  inline FLOAT get_ury() const {return get_second_y() + rhw * ( get_second_x() - get_first_x());};
  inline FLOAT get_lrx() const {return get_second_x() + rhw * ( get_second_y() - get_first_y());};
  inline FLOAT get_lry() const {return get_second_y() - rhw * ( get_second_x() - get_first_x());};

  FLOAT get_length() const; // used by set_width(ABSOLUTE_WIDTH)
  FLOAT get_angle()  const; // provided for testing; is it useful at all?
  void set_width(FLOAT w) {rhw = 0.5 * (w / get_length());}; // 'w' is absolute, unlike 'rhw'
  // Get the middle point of the baseline for printing caption:
  FLOAT get_midbaseline_x() const; // { return (get_first_x() + get_second_x() ) / 2;};
  FLOAT get_midbaseline_y() const; // { return (get_first_y() + get_second_y() ) / 2;};
  // Constructors:
  twoport() = default;
  twoport(const POINT & p1, const POINT & p2, std::string s = "", FLOAT relhw = 0.1)
  : segment_t(p1,p2), caption(s), rhw(relhw)  {};

};
template<typename FLOAT, typename POINT>
FLOAT twoport<FLOAT,POINT>::get_length() const {
  return sqrt( ( get_second_x() - get_first_x() ) *  ( get_second_x() - get_first_x() ) +
               ( get_second_y() - get_first_y() ) *  ( get_second_y() - get_first_y() ) );
};
template<typename FLOAT, typename POINT>
FLOAT twoport<FLOAT,POINT>::get_angle() const {
  return atan2(get_second_y() - get_first_y(),
               get_second_x() - get_first_x());
};
template<typename FLOAT, typename POINT>
FLOAT twoport<FLOAT,POINT>::get_midbaseline_x() const {
  return (get_first_x() + get_second_x() ) / 2
         + TWOPORT_BASELINE_K * (get_ulx() - get_llx());;

};
template<typename FLOAT, typename POINT>
FLOAT twoport<FLOAT,POINT>::get_midbaseline_y() const {
  return (get_first_y() + get_second_y() ) / 2
         + TWOPORT_BASELINE_K * (get_uly() - get_lly());

};


template<typename FLOAT = double,
         typename POINT = point<FLOAT, 2, boost::geometry::cs::cartesian>,
         typename OUT = std::ostream>
OUT & add_svg_unclosed(const twoport<FLOAT,POINT>& tp, OUT& o = std::cout) {
  if(!tp.caption.empty()) {
    //close_standalone_tag(o);
    //o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
    o << "<text x=\"" << tp.get_midbaseline_x() << "\" y=\"" << tp.get_midbaseline_y() << "\" ";
    o << "style=\"text-anchor: middle\" ";//fill=\"black\"
    o << "transform=\"rotate(" << angle_addressable<FLOAT>::rad_to_deg(tp.get_angle()) << ' ';
    o << tp.get_midbaseline_x() << ',' << tp.get_midbaseline_y() << ")\">";
    o << tp.caption << "</text>\n" << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  }
  o << "<polygon points=\"";
  o << tp.get_ulx() << ' ' << tp.get_uly() << ' ' << tp.get_llx() << ' ' << tp.get_lly() << ' ';
  o << tp.get_lrx() << ' ' << tp.get_lry() << ' ' << tp.get_urx() << ' ' << tp.get_ury() << '\"';
  return o;
};

#endif
