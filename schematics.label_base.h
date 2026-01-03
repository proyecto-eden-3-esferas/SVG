#ifndef SCHEMATICS_LABEL_BASE_H
#define SCHEMATICS_LABEL_BASE_H

#ifndef SVG_H
#include "svg.h"
#endif

#ifndef SCHEMATICS_ANGLE_H
#include "schematics.angle.h"
#endif

#include <string>
#include <vector>

std::string default_svg_text_std_attrs(" fill=\"black\" fill-opacity=\"1.0\" stroke=\"none\"");

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
  using typename svg_t::attr_map_type;
  using svg_t::add_attrs; // void add_attrs(MAP,OSTREAM,SEP)
  enum class text_anchor {start, middle, end};
  static void add_svg_unclosed(FLOAT x, FLOAT y,
                               FLOAT dg = 0,
                               text_anchor ta = text_anchor::middle,
                               std::ostream& o = std::cout,
                               FLOAT baseline_drop = 0.0);

  static void add_svg_unclosed(FLOAT x, FLOAT y,
                               const string_t& attrs,
                               FLOAT dg = 0,
                               text_anchor ta = text_anchor::middle,
                               std::ostream& o = std::cout,
                               FLOAT baseline_drop = 0.0)
  {
    add_svg_unclosed(x,y,dg,ta,o,baseline_drop);
    o << ' ' << attrs;
  };

  static void add_svg_unclosed(FLOAT x, FLOAT y,
                               const attr_map_type& attrs,
                               FLOAT dg = 0,
                               text_anchor ta = text_anchor::middle,
                               std::ostream& o = std::cout,
                               FLOAT baseline_drop = 0.0,
                               char sep = "\"")
  {

    add_svg_unclosed(x,y,dg,ta,o,baseline_drop);
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
  FLOAT dg,
  label_base<FLOAT,CHAR,CONT>::text_anchor ta,
  std::ostream& o,
  FLOAT baseline_drop) {

  x -= baseline_drop * cir_t::sin(dg);
  y += baseline_drop * cir_t::cos(dg);
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << "<text x=\"" << x << "\" y=\"" << y  << "\" ";
  o << "text-anchor=\"";
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

#endif
