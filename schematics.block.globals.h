#ifndef SCHEMATICS_BLOCK_GLOBALS_H
#define SCHEMATICS_BLOCK_GLOBALS_H

#ifndef SCHEMATICS_BLOCK_H
#include "schematics.block.h"
#endif

// Partial specialization of svg_unclosed(BLOCK&,OUT&)
#ifndef SVG_H
#include "svg.h"
#endif

template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const block<F>& blk, OUT& o = std::cout) {
  o << "<rect x=\"" << blk.x     << "\" y=\""      << blk.y << "\" ";
  o <<   "width=\"" << blk.width << "\" height=\"" << blk.height << "\"";
  //return o; // void return type
};

#endif
