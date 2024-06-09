#ifndef SCHEMATICS_ROUND_H
#define SCHEMATICS_ROUND_H

/* File "schematics.round.cpp"
 * Defines subhierarchy:
 *   angle_addressable<> and its children:
 *   circular, elliptical, and rectangular
 *   (location on perimeter by angle)
 */

#include <cmath>
#include <numbers>
#include <utility>
#include <vector>

/* angle_addressable<> and its children
 * (1) can return a point's coordinates according to an angle,
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
  static float_t deg_to_rads(float_t d) {return (d / 180)      * 3.141592;};
  static float_t rads_to_deg(float_t r) {return (r / 3.141592) * 180;};
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
  static long double  sinl(long double a) {return :: sin(a);};
  static long double  cosl(long double a) {return :: cos(a);};
  static long double atanl(long double a) {return ::atan(a);};
  virtual long double xperim(long double rads) const = 0;
  virtual long double yperim(long double rads) const = 0;
  angle_addressable() = default;
  angle_addressable(float_t x, float_t y) : cx(x), cy(y) {};
};

/* A 'circular' subhierarchy:
 * Derived class: 'slim_arrowhead',
   from which 'solid_arrowhead' is derived in turn.
 */
template <typename FLOAT = double>
class circular : public angle_addressable<FLOAT> {
public:
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  float_t r;
  using cir_t::cx, cir_t::cy;
  virtual float_t xperim(float_t rads) const {return cx + r*cir_t::cos(rads);};
  virtual float_t yperim(float_t rads) const {return cy - r*cir_t::sin(rads);};
  circular(float_t ra, float_t x=0, float_t y=0) : cir_t(x,y), r(ra) {};
};


template <typename FLOAT = double>
class elliptical : public angle_addressable<FLOAT> {
public:
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  using cir_t::cx, cir_t::cy;
  float_t rx, ry;
  virtual float_t xperim(float_t rads) const {return cx + rx*cir_t::cos(rads);};
  virtual float_t yperim(float_t rads) const {return cy - ry*cir_t::sin(rads);};
  //elliptical(float_t r_x, float_t r_y, float_t x=0, float_t y=0) : rx(r_x), ry(r_y), cx(x), cy(y) {};
  elliptical(float_t r_x, float_t r_y, float_t x=0, float_t y=0) : cir_t(x,y), rx(r_x), ry(r_y) {};
};

/* rectangular<> has sides parallel to X and Y axes */
template <typename FLOAT = double>
class rectangular : public angle_addressable<FLOAT> {
public:
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  float_t rx, ry;
  using cir_t::cx, cir_t::cy;
  float_t trans_angle; // angle of upper right-hand vertex
  float_t long_radius; // length from the center to a vertex == sqrt(rx^2 + ry^2)
  virtual float_t xperim(float_t rads) const;// {return rx*cir_t::cos(rads);};
  virtual float_t yperim(float_t rads) const;// {return rx*cir_t::sin(rads);};
  rectangular(float_t xr, float_t yr, float_t _cx = 0, float_t _cy=0) :
  cir_t(_cx, _cy), rx(xr), ry(yr), trans_angle(atan(yr/xr)), long_radius(sqrt(xr*xr + yr*yr)) {};
  //  rx(xr), ry(yr), cx(_cx), cy(_cy), trans_angle(atan(yr/xr)), long_radius(sqrt(xr*xr + yr*yr)) {};
};
template <typename FLOAT>
FLOAT rectangular<FLOAT>::xperim(FLOAT rads) const {
  if(abs(rads) <= trans_angle)
    return cx + rx;
  else
    return cx + long_radius*cir_t::cos(rads);
};
template <typename FLOAT>
FLOAT rectangular<FLOAT>::yperim(FLOAT rads) const {
  if(abs(rads) <= trans_angle)
    return cy - long_radius*cir_t::sin(rads);
  else
    return cy - ry;
};


// Partial specializations of add_svg_unclosed(ANGLE_ADDRESSABLE&,OUT&)
#ifndef SVG_H
#include "svg.h"
#endif
// First, specializations for angle-addressable components in "schematics.round.h"
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const circular<F>& cc, OUT& o = std::cout) {
  o << "<circle cx=\"" << cc.cx << "\" cy=\"" << cc.cy << "\" r=\"" << cc.r << "\"";
  return o;
};

template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const elliptical<F>& cc, OUT& o = std::cout) {
  o << "<ellipse cx=\"" << cc.cx << "\" cy=\"" << cc.cy << "\" rx=\"" << cc.rx << "\" ry=\"" << cc.ry << "\"";
  return o;
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const rectangular<F>& rct, OUT& o = std::cout) {
  o << "<rect x=\"" << rct.cx - rct.rx <<      "\" y=\"" << rct.cy - rct.ry << "\" ";
  o <<   "width=\"" <<        2*rct.rx << "\" height=\"" <<        2*rct.ry << "\"";
  return o;
};


#endif
