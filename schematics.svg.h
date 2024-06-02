#ifndef SCHEMATICS_SVG_H
#define SCHEMATICS_SVG_H

#ifndef SCHEMATICS_H
#include "schematics.h"
#endif

#ifndef SCHEMATICS_ROUND_H
#include "schematics.round.h"
#endif

/* SVG Helping Functions
 * Remember to define attribute 'stroke' (as black or some non-white colour)
 * in the svg opening tag, or in each svg shape
 * Sometimes you want to define fill to, possibly inside specific svg shapes
 * You rarely want to define <svg stroke="black" fill="black"
 * as the filling will hide a lot of detail
 */

#include <iostream>
#include <string>

// Define an indentation string, typically 2 spaces ("  ")
#ifndef SVG_FILE_INDENT_STR
#define SVG_FILE_INDENT_STR "  "
#endif

/* Open and close an SVG element
 * open_svg(OUT&, width, height, STROKECOLOUR, FILLCOLOUR, FILLOPACITY)
   sets enough attributes to show the contained shapes suitably.
 * Both functions output indentation string (SVG_FILE_INDENT_STR) twice
 */
template<typename F = double, typename OUT = std::ostream>
OUT& open_svg(OUT& o, F w = 200.0, F h = 200.0,
                                   const std::string& strk = "black",
                                   const std::string&  fll = "gray",
                                   F                   fllopct = 0.5) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << "<svg width=\"" << w << "\" height=\"" << h;
  o << "\" stroke=\"" << strk << "\" fill=\"" << fll << "\" fill-opacity=\"" << fllopct << "\">\n";
  return o;
}
template<typename OUT = std::ostream>
OUT& close_svg(OUT& o) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << "</svg>\n";
  return o;
};

/* 'add_svg_unclosed(SVG_ELEM&, OUT&)' leaves the tag add_svg_unclosed
   so that further attributes may be added.
 * Remember to close tag with 'close_standalone_tag(OUT&)'
   after adding those new attributes.
 * If you do not need to add further attributes, use 'add_svg(T&,OUT&)'
 * Remember to add 'close_standalone_tag(OUT&)'
 */
template<typename OUT = std::ostream>
OUT & close_standalone_tag(OUT& o = std::cout) {o << "/>\n"; return o;};
template<typename T, typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const T& t, OUT& o = std::cout) {o << "UNDEFINED WHATEVER!!!\n"; return o;};
template<typename T, typename F = double, typename OUT = std::ostream>
OUT & add_svg(const T& t, OUT& o = std::cout) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_svg_unclosed(t,o);
  return close_standalone_tag(o);
};

/* Partial specializations of add_svg_unclosed(SHAPE,OUT)
 */

#ifdef SCHEMATICS_ROUND_H
// First, specializations for angle-addressable components in "schematics.round.h"
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const circular<F>& cc, OUT& o = std::cout) {
  o << "<circle cx=\"" << cc.cx << "\" cy=\"" << cc.cy << "\" r=\"" << cc.r << "\"";
  return o;
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const elliptical<F>& cc, OUT& o = std::cout) {
  o << "<ellipse cx=\"" << cc.cx << "\" cy=\"" << cc.cy << "\" rx=\"" << cc.rx << "\" ry=\"" << cc.ry << "\"";
  return o;
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const rectangular<F>& rct, OUT& o = std::cout) {
  o << "<rect x=\"" << rct.cx - rct.rx <<      "\" y=\"" << rct.cy - rct.ry << "\" ";
  o <<   "width=\"" <<        2*rct.rx << "\" height=\"" <<        2*rct.ry << "\"";
  return o;
};
#endif


/* Then specializations for rectangle<>, polyline<> and polygon<>.
 * Specializations of add_svg_unclosed(POLYLINE&) and add_svg_unclosed(POLYGON&)
 * are analogous.
 */
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const rectangle<F>& rct, OUT& o = std::cout) {
  o << "<rect x=\"" << rct.x     << "\" y=\""      << rct.y << "\" ";
  o <<   "width=\"" << rct.width << "\" height=\"" << rct.height << "\"";
  return o;
};
template <typename F = double,
          typename POINT = std::pair<F,F>,
          typename CONT  = std::vector<POINT>,
          typename OUT = std::ostream>
OUT & add_svg_unclosed(const polyline<F,POINT,CONT>& pll, OUT& o = std::cout) {
  o << "<polyline points=\"";
  for(const auto & pt : pll.points)
    o << pt.first << ',' << pt.second << ' ';
  o << '\"';
  return o;
};
template <typename F = double,
          typename POINT = std::pair<F,F>,
          typename CONT  = std::vector<POINT>,
          typename OUT = std::ostream>
OUT & add_svg_unclosed(const polygon<F,POINT,CONT>& pll, OUT& o = std::cout) {
  o << "<polygon points=\"";
  for(const auto & pt : pll.points)
    o << pt.first << ',' << pt.second << ' ';
  o << '\"';
  return o;
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const twoline<F>& cc, OUT& o = std::cout) {
  o << "<line x1=\"" << cc.x.get_beg() << "\" y1=\"" << cc.y.get_beg();
  o <<    "\" x2=\"" << cc.x.get_end() << "\" y2=\"" << cc.y.get_end() << "\"";
  return o;
};

#ifdef SCHEMATICS_IC_H
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const ic<F>& i, OUT& o = std::cout) {
  o << "<rect x=\"" << i.get_x()     << "\" y=\""      << i.get_y() << "\" ";
  o <<   "width=\"" << i.get_width() << "\" height=\"" << i.get_height() << "\"";
  return o;
};
#endif

#endif
