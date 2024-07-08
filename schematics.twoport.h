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

#ifndef SCHEMATICS_LINE_H
#include "schematics.line.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

#ifndef SCHEMATICS_ROUND_H
#include "schematics.angle.h"
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
class twoport : public twoline<FLOAT> {
public:
  std::string caption;
  FLOAT rhw; // relative half-width
  typedef twoline<FLOAT> twoline_t;
  using twoline_t::get_xbeg, twoline_t::get_ybeg, twoline_t::get_xend, twoline_t::get_yend;
  inline FLOAT get_ulx() const {return get_xbeg() - rhw * ( get_yend() - get_ybeg());};
  inline FLOAT get_uly() const {return get_ybeg() + rhw * ( get_xend() - get_xbeg());};
  inline FLOAT get_llx() const {return get_xbeg() + rhw * ( get_yend() - get_ybeg());};
  inline FLOAT get_lly() const {return get_ybeg() - rhw * ( get_xend() - get_xbeg());};
  inline FLOAT get_urx() const {return get_xend() - rhw * ( get_yend() - get_ybeg());};
  inline FLOAT get_ury() const {return get_yend() + rhw * ( get_xend() - get_xbeg());};
  inline FLOAT get_lrx() const {return get_xend() + rhw * ( get_yend() - get_ybeg());};
  inline FLOAT get_lry() const {return get_yend() - rhw * ( get_xend() - get_xbeg());};

  FLOAT get_length() const; // used by set_width(ABSOLUTE_WIDTH)
  FLOAT get_angle()  const; // provided for testing; is it useful at all?
  void set_width(FLOAT w) {rhw = 0.5 * (w / get_length());}; // 'w' is absolute, unlike 'rhw'
  // Get the middle point of the baseline for printing caption:
  FLOAT get_midbaseline_x() const; // { return (get_xbeg() + get_xend() ) / 2;};
  FLOAT get_midbaseline_y() const; // { return (get_ybeg() + get_yend() ) / 2;};
  // Constructors:
  twoport() = default;
  twoport(float_t xb, float_t yb, float_t xe, float_t ye, std::string s = "", FLOAT relhw = 0.1) :
  twoline_t(xb,yb,xe,ye), caption(s), rhw(relhw) {};

};
template<typename FLOAT>
FLOAT twoport<FLOAT>::get_length() const {
  return sqrt( ( get_xend() - get_xbeg() ) *  ( get_xend() - get_xbeg() ) +
               ( get_yend() - get_ybeg() ) *  ( get_yend() - get_ybeg() ) );
};
template<typename FLOAT>
FLOAT twoport<FLOAT>::get_angle() const {
  return atan2(get_yend() - get_ybeg(),
               get_xend() - get_xbeg());
};
template<typename FLOAT>
FLOAT twoport<FLOAT>::get_midbaseline_x() const {
  return (get_xbeg() + get_xend() ) / 2
         + TWOPORT_BASELINE_K * (get_ulx() - get_llx());;

};
template<typename FLOAT>
FLOAT twoport<FLOAT>::get_midbaseline_y() const {
  return (get_ybeg() + get_yend() ) / 2
         + TWOPORT_BASELINE_K * (get_uly() - get_lly());

};

#ifndef SCHEMATICS_LABEL_H
#include "schematics.label.h"
#endif
template<typename FLOAT = double,
         typename POINT = point<FLOAT, 2, boost::geometry::cs::cartesian>,
         typename OUT = std::ostream>
OUT & add_svg_unclosed(const twoport<FLOAT>& tp, OUT& o = std::cout) {
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
    /*
    o << "<text x=\"" << tp.get_midbaseline_x() << "\" y=\"" << tp.get_midbaseline_y() << "\" ";
    o << "style=\"text-anchor: middle\" ";//fill=\"black\"
    o << "transform=\"rotate(" << angle_addressable<FLOAT>::rad_to_deg(tp.get_angle()) << ' ';
    o << tp.get_midbaseline_x() << ',' << tp.get_midbaseline_y() << ")\">";
    o << tp.caption << "</text>\n" << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
    */
  } // if
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << "<polygon points=\"";
  o << tp.get_ulx() << ' ' << tp.get_uly() << ' ' << tp.get_llx() << ' ' << tp.get_lly() << ' ';
  o << tp.get_lrx() << ' ' << tp.get_lry() << ' ' << tp.get_urx() << ' ' << tp.get_ury() << '\"';
  return o;
};

#endif
