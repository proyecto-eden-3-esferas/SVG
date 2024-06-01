/* File "schematics.cpp"
 * Defines several subhierarchies:
 * (1) component<> and its children:
 *     circular_component, elliptical_component, and rectangular_component
 *     (location on perimeter by angle)
 * (2) 'oneline' (1-dimensional line) and 'twoline'
 *     Actually, a twoline built by compounding two oneline's.
 *     Points are produced through interpolation
 * (3) 'ic_side', for an Integrated Circuit Side
 *     It (protect-ly) inherits from 'twoline'
 *     Points are located through a whole number index
 * (4) 'ic', an IC with pins on all four sides,
 *     'vic', an IC with pins on   vertical sides, and
 *     'hic', an IC with pins on horizontal sides,
 * NOTE: An 'ic_rectangle' can be defined by compounding ic_side's.
 * TODO:
 * (1) define a non-Axis parallel rectangular_component
 * (2) handle negative constructor parameters in rectangular_component<>
 * (3) define a rectangle with (x,y) being the coordinates of its top left-hand corner
 * (4) define 'ic'
 * (5) define poliline<>, then arrow<>
 */

#include <cmath>
#include <utility>
#include <vector>

/* component<> and its children
 * (1) can return a point's coordinates according to an angle,
 * (2) contains some static member functions for trigonometry,
 *     which are defined differently in specializations for FLOAT = float or long double
 * (3) declares pure virtual members 'xperim(rads)' and 'xperim(rads)'
 * (4) its children have member variables cx,cy (for center of shape) and rx,ry for radius
 *     save for circular_component<>, a circle, which only has 'r'
 *
 */
template <typename FLOAT = double>
class component {
public:
  typedef FLOAT float_t;
  static float_t deg_to_rads(float_t d) {return (d / 180)      * 3.141592;};
  static float_t rads_to_deg(float_t r) {return (r / 3.141592) * 180;};
  static float_t  sin(float_t a) {return :: sin(a);};
  static float_t  cos(float_t a) {return :: cos(a);};
  static float_t atan(float_t a) {return ::atan(a);};
  virtual float_t xperim(float_t rads) const = 0;
  virtual float_t yperim(float_t rads) const = 0;
};
template <>
class component<float> {
public:
  static float deg_to_rads(float d) {return (d / 180)      * 3.141592;};
  static float rads_to_deg(float r) {return (r / 3.141592) * 180;};
  static float  sinf(float a) {return :: sin(a);};
  static float  cosf(float a) {return :: cos(a);};
  static float atanf(float a) {return ::atan(a);};
  virtual float xperim(float rads) const = 0;
  virtual float yperim(float rads) const = 0;
};

template <>
class component<long double> {
public:
  static long double deg_to_rads(long double d) {return (d / 180)      * 3.141592;};
  static long double rads_to_deg(long double r) {return (r / 3.141592) * 180;};
  static long double  sinl(long double a) {return :: sin(a);};
  static long double  cosl(long double a) {return :: cos(a);};
  static long double atanl(long double a) {return ::atan(a);};
  virtual long double xperim(long double rads) const = 0;
  virtual long double yperim(long double rads) const = 0;
};

template <typename FLOAT = double>
class circular_component : public component<FLOAT> {
public:
  typedef component<FLOAT> cir_t;
  typedef FLOAT float_t;
  float_t r, cx, cy;
  virtual float_t xperim(float_t rads) const {return cx + r*cir_t::cos(rads);};
  virtual float_t yperim(float_t rads) const {return cy - r*cir_t::sin(rads);};
  circular_component(float_t ra, float_t x=0, float_t y=0) : r(ra), cx(x), cy(y) {};
};

template <typename FLOAT = double>
class elliptical_component : public component<FLOAT> {
public:
  typedef component<FLOAT> cir_t;
  typedef FLOAT float_t;
  float_t rx, ry, cx, cy;
  virtual float_t xperim(float_t rads) const {return cx + rx*cir_t::cos(rads);};
  virtual float_t yperim(float_t rads) const {return cy - ry*cir_t::sin(rads);};
  elliptical_component(float_t r_x, float_t r_y, float_t x=0, float_t y=0) : rx(r_x), ry(r_y), cx(x), cy(y) {};
};

