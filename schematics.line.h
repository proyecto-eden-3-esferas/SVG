#ifndef SCHEMATICS_LINE_H
#define SCHEMATICS_LINE_H

#include <vector>

#ifndef SCHEMATICS_ROUND_H
#include "schematics.angle.h"
#endif

/* Classes oneline<FLOAT> and twoline<FLOAT> define
   one- and two-dimensional "lines"
 * They make use of static oneline::interpolate(BEG,END,K)
   to interpolate between beginning and end by a factor k
 * Class oneline<>, a one-dimensional line,
   holds its beginning and ending as single floats,
   and has a  static FLOAT interpolate(BEG,END, K) member
 * Currently, I don't know what these classes would be good for.
 */
template <typename FLOAT=double>
class oneline {
public:
  typedef FLOAT float_t;
  static float_t interpolate(float_t b, float_t e, float_t k) {
    return b*(1 - k) + e*k;
  };
  float_t get_beg() const {return beg;};
  float_t get_end() const {return end;};
  const float_t beg, end;
  float_t get(float_t k) const {return interpolate(beg,end,k);};
  oneline(float_t b, float_t e) : beg(b), end(e) {};
};
/* class twoline<>
   holds two oneline's (named 'x' and 'y')
   and represents a line in 2-space
 * An analogous 3-D threeline might be written
 */
template <typename FLOAT = double>
struct twoline {
public:
  typedef FLOAT float_t;
  typedef oneline<FLOAT> oneline_t;
  oneline_t x,y;
  float_t get_xbeg() const {return x.get_beg();};
  float_t get_ybeg() const {return y.get_beg();};
  float_t get_xend() const {return x.get_end();};
  float_t get_yend() const {return y.get_end();};
  float_t get_x(float_t k) const {return x.get(k);};
  float_t get_y(float_t k) const {return y.get(k);};
  //
  FLOAT get_length() const;
  FLOAT get_angle()  const;
  FLOAT get_midx() const {return (get_xbeg() + get_xend() ) / 2;};
  FLOAT get_midy() const {return (get_ybeg() + get_yend() ) / 2;};
  //
  twoline(float_t xb, float_t yb, float_t xe, float_t ye) : x(xb,xe), y(yb,ye) {};
};
// Implementation of twoline members:
template<typename FLOAT>
FLOAT twoline<FLOAT>::get_length() const {
  return sqrt( ( get_xend() - get_xbeg() ) *  ( get_xend() - get_xbeg() ) +
               ( get_yend() - get_ybeg() ) *  ( get_yend() - get_ybeg() ) );
};
template<typename FLOAT>
FLOAT twoline<FLOAT>::get_angle() const {
  return atan2(get_yend() - get_ybeg(),
               get_xend() - get_xbeg());
};

#ifndef SVG_H
#include "svg.h"
#endif
/* Partial specializations of add_svg_unclosed(TWOLINE&,OUT) */
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const twoline<F>& cc, OUT& o = std::cout) {
  o << "<line x1=\"" << cc.x.get_beg() << "\" y1=\"" << cc.y.get_beg();
  o <<    "\" x2=\"" << cc.x.get_end() << "\" y2=\"" << cc.y.get_end() << "\"";
  return o;
};

/* classes polyline and polygon
 * class polyline is a line made up of straight segments
 * Points are held in a container supporting push/emplace_back()
 * class polygon  is defined analogously:
 * (just substitute 'polygon' for 'polyline')
 */
template <typename FLOAT = double,
          typename POINT = std::pair<FLOAT,FLOAT>,
          typename CONT  = std::vector<POINT> >
class polyline {
  public:
  typedef FLOAT float_t;
  typedef POINT point_t;
  typedef polyline<FLOAT,POINT,CONT> polyline_t;
  CONT points;
  void push_back(const POINT& p)  {points.push_back(p);};
  void push_back(FLOAT x, FLOAT y){points.emplace_back(x,y);};
  // constructors:
  polyline() = default;
  polyline(const polyline_t& pl) : points(pl.points) {};
  template <typename ITERATOR>
  polyline(const ITERATOR& b, const ITERATOR& e) : points(b,e) {};
};
template <typename FLOAT = double,
          typename POINT = std::pair<FLOAT,FLOAT>,
          typename CONT  = std::vector<POINT> >
class polygon {
  public:
  typedef FLOAT float_t;
  typedef POINT point_t;
  typedef polygon<FLOAT,POINT,CONT> polygon_t;
  CONT points;
  void push_back(const POINT& p)  {points.push_back(p);};
  void push_back(FLOAT x, FLOAT y){points.emplace_back(x,y);};
  polygon() = default;
  polygon(const polygon_t& pl) : points(pl.points) {};
  template <typename ITERATOR>
  polygon(const ITERATOR& b, const ITERATOR& e) : points(b,e) {};
};
/* Partial specializations for polyline<> and polygon<>.
 * Specializations of add_svg_unclosed(POLYLINE&) and add_svg_unclosed(POLYGON&)
 * are analogous.
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
OUT & add_svg_unclosed(const polygon<F,POINT,CONT>& plg, OUT& o = std::cout) {
  o << "<polygon points=\"";
  for(const auto & pt : plg.points)
    o << pt.first << ',' << pt.second << ' ';
  o << '\"';
  return o;
};


#endif
