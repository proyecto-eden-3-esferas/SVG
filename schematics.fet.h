#ifndef SCHEMATICS_FET_H
#define SCHEMATICS_FET_H

#ifndef SCHEMATICS_TRANSISTOR_H
#include "schematics.transistor.h"
#endif

#include <iostream>

template <typename FLOAT = double>
class fet : public transistor<FLOAT> {
public:
  typedef          circular<FLOAT> circular_t;
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  typedef std::size_t size_t;
  typedef transistor<FLOAT> transistor_t;
  using transistor_t::x_of_pin, transistor_t::y_of_pin;
  using transistor_t::add_circle_to_svg, transistor_t::add_base_to_svg;
  //
  template <typename OUT = std::ostream>
  OUT& add_emitter_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  OUT& add_collector_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  OUT& add_svg(OUT& o) const {
    add_emitter_to_svg(o);
    add_collector_to_svg(o);
    add_circle_to_svg(o);
    return add_base_to_svg(o);
  };
  //
  fet(float_t ra, float_t x=0, float_t y=0,
      float_t ab = cir_t::deg_to_rad(130),
      float_t ap = cir_t::deg_to_rad(60),
      float_t kb = 0.8, float_t kkb = 0.7) : transistor_t(ra, x, y, ab, ap, kb, kkb) {};
};

template <typename FLOAT>
template <typename OUT>
OUT& fet<FLOAT>::add_emitter_to_svg(OUT& o) const {
  o << "<line x1=\"" << x_of_pin(0) << "\" y1=\"" << y_of_pin(0) << '\"';
  o <<      " x2=\"" << x_of_pin(0) << "\" y2=\"" << y_of_pin(5) << "\"/>\n";
  o << "<line x1=\"" << x_of_pin(0) << "\" y1=\"" << y_of_pin(5) << '\"';
  o <<      " x2=\"" << x_of_pin(5) << "\" y2=\"" << y_of_pin(5) << "\"/>\n";
  return o;
};
template <typename FLOAT>
template <typename OUT>
OUT& fet<FLOAT>::add_collector_to_svg(OUT& o) const {
  o << "<line x1=\"" << x_of_pin(2) << "\" y1=\"" << y_of_pin(2) << '\"';
  o <<      " x2=\"" << x_of_pin(2) << "\" y2=\"" << y_of_pin(6) << "\"/>\n";
  o << "<line x1=\"" << x_of_pin(2) << "\" y1=\"" << y_of_pin(6) << '\"';
  o <<      " x2=\"" << x_of_pin(6) << "\" y2=\"" << y_of_pin(6) << "\"/>\n";
  return o;
};

#endif
