#ifndef SCHEMATICS_SVG_H
#define SCHEMATICS_SVG_H

#ifndef SCHEMATICS_H
#include "schematics.h"
#endif

/* 'add_svg_unclosed(SVG_ELEM&, OUT&) leaves the tag add_svg_unclosed
 * so that futher attributes may be added.
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
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const circular_component<F>& cc, OUT& o = std::cout) {
  o << "<circle cx=\"" << cc.cx << "\" cy=\"" << cc.cy << "\" r=\"" << cc.r << "\"";
  return o;
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const elliptical_component<F>& cc, OUT& o = std::cout) {
  o << "<ellipse cx=\"" << cc.cx << "\" cy=\"" << cc.cy << "\" rx=\"" << cc.rx << "\" ry=\"" << cc.ry << "\"";
  return o;
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const rectangular_component<F>& rct, OUT& o = std::cout) {
  o << "<rect x=\"" << rct.cx - rct.rx <<      "\" y=\"" << rct.cy - rct.ry << "\" ";
  o <<   "width=\"" <<        2*rct.rx << "\" height=\"" <<        2*rct.ry << "\"";
  return o;
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const rectangle<F>& rct, OUT& o = std::cout) {
  o << "<rect x=\"" << rct.x     << "\" y=\""      << rct.y << "\" ";
  o <<   "width=\"" << rct.width << "\" height=\"" << rct.height << "\"";
  return o;
};
/*  specializations of add_svg_unclosed(POLYLINE&) and add_svg_unclosed(POLYGONE&)
 *  are analogous.
 */
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
OUT & add_svg_unclosed(const polygone<F,POINT,CONT>& pll, OUT& o = std::cout) {
  o << "<polygon points=\"";
  for(const auto & pt : pll.points)
    o << pt.first << ',' << pt.second << ' ';
  o << '\"';
  return o;
};

template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const ic<F>& i, OUT& o = std::cout) {
  o << "<rect x=\"" << i.get_x     << "\" y=\""      << i.get_y << "\" ";
  o <<   "width=\"" << i.get_width << "\" height=\"" << i.get_height << "\"";
  return o;
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const twoline<F>& cc, OUT& o = std::cout) {
  o << "<line x1=\"" << cc.x.get_beg() << "\" y1=\"" << cc.y.get_beg();
  o <<    "\" x2=\"" << cc.x.get_end() << "\" y2=\"" << cc.y.get_end() << "\"";
  return o;
};

#endif
