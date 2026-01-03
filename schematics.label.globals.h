#ifndef SCHEMATICS_LABEL_GLOBALS_H
#define SCHEMATICS_LABEL_GLOBALS_H


#ifndef SCHEMATICS_LABEL_H
#include "schematics.label.h"
#endif

/* This file defines some global functions for printing labels as SVG code.
 * Classes in "schematics.label.h" are favoured over these globals.
 * Classes in "schematics.label.h" do not rely on any of these global functions.
 * WARNING : Maintenance is to be discontinued.
 */

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
