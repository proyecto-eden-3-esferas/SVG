#ifndef SCHEMATICS_ANGLE_H
#define SCHEMATICS_ANGLE_H

#ifndef GEOMETRY_2D
#include "geometry_2D.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

#include <iostream>

// For compatibility:
template <typename F = double>
using angle_addressable_base = geometry_2D<F>;

/* angle_addressable<>
 * (0) All angles are in degrees, not radians as in parent class geometry_2D<FLOAT>
 * (1) xperim(ANGLE) and xperim(ANGLE) are the only pure vitual members,
       and should return the coordinates (x,y) of a point on the periphery given an angle
 * (2) contains some static member functions for trigonometry,
       which are defined differently in specializations for FLOAT = float or long double
       - angle(x,y) (in degrees)
       - get_x_rotated(X,Y,ANGLE) and get_y_rotated(X,Y,ANGLE)
         return the X- and Y- coordinate of (x,y) after rotating it by ANGLE around (cx,cy)
       - rotate(X,Y,ANGLE), which takes X and Y as non-const references
         and rotates them around (cx,cy) by ANGLE
       -
 * (3) its children have member variables cx,cy (for center of shape) and rx,ry for radius
      save for circular<>, a circle, which only has one radius variable: 'r'
 * (4) angle_addressable<FLOAT> is often typedef'd as cir_t for brevity (shortness), as in:
         typedef angle_addressable<FLOAT> cir_t;
 * (5) In trigonometric libraries, a normalize() function is required,
       coded on some agreement as to what interval to normalize into.
       For instance, to normalize 400 into [0,360], 360 should be subtracted from 400,
       which yields 40, whereas to normalize -400,  360 should be added twice  to 400,
       which yields 320.
       The normalizing functions in this library are:
         void       angle_addressable<>::normalize(       DEGS&)
         float_type angle_addressable<>::normalized(const DEGS)
 *
 */

template<typename F> class angle_addressable;

template<typename F>
void add_svg_unclosed(const angle_addressable<F>& aa, std::ostream& o = std::cout) {
  o << "<text x=\"" << aa.cx << "\" y=\"" << aa.cy << "\" style=\"text-anchor: middle\"";
};

template <typename FLOAT = double>
class angle_addressable : public geometry_2D<FLOAT>, public svg_shape<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef geometry_2D<float_t> geo2d_t;
  using geo2d_t::sin,   geo2d_t::cos;
  //using geo2d_t::asin,  geo2d_t::acos;
  //using geo2d_t::atan,  geo2d_t::atan2;
  using geo2d_t::abs;
  using geo2d_t::sqrt;
  //using geo2d_t::normalize, geo2d_t::normalized;
  using geo2d_t::distance;
  using geo2d_t::angle;
  using geo2d_t::deg_to_rad, geo2d_t::rad_to_deg;
  //
  float_t cx, cy;  // the centre of a circle, rectangle, ellipse...
  static void  normalize( float_t& deg); // add/subtract 360 to get 'a' into [0,360]
  static FLOAT normalized(float_t  deg) {return normalize(deg);};
  // Members for rotating a point around around this->(cx,cy)
  float_t distance(float_t x, float_t y) const {return distance(cx, cy, x, y);};
  float_t    angle(float_t x, float_t y) const {return  rad_to_deg(angle(cx, cy, x, y));};
  float_t get_x_rotated(float_t x, float_t y, float_t a) const;
  float_t get_y_rotated(float_t x, float_t y, float_t a) const;
  void rotate(float_t& x, float_t& y, float_t a) const;

  /* Trigonometric functions in angle_addressable<F> return radians,
   * unlike geometry_2D<F>, its parent class.
   * Maybe this should be reflected in their name, e.g. by renaming sin() to rsin()
   */
  static float_t  sin(float_t a) {return geo2d_t::sin(deg_to_rad(a));};
  static float_t  cos(float_t a) {return geo2d_t::cos(deg_to_rad(a));};
  static float_t  asin(float_t si) {return rad_to_deg(geo2d_t::asin(si));};
  static float_t  acos(float_t co) {return rad_to_deg(geo2d_t::acos(co));};
  static float_t atan(float_t x) {return             rad_to_deg(geo2d_t::atan(x));};
  static float_t atan2(float_t y, float_t x) {return rad_to_deg(geo2d_t::atan2(y,x));};
  //
  virtual float_t xperim(float_t degs) const {return cx;}; // = 0;
  virtual float_t yperim(float_t degs) const {return cy;}; // = 0;
  void add_svg_unclosed(std::ostream& o = std::cout) const override {
    ::add_svg_unclosed(*this,o);
  };
  //
  angle_addressable() = default;
  angle_addressable(float_t x, float_t y) : cx(x), cy(y) {};
};




// Implementations of angle_addressable<> members

template <typename FLOAT>
void  angle_addressable<FLOAT>::normalize( float_t& deg) {
  /*const */float_t r {deg_to_rad(deg)};
  geo2d_t::normalize(r);
  deg = rad_to_deg(r);
};

template <typename FLOAT>
FLOAT angle_addressable<FLOAT>::get_x_rotated(FLOAT x, FLOAT y, FLOAT a) const {
  FLOAT d = distance(x,y);
  FLOAT new_a = angle(x,y) + a;
  return cx + d * cos(new_a);
};
template <typename FLOAT>
FLOAT angle_addressable<FLOAT>::get_y_rotated(FLOAT x, FLOAT y, FLOAT a) const {
  FLOAT d = distance(x,y);
  FLOAT new_a = angle(x,y) + a;
  return cy + d * sin(new_a);
};

template <typename FLOAT>
void angle_addressable<FLOAT>::rotate(FLOAT& x, FLOAT& y, FLOAT a) const {
  FLOAT d = distance(x,y);
  FLOAT new_a = angle(x,y) + a;
  x = cx + d * cos(new_a);
  y = cy + d * sin(new_a);
};

#endif
