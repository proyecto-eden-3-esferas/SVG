#ifndef SCHEMATICS_ROUND_H
#define SCHEMATICS_ROUND_H

/* File "schematics.round.cpp"
 * Defines subhierarchy of angle_addressable<> (its children):
 *   circular
 *   elliptical, and
 *   rectangular
 * Note that the names of the classes are adjectives
 */

#ifndef SCHEMATICS_ANGLE_H
#include "schematics.angle.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

//  Children of angle_addressable<>

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
  using cir_t::sin, cir_t::cos;
  using cir_t::atan, cir_t::atan2;
  using cir_t::abs, cir_t::sqrt;
  virtual float_t xperim(float_t degs) const {return cx + r * cos(degs);};
  virtual float_t yperim(float_t degs) const {return cy + r * sin(degs);};
  circular(float_t ra, float_t x=0, float_t y=0) : cir_t(x,y), r(ra) {};
};


template <typename FLOAT = double>
class elliptical : public angle_addressable<FLOAT> {
public:
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  using cir_t::cx, cir_t::cy;
  using cir_t::sin, cir_t::cos;
  float_t rx, ry;
  virtual float_t xperim(float_t degs) const {return cx + rx * cos(degs);};
  virtual float_t yperim(float_t degs) const {return cy + ry * sin(degs);};
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
  using cir_t::sin, cir_t::cos;
  using cir_t::atan, cir_t::atan2;
  using cir_t::abs, cir_t::sqrt;
  using cir_t::normalize;
protected:
  float_t trans_angle; // (positive) angle of upper right-hand vertex
  float_t long_radius; // length from the center to a vertex == sqrt(rx^2 + ry^2)
public:
  float_t get_trans_angle() const {return trans_angle;};
  float_t get_long_radius() const {return long_radius;};
  virtual float_t xperim(float_t degs) const;// {return rx*cos(degs);};
  virtual float_t yperim(float_t degs) const;// {return rx*sin(degs);};
  //
  rectangular(float_t xr, float_t yr, float_t _cx = 0, float_t _cy=0) :
  cir_t(_cx, _cy), rx(xr), ry(yr), trans_angle(atan(yr/xr)), long_radius(sqrt(xr*xr + yr*yr)) {};
};
/* Member functions rectangular::xperim(DEGS) and rectangular::xperim(DEGS)
   first normalize the angle input parameter to the interval [0,360]
   through angle_addressable::normalize(),
 * then
 */
template <typename FLOAT>
FLOAT rectangular<FLOAT>::xperim(FLOAT degs) const {
  normalize(degs);
  if( (degs <= trans_angle) || ( degs - 360 >= -trans_angle) )
    return cx + rx;
  if( abs(degs - 180) <= trans_angle)
    return cx - rx;
  else
    return cx + long_radius*cos(degs);
};
template <typename FLOAT>
FLOAT rectangular<FLOAT>::yperim(FLOAT degs) const {
  normalize(degs);
  if(degs <= trans_angle  ||  (degs - 180) >= -trans_angle )
    return cy + long_radius*sin(degs);
  else
    if(degs <= 180)
      return cy + ry;
    else
      return cy - ry;
};


// Partial specializations of add_svg_unclosed(ANGLE_ADDRESSABLE&,OUT&)

// First, specializations for angle-addressable components in "schematics.round.h"
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const circular<F>& cc, OUT& o = std::cout) {
  o << "<circle cx=\"" << cc.cx << "\" cy=\"" << cc.cy << "\" r=\"" << cc.r << "\"";
  //return o; // void return type
};

template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const elliptical<F>& cc, OUT& o = std::cout) {
  o << "<ellipse cx=\"" << cc.cx << "\" cy=\"" << cc.cy << "\" rx=\"" << cc.rx << "\" ry=\"" << cc.ry << "\"";
  //return o; // void return type
};
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const rectangular<F>& rct, OUT& o = std::cout) {
  o << "<rect x=\"" << rct.cx - rct.rx <<      "\" y=\"" << rct.cy - rct.ry << "\" ";
  o <<   "width=\"" <<        2*rct.rx << "\" height=\"" <<        2*rct.ry << "\"";
  //return o; // void return type
};

#endif
