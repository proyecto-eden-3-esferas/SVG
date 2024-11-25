#ifndef SCHEMATICS_FET_H
#define SCHEMATICS_FET_H

#ifndef SCHEMATICS_TRANSISTOR_H
#include "schematics.transistor.h"
#endif

#include <iostream>

/* Unipolar transistors, or FET's,
 * are imagined or drawn like this:
 *
             .----- (drain)
             |
             |
   (gate)----.----- (source)
 * They divide into quite a few categories:
 * JFET (Junction Field Effect Transistor's)
   - p-channel
   - n-channel
   and
   MOSFET
   - p-channel: enhancement and depletion mode
   - n-channel: enhancement and depletion mode
 * They generally have  gate, source  and drain ports
   instead of BJT's'    base, emitter and collector
 * MOSFET's additionally have a body port... often connected to source
 *
 *
 */
template <typename FLOAT = double>
class fet : public transistor<FLOAT> {
public:
  typedef          circular<FLOAT> circular_t;
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  typedef std::size_t size_t;
  typedef transistor<FLOAT> transistor_t;
  using cir_t::deg_to_rad, cir_t::rad_to_deg;
  using transistor_t::angle_of_sym_axis, transistor_t::aemitter;
  using transistor_t::add_circle_to_svg, transistor_t::add_base_to_svg;
  using transistor_t::get_emitter_angle, transistor_t::get_collector_angle;
  //
  enum points {source=0, gate, drain, // on enclosing circle
               source_side_start_of_gate_cord=3, drain_side_start_of_gate_cord=4,
               source_side_start_of_gate     =5, drain_side_start_of_gate     =6,
               source_meets_gate             =7, drain_meets_gate             =8,
               midgate                       =9 // middle point of the gate, possibly goes unused
  };
          float_t get_source_angle() const {return get_emitter_angle()  ;};
          float_t get_drain_angle()  const {return get_collector_angle();};
  virtual float_t get_gate_angle()   const {return 180 + angle_of_sym_axis - aemitter;};
  float_t x_of_pin(size_t idx) const {
    switch (idx) {
      case gate:           return circular_t::xperim(get_gate_angle()); break;
      default:             return transistor_t::x_of_pin(idx); break;
    }
  };
  float_t y_of_pin(size_t idx) const {
    switch (idx) {
      case gate:           return circular_t::  yperim(get_gate_angle()); break;
      default:             return transistor_t::y_of_pin(idx)         ; break;
    }
  };
  //
  template <typename OUT = std::ostream>
  void add_source_to_svg(OUT& o) const {transistor_t::add_emitter_to_svg(o);};
  template <typename OUT = std::ostream>
  void add_drain_to_svg(OUT& o) const {transistor_t::add_collector_to_svg(o);};
  template <typename OUT = std::ostream>
  void add_to_gate_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  void add_svg(OUT& o) const {
    add_circle_to_svg(o);
    add_source_to_svg(o);
    add_drain_to_svg(o);
    add_base_to_svg(o); // actually, add gate line inside the enclosing circle
    add_to_gate_to_svg(o);
  };
  //
    fet(float_t ra, float_t x=0, float_t y=0,
       float_t angle_source = 33.0,
       float_t kgate        =  0.7) // > 0.77 otherwise a NaN is generated at some step
    :
       transistor_t(ra, x, y,
                    angle_source,
                    180 - cir_t::asin( cir_t::sin(angle_source) / (2*(kgate > 0.77 ? kgate : 0.78) - 1) ),
                                                                     (kgate > 0.77 ? kgate : 0.78),  1)
       {};
};

template <typename FLOAT>
template <typename OUT>
void fet<FLOAT>::add_to_gate_to_svg(OUT& o) const {
  o << "<line x1=\"" << x_of_pin(1) << "\" y1=\"" << y_of_pin(1) << '\"';
  o <<      " x2=\"" << x_of_pin(7) << "\" y2=\"" << y_of_pin(7) << "\"/>\n";
  //return o; // void return type
};


template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const fet<F>& tr, OUT& o = std::cout) { tr.add_svg(o);};

#endif
