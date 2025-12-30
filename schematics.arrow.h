#ifndef SCHEMATICS_ARROW_H
#define SCHEMATICS_ARROW_H

#ifndef SCHEMATICS_ROUND_H
#include "schematics.round.h"
#endif


template <typename FLOAT = double>
class slim_arrowhead : public circular<FLOAT> {
public:
  typedef angle_addressable<FLOAT> cir_t;
  typedef circular<FLOAT>     circular_t;
  typedef FLOAT float_t;
  /* An arrowhead is defined by the coordinates of the tip, and
     the coordinates of its back points or barbs.
   * The angle of each barb to the shaft is its "half_angle"
   * The coordinates for the barbs are produced from:
     cx,cy, r, shaft_angle, and half_angle
   * Rotations are effected through rotate_to(ABS_ANGLE) and rotate_by(ABS_ANGLE),
     which limit themselves to changing variable "shaft_angle".
   * Translations are effected by changing (cx,cy)
   */
  using cir_t::cx, cir_t::cy; // the coordinates of the tip
  using circular_t::r;
  float_t half_angle;
protected:
  // The following barb end coordinates assume that the tip is a (0,0):
  float_t shaft_angle;
public:
  float_t get_barb0x() const {return cx - r * cir_t::cos(shaft_angle + half_angle);};
  float_t get_barb0y() const {return cy + r * cir_t::sin(shaft_angle + half_angle);};
  float_t get_barb1x() const {return cx - r * cir_t::cos(shaft_angle - half_angle);};
  float_t get_barb1y() const {return cy + r * cir_t::sin(shaft_angle - half_angle);};
  //
  void rotate_to( float abs_angle ) {shaft_angle = abs_angle;};
  void rotate_by( float rel_angle ) {rotate_to(shaft_angle + rel_angle);};
  float_t get_shaft_angle() const {return shaft_angle;};
  //
  void add_svg_unclosed(std::ostream& o = std::cout) const override;
  // constructor(s)
  slim_arrowhead(float_t ra, float_t x=0, float_t y=0,
                 float_t sa = 0.0, float_t ha=cir_t::deg_to_rad(15))
  : circular_t(ra,x,y), half_angle(ha), shaft_angle(sa) {};
};
template<typename F>
void slim_arrowhead<F>::add_svg_unclosed(std::ostream& o) const {
  o << "<polyline fill=\"none\" points=\"";
  o << this->get_barb0x() << ' ' << this->get_barb0y() << "  ";
  o << this->cx << ' ' << this->cy << "  ";
  o << this->get_barb1x() << ' ' << this->get_barb1y() << '\"';
  //return o; // void return type
};



template <typename FLOAT = double>
class  solid_arrowhead : public slim_arrowhead<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef angle_addressable<FLOAT> cir_t;
  typedef slim_arrowhead<FLOAT> parent_t;
  using parent_t::get_barb0x, parent_t::get_barb0y;
  using parent_t::get_barb1x, parent_t::get_barb1y;
  // The "base" is the point where the shaft would meet the arrowhead as a triangle
  float_t get_base_x() const {return (get_barb0x() + get_barb1x()) / 2;};
  float_t get_base_y() const {return (get_barb0y() + get_barb1y()) / 2;};
  //
  void add_svg_unclosed(std::ostream& o = std::cout) const override;
  // constructor:
  solid_arrowhead(float_t ra, float_t x=0, float_t y=0,
                  float_t sa = 0.0, float_t ha=cir_t::deg_to_rad(15))
  : slim_arrowhead<FLOAT>(ra, x, y, sa, ha) {};
};
template<typename F>
void solid_arrowhead<F>::add_svg_unclosed(std::ostream& o) const {
  o << "<polygon points=\"";
  o << this->get_barb0x() << ' ' << this->get_barb0y() << "  ";
  o << this->cx << ' ' << this->cy << "  ";
  o << this->get_barb1x() << ' ' << this->get_barb1y() << '\"';
};

#ifndef FORMER
// Specializations for slim_arrowhead<FLOAT> and solid_arrowhead<FLOAT>:
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const slim_arrowhead<F>& ah, OUT& o = std::cout) {
  ah.add_svg_unclosed(o);
};
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const solid_arrowhead<F>& ah, OUT& o = std::cout) {
  ah.add_svg_unclosed(o);
};
#else
// Specializations for slim_arrowhead<FLOAT> and solid_arrowhead<FLOAT>:
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const slim_arrowhead<F>& ah, OUT& o = std::cout) {
  o << "<polyline fill=\"none\" points=\"";
  o << ah.get_barb0x() << ' ' << ah.get_barb0y() << "  ";
  o << ah.cx << ' ' << ah.cy << "  ";
  o << ah.get_barb1x() << ' ' << ah.get_barb1y() << '\"';
};
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const solid_arrowhead<F>& ah, OUT& o = std::cout) {
  o << "<polygon points=\"";
  o << ah.get_barb0x() << ' ' << ah.get_barb0y() << "  ";
  o << ah.cx << ' ' << ah.cy << "  ";
  o << ah.get_barb1x() << ' ' << ah.get_barb1y() << '\"';
};
#endif

#endif
