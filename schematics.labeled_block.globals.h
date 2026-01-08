#ifndef SCHEMATICS_LABELED_BLOCK_GLOBALS_H
#define SCHEMATICS_LABELED_BLOCK_GLOBALS_H

#ifndef SCHEMATICS_LABELED_BLOCK_H
#include "schematics.labeled_block.h"
#endif

#ifndef SCHEMATICS_BLOCK_GLOBALS_H
#include "schematics.block.globals.h"
#endif


// Partial specialization of svg_unclosed(BLOCK&,OUT&)
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const labeled_block<F>& lblk, OUT& o = std::cout, F raise = 25.0) {
  for(int i = 0; i < lblk.size(); ++i) {
    o << "<text x=\"" << lblk.xperim(i) << "\" y=\"" << lblk.yperim(i) + raise << "\" ";
    o << " fill=\"black\" ";
    o << "style=\"text-anchor: ";
    switch (lblk.faces(i)) {
      case labeled_block<F>::facing::lt:
        o << "end";
        break;
      case labeled_block<F>::facing::bt:
        o << "end\" transform=\"rotate(-45 " << lblk.xperim(i) << ',' << lblk.yperim(i) << ')';
        break;
      case labeled_block<F>::facing::rt:
        o << "start";
        break;
      case labeled_block<F>::facing::tp:
        o << "start\" transform=\"rotate(-45 " << lblk.xperim(i) << ',' << lblk.yperim(i) << ')';
        break;
      default:
        o << "middle";
        break;
    }
    o << "\">" << lblk.strings[i] << "</text>\n" << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  }
  add_svg_unclosed(static_cast<const block<F>&>(lblk), o);
  //return o; // void return type
};

// Partial specialization of svg_unclosed(BLOCK&,OUT&) taking an additional, default, argument in
template <typename F = double, typename OUT = std::ostream>
void add_svg(const labeled_block<F>& lblk,
             OUT& o = std::cout,
             F raise = 25.0) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_svg_unclosed(lblk,o,raise);
  close_standalone_tag(o);
};

#endif
