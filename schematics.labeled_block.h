#ifndef SCHEMATICS_LABELED_BLOCK_H
#define SCHEMATICS_LABELED_BLOCK_H

/* Class labeled_block...
 * TODO
 * [ ] Labels should be printed further off the block sides.
 *     You could append or prepend
 * [ ] Also, clients should be able to choose the angle
 *     that top and bottom labels are to be printed at,
 *     say -45 is just a reasonable default
 */

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
  using block_t::faces;
  string_container_t strings;
  float_t raise;
  //
  void add_svg_labels(  std::ostream& o = std::cout,
                        const std::string& attrs = " fill=\"black\" fill-opacity=\"1.0\"") const;
  void add_svg(         std::ostream& o = std::cout,
                        const std::string& attrs = " fill=\"black\" fill-opacity=\"1.0\"") const override {
    o << "\n<!-- into overriden add_svg -->\n";
    block_t::add_svg_unclosed(o);
    o << "/>\n";
    add_svg_labels(o,attrs);
    o << "\n<!-- out of overriden add_svg -->\n";
  };
  void add_svg_unclosed(std::ostream& o = std::cout,
                        const std::string& attrs = " fill=\"black\" fill-opacity=\"1.0\"") const {
    /*
    //o << "\n<!-- into labeled_block::add_svg_unclosed -->\n";
    add_svg_labels(o,attrs);
    block_t::add_svg_unclosed(o); // WARNING adding further attributes to OSTREAM o
                                  //         would apply to rectangle shape (block)
                                  //         not to text (labels)
    //o << "\n<!-- out of labeled_block::add_svg_unclosed -->\n";
    */
  };
  // constructor:
  labeled_block(float_t x, float_t y, float_t w, float_t h,
                float_t l, float_t b, float_t r, float_t u,
                float_t rai=0.0) :
                block_t(x, y, w, h, l, b, r, u), raise(rai) {};
  template <typename ITER>
  labeled_block(float_t x, float_t y, float_t w, float_t h,
                float_t l, float_t b, float_t r, float_t u,
                ITER beg, ITER end,
                float_t rai=0.0) :
                block_t(x, y, w, h, l, b, r, u), strings(beg,end), raise(rai) {};
};

// Implementation of member functions in labeled_block<>:
template <typename FLOAT, typename STRING>
void labeled_block<FLOAT,STRING>::add_svg_labels(std::ostream& o, const std::string& attrs) const {
  for(int i = 0; i < strings.size(); ++i) {
    o << "<text x=\"" << xperim(i) << "\" y=\"" << yperim(i) + raise << "\" ";
    o << "style=\"text-anchor: ";
    switch (faces(i)) {
      case labeled_block<FLOAT,STRING>::facing::lt:
        o << "end";
        break;
      case labeled_block<FLOAT,STRING>::facing::bt:
        o << "end\" transform=\"rotate(-45 " << xperim(i) << ',' << yperim(i) << ')';
        break;
      case labeled_block<FLOAT,STRING>::facing::rt:
        o << "start";
        break;
      case labeled_block<FLOAT,STRING>::facing::tp:
        o << "start\" transform=\"rotate(-45 " << xperim(i) << ',' << yperim(i) << ')';
        break;
      default:
        o << "middle";
        break;
    }
    o << "\" " << attrs << '>' << strings[i] << "</text>\n" << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  }
};

#endif
