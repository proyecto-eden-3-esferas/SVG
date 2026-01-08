#ifndef SCHEMATICS_REF_LABEL_H
#define SCHEMATICS_REF_LABEL_H

#ifndef SCHEMATICS_LABEL_BASE_H
#include "schematics.label_base.h"
#endif

/* This file defines class ref_label<FLOAT,CHAR,CONT>
 * TODO
 * [ ] define class ref_label<>,
 *     which holds not values but references to 'x', 'y' and (possibly also) 'deg'
 *     Instances of ref_label are matched to a 2D shape (rectangle, circle etc)
 *     and are meant to pring a label inside their matching shape
 */

/* Class label<FLOAT,CHAR,CONT> holds all the variables to print a one-line label in 2D
 */
template<typename FLOAT = double,
         typename  CHAR = char,
         template <typename> typename CONT = std::vector >
class ref_label : public label_base<FLOAT,CHAR,CONT> {
public:
  typedef svg_shape<FLOAT> svg_t;
  typedef label_base<FLOAT,CHAR,CONT> label_base_t;
  using typename label_base_t::string_t;
  using typename label_base_t::text_anchor;
  using typename label_base_t::attr_map_type;
  //
  const FLOAT &x, &y;
  string_t text;
  const FLOAT & deg;
  text_anchor anchor;
  FLOAT baseline_drop;
  void add_svg_unclosed(std::ostream& o = std::cout, const string_t& attrs = "") const {
    label_base_t::add_svg_unclosed(x, y, attrs, deg, anchor, o, baseline_drop);
  };
  void add_svg(std::ostream& o = std::cout, const std::string& attrs = "") const override {
    add_svg_unclosed(o, attrs);
    o << '>' <<  text << "</text>\n";
  };
  void add_svg(const attr_map_type& m, std::ostream& o = std::cout, char sep='\"') const override {
    svg_t::add_svg_unclosed(m,o,sep);
    o << '>' <<  text << "</text>\n";
  };
  // Constructor(s):
  ref_label(const FLOAT & xx, const FLOAT & yy,
            string_t s,
            const FLOAT & dg,
            text_anchor ta = text_anchor::middle,
            FLOAT bld = 0.0)
  : x(xx), y(yy), text(s), deg(dg), anchor(ta), baseline_drop(bld) {};
};

#endif
