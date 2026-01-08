#ifndef SCHEMATICS_BLOCK_H
#define SCHEMATICS_BLOCK_H

#ifndef SCHEMATICS_RECTANGLE_H
#include "schematics.rectangle.h"
#endif

/* Class block<>, a child of rectangle<>
 * It stores the number of ports (possibly realized as pins or as named connections)
   on each of its four sides.
 * It produces the coordinates of a port on its perimeter
   through members 'get_x_right(INDEX)' and so on,
   or through newly added xperim(IDX) and yperim(IDX) members, which match members of class ic
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
  //
  size_t size() const {return num_lft + num_btm + num_rht + num_upr;};
protected:
  size_t num_lft, num_btm, num_rht, num_upr; // number of ports on sides right, upper, left and bottom
  /* The following take relative indexes,
   * are referenced in "schmatics.block.test.cpp", and
   * should be made protected virtual */
  virtual float_t get_x_left(  index_t idx) const {return x;};
  virtual float_t get_y_left(  index_t idx) const {return y + ((idx + 0.5) / num_lft) * height;};
  virtual float_t get_x_bottom(index_t idx) const {return x + ((idx + 0.5) / num_btm) * width;};
  virtual float_t get_y_bottom(index_t idx) const {return y + height;};
  virtual float_t get_x_right( index_t idx) const {return x + width;};
  virtual float_t get_y_right( index_t idx) const {return y + ((num_rht - idx - 0.5) / num_rht) * height;};
  virtual float_t get_x_top(   index_t idx) const {return x + ((num_upr - idx - 0.5) / num_upr) * width;};
  virtual float_t get_y_top(   index_t idx) const {return y;};
public:
  // members for getting the coordinates and facing of pins
  enum    facing {lt, bt, rt, tp, none};        // for left, bottom, right, and top
  virtual facing faces(size_t idx) const; // Whether pin 'idx' faces left, down, right, or up
  virtual float_t xperim(size_t idx) const;
  virtual float_t yperim(size_t idx) const;
  //
  void add_svg_unclosed(std::ostream& o = std::cout, const std::string& attrs = "") const override;
  block(float_t x, float_t y, float_t w, float_t h,
        float_t l, float_t b, float_t r, float_t u) :
    rectangle_t(w,h,x,y), num_lft(l), num_btm(b), num_rht(r), num_upr(u)  {};
};
// block_t(x,y,w,h, l,b,r,u)

// Implementation of members of block<FLOAT>
template <typename FLOAT>
block<FLOAT>::facing block<FLOAT>::faces(std::size_t idx) const {
  if(idx < num_lft)
    return lt;
  else
    if(idx < (num_lft + num_btm))
      return bt;
    else
      if(idx < (num_lft + num_btm + num_rht))
        return rt;
      else
        if(idx < (num_lft + num_btm + num_rht + num_upr))
          return tp;
        else
          return none;
};
template <typename FLOAT>
FLOAT block<FLOAT>::xperim(std::size_t idx) const {
  switch(faces(idx)) {
    case facing::lt:
      return get_x_left(idx);
      break;
    case facing::bt:
      return get_x_bottom(idx - num_lft);
      break;
    case facing::rt:
      return get_x_right(idx - num_lft - num_btm);
      break;
    case facing::tp:
      return get_x_top(idx - num_lft - num_btm - num_rht);
      break;
    default:
      return x;
      break;
  }
};
template <typename FLOAT>
FLOAT block<FLOAT>::yperim(std::size_t idx) const {
  switch(faces(idx)) {
    case facing::lt:
      return get_y_left(idx);
      break;
    case facing::bt:
      return get_y_bottom(idx - num_lft);
      break;
    case facing::rt:
      return get_y_right(idx - num_lft - num_btm);
      break;
    case facing::tp:
      return get_y_top(idx - num_lft - num_btm - num_rht);
      break;
    default:
      return y;
      break;
  }
};

template <typename FLOAT>
void block<FLOAT>::add_svg_unclosed(std::ostream& o, const std::string& attrs) const {
  o << "<rect x=\"" << x     << "\" y=\""      << y << "\" ";
  o <<   "width=\"" << width << "\" height=\"" << height << "\"";
  o << ' ' << attrs;
};

#endif
