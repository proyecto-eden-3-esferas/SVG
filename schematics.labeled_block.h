#ifndef SCHEMATICS_LABELED_BLOCK_H
#define SCHEMATICS_LABELED_BLOCK_H

#ifndef SCHEMATICS_BLOCK_H
#include "schematics.block.h"
#endif

#include <string>
#include <vector>

template <typename FLOAT = double, typename STRING = std::string>
class labeled_block : public block<FLOAT> {
public:
  typedef FLOAT float_t;
  typedef block<FLOAT> block_t;
  typedef std::size_t size_t;
  typedef std::size_t index_t;
  typedef STRING string_t;
  typedef std::vector<string_t> string_container_t;
  using block_t::num_lft, block_t::num_btm, block_t::num_rht, block_t::num_upr;
  using block_t::xperim, block_t::yperim;
  using block_t::facing;
  string_container_t strings;
  // constructor:
  labeled_block(float_t x, float_t y, float_t w, float_t h,
                float_t l, float_t b, float_t r, float_t u) :
                block_t(x, y, w, h, l, b, r, u) {};
  template <typename ITER>
  labeled_block(float_t x, float_t y, float_t w, float_t h,
                float_t l, float_t b, float_t r, float_t u,
                ITER beg, ITER end) :
                block_t(x, y, w, h, l, b, r, u), strings(beg,end) {};
};

// Partial specialization of svg_unclosed(BLOCK&,OUT&)
template<typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const labeled_block<F>& lblk, OUT& o = std::cout, F raise = 25) {
  for(int i = 0; i < lblk.size(); ++i) {
    o << "<text x=\"" << lblk.xperim(i) << "\" y=\"" << lblk.yperim(i) + raise << "\" ";
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

#endif
