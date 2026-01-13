#ifndef SCHEMATICS_ROUND_H
#define SCHEMATICS_ROUND_H

/* File "schematics.round.cpp"
 * Defines subhierarchy of angle_addressable<> (its children):
 *   circular, and
 *   elliptical
 * Other classes derived from angle_addressable<> are
 * rectangular (in "schematics.rectangular.h")
 * polygonal   (in "schematics.polygonal.h")
 * Note that the names of the classes are adjectives, not nouns
 * TODO
 */

#ifndef SCHEMATICS_ANGLE_H
#include "schematics.angle.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

/* A 'circular' subhierarchy:
 * Derived class: 'slim_arrowhead',
   from which 'solid_arrowhead' is derived in turn.
 */
template <typename FLOAT = double>
class circular : public angle_addressable<FLOAT>, public svg_shape<FLOAT> {
public:
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  float_t r;
  using cir_t::cx, cir_t::cy;
  using cir_t::sin, cir_t::cos;
  virtual float_t xperim(float_t degs) const {return cx + r * cos(degs);};
  virtual float_t yperim(float_t degs) const {return cy + r * sin(degs);};
  void add_svg_unclosed(std::ostream& o = std::cout, const std::string& attrs = "") const override;
  //
  circular(float_t ra, float_t x=0, float_t y=0) : cir_t(x,y), r(ra) {};
};

template <typename FLOAT = double>
class elliptical : public angle_addressable<FLOAT>, public svg_shape<FLOAT> {
public:
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  using cir_t::cx, cir_t::cy;
  using cir_t::sin, cir_t::cos;
  float_t rx, ry;
  virtual float_t xperim(float_t degs) const {return cx + rx * cos(degs);};
  virtual float_t yperim(float_t degs) const {return cy + ry * sin(degs);};
  void add_svg_unclosed(std::ostream& o = std::cout, const std::string& attrs = "") const override;
  //
  elliptical(float_t r_x, float_t r_y, float_t x=0, float_t y=0) : cir_t(x,y), rx(r_x), ry(r_y) {};
};



/* Implementaions of class member funcions: */
template <typename FLOAT>
void circular<FLOAT>::add_svg_unclosed(std::ostream& o, const std::string& attrs) const {
  o << "<circle cx=\"" << this->cx << "\" cy=\"" << this->cy << "\" r=\"" << this->r << "\"";
};
template <typename FLOAT>
void elliptical<FLOAT>::add_svg_unclosed(std::ostream& o, const std::string& attrs) const {
  o << "<ellipse cx=\"" << this->cx << "\" cy=\"" << this->cy << "\" rx=\"" << this->rx << "\" ry=\"" << this->ry << "\"";
  //return o; // void return type
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


#endif
