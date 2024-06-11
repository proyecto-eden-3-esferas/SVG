#ifndef SCHEMATICS_ARROW_H
#define SCHEMATICS_ARROW_H

#ifndef SCHEMATICS_ROUND_H
#include #include "schematics.round.h"
#endif


template <typename FLOAT = double>
class slim_arrowhead : public circular<FLOAT> {
public:
  typedef angle_addressable<FLOAT> cir_t;
  typedef circular<FLOAT>     circular_t;
  typedef FLOAT float_t;
  /* An arrowhead is defined by the coordinates of the tip,
     the coordinates of its back points or barbs,
     and the angle of each barb to the shaft ('half_angle')
   * The coordinates for the barbs are set upon initialization,
     and 'half_angle' is kept in case we want to rotate
     the arrowhead to an angle, through rotate_to(ABS_ANGLE).
   * Rotation only changes the four barb[01][xy] coordinates
   * Clients should not access these directly, but call get_barb**() instead.
   * Translations are effected by changing (cx,cy)
   */
  using cir_t::cx, cir_t::cy;
  using circular_t::r;
  float_t half_angle;
  // The following barb end coordinates assume that the tip is a (0,0):
  float_t barb0x, barb0y, barb1x, barb1y;
  float_t get_barb0x() const {return cx + barb0x;};
  float_t get_barb0y() const {return cy + barb0y;};
  float_t get_barb1x() const {return cx + barb1x;};
  float_t get_barb1y() const {return cy + barb1y;};
  float_t shaft_angle;
  //void rotate_by( float rel_angle ) {}; // UNIMPLEMENTED
  void rotate_to( float abs_angle ) {
    shaft_angle = abs_angle;
    barb0x = r * cir_t::cos(std::numbers::pi - half_angle + shaft_angle);
    barb0y = r * cir_t::sin(std::numbers::pi - half_angle + shaft_angle);
    barb1x = r * cir_t::cos(std::numbers::pi + half_angle + shaft_angle);
    barb1y = r * cir_t::sin(std::numbers::pi + half_angle + shaft_angle);
  };
  void rotate_by( float rel_angle ) {rotate_to(shaft_angle + rel_angle);};
  slim_arrowhead(float_t ra, float_t x=0, float_t y=0, float_t ha=cir_t::deg_to_rad(15) )
  : circular_t(ra,x,y), half_angle(ha),
    barb0x( - r * cir_t::cos(half_angle)),
    barb0y( + r * cir_t::sin(half_angle)),
    barb1x( + barb0x),
    barb1y( - barb0y), shaft_angle(0.0) {};
};
template <typename FLOAT = double>
class  solid_arrowhead : public slim_arrowhead<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef angle_addressable<FLOAT> cir_t;
  typedef slim_arrowhead<FLOAT> parent_t;
  using parent_t::get_barb0x, parent_t::get_barb0y;
  using parent_t::get_barb1x, parent_t::get_barb1y;
  //
  float_t get_base_x() const {return (get_barb0x() + get_barb1x()) / 2;};
  float_t get_base_y() const {return (get_barb0y() + get_barb1y()) / 2;};
  solid_arrowhead(float_t ra, float_t x=0, float_t y=0, float_t ha=cir_t::deg_to_rad(15) )
  : slim_arrowhead<FLOAT>(ra, x, y, ha) {};
};

// Specializations for slim_arrowhead<FLOAT> and solid_arrowhead<FLOAT>:
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const slim_arrowhead<F>& ah, OUT& o = std::cout) {
  o << "<polyline points=\"";
  o << ah.get_barb0x() << ' ' << ah.get_barb0y() << "  ";
  o << ah.cx << ' ' << ah.cy << "  ";
  o << ah.get_barb1x() << ' ' << ah.get_barb1y() << '\"';
  return o;
};
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const solid_arrowhead<F>& ah, OUT& o = std::cout) {
  o << "<polygon points=\"";
  o << ah.get_barb0x() << ' ' << ah.get_barb0y() << "  ";
  o << ah.cx << ' ' << ah.cy << "  ";
  o << ah.get_barb1x() << ' ' << ah.get_barb1y() << '\"';
  return o;
};

#endif
