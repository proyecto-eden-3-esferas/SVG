#ifndef SCHEMATICS_TRANSISTOR_H
#define SCHEMATICS_TRANSISTOR_H

#include "schematics.round.h"
#include "schematics.line.h"
#include "schematics.arrow.h"

/* Class bjt (a bipolar-junction transistor)
 * The pins are:
 * (0) emitter
 * (1) base
 * (2) collector
 * (3) emitter-side start of cord
 * (4) collector-side start of cord
 * (5) from 0
 * (6) from 1
 * (7) from 2
 */

template <typename FLOAT = double>
class bjt : public circular<FLOAT> {
public:
  typedef          circular<FLOAT> circular_t;
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  typedef std::size_t size_t;
  enum ports {emitter, base, collector, emitter_side_start_of_cord, collector_side_start_of_cord, from0, from1, from2};
  FLOAT apow;  // angle of the emitter or, symetrically, the collector
  FLOAT abase; // angle of the base
  FLOAT kbase; //
  FLOAT x_of_pin(size_t idx) const;
  FLOAT y_of_pin(size_t idx) const;
  bjt(float_t ra, float_t x=0, float_t y=0,
             float_t ab = cir_t::deg_to_rad(120),
             float_t ap = cir_t::deg_to_rad(60),
             float_t kb = 0.2) :
    circular_t(ra,x,y), apow(ap), abase(ab), kbase(0.2) {};
};
template <typename FLOAT>
FLOAT bjt<FLOAT>::x_of_pin(size_t idx) const {
  switch (idx) {
    case 0: return circular_t::x + circular_t::r * cir_t::cos(apow);
    case 1: return circular_t::x + circular_t::r * cir_t::cos(abase);
    case 2: return circular_t::x - circular_t::r;
    case 3: return circular_t::x + circular_t::r * cir_t::cos(abase);
    case 4: return circular_t::x + circular_t::r * cir_t::cos(apow);
    // Inside the bjt circle, along the base, top to bottom:
    case 5: return circular_t::x + circular_t::r * cir_t::cos(abase);
    case 6: return circular_t::x + circular_t::r * cir_t::cos(abase);
    case 7: return circular_t::x + circular_t::r * cir_t::cos(abase);
  }
};
template <typename FLOAT>
FLOAT bjt<FLOAT>::y_of_pin(size_t idx) const {
  switch (idx) {
    case 0: return circular_t::x + circular_t::r * cir_t::sin(apow);
    case 1: return circular_t::x + circular_t::r * cir_t::sin(abase);
    case 2: return circular_t::x - circular_t::r;
    case 3: return circular_t::x + circular_t::r * cir_t::sin(abase);
    case 4: return circular_t::x + circular_t::r * cir_t::sin(apow);
    // Inside the bjt circle, along the base, top to bottom:
    case 5: return circular_t::x + circular_t::r * cir_t::sin(abase);
    case 6: return circular_t::x + circular_t::r * cir_t::sin(abase);
    case 7: return circular_t::x + circular_t::r * cir_t::sin(abase);
  }
};

template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const bjt<F>& cc, OUT& o = std::cout) {
  o << "<circle cx=\"" << cc.cx << "\" cy=\"" << cc.cy << "\" r=\"" << cc.r << "\"/>";
  // add_svg(static_cast<circular<float_type>>(b), o);
  return o;
};


#endif
