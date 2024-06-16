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
  container_t lengths;
  //
  bool even(size_t idx) const {return idx % 2 == 0;};
  bool  odd(size_t idx) const {return idx % 2 == 1;};
  // constructors:
  vec_polyline() = default;
  vec_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2) : sq_polyline_t(x1,y1,x2,y2)         {};
  vec_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2,
              std::initializer_list<FLOAT> l)         : sq_polyline_t(x1,y1,x2,y2), lengths(l) {};
  template <typename ITER = container_t::const_iterator>
  vec_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2,
              ITER & b, ITER & e)                   : sq_polyline_t(x1,y1,x2,y2), lengths(b,e) {};
};

#endif
