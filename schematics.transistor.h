#ifndef SCHEMATICS_TRANSISTOR_H
#define SCHEMATICS_TRANSISTOR_H

#include "schematics.round.h"
#include "schematics.line.h"
#include "schematics.arrow.h"
#include <iostream>

/* Class bjt/transistor (a bipolar-junction transistor)
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
class transistor : public circular<FLOAT> {
public:
  typedef          circular<FLOAT> circular_t;
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  typedef std::size_t size_t;
  enum points {emitter, base, collector=2,
               emitter_side_start_of_base=3, collector_side_start_of_base=4,
               emitter_meets_base=5, collector_meets_base=6,
               from0, from1, from2};
  using circular_t::cx, circular_t::cy, circular_t::r;
  using circular_t::xperim, circular_t::yperim;
  FLOAT ae;    // angle of the emitter   to the X axis
  FLOAT ac;    // angle of the collector to the X axis
  FLOAT abase; // angle of the base      to the X axis
  FLOAT kbase;  // k is a factor: k==1.0 means the base is drawn as a chord
  FLOAT kkbase; // k==1.0 means emitter and collector leads meat the base at the edge
  FLOAT x_of_pin(size_t idx) const;
  FLOAT y_of_pin(size_t idx) const;
  template <typename OUT = std::ostream>
  OUT& add_circle_to_svg(OUT& o) const;
  // Lines inside the transistor circle: base, emitter, collector
  template <typename OUT = std::ostream>
  OUT& add_base_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  OUT& add_emitter_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  OUT& add_collector_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  OUT& add_svg(OUT& o) const;
  //
  transistor(float_t ra, float_t x=0, float_t y=0,
             float_t ab = cir_t::deg_to_rad(130),
             float_t ap = cir_t::deg_to_rad(60),
             float_t kb = 0.8) :
    circular_t(ra,x,y), ae(ap), ac(ap), abase(ab), kbase(kb), kkbase(kb) {};
};
/* Implementations of transistor<FLOAT> methods
 */
template <typename FLOAT>
template <typename OUT>
OUT& transistor<FLOAT>::add_circle_to_svg(OUT& o) const {
  o << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << r << "\"/>\n";
  return o;
};
template <typename FLOAT>
template <typename OUT>
OUT& transistor<FLOAT>::add_base_to_svg(OUT& o) const {
  o << "<line x1=\"" << x_of_pin(3) << "\" y1=\"" << y_of_pin(3) << '\"';
  o <<      " x2=\"" << x_of_pin(4) << "\" y2=\"" << y_of_pin(4) << "\"/>\n";
  return o;
};
template <typename FLOAT>
template <typename OUT>
OUT& transistor<FLOAT>::add_emitter_to_svg(OUT& o) const {
  o << "<line x1=\"" << x_of_pin(0) << "\" y1=\"" << y_of_pin(0) << '\"';
  o <<      " x2=\"" << x_of_pin(5) << "\" y2=\"" << y_of_pin(5) << "\"/>\n";
  return o;
};
template <typename FLOAT>
template <typename OUT>
OUT& transistor<FLOAT>::add_collector_to_svg(OUT& o) const {
  o << "<line x1=\"" << x_of_pin(2) << "\" y1=\"" << y_of_pin(2) << '\"';
  o <<      " x2=\"" << x_of_pin(6) << "\" y2=\"" << y_of_pin(6) << "\"/>\n";
  return o;
};
template <typename FLOAT>
template <typename OUT>
OUT& transistor<FLOAT>::add_svg(OUT& o) const {
  add_emitter_to_svg(o);
  add_collector_to_svg(o);
  add_circle_to_svg(o);
  return add_base_to_svg(o);
};
//
template <typename FLOAT>
FLOAT transistor<FLOAT>::x_of_pin(size_t idx) const {
  switch (idx) {
    case 0: return cx + r * cir_t::cos(ae);
    case 1: return cx - r;
    case 2: return cx + r * cir_t::cos(ac);
    case 3:// return cx + r * cir_t::cos(abase);
    case 4:// return cx + r * cir_t::cos(abase);
    // Inside the transistor circle, along the base, top to bottom:
    case 5:
    case 6: return cx + r * cir_t::cos(abase);
    case 7: return cx + r * cir_t::cos(ac);;
    default: return 0.0;
  }
};
template <typename FLOAT>
FLOAT transistor<FLOAT>::y_of_pin(size_t idx) const {
  switch (idx) {
    case 0: return cy - r * cir_t::sin(ae);
    case 1: return cy - r;
    case 2: return cy + r * cir_t::sin(ac);
    case 3: return cy - kbase * r * cir_t::sin(abase);
    case 4: return cy + kbase * r * cir_t::sin(abase);
    // Inside the transistor circle, along the base, top to bottom:
    case 5: return cy - kkbase * kbase * r * cir_t::sin(abase);
    case 6: return cy + kkbase * kbase * r * cir_t::sin(abase);
    default: return 0.0;
  }
};

template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const transistor<F>& tr, OUT& o = std::cout) {
  o << "<circle cx=\"" << tr.cx << "\" cy=\"" << tr.cy << "\" r=\"" << tr.r << "\"/>\n";
  o << "<line x1=\"" << tr.x_of_pin(3) << "\" y1=\"" << tr.y_of_pin(3) << '\"';
  o <<       "x2=\"" << tr.x_of_pin(4) << "\" y2=\"" << tr.y_of_pin(4) << "\">\n";
  // add_svg(static_cast<circular<float_type>>(b), o);
  return o;
};


#endif
