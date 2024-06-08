#ifndef SCHEMATICS_IC_H
#define SCHEMATICS_IC_H

// We need twoline<>, rectangle<> etc. so we...

#ifndef SCHEMATICS_H
#include "schematics.h"
#endif

#ifndef SCHEMATICS_LINE_H
#include "schematics.line.h"
#endif

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
/* Following are two DIP (Dual In Package) classes,
 * vertically- and horizontally-pinned,
 * class vic<FLOAT>, for Vertical Integrated Circuit
 * has pins only on its vertical --left and right-- sides.
 * class hic<FLOAT>, for Horizontal Integrated Circuit
 * has pins only on its horizontal --bottom and top-- sides.
 * Thus,      it only needs to define or redefine [x|y]perim(IDX).
 * which, again, only needs to define or redefine [x|y]perim(IDX).
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
template <typename FLOAT = double>
class hic : public ic<FLOAT> {
public:
  typedef           FLOAT      float_t;
  typedef        ic<FLOAT>        ic_t;
  typedef rectangle<FLOAT> rectangle_t;
  typedef std::size_t size_t;
  size_t adjust(size_t idx) const {
    if(idx < ic_t::num_h)
      return idx +   ic_t::num_v;
    else
      return idx + 2*ic_t::num_h;
  };
  float_t     xperim(size_t idx) const {return ic_t::xperim(adjust(idx));};
  float_t     yperim(size_t idx) const {return ic_t::yperim(adjust(idx));};
  ic_t::facing faces(size_t idx) const {return ic_t::faces( adjust(idx));};
  // constructor:
  hic(float_t x, float_t y,    // coordinates of upper left-hand corner
     float_t sp,               // separation between pins
     float_t nh, float_t nv) : // number of pins horizontal- and vertical-wise
     ic_t(x,y,sp,nh,nv) {};
};

#endif
