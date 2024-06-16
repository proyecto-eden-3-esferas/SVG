#ifndef SCHEMATICS_VEC_POLYLINE_H
#define SCHEMATICS_VEC_POLYLINE_H

#ifndef SCHEMATICS_SQ_POLYLINE_H
#include "schematics.sq_polyline.h"
#endif

template <typename FLOAT=double, typename CONTAINER = std::vector<FLOAT> >
class vec_polyline : public sq_polyline<FLOAT> {
public:
  typedef std::size_t size_t;
  typedef CONTAINER container_t;
  typedef sq_polyline<FLOAT> sq_polyline_t;
  using sq_polyline_t::add_start_to_svg_path, sq_polyline_t::add_end_to_svg_path;
  using sq_polyline_t::x1, sq_polyline_t::y1, sq_polyline_t::x2, sq_polyline_t::y2;
  container_t lengths;
  //
  bool even(size_t idx) const {return idx % 2 == 0;};
  bool  odd(size_t idx) const {return idx % 2 == 1;};
  virtual void add_to_svg_path(std::ostream& o) const {
    FLOAT curx(x1), cury(y1); // current x,y as horizontal and vertical lines are added
    add_start_to_svg_path(o);
    for(int i = 0; i < lengths.size(); ++i) {
      if(even(i)) {
        o << " h " << lengths[i];
        curx += lengths[i];
      } else {
        o << " v " << lengths[i];
        cury += lengths[i];
      }
    } // for
    if(even(lengths.size() ) ) { // last segment was vertical,   so
      o << " L " << x2;
      o << " V " << y2;
    } else {                   // last segment was horizontal, so
      o << " V " << y2;
      o << " L " << x2;
    }
    add_end_to_svg_path(  o);
  };
  // constructors:
  vec_polyline() = default;
  vec_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2) : sq_polyline_t(x1,y1,x2,y2) {};
  vec_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2,
              std::initializer_list<FLOAT> l) : sq_polyline_t(x1,y1,x2,y2), lengths(l) {};

  template <typename ITER = container_t::const_iterator>
  vec_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2,
              ITER & b, ITER & e) :             sq_polyline_t(x1,y1,x2,y2), lengths(b,e) {};
};

#endif
