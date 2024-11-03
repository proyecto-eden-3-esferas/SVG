#ifndef GEOMETRY_2D
#define GEOMETRY_2D

#include <cmath>
#include <numbers>
#include <utility>



/* class geometry_2D_base<>
   provides trigonometric functions, plus abs() and sqrt()
   in specializations for float, double and long double.
 * It uses radians, whereas its only child angle_addressable<>
   uses degrees.
 */

template <typename FLOAT = double>
class geometry_2D_base {
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
};

template <>
class geometry_2D_base<float> {
public:
  typedef std::pair<float,float> pair_t;
  static float  sin(float a) {return :: sinf(a);};
  static float  cos(float a) {return :: cosf(a);};
  static float atan(float a) {return ::atanf(a);};
  static float atan2(float a, float b) {return ::atan2f(a,b);};
  //
  static float   abs(float f) {return ::fabsf(f);};
  static float  sqrt(float f) {return ::sqrtf(f);};
};

template <>
class geometry_2D_base<long double> {
public:
  typedef std::pair<long double,long double> pair_t;
  static long double  sin(long double a) {return :: sinl(a);};
  static long double  cos(long double a) {return :: cosl(a);};
  static long double atan(long double a) {return ::atanl(a);};
  static long double atan2(long double a, long double b) {return ::atan2l(a,b);};
  //
  static long double   abs(long double ld) {return ::fabsl(ld);};
  static long double  sqrt(long double ld) {return ::sqrt(ld);};
};


/* class geometry_2D<> provides geometry static functions
 * that need not be specialized for numeric type (fload, double, long double)
   - normalize(FLOAT&) and normalized(FLOAT)
   - distance(X1,Y1, X2,Y2)
   - distance(X1,Y1, X2,Y2), and
   - set_angle_dist_from_of(ANGLE, DISTANCE, CONST POINT&, POINT&)
 * Like its parent, it uses radians,
 * (whereas its only child angle_addressable<>,
   in another header or compilation unit, uses degrees.
 */

template <typename FLOAT = double>
class geometry_2D : public geometry_2D_base<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef std::pair<float_t,float_t> pair_t;
  typedef geometry_2D_base<float_t> geometry_2D_base_t;
  using geometry_2D_base_t::sin;
  using geometry_2D_base_t::cos;
  using geometry_2D_base_t::atan;
  using geometry_2D_base_t::atan2;
  using geometry_2D_base_t::abs;
  using geometry_2D_base_t::sqrt;
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
  static float_t distance(const pair_t& p1, const pair_t& p2) {
    return distance(p1.first, p1.second, p2.first, p2.second); }
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
}; // class geometry_2D<FLOAT>

#endif
