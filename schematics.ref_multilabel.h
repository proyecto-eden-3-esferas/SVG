#ifndef SCHEMATICS_REF_MULTILABEL_H
#define SCHEMATICS_REF_MULTILABEL_H

#ifndef SCHEMATICS_LABEL_BASE_H
#include "schematics.label_base.h"
#endif

/* This file defines class ref_multilabel<FLOAT,CHAR,CONT>
 * TODO
 * [ ] define class ref_multilabel<>,
 *     which holds not values but references to 'x', 'y' and (possibly also) 'deg'
 *     Instances of ref_multilabel are matched to a 2D shape (rectangle, circle etc)
 *     and are meant to pring a label inside their matching shape
 */



/* Class ref_multilabel<FLOAT,CHAR,CONT> holds all the variables to print a multiline label in 2D
 * It shares all member variables but 'text' with its analog class, 'label<FLOAT>'
 */
template<typename FLOAT = double,
         typename  CHAR = char,
         template <typename> typename CONT = std::vector
        >
class ref_multilabel : public label_base<FLOAT,CHAR,CONT> {
public:
  typedef label_base<FLOAT,CHAR,CONT> label_base_t;
  using                      typename label_base_t::string_t;
  using                      typename label_base_t::text_anchor;
  using                      typename label_base_t::attr_map_type;
  typedef                                      CONT<string_t> lines_t;
  typedef svg_shape<FLOAT> svg_t;
  //
  const FLOAT &x,&y;
  const FLOAT &r; // Just as with multilabel (its non-ref analog)
                  // the baselines of the first and last line in 'lines'
                  // meet the top and bottom of a circle of radius == 'r'
  const FLOAT & deg;
  text_anchor anchor;
  FLOAT baseline_drop;
  lines_t lines;
  //
  void add_svg_unclosed(std::ostream& o = std::cout, const string_t& attrs = "") const {
    label_base_t::add_svg_unclosed(x, y, attrs, deg, anchor, o, baseline_drop);
  };
  void add_svg(std::ostream& o = std::cout, const std::string& attrs = "") const override {
    add_svg_unclosed(o,attrs);
    o << '>';
    label_base_t::add_lines(x, y, r, lines, o);
    o <<  "</text>\n";
  };
  void add_svg(const attr_map_type& m, std::ostream& o = std::cout, char sep='\"') const override {
    svg_t::add_svg_unclosed(m, o, sep);
    o << '>';
    label_base_t::add_lines(x, y, r, lines, o);
    o <<  "</text>\n";
  };
  //
  ref_multilabel(const FLOAT & xx, const FLOAT & yy,
             const FLOAT & rr,
             const FLOAT & dg,
             text_anchor ta = text_anchor::middle,
             FLOAT bld = 0.0)
  : x(xx), y(yy), r(rr),           deg(dg), anchor(ta), baseline_drop(bld) {};
  ref_multilabel(const FLOAT & xx, const FLOAT & yy,
             const FLOAT & rr,
             const lines_t& l,
             const FLOAT & dg,
             text_anchor ta = text_anchor::middle,
             FLOAT bld = 0.0)
  : x(xx), y(yy), r(rr), lines(l), deg(dg), anchor(ta), baseline_drop(bld) {};
};

#endif
