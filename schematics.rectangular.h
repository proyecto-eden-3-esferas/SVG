#ifndef RECTANGULAR_H

#ifndef SCHEMATICS_ANGLE_H
#include "schematics.angle.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

/* class rectangular<> has sides parallel to X and Y axes
 * It does not take corner radius parameters (rx,ry)
 * as this would make the coding of xperim(ANGLE) and yperim(ANGLE)
 * very hard.
 * For a rectangle with rounded corners, see class rectangle
 * in "schematics.rectangle.h
 *
 */
template <typename FLOAT>
class rectangular : public angle_addressable<FLOAT>, public svg_shape<FLOAT> {
public:
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  float_t halfwidth, halfheight;
  using cir_t::cx, cir_t::cy;
  using cir_t::sin, cir_t::cos;
  using cir_t::atan, cir_t::atan2;
  using cir_t::abs, cir_t::sqrt;
  using cir_t::normalize;
protected:
  float_t trans_angle; // (positive) angle of upper right-hand vertex
  float_t long_radius; // length from the center to a vertex == sqrt(halfwidth^2 + halfheight^2)
public:
  float_t get_trans_angle() const {return trans_angle;};
  float_t get_long_radius() const {return long_radius;};
  virtual float_t xperim(float_t degs) const;// {return halfwidth*cos(degs);};
  virtual float_t yperim(float_t degs) const;// {return halfwidth*sin(degs);};
  void add_svg_unclosed(std::ostream& o = std::cout, const std::string& attrs = "") const override;
  //
  rectangular(float_t xr, float_t yr, float_t hw = 0, float_t hh=0) :
  cir_t(hw, hh), halfwidth(xr), halfheight(yr), trans_angle(atan(yr/xr)), long_radius(sqrt(xr*xr + yr*yr)) {};
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
    return cx + halfwidth;
  if( abs(degs - 180) <= trans_angle)
    return cx - halfwidth;
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
      return cy + halfheight;
    else
      return cy - halfheight;
};
template <typename FLOAT>
void rectangular<FLOAT>::add_svg_unclosed(std::ostream& o, const std::string& attrs) const {
  o << "<rect x=\"" << this->cx - this->halfwidth <<      "\" y=\"" << this->cy - this->halfheight << "\" ";
  o << "width=\"" << 2 * this->halfwidth << "\" height=\"" << 2 * this->halfheight << "\"";
};


// Partial specializations of add_svg_unclosed(RECTANGULAR,OUT)
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const rectangular<F>& rct, OUT& o = std::cout) {
  o << "<rect x=\"" << rct.cx - rct.halfwidth <<      "\" y=\"" << rct.cy - rct.halfheight << "\" ";
  o <<   "width=\"" <<        2*rct.halfwidth << "\" height=\"" <<        2*rct.halfheight << "\"";
  //return o; // void return type
};

#endif
