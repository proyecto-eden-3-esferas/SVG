#ifndef SCHEMATICS_LINE_H
#define SCHEMATICS_LINE_H

#include <vector>

#ifndef SCHEMATICS_ROUND_H
#include "schematics.angle.h"
#endif

#ifndef SVG_H
#include "svg.h"
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
class twoline {
public:
  typedef FLOAT float_t;
  typedef oneline<FLOAT> oneline_t;
  typedef twoline<FLOAT> twoline_t;
  oneline_t x,y;
  float_t get_xbeg() const {return x.get_beg();};
  float_t get_ybeg() const {return y.get_beg();};
  float_t get_xend() const {return x.get_end();};
  float_t get_yend() const {return y.get_end();};
  float_t get_x(float_t k) const {return x.get(k);};
  float_t get_y(float_t k) const {return y.get(k);};
  //
  float_t get_length() const;
  float_t get_angle()  const;
  float_t get_midx() const {return (get_xbeg() + get_xend() ) / 2;};
  float_t get_midy() const {return (get_ybeg() + get_yend() ) / 2;};
  //
  float_t xperim(float_t rela, // relative angle
                 float_t r,
                 float_t k = 0.5) const;
  float_t yperim(float_t rela, // relative angle
                 float_t r,
                 float_t k = 0.5) const;
  float_t xperim(float_t rela) const {return xperim(rela, get_length() / 2, 0.5);};
  float_t yperim(float_t rela) const {return yperim(rela, get_length() / 2, 0.5);};
  /* Members add_circle_to_svg_unclosed() and add_circle_to_svg()
   * insert a circle whose radius defaults to get_length() / 2 and
   * whose center defaults to (get_midx(), get_midy()).
   * This is useful for drawing voltage sources.
   */
  template <typename OUT = std::ostream>
  void add_circle_to_svg_unclosed(OUT& o, float_t r, float_t cx, float_t cy) const {
    o << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << r << "\" "; };
  template <typename OUT = std::ostream>
  void add_circle_to_svg_unclosed(OUT& o, float_t r) const {
    add_circle_to_svg_unclosed(o,            r, get_midx(), get_midy());};
  template <typename OUT = std::ostream>
  void add_circle_to_svg_unclosed(OUT& o) const {
    add_circle_to_svg_unclosed(o, get_length(), get_midx(), get_midy());};
  template <typename OUT = std::ostream>
  //
  void add_circle_to_svg(OUT& o, float_t r, float_t cx, float_t cy) const {
    add_circle_to_svg_unclosed(o,r,cx,cy);
    o << "/>";
  };
  template <typename OUT = std::ostream>
  void add_circle_to_svg(OUT& o, float_t r) const { add_circle_to_svg(o,r,get_midx(),get_midy()); };
  template <typename OUT = std::ostream>
  void add_circle_to_svg(OUT& o) const {add_circle_to_svg(o,get_length(), get_midx(), get_midy());};
  //
  twoline(float_t xb, float_t yb, float_t xe, float_t ye) : x(xb,xe), y(yb,ye) {};
};
// Implementation of twoline members:
template<typename FLOAT>
FLOAT twoline<FLOAT>::get_length() const {
  return angle_addressable<FLOAT>::sqrt
  ( ( get_xend() - get_xbeg() ) *  ( get_xend() - get_xbeg() ) +
    ( get_yend() - get_ybeg() ) *  ( get_yend() - get_ybeg() ) );
};
template<typename FLOAT>
FLOAT twoline<FLOAT>::get_angle() const {
  return angle_addressable<FLOAT>::atan2(get_yend() - get_ybeg(),
               get_xend() - get_xbeg());
};
template<typename FLOAT>
FLOAT twoline<FLOAT>::xperim(FLOAT rela, FLOAT r, FLOAT k) const {
  FLOAT a = rela + get_angle();
  FLOAT cx = get_x(k);
  return cx + r*angle_addressable<FLOAT>::cos(a);
};
template<typename FLOAT>
FLOAT twoline<FLOAT>::yperim(FLOAT rela, FLOAT r, FLOAT k) const {
  FLOAT a = rela + get_angle();
  FLOAT cy = get_y(k);
  return cy + r*angle_addressable<FLOAT>::sin(a);
};



/* Partial specializations of add_svg_unclosed(TWOLINE&,OUT) */
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const twoline<F>& cc, OUT& o = std::cout) {
  o << "<line x1=\"" << cc.x.get_beg() << "\" y1=\"" << cc.y.get_beg();
  o <<    "\" x2=\"" << cc.x.get_end() << "\" y2=\"" << cc.y.get_end() << "\"";
  //return o; // void return type
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
void add_svg_unclosed(const polyline<F,POINT,CONT>& pll, OUT& o = std::cout) {
  o << "<polyline points=\"";
  for(const auto & pt : pll.points)
    o << pt.first << ',' << pt.second << ' ';
  o << '\"';
  //return o; // void return type
};
template <typename F = double,
          typename POINT = std::pair<F,F>,
          typename CONT  = std::vector<POINT>,
          typename OUT = std::ostream>
void add_svg_unclosed(const polygon<F,POINT,CONT>& plg, OUT& o = std::cout) {
  o << "<polygon points=\"";
  for(const auto & pt : plg.points)
    o << pt.first << ',' << pt.second << ' ';
  o << '\"';
  //return o; // void return type
};

#endif
