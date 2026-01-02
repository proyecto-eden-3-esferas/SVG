#ifndef SCHEMATICS_LABEL_H
#define SCHEMATICS_LABEL_H

#ifndef SVG_H
#include "svg.h"
#endif

#ifndef SCHEMATICS_ANGLE_H
#include "schematics.angle.h"
#endif

#include <string>
#include <vector>

std::string svg_text_std_attrs(" fill=\"black\" fill-opacity=\"1.0\" stroke=\"none\"");

/* Class label_base<FLOAT,CHAR> ...
 * remains abstract, as it does not implement:
 *   void svg<FLOAT>::add_svg_unclosed(OSTREAM, ATTRS) const
 */
template<typename FLOAT = double,
         typename  CHAR = char,
         template <typename> typename  CONT = std::vector >
class label_base : public svg_shape<FLOAT> {
public:
  typedef angle_addressable<FLOAT>   cir_t;
  typedef         svg_shape<FLOAT>   svg_t;
  typedef std::basic_string<CHAR> string_t;
  typedef                    CONT<string_t> lines_t;
  using svg_t::attr_map_type;
  using svg_t::add_attrs; // void add_attrs(MAP,OSTREAM,SEP)
  enum class text_anchor {start, middle, end};
  static void add_svg_unclosed(FLOAT x, FLOAT y,
                        const string_t& lbl,
                        FLOAT dg = 0,
                        text_anchor ta = text_anchor::middle,
                        std::ostream& o = std::cout,
                        FLOAT baseline_drop = 0.0);
  static void add_label_to_svg_unclosed(FLOAT x, FLOAT y,
                                 FLOAT dg = 0, // angle of text/baseline to the X axis
                                 text_anchor ta = text_anchor::middle,
                                 std::ostream& o = std::cout,
                                 FLOAT baseline_drop = 0.0); // no additional/optional attrs
  static void add_label_to_svg_unclosed(FLOAT x, FLOAT y,
                                 FLOAT dg = 0, // angle of text/baseline to the X axis
                                 text_anchor ta = text_anchor::middle,
                                 std::ostream& o = std::cout,
                                 FLOAT baseline_drop = 0.0,
                                 const string_t& attrs = svg_text_std_attrs) {
    add_label_to_svg_unclosed(x,y,dg,ta,o,baseline_drop);
    o << ' ' << attrs;
  };
  static void add_label_to_svg_unclosed(FLOAT x, FLOAT y,
                                 FLOAT dg = 0, // angle of text/baseline to the X axis
                                 text_anchor ta = text_anchor::middle,
                                 std::ostream& o = std::cout,
                                 FLOAT baseline_drop = 0.0,
                                 const svg_t::attr_map_type& attrs = attr_map_type(),
                                 char sep = "\"") {
    add_label_to_svg_unclosed(x,y,dg,ta,o,baseline_drop);
    add_attrs(attrs,o,sep);
  };
  static void add_lines(FLOAT x, FLOAT y, FLOAT radius,
                        // FLOAT dg, anchor,
                        const lines_t& lines,
                        std::ostream& o = std::cout);
};
/* Implementation of label_base<FLOAT,CHAR,CONT> member variables:
 * Member label_base<FLOAT,CHAR>::add_svg_unclosed(...) are based on overload
 *        label_base<FLOAT,CHAR>::add_svg_unclosed(X,Y,LABEL,DEG,TA,OSTREAM,BASELINE_DROP),
 * that is, it does not add additional/optional attributes
 */

