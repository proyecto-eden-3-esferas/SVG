#ifndef SCHEMATICS_ANGLE_H
#define SCHEMATICS_ANGLE_H

#include <numbers>
#include <cmath>


/* class angle_addressable_base<>
   provides trigonometric functions
   in specializations for float, double and long double.
 * It uses radians, whereas its only child angle_addressable<>
   uses degrees.
 * In trigonometric libraries, a normalize() function is required,
   coded on some agreement as to what interval to normalize into.
   For instance, to normalize 400 into [0,360], 360 should be subtracted from 400,
   which yields 40, whereas to normalize -400,  360 should be added twice  to 400,
   which yields 320.
   The normalizing funcion in this library is 'angle_addressable<>::normalize(DEGS)'.
 */

template <typename FLOAT = double>
class angle_addressable_base {
public:
  typedef FLOAT float_t;
  static float_t  sin(float_t a) {return :: sin(a);};
  static float_t  cos(float_t a) {return :: cos(a);};
  static float_t atan(float_t a) {return ::atan(a);};
  static float_t atan2(float_t a, float_t b) {return ::atan2(a,b);};
  //
  static float_t   abs(float_t dbl) {return ::fabs(dbl);};
  static float_t  sqrt(float_t dbl) {return ::sqrt(dbl);};
};

template <>
class angle_addressable_base<float> {
public:
  static float  sin(float a) {return :: sinf(a);};
  static float  cos(float a) {return :: cosf(a);};
  static float atan(float a) {return ::atanf(a);};
  static float atan2(float a, float b) {return ::atan2f(a,b);};
  //
  static float_t   abs(float_t f) {return ::fabsf(f);};
  static float_t  sqrt(float_t f) {return ::sqrtf(f);};
};

template <>
class angle_addressable_base<long double> {
public:
  static long double  sin(long double a) {return :: sinl(a);};
  static long double  cos(long double a) {return :: cosl(a);};
  static long double atan(long double a) {return ::atanl(a);};
  static long double atan2(long double a, long double b) {return ::atan2l(a,b);};
  //
  static float_t   abs(float_t ld) {return ::fabsl(ld);};
  static float_t  sqrt(float_t ld) {return ::sqrt(ld);};
};

/* angle_addressable<>
 * (0) All angles are in degrees, not radians as in parent class angle_addressable_base<FLOAT>
 * (1) xperim(ANGLE) and xperim(ANGLE) are the only pure vitual members,
       and should return coordinates (x,y) given an angle
 * (2) contains some static member functions for trigonometry,
       which are defined differently in specializations for FLOAT = float or long double
       - distance(x,y) and angle(x,y)
       - get_x_rotated(X,Y,ANGLE) and get_y_rotated(X,Y,ANGLE)
         return the X- and Y- coordinate of (x,y) after rotating it by ANGLE around (cx,cy)
       - rotate(X,Y,ANGLE), which takes X and Y as non-const references
         and rotates them around (cx,cy) by ANGLE
       -
 * (3) its children have member variables cx,cy (for center of shape) and rx,ry for radius
      save for circular<>, a circle, which only has one radius variable: 'r'
 * (4) angle_addressable<FLOAT> is often typedef'd as cir_t, as in:
         typedef angle_addressable<FLOAT> cir_t;
 *
 */
template <typename FLOAT = double>
class angle_addressable : public angle_addressable_base<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef angle_addressable_base<float_t> angle_addressable_base_t;
  using angle_addressable_base_t::sin,  angle_addressable_base_t::cos;
  using angle_addressable_base_t::atan, angle_addressable_base_t::atan2;
  using angle_addressable_base_t::abs, angle_addressable_base_t::sqrt;
  float_t cx, cy;
  //
  static void normalize(float_t& a); // +- 360 to get 'a' into [0,360]
  // Members for rotating a point around around this->(cx,cy)
  float_t distance(float_t x, float_t y) const { return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy) );};
  float_t    angle(float_t x, float_t y) const { return atan2(y - cy,               x - cx);};
  float_t get_x_rotated(float_t x, float_t y, float_t a) const;
  float_t get_y_rotated(float_t x, float_t y, float_t a) const;
  void rotate(float_t& x, float_t& y, float_t a) const;
  static float_t deg_to_rad(float_t d) {return (d / 180) * std::numbers::pi_v<float_t>;};
  static float_t rad_to_deg(float_t r) {return (r / std::numbers::pi_v<float_t>) * 180;};
  static float_t  sin(float_t a) {return ::sin(deg_to_rad(a));};
  static float_t  cos(float_t a) {return ::cos(deg_to_rad(a));};
  static float_t atan(float_t x) {return             rad_to_deg(::atan(x));};
  static float_t atan2(float_t y, float_t x) {return rad_to_deg(::atan2(y,x));};
  //
  virtual float_t xperim(float_t degs) const = 0;
  virtual float_t yperim(float_t degs) const = 0;
  angle_addressable() = default;
  angle_addressable(float_t x, float_t y) : cx(x), cy(y) {};
};

// Implementations of angle_addressable<> members

template <typename FLOAT>
void angle_addressable<FLOAT>::normalize(FLOAT& a) {
  while( a < 0)
    a +=     360;
  while( a > 360)
    a -=     360;
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
