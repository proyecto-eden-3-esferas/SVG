#ifndef SCHEMATICS_TRANSISTOR_H
#define SCHEMATICS_TRANSISTOR_H

#include "schematics.round.h"
#include "schematics.line.h"
#include "schematics.arrow.h"
#include <iostream>

/* Class 'transistor' (a proto- bipolar-junction transistor)
   is both a generic BJT and the base of classes
   'pnp' and 'npn' (BJT's), and
   'fet' (in file "schematics.fet.h", itself sub- and subsub-classed into several others)
 * All transistors are drawn inside a circle (the "enclosing circle"),
   which is inherited down the hierarchy.
 * Functions x_of_pin(IDX) and y_of_pin(IDX) output coordinates of:
   (0) emitter   (on enclosing circle)
   (1) base      (on enclosing circle)
   (2) collector (on enclosing circle)
   (3) emitter-side   start of base cord (on enclosing circle)
   (4) collector-side start of base cord (on enclosing circle)
   (5) where the base starts (on the emitter   side)
   (6) where the base starts (on the collector side)
   (7) where emitter   meets base (along the base)
   (8) where collector meets base (along the base)
   (9) middle point of base
   This numbering convention is reflected in enum transistor::points.
   Derived classes might and should redefine enum points.
 * TODO
   [x] template <typename OUT = std::ostream>
       void add_to_midbase_to_svg(OUT& o) const;
   [x] explain/clear up float variable 'abase'
   [ ] provision for drawing arrows, currently through
       member variables: arrow_len_k and arrow_half_angle (in hex degrees), and
       member functions: get_arrow_len() and get_arrow_half_wid(),
       well...
       we could define a member function taking all the parameters, like:
       transistor_t::draw_arrow(X,Y, ANGLE, LEN, HALFWIDTH = LEN / 5,
                                OUTSTREAM = std::cout,
                                STRING="class=\"tr-arrow\"")
   [ ] all SVG transistor elements should contain a class attribute
       (default: "transistor"). Elements that should be styled differently,
       like a BJT base line, should have their class set to something
       even more specific.
   [ ] deal with inversion around the X-axis
   [ ] write classes pnp<> and npn<>
 */

template <typename FLOAT = double>
class transistor : public circular<FLOAT> {
public:
  typedef          circular<FLOAT> circular_t;
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  typedef std::size_t size_t;
  using circular_t::cx, circular_t::cy, circular_t::r;
  // Inherit member functions for locating points on enclosing circle:
  using circular_t::xperim, circular_t::yperim;
  enum points {emitter=0, base, collector, // on enclosing circle
               emitter_side_start_of_base_cord=3, collector_side_start_of_base_cord=4,
               emitter_side_start_of_base=5, collector_side_start_of_base=6,
               emitter_meets_base=7, collector_meets_base=8,
               midbase=9 // middle of the base
  };
  // Inherit variables defining the enclosing circle:
  float_t angle_of_sym_axis{0.0}; // angle     of the symmetry axis to the X axis
  float_t aemitter;    // angle of the emitter to the symmetry axis of the transistor
  float_t abase; // angle of the base's cord meeting the enclosing circle to the X axis
  float_t kbase;  // k is a factor: k==1.0 means the base is drawn as a chord
  float_t kkbase; // k==1.0 means emitter and collector leads meet the base at the edge
  //
  float_t get_emitter_angle()   const {return angle_of_sym_axis + aemitter;};
  float_t get_collector_angle() const {return angle_of_sym_axis - aemitter;};
  //
  float_t arrow_len_k{0.2}, arrow_half_angle{15}; // in hex degrees
  float get_arrow_len()      const {return arrow_len_k*r;}
  float get_arrow_half_wid() const {return get_arrow_len()*cir_t::sin(arrow_half_angle);}
  //
  float_t x_of_pin(size_t idx) const;
  float_t y_of_pin(size_t idx) const;
  template <typename OUT = std::ostream>
  void add_circle_to_svg(OUT& o) const;
  // Lines inside the transistor circle: base, emitter, collector
  template <typename OUT = std::ostream>       // line from 1 to 9
  void add_to_midbase_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  void add_base_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  void add_emitter_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  void add_collector_to_svg(OUT& o) const;
  template <typename OUT = std::ostream>
  void add_svg(OUT& o) const {
    add_emitter_to_svg(o);
    add_collector_to_svg(o);
    add_circle_to_svg(o);
    add_base_to_svg(o);
    add_to_midbase_to_svg(o);
  };
  //
  transistor(float_t ra, float_t x=0, float_t y=0,
             float_t ae =  60, //cir_t::deg_to_rad( 60),
             float_t ab = 115, //cir_t::deg_to_rad(125),
             float_t kb = 0.85, float_t kkb = 0.85) :
    circular_t(ra,x,y), aemitter(ae), abase(ab), kbase(kb), kkbase(kkb) {};
};


