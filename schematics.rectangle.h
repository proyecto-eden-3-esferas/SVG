#ifndef SCHEMATICS_RECTANGLE_H
#define SCHEMATICS_RECTANGLE_H

#include <iostream> // for std::size_t

#ifndef SVG_H
#include "svg.h"
#endif

/* rectangle<> has location (x,y) = upper left-hand corner
   and is very much modelled on svg::rect
 * It has sides parallel to X and Y axes.
 * Its child 'block' is meant to be used in block diagrammes
 */
template <typename FLOAT = double>
class rectangle : public svg_shape<FLOAT> {
public:
  typedef FLOAT float_t;
  float_t width, height;
  float_t x, y; // coordinates of upper left-hand corner
  float_t rx, ry; // corner radii: for square corners make rx = ry = 0.0
  //
  float_t get_cx() const {return x + ( width / 2);};
  float_t get_cy() const {return y + (height / 2);};
  void set_cx(float_t newcx) {x = newcx - ( width / 2);};
  void set_cy(float_t newcy) {y = newcy - (height / 2);};
  //
  void add_svg_unclosed(   std::ostream& o = std::cout, const std::string& attrs = "") const override;
  // Constructors:
  rectangle(float_t w,   float_t h,
            float_t lft, float_t uppr,
            float_t r=0.0) : width(w), height(h), x(lft), y(uppr), rx(r), ry(r) {};
  rectangle(float_t w,   float_t h,
            float_t lft, float_t uppr,
            float_t _rx, float_t _ry) : width(w), height(h), x(lft), y(uppr), rx(_rx), ry(_ry) {};
};
template <typename FLOAT>
void rectangle<FLOAT>::add_svg_unclosed(   std::ostream& o, const std::string& attrs) const {
  o << "<rect x=\"" << x     << "\" y=\""      << y << "\" ";
  o <<   "width=\"" << width << "\" height=\"" << height << "\"";
  o <<   "rx=\"" << rx << "\" ry=\"" << ry << "\"";
  if(attrs.length() > 0)
    o << ' ' << attrs;
};

#endif
