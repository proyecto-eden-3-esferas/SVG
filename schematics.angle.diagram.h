#ifndef SCHEMATICS_ANGLE_DIAGRAM_H
#define SCHEMATICS_ANGLE_DIAGRAM_H

#ifndef SCHEMATICS_ROUND_H
#include "schematics.round.h"
#endif

#include <iostream>
#include <string>

template <typename FLOAT = double>
FLOAT angle(const angle_addressable<FLOAT>& aa1, const angle_addressable<FLOAT>& aa2) {
  return aa1.angle(aa2.cx, aa2.cy);
}

/* The following strings may be used for defining svg markers
 * through inserion into an svg defs element like so:
 *   ofile << "<defs>\n";
 *   ofile << solid_arrowhead_marker << '\n';
 *   ofile << "</defs>";
 * These strings are used by function 'add_svg_arrow'
 */
std::string solid_arrowhead_marker{"<marker id=\"solid-arrow\"\
  markerWidth=\"10\" markerHeight=\"10\"\
  refX=\"10\" refY=\"5\" orient=\"auto\">\n\
  <path d=\"M 0 0 L 10 5 L 0 10 z\" fill=\"black\" fill-opacity=\"1.0\"/> \n\
</marker>"};

std::string hollow_arrowhead_marker{"<marker id=\"hollow-arrow\"\
  markerWidth=\"10\" markerHeight=\"10\"\
  refX=\"10\" refY=\"5\" orient=\"auto\">\n\
  <path d=\"M 0 0 L 10 5 L 0 10 z\"\n\
    fill=\"none\" fill-opacity=\"0.0\" stroke=\"black\" stroke-opacity=\"1.0\"/> \n\
</marker>"};

std::string stick_arrowhead_marker{"<marker id=\"stick-arrow\"\
  markerWidth=\"10\" markerHeight=\"10\"\
  refX=\"10\" refY=\"5\" orient=\"auto\">\n\
  <path d=\"M 0 0 L 10 5 L 0 10\" stroke=\"black\" stroke-opacity=\"1.0\"/> \n\
</marker>"};


template <typename FLOAT = double>
void add_svg_line(angle_addressable<FLOAT>& aa1,
                  angle_addressable<FLOAT>& aa2,
                  std::ostream& o = std::cout) {
  FLOAT deg = angle(aa1,aa2);
  o << "<line x1=\"" << aa1.xperim(deg) << "\" y1=\"" << aa1.yperim(deg) << "\" ";
  o << "x2=\"" << aa2.xperim(deg + 180) << "\" y2=\"" << aa2.yperim(deg + 180) << "\"/>\n";
};

template <typename FLOAT = double>
void add_svg_arrow(angle_addressable<FLOAT>& aa1,
                   angle_addressable<FLOAT>& aa2,
                   std::ostream& o = std::cout,
                   const std::string& endMarkerId = "solid-arrow") {
  FLOAT deg = angle(aa1,aa2);
  o << "<line x1=\"" << aa1.xperim(deg) << "\" y1=\"" << aa1.yperim(deg) << "\" ";
  o << "x2=\"" << aa2.xperim(deg + 180) << "\" y2=\"" << aa2.yperim(deg + 180) << "\" ";
  o << "marker-end=\"url(#" << endMarkerId << ")\"" << "/>\n";
};

#endif
