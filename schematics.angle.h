#ifndef SCHEMATICS_ANGLE_H
#define SCHEMATICS_ANGLE_H

#include <cmath>
#include <numbers>
#include <utility>


/* class angle_addressable_base<>
   provides trigonometric functions, plus abs() and sqrt()
   in specializations for float, double and long double.
 * It uses radians, whereas its only child angle_addressable<>
   uses degrees.
 */

template <typename FLOAT = double>
class angle_addressable_base {
public:
  typedef FLOAT float_t;
  typedef std::pair<float_t,float_t> pair_t;
  static float_t  sin(float_t a) {return  ::sin(a);};
  static float_t  cos(float_t a) {return  ::cos(a);};
  static float_t atan(float_t a) {return ::atan(a);};
  static float_t atan2(float_t a, float_t b) {return ::atan2(a,b);};
  //
  static float_t   abs(float_t dbl) {return ::fabs(dbl);};
  static float_t  sqrt(float_t dbl) {return ::sqrt(dbl);};
  //
  static void normalize(FLOAT& a) { // add/subtract 2pi until a is within [a, 2pi]
    while( a < 0)
      a +=     2 * std::numbers::pi_v<FLOAT>;
    while( a > 2 * std::numbers::pi_v<FLOAT>)
      a -=     2 * std::numbers::pi_v<FLOAT>;
  };
  static float_t normalized(float_t  a) {float_t temp(a); normalize(temp); return temp;};
  //
  static float_t distance(float_t x1, float_t y1, float_t x2, float_t y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) );};
  static float_t    angle(float_t x1, float_t y1, float_t x2, float_t y2) {
    return atan2(y2 - y1, x2 - x1);};
  static float_t deg_to_rad(float_t d) {return (d / 180) * std::numbers::pi_v<float_t>;};
  static float_t rad_to_deg(float_t r) {return (r / std::numbers::pi_v<float_t>) * 180;};
  /* static void set_angle_dist_from_of(...)
     takes a source point (from), an angle to the X-axis,
     an in/out point "to" (non-const reference) and a distance 'dist',
     and sets the in/out point 'to'
     so that the line from 'from' to 'to' is at an angle 'a' to the X-axis,
     and is dist[ance] units long.*/
  static void set_angle_dist_from_of(float_t a, float_t dist, const pair_t& from, pair_t& to) {
    to.first  = from.first  + dist*cos(a);
    to.second = from.second + dist*sin(a);
  };
};

template <>
class angle_addressable_base<float> {
public:
  typedef std::pair<float,float> pair_t;
  static float  sin(float a) {return :: sinf(a);};
  static float  cos(float a) {return :: cosf(a);};
  static float atan(float a) {return ::atanf(a);};
  static float atan2(float a, float b) {return ::atan2f(a,b);};
  //
  static float   abs(float f) {return ::fabsf(f);};
  static float  sqrt(float f) {return ::sqrtf(f);};
  //
  static void normalize(float& a) { // add/subtract 2pi until a is within [a, 2pi]
    while( a < 0)
      a +=     2 * std::numbers::pi_v<float>;
    while( a > 2 * std::numbers::pi_v<float>)
      a -=     2 * std::numbers::pi_v<float>;
  };
  static float normalized(float  a) {float temp(a); normalize(temp); return temp;};
  //
  static float distance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) );};
  static float    angle(float x1, float y1, float x2, float y2) {
    return atan2(y2 - y1, x2 - x1);};
  static float deg_to_rad(float d) {return (d / 180) * std::numbers::pi_v<float>;};
  static float rad_to_deg(float r) {return (r / std::numbers::pi_v<float>) * 180;};
  static void set_angle_dist_from_of(float a, float dist, const pair_t& from, pair_t& to) {
    to.first  = from.first  + dist*cos(a);
    to.second = from.second + dist*sin(a);
  };
};

