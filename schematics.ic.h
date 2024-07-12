#ifndef SCHEMATICS_IC_H
#define SCHEMATICS_IC_H

// We need twoline<>, rectangle<> etc. so we...

#ifndef SCHEMATICS_RECTANGLE_H
#include "schematics.rectangle.h"
#endif

#include "schematics.block.h"

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
 * By convention, the pins on an IC are numbered counterclockwise,
   starting with the upper-left pin closest to the clocking mark.
 * The constructor does NOT take width and height arguments but calculates them
   from the number of pins on each side
 */
template <typename FLOAT = double>
class ic : public block<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef rectangle<FLOAT> rectangle_t;
  typedef block<FLOAT> block_t;
  typedef std::size_t size_t;
  using block_t::x, block_t::y, block_t::width, block_t::height;
  // Constructor:
  ic(float_t x, float_t y, // coordinates of upper left-hand corner
     float_t sp,          // separation between pins
     size_t nh, float_t nv) : // number of pins horizontal- and vertical-wise
     block_t(x, y, nh*sp, nv*sp, nv, nh, nv, nh) //, num_h(nh), num_v(nv), sep(sp), halfsep(sp/2)
     {};
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
  // constructor:
  vic(float_t x, float_t y,    // coordinates of upper left-hand corner
     float_t sp,               // separation between pins
     size_t num) : // number of pins vertical-wise
     ic_t(x,y,sp,0,num) {};
};
template <typename FLOAT = double>
class hic : public ic<FLOAT> {
public:
  typedef           FLOAT      float_t;
  typedef        ic<FLOAT>        ic_t;
  typedef rectangle<FLOAT> rectangle_t;
  typedef std::size_t size_t;
  // constructor:
  hic(float_t x, float_t y,    // coordinates of upper left-hand corner
     float_t sp,               // separation between pins
     size_t num) : // number of pins horizontal-wise
     ic_t(x,y,sp,num,0) {};
};

#ifndef SVG_H
#include "svg.h"
#endif
/* Partial specializations of add_svg_unclosed(IC&,OUT) */
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const ic<F>& i, OUT& o = std::cout) {
  o << "<rect x=\"" << i.x     << "\" y=\""      << i.y << "\" ";
  o <<   "width=\"" << i.width << "\" height=\"" << i.height << "\"";
  //return o; // void return type
};


#endif
