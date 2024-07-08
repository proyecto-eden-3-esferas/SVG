#ifndef SCHEMATICS_ANGLE_H
#define SCHEMATICS_ANGLE_H

#include <cmath>

/* angle_addressable<>
 * (1) can return a point's coordinates from an angle,
 * (2) contains some static member functions for trigonometry,
 *     which are defined differently in specializations for FLOAT = float or long double
 * (3) declares pure virtual members 'xperim(rads)' and 'xperim(rads)'
 * (4) its children have member variables cx,cy (for center of shape) and rx,ry for radius
 *     save for circular<>, a circle, which only has 'r'
 *
 */
template <typename FLOAT = double>
class angle_addressable {
public:
  typedef FLOAT float_t;
  float_t cx, cy;
  //static float_t deg_to_rads(float_t d) {return (d / 180)      * 3.141592;};
  //static float_t rads_to_deg(float_t r) {return (r / 3.141592) * 180;};
  static float_t deg_to_rad(float_t d) {return (d / 180)      * 3.141592;};
  static float_t rad_to_deg(float_t r) {return (r / 3.141592) * 180;};
  static float_t  sin(float_t a) {return :: sin(a);};
  static float_t  cos(float_t a) {return :: cos(a);};
  static float_t atan(float_t a) {return ::atan(a);};
  virtual float_t xperim(float_t rads) const = 0;
  virtual float_t yperim(float_t rads) const = 0;
  angle_addressable() = default;
  angle_addressable(float_t x, float_t y) : cx(x), cy(y) {};
};
template <>
class angle_addressable<float> {
public:
  typedef float float_t;
  float_t cx, cy;
  static float deg_to_rads(float d) {return (d / 180)      * 3.141592;};
  static float rads_to_deg(float r) {return (r / 3.141592) * 180;};
  static float deg_to_rad( float d) {return (d / 180)      * 3.141592;};
  static float rad_to_deg( float r) {return (r / 3.141592) * 180;};
  static float  sinf(float a) {return :: sin(a);};
  static float  cosf(float a) {return :: cos(a);};
  static float atanf(float a) {return ::atan(a);};
  virtual float xperim(float rads) const = 0;
  virtual float yperim(float rads) const = 0;
  angle_addressable() = default;
  angle_addressable(float_t x, float_t y) : cx(x), cy(y) {};
};
template <>
class angle_addressable<long double> {
public:
  typedef long double float_t;
  float_t cx, cy;
  static long double deg_to_rads(long double d) {return (d / 180)      * 3.141592;};
  static long double rads_to_deg(long double r) {return (r / 3.141592) * 180;};
  static long double deg_to_rad(long double d) {return (d / 180)      * 3.141592;};
  static long double rad_to_deg(long double r) {return (r / 3.141592) * 180;};
  static long double  sinl(long double a) {return :: sin(a);};
  static long double  cosl(long double a) {return :: cos(a);};
  static long double atanl(long double a) {return ::atan(a);};
  virtual long double xperim(long double rads) const = 0;
  virtual long double yperim(long double rads) const = 0;
  angle_addressable() = default;
  angle_addressable(long double x, long double y) : cx(x), cy(y) {};
};

#endif
