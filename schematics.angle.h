#ifndef SCHEMATICS_ANGLE_H
#define SCHEMATICS_ANGLE_H

#include <cmath>


template <typename FLOAT = double>
class angle_addressable_base {
public:
  typedef FLOAT float_t;
  static float_t  sin(float_t a) {return :: sin(a);};
  static float_t  cos(float_t a) {return :: cos(a);};
  static float_t atan(float_t a) {return ::atan(a);};
  static float_t atan2(float_t a, float_t b) {return ::atan2(a,b);};
};

template <>
class angle_addressable_base<float> {
public:
  static float  sin(float a) {return :: sinf(a);};
  static float  cos(float a) {return :: cosf(a);};
  static float atan(float a) {return ::atanf(a);};
  static float atan2(float a, float b) {return ::atan2f(a,b);};
};

template <>
class angle_addressable_base<long double> {
public:
  static long double  sin(long double a) {return :: sinl(a);};
  static long double  cos(long double a) {return :: cosl(a);};
  static long double atan(long double a) {return ::atanl(a);};
  static long double atan2(long double a, long double b) {return ::atan2l(a,b);};
};

/* angle_addressable<>
 * (1) xperim(ANGLE) and xperim(ANGLE) are the only pure vitual members,
       and return (x,y) given an angle
 * (2) contains some static member functions for trigonometry,
       which are defined differently in specializations for FLOAT = float or long double
       - distance(x,y) and angle(x,y)
       - get_x_rotated(X,Y,ANGLE) and get_y_rotated(X,Y,ANGLE)
         return the X- and Y- coordinate of (x,y) after rotating it by ANGLE around (cx,cy)
       - rotate(X,Y,ANGLE), which takes X and Y as non-const references
         and rotates them around (cx,cy) by ANGLE
       -
 * (3) its children have member variables cx,cy (for center of shape) and rx,ry for radius
      save for circular<>, a circle, which only has 'r'
 * (4) angle_addressable<FLOAT> is often typedef'd as cir_t, as in
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
  float_t cx, cy;
  // Members for rotating a point around around this->(cx,cy)
  float_t distance(float_t x, float_t y) const { return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy) );};
  float_t    angle(float_t x, float_t y) const { return atan2( y - cy, x - cx);};
  float_t get_x_rotated(float_t x, float_t y, float_t a) const {
    float_t d = distance(x,y);
    float_t new_a = angle(x,y) + a;
    return cx + d * cos(new_a);
  };
  float_t get_y_rotated(float_t x, float_t y, float_t a) const {
    float_t d = distance(x,y);
    float_t new_a = angle(x,y) + a;
    return cy + d * sin(new_a);
  };
  void rotate(float_t& x, float_t& y, float_t a) const {
    float_t d = distance(x,y);
    float_t new_a = angle(x,y) + a;
    x = cx + d * cos(new_a);
    y = cy + d * sin(new_a);
  };
  //static float_t deg_to_rads(float_t d) {return (d / 180)      * 3.141592;};
  //static float_t rads_to_deg(float_t r) {return (r / 3.141592) * 180;};
  static float_t deg_to_rad(float_t d) {return (d / 180)      * 3.141592;};
  static float_t rad_to_deg(float_t r) {return (r / 3.141592) * 180;};
  static float_t  sin(float_t a) {return :: sin(a);};
  static float_t  cos(float_t a) {return :: cos(a);};
  static float_t atan(float_t a) {return ::atan(a);};
  static float_t atan2(float_t a, float_t b) {return ::atan2(a,b);};
  virtual float_t xperim(float_t rads) const = 0;
  virtual float_t yperim(float_t rads) const = 0;
  angle_addressable() = default;
  angle_addressable(float_t x, float_t y) : cx(x), cy(y) {};
};

#endif