template <>
class angle_addressable_base<long double> {
public:
  typedef std::pair<long double,long double> pair_t;
  static long double  sin(long double a) {return :: sinl(a);};
  static long double  cos(long double a) {return :: cosl(a);};
  static long double atan(long double a) {return ::atanl(a);};
  static long double atan2(long double a, long double b) {return ::atan2l(a,b);};
  //
  static long double   abs(long double ld) {return ::fabsl(ld);};
  static long double  sqrt(long double ld) {return ::sqrt(ld);};
  //
  static void normalize(long double& a) { // add/subtract 2pi until a is within [a, 2pi]
    while( a < 0)
      a +=     2 * std::numbers::pi_v<long double>;
    while( a > 2 * std::numbers::pi_v<long double>)
      a -=     2 * std::numbers::pi_v<long double>;
  };
  static long double normalized(long double  a) {long double temp(a); normalize(temp); return temp;};
  //
  static long double distance(long double x1, long double y1, long double x2, long double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) );};
  static long double    angle(long double x1, long double y1, long double x2, long double y2) {
    return atan2(y2 - y1, x2 - x1);};
  static long double deg_to_rad(long double d) {return (d / 180) * std::numbers::pi_v<long double>;};
  static long double rad_to_deg(long double r) {return (r / std::numbers::pi_v<long double>) * 180;};
  static void set_angle_dist_from_of(long double a, long double dist, const pair_t& from, pair_t& to) {
    to.first  = from.first  + dist*cos(a);
    to.second = from.second + dist*sin(a);
  };
};


/* angle_addressable<>
 * (0) All angles are in degrees, not radians as in parent class angle_addressable_base<FLOAT>
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
template <typename FLOAT = double>
class angle_addressable : public angle_addressable_base<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef angle_addressable_base<float_t> angle_addressable_base_t;
  using angle_addressable_base_t::sin,  angle_addressable_base_t::cos;
  using angle_addressable_base_t::atan, angle_addressable_base_t::atan2;
  using angle_addressable_base_t::abs;
  using angle_addressable_base_t::sqrt;
  using angle_addressable_base_t::normalize, angle_addressable_base_t::normalized;
  using angle_addressable_base_t::distance;
  using angle_addressable_base_t::angle;
  using angle_addressable_base_t::deg_to_rad, angle_addressable_base_t::rad_to_deg;
  //
  float_t cx, cy;
  static void  normalize( float_t& deg); // add/subtract 360 to get 'a' into [0,360]
  static FLOAT normalized(float_t  deg) {return normalize(deg);};
  // Members for rotating a point around around this->(cx,cy)
  float_t distance(float_t x, float_t y) const {return distance(cx, cy, x, y);};
  float_t    angle(float_t x, float_t y) const {return  rad_to_deg(angle(cx, cy, x, y));};
  float_t get_x_rotated(float_t x, float_t y, float_t a) const;
  float_t get_y_rotated(float_t x, float_t y, float_t a) const;
  void rotate(float_t& x, float_t& y, float_t a) const;

  /* Trigonometric functions in angle_addressable<F> return radians,
   * unlike angle_addressable_base<F>, its parent class.
   * Maybe this should be reflected in their name, e.g. by renaming sin() to rsin()
   */
  static float_t  sin(float_t a) {return angle_addressable_base_t::sin(deg_to_rad(a));};
  static float_t  cos(float_t a) {return angle_addressable_base_t::cos(deg_to_rad(a));};
  static float_t atan(float_t x) {return             rad_to_deg(angle_addressable_base_t::atan(x));};
  static float_t atan2(float_t y, float_t x) {return rad_to_deg(angle_addressable_base_t::atan2(y,x));};
  //
  virtual float_t xperim(float_t degs) const = 0;
  virtual float_t yperim(float_t degs) const = 0;
  angle_addressable() = default;
  angle_addressable(float_t x, float_t y) : cx(x), cy(y) {};
};


// Implementations of angle_addressable<> members

template <typename FLOAT>
void  angle_addressable<FLOAT>::normalize( float_t& deg) {
  rad_to_deg(normalize(deg_to_rad(deg)));
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
