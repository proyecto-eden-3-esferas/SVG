#ifndef GEOMETRY_2D_H
#define GEOMETRY_2D_H

#include <cmath>
#include <numbers>
#include <utility>

#ifndef TRIGONOMETRY_H
#include "trigonometry.h"
#endif

#ifndef NUMERICAL_H
#include "numerical.h"
#endif

#ifndef NAMED_TYPE_H
#include "NamedType.h"
#endif

/* class geometry_2d<> provides geometry static functions
 * that need not be specialized for numeric type (fload, double, long double)
   - normalize(FLOAT&) and normalized(FLOAT)
   - distance(X1,Y1, X2,Y2),
   - distance(std::pair(X1,Y1), std::pair(X2,Y2), and
   - set_angle_dist_from_of(ANGLE, DISTANCE, CONST POINT&, POINT&)
 * Like its parents (trigonometry<> and numerical<>), it uses radians,
 * (whereas its only child uses degrees.
 */

template <typename FLOAT = double>
class geometry_2d : public trigonometry<FLOAT>, public numerical<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef std::pair<float_t,float_t> pair_t;
  typedef trigonometry<float_t> trigonometry_t;
  typedef numerical<   float_t>    numerical_t;
  using trigonometry_t::sin;
  using trigonometry_t::cos;
  using trigonometry_t::atan;
  using trigonometry_t::atan2;
  using numerical_t::abs;
  using numerical_t::sqrt;
  //
  static void normalize(FLOAT& a);
  static float_t normalized(float_t  a) {float_t temp(a); normalize(temp); return temp;};
  //
  static float_t distance(float_t x1, float_t y1, float_t x2, float_t y2);
  static float_t distance(const pair_t& p1, const pair_t& p2);

  static float_t    angle(float_t x1, float_t y1, float_t x2, float_t y2);

  static float_t deg_to_rad(float_t d) {return (d / 180) * std::numbers::pi_v<float_t>;};
  static float_t rad_to_deg(float_t r) {return (r / std::numbers::pi_v<float_t>) * 180;};
  /* static void set_angle_dist_from_of(...)
     takes a source point (from), an angle to the X-axis,
     an in/out point "to" (non-const reference) and a distance 'dist',
     and sets the in/out point 'to'
     so that the line from 'from' to 'to' is at an angle 'a' to the X-axis,
     and is dist[ance] units long.*/
  static void set_angle_dist_from_of(float_t a, float_t dist, const pair_t& from, pair_t& to);
}; // class geometry_2d<FLOAT>

#endif


#ifndef GEOMETRY_2D_CPP
#define GEOMETRY_2D_CPP

#ifndef GEOMETRY_2D_H
#include "geometry_2d.h"
#endif

template <typename FLOAT>
void geometry_2d<FLOAT>::normalize(FLOAT& a) { // add/subtract 2pi until a is within [a, 2pi]
  while( a < 0)
    a +=     2 * std::numbers::pi_v<FLOAT>;
  while( a > 2 * std::numbers::pi_v<FLOAT>)
    a -=     2 * std::numbers::pi_v<FLOAT>;
};

template <typename FLOAT>
FLOAT geometry_2d<FLOAT>::distance(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) );};
template <typename FLOAT>
FLOAT geometry_2d<FLOAT>::distance(const std::pair<FLOAT,FLOAT>& p1, const std::pair<FLOAT,FLOAT>& p2) {
  return distance(p1.first, p1.second, p2.first, p2.second); };
template <typename FLOAT>
FLOAT geometry_2d<FLOAT>::angle(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2) {
  return atan2(y2 - y1, x2 - x1);};
template <typename FLOAT>
void geometry_2d<FLOAT>::set_angle_dist_from_of(FLOAT a,
                                         FLOAT dist,
                                         const std::pair<FLOAT,FLOAT>& from,
                                               std::pair<FLOAT,FLOAT>& to) {
  to.first  = from.first  + dist*cos(a);
  to.second = from.second + dist*sin(a);
};

#endif
