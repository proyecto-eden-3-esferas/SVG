#ifndef SCHEMATICS_RECTANGLE_H
#define SCHEMATICS_RECTANGLE_H

#include <iostream> // for std::size_t

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
// Partial specializations of add_svg_unclosed(RECTANGLE&,OUT&) and svg_unclosed(BLOCK&,OUT&)
#ifndef SVG_H
#include "svg.h"
#endif
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const rectangle<F>& rct, OUT& o = std::cout) {
  o << "<rect x=\"" << rct.x     << "\" y=\""      << rct.y << "\" ";
  o <<   "width=\"" << rct.width << "\" height=\"" << rct.height << "\"";
  return o;
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const block<F>& blk, OUT& o = std::cout) {
  o << "<rect x=\"" << blk.x     << "\" y=\""      << blk.y << "\" ";
  o <<   "width=\"" << blk.width << "\" height=\"" << blk.height << "\"";
  return o;
};

#endif