template<typename FLOAT, typename  CHAR, template<typename> typename CONT >
void label_base<FLOAT,CHAR,CONT>::add_svg_unclosed(
  FLOAT x, FLOAT y,
  const typename label_base<FLOAT,CHAR,CONT>::string_t& lbl,
  FLOAT dg,
  label_base<FLOAT,CHAR,CONT>::text_anchor ta,
  std::ostream& o,
  FLOAT baseline_drop) {

  x -= baseline_drop * cir_t::sin(dg);
  y += baseline_drop * cir_t::cos(dg);
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << "<text x=\"" << x << "\" y=\"" << y  << "\" ";
  o << "style=\"text-anchor: ";
  switch(ta) {
    case text_anchor::start : o << "start\" "; break;
    case text_anchor::middle: o << "middle\" "; break;
    case text_anchor::end   : o << "end\" "; break;
    default                 : o << "start\" "; break;
  }
  o << "transform=\"rotate(" << dg << ' ' << x << ',' << y << ")\"";
};
template<typename FLOAT, typename  CHAR, template<typename> typename CONT >
void label_base<FLOAT,CHAR,CONT>::add_lines(FLOAT x, FLOAT y, FLOAT radius,
                                            // FLOAT dg, anchor,
                                            const lines_t& lines,
                                            std::ostream& o) {
  FLOAT step = (radius * 2.0) / (lines.size() - 1);
  FLOAT offset = - radius;
  for(auto & str : lines) {
    //::add_label_to_svg(x, y, str, deg, anchor, o, offset + baseline_drop);
    o << "<tspan x=\"" << x << "\" y=\"" << y + offset << "\">";
    o << str;
    o << "</tspan>\n";
    offset += step;
  }
};

/* Class label<FLOAT,CHAR> holds all the variables to print a one-line label in 2D
 */
template<typename FLOAT = double,
         typename  CHAR = char,
         template <typename> typename CONT = std::vector >
class label : public label_base<FLOAT,CHAR,CONT> {
public:
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
    add_label_to_svg_unclosed(x, y, deg, anchor, o, baseline_drop, attrs);
  };
  void add_svg_unclosed(std::ostream& o = std::cout, const attr_map_type& attrs = attr_map_type()) const {
    add_label_to_svg_unclosed(x, y, deg, anchor, o, baseline_drop, attrs);
  };
  void add_svg(std::ostream& o = std::cout, const std::string& attrs = "") const override {
    add_svg_unclosed(o,attrs);
    o << '>' <<  text << "</text>\n";
  };
  void add_svg(const attr_map_type& m, std::ostream& o = std::cout, char sep='\"') const override {
    add_svg_unclosed(m, o, sep);
    o << '>' <<  text << "</text>\n";
  };
  //
  label(FLOAT xx, FLOAT yy, string_t s,
        FLOAT dg = 0.0, text_anchor ta = text_anchor::middle, FLOAT bld = 0.0)
  : x(xx), y(yy), text(s), deg(dg), anchor(ta), baseline_drop(bld) {};
};

/* Class multilabel<FLOAT,CHAR> holds all the variables to print a multiline label in 2D
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
  //
  FLOAT x, y, r;
  FLOAT deg;
  text_anchor anchor;
  FLOAT baseline_drop;
  lines_t lines;
  //
  void add_svg_unclosed(std::ostream& o = std::cout, const string_t& attrs = "") const {
    add_label_to_svg_unclosed(x, y, deg, anchor, o, baseline_drop, attrs);
  };
  void add_svg_unclosed(std::ostream& o = std::cout, const attr_map_type& attrs = attr_map_type()) const {
    add_label_to_svg_unclosed(x, y, deg, anchor, o, baseline_drop, attrs);
  };
  void add_svg(std::ostream& o = std::cout, const std::string& attrs = "") const override {
    add_svg_unclosed(o,attrs);
    o << '>';
    typename label_base_t::add_lines(x, y, r, lines, o);
    o <<  "</text>\n";
  };
  void add_svg(const attr_map_type& m, std::ostream& o = std::cout, char sep='\"') const override {
    add_svg_unclosed(m, o, sep);
    o << '>';
    typename label_base_t::add_lines(x, y, r, lines, o);
    o <<  "</text>\n";
  };
  //
  multilabel(FLOAT xx, FLOAT yy, FLOAT rr, FLOAT dg = 0.0, text_anchor ta = text_anchor::middle, FLOAT bld = 0.0)
  : x(xx), y(yy), r(rr),           deg(dg), anchor(ta), baseline_drop(bld) {};
  multilabel(FLOAT xx, FLOAT yy, FLOAT rr, const lines_t& l, FLOAT dg = 0.0, text_anchor ta = text_anchor::middle, FLOAT bld = 0.0)
  : x(xx), y(yy), r(rr), lines(l), deg(dg), anchor(ta), baseline_drop(bld) {};
};


#endif


#ifndef SCHEMATICS_LABEL_GLOBALS_H
#define SCHEMATICS_LABEL_GLOBALS_H


#ifndef SCHEMATICS_LABEL_H
#include "schematics.label.h"
#endif


// Enumeraton class 'text_anchor' for SVG:
enum text_anchor {start, middle, end};

/* First, we define global function add_label_to_svg(X,Y,TEXT,DEGREES,TEXT_ANCHOR,OUT,BASELINE_DROP),
   to be used to print single line and multiline labels (classes line and multiline)
 * Note that the order of input parameters places the most defaultable ones last
 * 'baseline_drop' should be half the height of letters x, a, m ... so that text looks natural
 */

