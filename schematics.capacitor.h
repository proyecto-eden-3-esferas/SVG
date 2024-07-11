#ifndef SCHEMATICS_CAPACITOR_H
#define SCHEMATICS_CAPACITOR_H

/* As a capacitor<> is drawn as a ...
 * TWOPORT_BASELINE_K is a positive fractional number between 0 and 0.5,
   but it seems that 0.1 yields the best result.
 */


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

/* Class capacitor<FLOAT>
 * Draws a 2-port (electronics) capacitor as a gapped lined and 2 plates (-||-)
 * Its constructor takes two points, a caption, a plate width argument...
   (This third and last parameter defaults to 0.1.)
 * If you want to use absolute widths, call set_width(ABSOLUTE_WIDTH) after construction.
 */
template<typename FLOAT = double>
class capacitor : public twoline<FLOAT> {
public:
  std::string caption;
  FLOAT half_width; // half the plate dimension (sort of a radius)
  FLOAT half_sep;   // half the separation between plates
  FLOAT len;
  FLOAT angle;
  typedef twoline<FLOAT> twoline_t;
  using twoline_t::get_xbeg, twoline_t::get_ybeg, twoline_t::get_xend, twoline_t::get_yend;
  using twoline_t::get_length, twoline_t::get_angle;
  using twoline_t::get_midx, twoline_t::get_midy;
  //
  FLOAT get_midx1() const {return get_midx() - half_sep * cos(angle);};
  FLOAT get_midy1() const {return get_midx() - half_sep * sin(angle);};
  FLOAT get_midx2() const {return get_midx() + half_sep * cos(angle);};
  FLOAT get_midy2() const {return get_midx() + half_sep * sin(angle);};
  //
  template <typename OUT = std::ostream>
  OUT& add_label_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  OUT& add_line1_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  OUT& add_line2_to_svg(OUT& o) const;
  //
  template <typename OUT = std::ostream>
  OUT& add_perp1_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  OUT& add_perp2_to_svg(OUT& o) const;
  // Constructors:
  capacitor() = default;
  capacitor(float_t xb, float_t yb, float_t xe, float_t ye, std::string s, FLOAT w, FLOAT sp) :
  twoline_t(xb,yb,xe,ye), caption(s), half_width(w/2), half_sep(sp/2), len(get_length()), angle(get_angle()) {};
};
// Implementation of capacitor<> member functions:
template <typename FLOAT>
template <typename OUT>
OUT& capacitor<FLOAT>::add_label_to_svg(OUT& o) const {
  return
  add_svg( label<FLOAT, char>(get_midx(),
                              get_midy(),
                              caption,
                              angle_addressable<FLOAT>::rad_to_deg(get_angle()),
                              label<FLOAT,char>::text_anchor::middle),
                                                                        o);
};
//
template <typename FLOAT>
template <typename OUT>
OUT& capacitor<FLOAT>::add_line1_to_svg(OUT& o) const {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << "<line ";
  o << "x1=\"" << get_xbeg()  << "\" y1=\"" << get_ybeg() << "\" ";
  o << "x2=\"" << get_midx1() << "\" y2=\"" << get_midy1() << "\"/>\n";
  return o;
};
template <typename FLOAT>
template <typename OUT>
OUT& capacitor<FLOAT>::add_line2_to_svg(OUT& o) const {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << "<line ";
  o << "x1=\"" << get_midx2()  << "\" y1=\"" << get_midy2() << "\" ";
  o << "x2=\"" << get_xend() << "\" y2=\"" << get_yend() << "\"/>";
  return o;
};
//
template <typename FLOAT>
template <typename OUT>
OUT& capacitor<FLOAT>::add_perp1_to_svg(OUT& o) const {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << "<line ";
  o << "x1=\"" << get_midx1() + half_width*sin(angle) << "\" y1=\"" << get_midy1() - half_width*cos(angle) << "\" ";
  o << "x2=\"" << get_midx1() - half_width*sin(angle) << "\" y2=\"" << get_midy1() + half_width*cos(angle) << "\"/>\n";
  return o;
};
template <typename FLOAT>
template <typename OUT>
OUT& capacitor<FLOAT>::add_perp2_to_svg(OUT& o) const {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << "<line ";
  o << "x1=\"" << get_midx2() + half_width*sin(angle) << "\" y1=\"" << get_midy2() - half_width*cos(angle) << "\" ";
  o << "x2=\"" << get_midx2() - half_width*sin(angle) << "\" y2=\"" << get_midy2() + half_width*cos(angle) << "\"/>\n";
  return o;
};


#ifndef SCHEMATICS_LABEL_H
#include "schematics.label.h"
#endif

template<typename F = double, typename OUT = std::ostream>
OUT & add_svg(const capacitor<F>& cp, OUT& o = std::cout) {
  cp.add_line1_to_svg(o);
  cp.add_line2_to_svg(o);
  cp.add_perp1_to_svg(o);
  cp.add_perp2_to_svg(o);
  cp.add_label_to_svg(o);
  return o;
};


#endif