/* rectangular_component<> has sides parallel to X and Y axes */
template <typename FLOAT = double>
class rectangular_component : public component<FLOAT> {
public:
  typedef component<FLOAT> cir_t;
  typedef FLOAT float_t;
  float_t rx, ry;
  float_t cx, cy;
  float_t trans_angle; // angle of upper right-hand vertex
  float_t long_radius; // length from the center to a vertex == sqrt(rx^2 + ry^2)
  virtual float_t xperim(float_t rads) const;// {return rx*cir_t::cos(rads);};
  virtual float_t yperim(float_t rads) const;// {return rx*cir_t::sin(rads);};
  rectangular_component(float_t xr, float_t yr, float_t _cx = 0, float_t _cy=0) :
    rx(xr), ry(yr), cx(_cx), cy(_cy), trans_angle(atan(yr/xr)), long_radius(sqrt(xr*xr + yr*yr)) {};
};
template <typename FLOAT>
FLOAT rectangular_component<FLOAT>::xperim(FLOAT rads) const {
  if(abs(rads) <= trans_angle)
    return cx + rx;
  else
    return cx + long_radius*cir_t::cos(rads);
};
template <typename FLOAT>
FLOAT rectangular_component<FLOAT>::yperim(FLOAT rads) const {
  if(abs(rads) <= trans_angle)
    return cy - long_radius*cir_t::sin(rads);
  else
    return cy - ry;
};


/* rectangle<> has location (x,y) = upper left-hand corner
 * and is very much modelled on svg::rect
 * It has sides parallel to X and Y axes.
 */
template <typename FLOAT = double>
class rectangle {
public:
  typedef FLOAT float_t;
  float_t width, height;
  float_t x, y; // coordinates of upper left-hand corner
  rectangle(float_t w, float_t h, float_t l=0, float_t u=0) : width(w), height(h), x(l), y(u) {};
};

/* class polyline: a line made up of straight segments
 * Points are held in a container supporting push/emplace_back()
 * class polygone  is defined analogously:
 *   just substitute 'polygone' for 'polyline'
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
  polyline() = default;
  polyline(const polyline_t& pl) : points(pl.points) {};
};
template <typename FLOAT = double,
          typename POINT = std::pair<FLOAT,FLOAT>,
          typename CONT  = std::vector<POINT> >
class polygone {
  public:
  typedef FLOAT float_t;
  typedef POINT point_t;
  typedef polygone<FLOAT,POINT,CONT> polygone_t;
  CONT points;
  void push_back(const POINT& p)  {points.push_back(p);};
  void push_back(FLOAT x, FLOAT y){points.emplace_back(x,y);};
  polygone() = default;
  polygone(const polygone_t& pl) : points(pl.points) {};
};

/* class oneline<> is a one-dimensional line
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
 * holds two oneline's (named 'x' and 'y')
 * and represents a line in 2-space
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
  twoline(float_t xb, float_t yb, float_t xe, float_t ye) : x(xb,xe), y(yb,ye) {};
};

template <typename FLOAT = double>
class ic_side : public twoline<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef oneline<FLOAT> twoline_t;
  typedef std::size_t size_t;
  size_t num;
  float_t get_x(size_t idx) const {return twoline_t::get_x((idx + 0.5) / num);}; // idx < n
  float_t get_y(size_t idx) const {return twoline_t::get_y((idx + 0.5) / num);}; // idx < n
  ic_side(float_t xb, float_t yb, float_t xe, float_t ye, size_t n) :
    twoline_t(xb,yb,xe,ye), num(n) {};
  //float_t
};

/* class 'ic'
 * By convention, the pins on an IC are numbered counterclockwise, starting with the upper-left pin closest to the clocking mark.
 */
