#ifndef SCHEMATICS_H
#define SCHEMATICS_H

/* File "schematics.cpp"
 * Defines several subhierarchies:
 * (1) angle_addressable<> and its children:
 *     circular, elliptical, and rectangular
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
 * (1) define a non-Axis parallel rectangular
 * (2) handle negative constructor parameters in rectangular<>
 * (3) define a rectangle with (x,y) being the coordinates of its top left-hand corner
 * (4) define 'ic'
 * (5) define poliline<>, then arrow<>
 */

#include <cmath>
#include <utility>
#include <vector>


/* rectangle<> has location (x,y) = upper left-hand corner
   and is very much modelled on svg::rect
 * It has sides parallel to X and Y axes.
 * Its child 'block' is meant to be used in block diagrammes
 */
template <typename FLOAT = double>
class rectangle {
public:
  typedef FLOAT float_t;
  float_t width, height;
  float_t x, y; // coordinates of upper left-hand corner
  rectangle(float_t w, float_t h, float_t lft=0, float_t uppr=0) : width(w), height(h), x(lft), y(uppr) {};
};
/* Class block<>, a child of rectangle<>
 * It keeps the number of ports (possibly realized as pins or as named connections)
   for each of its four sides.
 * It produces the coordinates of a port on its perimeter
   through members 'get_x_right(INDEX)' and so on
 * These members can be used to write a general get_x(INDEX) and get_y(INDEX)
   for any index smaller than the total number of ports.
 * ...
 */
template <typename FLOAT = double>
class block : public rectangle<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef std::size_t size_t;
  typedef std::size_t index_t;
  typedef rectangle<FLOAT> rectangle_t;
  using rectangle_t::x, rectangle_t::y, rectangle_t::width, rectangle_t::height;
  size_t num_rht, num_btm, num_lft, num_upr; // number of ports on sides right, upper, left and bottom
  // float_t num_rht, num_upr, num lft, num_btm; // number of ports on sides right, upper, left and bottom
  float_t get_x_right( index_t idx) const {return x + width;};
  float_t get_y_right( index_t idx) const {return y + ((idx + 0.5)/num_rht) * height;};
  float_t get_x_bottom(index_t idx) const {return x + ((num_btm - idx - 0.5) / num_btm) * width;};
  float_t get_y_bottom(index_t idx) const {return y + height;};
  float_t get_x_left(  index_t idx) const {return x;};
  float_t get_y_left(  index_t idx) const {return y + ((num_lft - idx - 0.5)/num_lft) * height;};
  float_t get_x_top(   index_t idx) const {return x + ((idx + 0.5)/num_upr) * width;};
  float_t get_y_top(   index_t idx) const {return y;};
  //
  block(float_t w, float_t h, float_t x, float_t y,
        float_t r, float_t b, float_t l, float_t u) :
    rectangle_t(w,h,x,y), num_rht(r), num_btm(b), num_lft(l), num_upr(u)  {};
};

/* classes polyline and polygon
 * class poliline is a line made up of straight segments
 * Points are held in a container supporting push/emplace_back()
 * class polygon  is defined analogously:
 * (  )just substitute 'polygon' for 'polyline')
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
};

/* class oneline<> is a one-dimensional line
 * which holds its beginning and ending as single floats,
 * and with a  static FLOAT interpolate(BEG,END, K) member
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

#endif
