#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H


/* Class trigonometry<> uses radians,
 * Its (only) child, 'geometry_2d' has no template specializations
   and adds member functions:
   - normalize
   - normalized
   - distance
   - angle
   - deg_to_rad
   - rad_to_deg
   whereas its grandchild uses degrees.
 * None of these classes has member variables.
   Thus, all member functions are declared static.
 */

#ifndef NAMED_TYPE_H
#include "NamedType.h"
#endif

#include <cmath>
#include <numbers>
//#include <utility>

template <typename FLOAT = double>
class trigonometry {
public:
  typedef FLOAT float_t;
  using radian_t = Radian<float_t>;
  typedef std::pair<float_t,float_t> pair_t;
  static float_t  sin(radian_t a) {return  ::sin(a.get());};
  static float_t  cos(radian_t a) {return  ::cos(a.get());};
  //
  static radian_t  asin(float_t sn) {return  radian_t(::asin(sn));};
  static radian_t  acos(float_t cs) {return  radian_t(::acos(cs));};
  static radian_t atan(float_t n) {return radian_t(::atan(n));};
  static radian_t atan2(float_t x, float_t y) {return radian_t(::atan2(x,y));};
  //
};

template <>
class trigonometry<float> {
public:
  using radian_t = Radian<float>;
  typedef std::pair<float,float> pair_t;
  static float  sin(radian_t a) {return :: sinf(a.get());};
  static float  cos(radian_t a) {return :: cosf(a.get());};
  //
  static radian_t  asin(float_t sn) {return  radian_t(::asinf(sn));};
  static radian_t  acos(float_t cs) {return  radian_t(::acosf(cs));};
  static radian_t atan(float n) {return radian_t(::atanf(n));};
  static radian_t atan2(float x, float y) {return radian_t(::atan2f(x, y));};
};

template <>
class trigonometry<long double> {
public:
  using radian_t = Radian<long double>;
  typedef std::pair<long double,long double> pair_t;
  static long double  sin(radian_t a) {return :: sinl(a.get());};
  static long double  cos(radian_t a) {return :: cosl(a.get());};
  //
  static radian_t  asin(float_t sn) {return  radian_t(::asinl(sn));};
  static radian_t  acos(float_t cs) {return  radian_t(::acosl(cs));};
  static radian_t atan( long double n) {return radian_t(::atanl(n));};
  static radian_t atan2(long double x, long double y) {return radian_t(::atan2l(x,y));};
};

#endif
