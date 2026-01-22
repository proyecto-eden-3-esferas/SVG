#ifndef WHEEL_H
#define WHEEL_H

#ifndef SCHEMATICS_ANGLE_H
#include "schematics.angle.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

#include <iostream>

template <typename F = double>
class wheel : protected angle_addressable<F>, public svg_shape<F> {
protected:
  typedef std::size_t size_t;
  typedef angle_addressable<F> angle_addressable_t;
  using angle_addressable_t::cx,  angle_addressable_t::cy;
  using angle_addressable_t::cos, angle_addressable_t::sin;
  typedef svg_shape<F> svg_shape_t;
  typedef wheel<F> wheel_t;
  using svg_shape_t::attr_map_type;
protected:
  F radius;
  mutable F span_angle; // sexagesimal
  size_t num_parts;
  F start_angle;
public:
  F             get_cx() const {return cx;};
  F             get_cy() const {return cy;};
  F         get_radius() const {return radius;};
  size_t get_num_parts() const {return num_parts;};
  void   set_num_parts(size_t n);
  F     get_span_angle() const {return span_angle;};
  F    get_start_angle() const {return start_angle;};
  wheel_t& rotate(F angle)       {start_angle += angle;     return *this;};
  wheel_t& translate(F dx, F dy) {cx += dx; cy += dy; return *this;};
protected:
  void add_svg_unclosed(std::ostream& o = std::cout, const std::string& attrs ="") const override;
public:
  virtual void print_svg_part(      std::ostream&    o=std::cout,
                                         size_t      n=0,
                              const std::string& attrs="") const;
  void print_svg_circle(std::ostream& o=std::cout,             const std::string& attrs="") const;
  void add_svg(         std::ostream& o = std::cout, const std::string& attrs = "") const override;
  /* Add to OSTREAM:
   * <animateTransform attributeName="transform" type="rotate"
   * with further attribute parameters:
       begin="0s" "dur="DUR"
       from="ANGLE CX Cy"
       repeatCount="indefinite />
   */
  enum angleDir {anticlockwise, clockwise};
  void animate_rotate(std::ostream& o = std::cout,
                      enum angleDir ad = angleDir::anticlockwise,
                      F durInSecs = 10, // this default should be overriden!
                      F begSecs = 0, F fromAngle = 0, F toAngle = 360) const;
  //void add_svg_animate_rotate(OSTREAM&,CLOCKWISE,SECONDS)

  //
  wheel(F cx=0.0, F cy=0.0, F r=100, size_t n=16, F sa=0.0)
  : angle_addressable_t(cx,cy),
    radius(r), num_parts(n), span_angle(360 / n),
    start_angle(sa)
    {};
};

/* Implementations of wheel<FLOAT> member functions: */

template <typename F>
void wheel<F>::animate_rotate(std::ostream& o, enum angleDir ad,
                              F durInSecs, F begSecs,
                              F fromAngle, F toAngle) const
{
  F tempAngle;
  if(ad == angleDir::anticlockwise) {
    tempAngle = fromAngle;
    fromAngle = toAngle;
    toAngle   = tempAngle;
  }
  o << "<animateTransform attributeName=\"transform\" type=\"rotate\"";
  o << " begin=\"" << begSecs << "s\" dur=\"" << durInSecs << "s\"";
  o << " from=\"" <<  fromAngle << ' ' << get_cx() << ' ' << get_cy() << "\"";
  o <<   " to=\"" <<    toAngle << ' ' << get_cx() << ' ' << get_cy() << "\"";
  o << " repeatCount=\"indefinite\"/>";
};

template <typename F>
void wheel<F>::set_num_parts(std::size_t n) {
  num_parts = n;
  span_angle = 360 / n;
};
template <typename F>
void wheel<F>::print_svg_part(std::ostream& o, size_t n, const std::string& attrs) const {
  F angle = start_angle + n * get_span_angle();
  o << "<polyline points=\"";
  o << cx << ' ' << cy << ' ';
  o << cx + radius * cos(angle) << ' ' << cy + radius * sin(angle) << ' ';
  angle += get_span_angle();
  o << cx + radius * cos(angle) << ' ' << cy + radius * sin(angle);;
  o << "\" " << attrs << "/>\n";
};
template <typename F>
void wheel<F>::print_svg_circle(std::ostream& o, const std::string& attrs) const {
  o << "<circle ";
  o << "cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << radius << '\"';
  o << attrs << "/>\n";
};
template <typename F>
void wheel<F>::add_svg_unclosed(      std::ostream& o,
                                const std::string & attrs) const
{
  o << "<polygon points =\"";
  o << cx + radius << ' ' << cy          << ' ';
  o << cx          << ' ' << cy - radius << ' ';
  o << cx - radius << ' ' << cy          << ' ';
  o << cx          << ' ' << cy + radius << '\"';
  o << ' ' << attrs;
};
template <typename F>
void wheel<F>::add_svg(      std::ostream& o,
                       const std::string & attrs) const {
  for(int i=0; i < num_parts; ++i)
    print_svg_part(o,i,attrs);
};






#endif
