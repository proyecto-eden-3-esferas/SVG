#ifndef SCHEMATICS_SQ_POLYLINE_H
#define SCHEMATICS_SQ_POLYLINE_H

#include <initializer_list>
#include <iostream>
#include <vector>

/* class hv_polyline represents a polyline whose segments are alternatively horizontal and vertical
 *
 */
template <typename FLOAT=double, typename CONTAINER = std::vector<FLOAT> >
class sq_polyline {
public:
  typedef std::size_t size_t;
  bool even(size_t idx) const {return idx % 2 == 0;};
  bool  odd(size_t idx) const {return idx % 2 == 1;};
  FLOAT x1, y1, x2, y2; // same names as attributes of svg::line
  typedef CONTAINER container_t;
  container_t lengths;
  //
  sq_polyline() = default;
  sq_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2) : x1(x1), y1(y1), x2(x2), y2(y2) {};
  sq_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2,
              std::initializer_list<FLOAT> l)         : x1(x1), y1(y1), x2(x2), y2(y2), lengths(l) {};
  template <typename ITER = container_t::const_iterator>
  sq_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2,
              ITER & b, ITER & e)                     : x1(x1), y1(y1), x2(x2), y2(y2), lengths(b,e) {};
};



/* class sq_polyline represents a polyline whose segments are alternatively horizontal and vertical
 *
 */
template <typename FLOAT=double, typename CONTAINER = std::vector<FLOAT> >
class vh_polyline : public sq_polyline<FLOAT,CONTAINER> {
public:
  typedef std::size_t size_t;
  typedef  sq_polyline<FLOAT,CONTAINER> parent_t;
  typedef CONTAINER container_t;
  //
  using parent_t::even, parent_t::odd;
  using parent_t::x1, parent_t::y1, parent_t::x2, parent_t::y2;
  using parent_t::lengths;
  //
  vh_polyline() = default;
  vh_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2) : parent_t(x1, y1, x2, y2) {};
  vh_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2,
              std::initializer_list<FLOAT> l)         : parent_t(x1, y1, x2, y2, l) {};
  template <typename ITER = container_t::const_iterator>
  vh_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2,
              ITER & b, ITER & e)                     : parent_t(x1, y1, x2, y2, b, e) {};
};



#endif
