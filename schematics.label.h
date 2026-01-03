#ifndef SCHEMATICS_LABEL_H
#define SCHEMATICS_LABEL_H

#ifndef SCHEMATICS_LABEL_BASE_H
#include "schematics.label_base.h"
#endif

/* This file defines classes label<FLOAT,CHAR,CONT> and multilabel<FLOAT,CHAR,CONT>
 * TODO
 * [ ] define classes ref_label<> and ref_multilabel<>,
 *     which hold not values but references to 'x', 'y' and (possibly also) 'deg'
 *     Instances of ref_label and ref_multilabel are matched to a shape
 *     and are meant to pring a label inside their matching shape
 */

/* Class label<FLOAT,CHAR,CONT> holds all the variables to print a one-line label in 2D
 */
template<typename FLOAT = double,
         typename  CHAR = char,
         template <typename> typename CONT = std::vector >
class label : public label_base<FLOAT,CHAR,CONT> {
public:
  typedef svg_shape<FLOAT> svg_t;
  typedef label_base<FLOAT,CHAR,CONT> label_base_t;
  using typename label_base_t::string_t;
  using typename label_base_t::text_anchor;
  using typename label_base_t::attr_map_type;
  //
  FLOAT x, y;
  string_t text;
  FLOAT deg;
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
  //
  label(FLOAT xx, FLOAT yy, string_t s,
        FLOAT dg = 0.0, text_anchor ta = text_anchor::middle, FLOAT bld = 0.0)
  : x(xx), y(yy), text(s), deg(dg), anchor(ta), baseline_drop(bld) {};
};

/* Class multilabel<FLOAT,CHAR,CONT> holds all the variables to print a multiline label in 2D
 * It shares all member variables but 'text' with its analog class, 'label<FLOAT>'
 */
template<typename FLOAT = double,
         typename  CHAR = char,
         template <typename> typename CONT = std::vector
        >
class multilabel : public label_base<FLOAT,CHAR,CONT> {
public:
  typedef label_base<FLOAT,CHAR,CONT> label_base_t;
  using                      typename label_base_t::string_t;
  using                      typename label_base_t::text_anchor;
  using                      typename label_base_t::attr_map_type;
  typedef                                      CONT<string_t> lines_t;
  typedef svg_shape<FLOAT> svg_t;
  //
  FLOAT x, y, r;
  FLOAT deg;
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
  multilabel(FLOAT xx, FLOAT yy, FLOAT rr, FLOAT dg = 0.0, text_anchor ta = text_anchor::middle, FLOAT bld = 0.0)
  : x(xx), y(yy), r(rr),           deg(dg), anchor(ta), baseline_drop(bld) {};
  multilabel(FLOAT xx, FLOAT yy, FLOAT rr, const lines_t& l, FLOAT dg = 0.0, text_anchor ta = text_anchor::middle, FLOAT bld = 0.0)
  : x(xx), y(yy), r(rr), lines(l), deg(dg), anchor(ta), baseline_drop(bld) {};
};

#endif
