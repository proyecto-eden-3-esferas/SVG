#ifndef SCHEMATICS_LABEL_H
#define SCHEMATICS_LABEL_H

#ifndef SVG_H
#include "svg.h"
#endif

#ifndef SCHEMATICS_ANGLE_H
#include "schematics.angle.h"
#endif

#include <string>
//#include <string_view>
#include <vector>

// Enumeraton class 'text_anchor' for SVG:
enum class text_anchor {start, middle, end};
/* First, we define global function add_label_to_svg(X,Y,TEXT,DEGREES,TEXT_ANCHOR,OUT,BASELINE_DROP),
   to be used to print single line and multiline labels (classes line and multiline)
 * Note that the order of input parameters places the most defaultable ones last
 * 'baseline_drop' should be half the height of letters x, a, m ... so that text looks natural
 */
template<typename FLOAT = double, typename CHAR=char, typename OUT = std::ostream>
void add_label_to_svg_unclosed(FLOAT x, FLOAT y,
                      const std::basic_string<CHAR>& lbl,
                      //std::basic_string_view<CHAR> lbl,
                      FLOAT dg = 0,
                      text_anchor ta = text_anchor::middle,
                      OUT& o = std::cout,
                      FLOAT baseline_drop = 0.0)
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
  o << "transform=\"rotate(" << dg << ' ' << x << ',' << y << ")\">";
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


/* Class label<FLOAT,CHAR> holds all the variables to print a one-line label in 2D
 */
template<typename FLOAT = double,
         typename  CHAR = char
        >
class label {
public:
  typedef std::string string_t;
  //
  FLOAT x, y;
  string_t text;
  FLOAT deg;
  text_anchor anchor;
  FLOAT baseline_drop;
  //
  label(FLOAT xx, FLOAT yy, string_t s, FLOAT dg = 0.0, text_anchor ta = text_anchor::middle, FLOAT bld = 0.0)
  : x(xx), y(yy), text(s), deg(dg), anchor(ta), baseline_drop(bld) {};
};
/* Class multilabel<FLOAT,CHAR> holds all the variables to print a multiline label in 2D
 * It shares all member variables but 'text' with its analog class, 'label<FLOAT>'
 */
template<typename FLOAT = double,
         typename  CHAR = char,
         typename  CONT = std::vector<std::basic_string<CHAR> >
        >
class multilabel {
public:
  typedef std::string string_t;
  typedef CONT lines_t;
  lines_t lines;
  //
  FLOAT x, y, r;
  FLOAT deg;
  text_anchor anchor;
  FLOAT baseline_drop;
  /*
  void set_deg(FLOAT dg);
  void set_rad(FLOAT dg);
  */
  multilabel(FLOAT xx, FLOAT yy, FLOAT rr,                   FLOAT dg = 0.0, text_anchor ta = text_anchor::middle, FLOAT bld = 0.0)
  : x(xx), y(yy), r(rr),           deg(dg), anchor(ta), baseline_drop(bld) {};
  multilabel(FLOAT xx, FLOAT yy, FLOAT rr, const lines_t& l, FLOAT dg = 0.0, text_anchor ta = text_anchor::middle, FLOAT bld = 0.0)
  : x(xx), y(yy), r(rr), lines(l), deg(dg), anchor(ta), baseline_drop(bld) {};
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
