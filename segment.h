#ifndef SEGMENT_H
#define SEGMENT_H

#include <utility> // also provides typedef std::size_t

/* class segment<> is to behave just like (same interface as)
 * boost::geometry::model::segment
 */
template<typename POINT>
class segment : public std::pair<POINT, POINT> {
public:
  typedef POINT point_t;
  typedef std::pair<POINT, POINT> pair_t;
  using pair_t::first, pair_t::second;
  //
  /*
  template<std::size_t IDX>
  const POINT & get() const {  // get either component point
    if(IDX == 0) return pair_t::first;
    else         return pair_t::second;
  };
  template<std::size_t IDX>
  void set(POINT const & pt) { // Set either component point
    if(IDX == 0) pair_t::first  = pt;
    else         pair_t::second = pt;
  };
  */
  // Constructors:
  segment() = default;
  segment(POINT const & p1, POINT const & p2) : pair_t(p1,p2) {};
};


#ifndef POINT_H
#include "point.h"
#endif

namespace bg = boost::geometry;

/* Overrides of global set<INDEX> and get<INDEX>
 * First we define [const] POINT& get<IDX>([const] SEGMENT&)
 * Then FLOAT& get<PTINDEX, COMPONENT_INDEX)(const SEGMENT& ) and
 *      void   set<PTINDEX, COMPONENT_INDEX)(const SEGMENT& seg, FLOAT val)
 */

template<std::size_t INDEX=0,
         typename POINT = point<double,2,boost::geometry::cs::cartesian> >
const POINT& get(const segment<POINT>& sg) {
  if(INDEX == 0) return sg.first;
  else           return sg.second;
};
template<std::size_t INDEX=0,
         typename POINT = point<double,2,boost::geometry::cs::cartesian> >
      POINT& get(      segment<POINT>& sg) {
  if(INDEX == 0) return sg.first;
  else           return sg.second;
};

template<std::size_t PTINDEX,
         std::size_t CINDEX,
         typename POINT = point<double,2,boost::geometry::cs::cartesian>,
         typename FLOAT = double>
FLOAT get(const segment<POINT>& seg) {
  return get<CINDEX>( get<PTINDEX>(seg) );
};

template<std::size_t PTINDEX,
         std::size_t CINDEX,
         typename POINT = point<double,2,boost::geometry::cs::cartesian>,
         typename FLOAT = double>
void set(segment<POINT>& seg, FLOAT val) {
  return set<CINDEX>(get<PTINDEX>(seg), val);
};

#endif