// std::string svg_text_std_attrs(" fill=\"black\" fill-opacity=\"1.0\" stroke=\"none\"");

template<typename FLOAT = double, typename CHAR=char, typename OUT = std::ostream>
void add_label_to_svg_unclosed(FLOAT x, FLOAT y,
                               const std::basic_string<CHAR>& lbl,
                               //std::basic_string_view<CHAR> lbl,
                               FLOAT dg = 0, // angle of text/baseline to the X axis
                               text_anchor ta = text_anchor::middle,
                               OUT& o = std::cout,
                               FLOAT baseline_drop = 0.0,
                               const std::basic_string<CHAR>& attrs = svg_text_std_attrs)
{
  typedef angle_addressable<FLOAT> cir_t;
  x -= baseline_drop * cir_t::sin(dg);
  y += baseline_drop * cir_t::cos(dg);
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << "<text x=\"" << x << "\" y=\"" << y  << "\" ";
  o << "style=\"text-anchor: ";
  switch(ta) {
    case text_anchor::start : o << "start\" "; break;
    case text_anchor::middle: o << "middle\" "; break;
    case text_anchor::end   : o << "end\" "; break;
    default                 : o << "start\" "; break;
  }
  o << "transform=\"rotate(" << dg << ' ' << x << ',' << y << ")\" " << attrs << '>';
  o << lbl << "</text>\n";
};
template<typename FLOAT = double, typename CHAR=char, typename OUT = std::ostream>
void add_label_to_svg(FLOAT x, FLOAT y,
                      const std::basic_string<CHAR>& lbl,
                      //std::basic_string_view<CHAR> lbl,
                      FLOAT dg = 0,
                      text_anchor ta = text_anchor::middle,
                      OUT& o = std::cout,
                      FLOAT baseline_drop = 0.0)
{ add_label_to_svg_unclosed(x, y, lbl, dg, ta, o, baseline_drop);
  close_standalone_tag(o);
};

// Using ::add_label_to_svg(X,Y,TEXT,DEGREES,TEXT_ANCHOR,OUT,BASELINE_DROP)
template<typename FLOAT = double, typename OUT = std::ostream>
void add_svg_unclosed(const label<FLOAT>& lbl, OUT& o = std::cout) {
  add_label_to_svg_unclosed(lbl.x, lbl.y, lbl.text,
                            lbl.deg, lbl.anchor, o, lbl.baseline_drop);
};
template<typename FLOAT = double, typename OUT = std::ostream>
void add_svg(const label<FLOAT>& lbl, OUT& o = std::cout) {
  add_svg_unclosed(lbl,o);
  close_standalone_tag(o);
};
template<typename FLOAT = double, typename OUT = std::ostream>
void add_svg(const multilabel<FLOAT>& ml, OUT& o = std::cout) {
  FLOAT step = (ml.r * 2.0) / (ml.lines.size() - 1);
  FLOAT offset = - ml.r;
  for(auto & str : ml.lines) {
    add_label_to_svg(ml.x, ml.y, str, ml.deg, ml.anchor, o, offset + ml.baseline_drop);
    offset += step;
  }
};

/*
template<typename FLOAT = double, typename OUT = std::ostream>
void add_svg(const label<FLOAT>& lbl, OUT& o = std::cout) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << "<text x=\"" << lbl.x << "\" y=\"" << lbl.y << "\" ";
  o << "style=\"text-anchor: ";
  switch(lbl.anchor) {
    case text_anchor::start : o << "start\" "; break;
    case text_anchor::middle: o << "middle\" "; break;
    case text_anchor::end   : o << "end\" "; break;
    default                               : o << "start\" "; break;
  }
  o << "transform=\"rotate(" << lbl.deg << ' ' << lbl.x << ',' << lbl.y << ")\">";
  o << lbl.text << "</text>\n";
};
*/


#endif