template <typename FLOAT = double>
class ic : public rectangle<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef rectangle<FLOAT> rectangle_t;
  typedef std::size_t size_t;
  float_t num_h, num_v; // number of pins vertical-wise and horizontal-wise
  float_t sep, halfsep; // full and half separation between pins
  float_t get_x() const {return rectangle_t::x;};
  float_t get_y() const {return rectangle_t::y;};
  float_t get_width()  const {return rectangle_t::width;};
  float_t get_height() const {return rectangle_t::height;};
  // members for getting the coordinates and facing of pins
  virtual float_t xperim(size_t idx) const;
  virtual float_t yperim(size_t idx) const;
  enum facing {lt, bt, rt, tp};
  virtual facing faces(size_t idx) const;
  ic(float_t x, float_t y, // coordinates of upper left-hand corner
     float_t sp,          // separation between pins
     float_t nh, float_t nv) : // number of pins horizontal- and vertical-wise
     rectangle_t(nh*sp, nv*sp, x, y), num_h(nh), num_v(nv), sep(sp), halfsep(sp/2) {};
};
template <typename FLOAT>
FLOAT ic<FLOAT>::xperim(std::size_t idx) const {
  if(idx < num_v)
    return get_x();
  else
    if(idx < (num_v + num_h))
      return get_x() + sep*(idx - num_v) + halfsep;
    else
      if(idx < (2*num_v + num_h))
        return get_x() + get_width();
      else
        return get_x() + get_width() - sep*(idx - num_h - 2*num_v) - halfsep;
};
template <typename FLOAT>
FLOAT ic<FLOAT>::yperim(std::size_t idx) const {
  if(idx < num_v)
    return get_y() + sep*idx + halfsep;
  else {
    if(idx < (num_v + num_h))
      return get_y() + get_height();
    else
      if(idx < (2*num_v + num_h))
        return get_y() + get_height() - sep*(idx - num_v - num_h) - halfsep;
      else
        return get_y();
  }
};
template <typename FLOAT>
ic<FLOAT>::facing ic<FLOAT>::faces(std::size_t idx) const {
  if(idx < num_v)
    return lt;
  else
    if(idx < (num_v + num_h))
      return bt;
    else
      if(idx < (2*num_v + num_h))
        return rt;
      else
        return tp;
};
/* Class vic<FLOAT>, for Vertical Integrated Circuit,
 * has pins only on its vertical --left and right-- sides.
 * Thus, it only needs to define or redefine [x|y]perim(IDX).
 */
template <typename FLOAT = double>
class vic : public ic<FLOAT> {
public:
  typedef           FLOAT      float_t;
  typedef        ic<FLOAT>        ic_t;
  typedef rectangle<FLOAT> rectangle_t;
  typedef std::size_t size_t;
  size_t adjust(size_t idx) const {
    if(idx < ic_t::num_v)
      return idx;
    else
      return idx + ic_t::num_h;
  };
  float_t     xperim(size_t idx) const {return ic_t::xperim(adjust(idx));};
  float_t     yperim(size_t idx) const {return ic_t::yperim(adjust(idx));};
  ic_t::facing faces(size_t idx) const {return ic_t::faces( adjust(idx));};
  // constructor:
  vic(float_t x, float_t y,    // coordinates of upper left-hand corner
     float_t sp,               // separation between pins
     float_t nh, float_t nv) : // number of pins horizontal- and vertical-wise
     ic_t(x,y,sp,nh,nv) {};
};


/* SVG Helping Functions
 * Remember to define attribute 'stroke' (as black or some non-white colour)
 * in the svg opening tag, or in each svg shape
 * Sometimes you want to define fill to, possibly inside specific svg shapes
 * You rarely want to define <svg stroke="black" fill="black"
 * as the filling will hide a lot of detail
 */
#include <iostream>
#include <string>
#ifndef SVG_FILE_INDENT_STR
#define SVG_FILE_INDENT_STR "  "
#endif
template<typename OUT = std::ostream>
OUT& close_svg(OUT& o) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << "</svg>\n";
  return o;
};
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