/* PNP BJT: arrow from emitter to base */
template <typename FLOAT = double>
class pnp : public transistor<FLOAT> {};
/* PNP BJT: arrow from collector to base */
template <typename FLOAT = double>
class npn : public transistor<FLOAT> {};

/* Implementations of transistor<FLOAT> methods
 */

template <typename FLOAT>
FLOAT transistor<FLOAT>::x_of_pin(size_t idx) const {
  switch (idx) {
    case 0: return cx + r * cir_t::cos(get_emitter_angle()  ); break;
    case 1: return cx - r * cir_t::cos(angle_of_sym_axis    ); break;
    case 2: return cx + r * cir_t::cos(get_collector_angle()); break;
    case 3: return cx + r * cir_t::cos(angle_of_sym_axis + abase); break;
    case 4: return cx + r * cir_t::cos(angle_of_sym_axis - abase); break;
    // Inside the transistor circle and along the base:
    case 5: return x_of_pin(3)*kbase        + x_of_pin(4)*(1 - kbase       ); break;
    case 6: return x_of_pin(4)*kbase        + x_of_pin(3)*(1 - kbase       ); break;
    case 7: return x_of_pin(3)*kbase*kkbase + x_of_pin(4)*(1 - kbase*kkbase); break;
    case 8: return x_of_pin(4)*kbase*kkbase + x_of_pin(3)*(1 - kbase*kkbase); break;
    case 9: return 0.5 * (x_of_pin(3) + x_of_pin(4)); break;
    default: return 0.0;
  }
};
template <typename FLOAT>
FLOAT transistor<FLOAT>::y_of_pin(size_t idx) const {
  switch (idx) {
    case 0: return cy + r * cir_t::sin(get_emitter_angle()  ); break;
    case 1: return cy - r * cir_t::sin(angle_of_sym_axis    ); break;
    case 2: return cy + r * cir_t::sin(get_collector_angle()); break;
    case 3: return cy + r * cir_t::sin(angle_of_sym_axis + abase); break;
    case 4: return cy + r * cir_t::sin(angle_of_sym_axis - abase); break;
    // Inside the transistor circle and along the base:
    case 5: return y_of_pin(3)*kbase        + y_of_pin(4)*(1 - kbase       ); break;
    case 6: return y_of_pin(4)*kbase        + y_of_pin(3)*(1 - kbase       ); break;
    case 7: return y_of_pin(3)*kbase*kkbase + y_of_pin(4)*(1 - kbase*kkbase); break;
    case 8: return y_of_pin(4)*kbase*kkbase + y_of_pin(3)*(1 - kbase*kkbase); break;
    case 9: return 0.5 * (y_of_pin(3) + y_of_pin(4)); break;
    default: return 0.0;
  }
};

//

template <typename FLOAT>
template <typename OUT>
void transistor<FLOAT>::add_circle_to_svg(OUT& o) const {
  o << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << r << "\"/>\n";
  //return o; // void return type
};

template <typename FLOAT>
template <typename OUT>
void transistor<FLOAT>::add_to_midbase_to_svg(OUT& o) const {
  o << "<line x1=\"" << x_of_pin(1) << "\" y1=\"" << y_of_pin(1) << '\"';
  o <<      " x2=\"" << x_of_pin(9) << "\" y2=\"" << y_of_pin(9) << "\"/>\n";
  //return o; // void return type
};


template <typename FLOAT>
template <typename OUT>
void transistor<FLOAT>::add_base_to_svg(OUT& o) const {
  o << "<line x1=\"" << x_of_pin(5) << "\" y1=\"" << y_of_pin(5) << '\"';
  o <<      " x2=\"" << x_of_pin(6) << "\" y2=\"" << y_of_pin(6) << "\"/>\n";
  //return o; // void return type
};
template <typename FLOAT>
template <typename OUT>
void transistor<FLOAT>::add_emitter_to_svg(OUT& o) const {
  o << "<line x1=\"" << x_of_pin(0) << "\" y1=\"" << y_of_pin(0) << '\"';
  o <<      " x2=\"" << x_of_pin(7) << "\" y2=\"" << y_of_pin(7) << "\"/>\n";
  //return o; // void return type
};
template <typename FLOAT>
template <typename OUT>
void transistor<FLOAT>::add_collector_to_svg(OUT& o) const {
  o << "<line x1=\"" << x_of_pin(2) << "\" y1=\"" << y_of_pin(2) << '\"';
  o <<      " x2=\"" << x_of_pin(8) << "\" y2=\"" << y_of_pin(8) << "\"/>\n";
  //return o; // void return type
};
//
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const transistor<F>& tr, OUT& o = std::cout) { tr.add_svg(o);};

#endif
