#ifndef SCHEMATICS_TWOPORT_H
#define SCHEMATICS_TWOPORT_H

/* As a twoport<> is drawn as a long rectangle.
 * The baseline of a label inside a twoport
   must fall below is major axis so as to look right.
 * TWOPORT_BASELINE_K is a positive fractional number between 0 and 0.5,
   but it seems that 0.1 yields the best result.
 */
#ifndef TWOPORT_BASELINE_K
#define TWOPORT_BASELINE_K 0.1
#endif

#ifndef SCHEMATICS_LINE_H
#include "schematics.line.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif


#include <cmath> // for atan2(y,x), returning an angle in rads
#include <string>

/* Class twoport<FLOAT>
 * Draws a generic 2-port (electronics) component as a rectangle
 * Its constructor takes two points plus a relative half width argument to set 'rhw'
   (This third and last parameter defaults to 0.1.)
 * If you want to use absolute widths, call set_width(ABSOLUTE_WIDTH) after construction.
 */
template<typename FLOAT = double>
class twoport : protected twoline<FLOAT> {
  FLOAT half_width;
  FLOAT len;
public:
  std::string caption;
  typedef twoline<FLOAT> twoline_t;
  using twoline_t::get_xbeg, twoline_t::get_ybeg, twoline_t::get_xend, twoline_t::get_yend;
  using twoline_t::get_length, twoline_t::get_angle;
  using twoline_t::get_midx, twoline_t::get_midy;
  using twoline_t::add_circle_to_svg_unclosed, twoline_t::add_circle_to_svg;
  FLOAT get_ulx() const {return get_xbeg() - half_width * ( get_yend() - get_ybeg()) / len;};
  FLOAT get_uly() const {return get_ybeg() + half_width * ( get_xend() - get_xbeg()) / len;};
  FLOAT get_llx() const {return get_xbeg() + half_width * ( get_yend() - get_ybeg()) / len;};
  FLOAT get_lly() const {return get_ybeg() - half_width * ( get_xend() - get_xbeg()) / len;};

  FLOAT get_urx() const {return get_xend() - half_width * ( get_yend() - get_ybeg()) / len;};
  FLOAT get_ury() const {return get_yend() + half_width * ( get_xend() - get_xbeg()) / len;};
  FLOAT get_lrx() const {return get_xend() + half_width * ( get_yend() - get_ybeg()) / len;};
  FLOAT get_lry() const {return get_yend() - half_width * ( get_xend() - get_xbeg()) / len;};
  // Get the middle point of the baseline for printing caption:
  FLOAT get_midbaseline_x() const; // { return (get_xbeg() + get_xend() ) / 2;};
  FLOAT get_midbaseline_y() const; // { return (get_ybeg() + get_yend() ) / 2;};
  // Constructors:
  twoport() = default;
  twoport(float_t xb, float_t yb, float_t xe, float_t ye, std::string s, FLOAT w) :
  twoline_t(xb,yb,xe,ye), caption(s), half_width(w/2), len(get_length()) {};
}; // class twoport

template<typename FLOAT>
FLOAT twoport<FLOAT>::get_midbaseline_x() const {
  return get_midx() + TWOPORT_BASELINE_K * (get_ulx() - get_llx());
};
template<typename FLOAT>
FLOAT twoport<FLOAT>::get_midbaseline_y() const {
  return get_midy() + TWOPORT_BASELINE_K * (get_uly() - get_lly());
};

#ifndef SCHEMATICS_LABEL_H
#include "schematics.label.h"
#endif
template<typename FLOAT = double,
         typename POINT = point<FLOAT, 2, boost::geometry::cs::cartesian>,
         typename OUT = std::ostream>
void add_svg_unclosed(const twoport<FLOAT>& tp, OUT& o = std::cout) {
  if(!tp.caption.empty()) {
    /* add a text element to the SVG element
     * by means of add_svg(TEMP_LABEL),
     * where TEMP_LABEL is a temporary label constructed from 'tp'
     * Neither you nor I like to construct a temporary and throw it away at once, but
     * I have avoided duplicating code.
     */
    add_svg( label<FLOAT, char>(tp.get_midbaseline_x(),
                                tp.get_midbaseline_y(),
                                tp.caption,
                                angle_addressable<FLOAT>::rad_to_deg(tp.get_angle()),
                                label<FLOAT,char>::text_anchor::middle),
                                                                         o);
  } // if
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << "<polygon points=\"";
  o << tp.get_ulx() << ' ' << tp.get_uly() << ' ' << tp.get_llx() << ' ' << tp.get_lly() << ' ';
  o << tp.get_lrx() << ' ' << tp.get_lry() << ' ' << tp.get_urx() << ' ' << tp.get_ury() << '\"';
  //return o; // void return type
};

#endif
