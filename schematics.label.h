#ifndef SCHEMATICS_LABEL_H
#define SCHEMATICS_LABEL_H

#ifndef POINT_H
#include "point.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

#include <string>

template<typename FLOAT = double,
//       typename POINT = point<FLOAT, 2, boost::geometry::cs::cartesian>
         typename  CHAR = char
        >
class label {
public:
  typedef std::string string_t;
  enum class text_anchor {start, middle, end};
  //
  FLOAT x, y;
  string_t text;
  FLOAT deg;
  text_anchor anchor;
  /*
  void set_deg(FLOAT dg);
  void set_rad(FLOAT dg);
  */
  label(FLOAT xx, FLOAT yy, string_t s, FLOAT dg = 0.0, text_anchor ta = text_anchor::middle)
  : x(xx), y(yy), text(s), deg(dg), anchor(ta) {};
};

template<typename FLOAT = double, typename OUT = std::ostream>
OUT & add_svg(const label<FLOAT>& lbl, OUT& o = std::cout) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << "<text x=\"" << lbl.x << "\" y=\"" << lbl.y << "\" ";
  o << "style=\"text-anchor: ";
  switch(lbl.anchor) {
    case label<FLOAT>::text_anchor::start : o << "start\" "; break;
    case label<FLOAT>::text_anchor::middle: o << "middle\" "; break;
    case label<FLOAT>::text_anchor::end   : o << "end\" "; break;
    default                               : o << "start\" "; break;
  }
  o << "transform=\"rotate(" << lbl.deg << ' ' << lbl.x << ',' << lbl.y << ")\">";
  o << lbl.text << "</text>\n";
  return o;
};


#endif
