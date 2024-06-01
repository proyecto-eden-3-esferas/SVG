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

#endif
