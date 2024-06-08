#ifndef POINT_XY_H
#define POINT_XY_H

#include <array>
#include <iostream> // for std::size_t

#include <boost/geometry/core/cs.hpp>

/* class point<> is to behave just like (same interface as)
 * boost::geometry::model::d2::point_xy
 */
template<typename FLOAT = double,
         //std::size_t DIM = 3, // typically 2 or 3
         typename CoordinateSystem = boost::geometry::cs::cartesian>
class point_xy {
  FLOAT first, second;
public:
  FLOAT const & x() const {return  first;}; // Get x-value.
  FLOAT const & y() const {return second;}; // Get y-value.
  void x(FLOAT const & v) {first  = v;};
  void y(FLOAT const & v) {second = v;};
  // constructors:
  point_xy() = default;
  point_xy(FLOAT const & x, FLOAT const & y) : first(x), second(y) {}
};

namespace bg = boost::geometry;
// Overrides of global set<INDEX> and get<INDEX>:

template<std::size_t IDX>
float get(   const point_xy<float, bg::cs::cartesian> & pt)   {return pt.x();};
template<>
float get<1>(const point_xy<float, bg::cs::cartesian> & pt)   {return pt.y();};
template<std::size_t IDX>
void  set(         point_xy<float, bg::cs::cartesian> & pt, float v) {pt.x(v);};
template<>
void  set<1>(      point_xy<float, bg::cs::cartesian> & pt, float v) {pt.y(v);};

template<std::size_t IDX>
double get(   const point_xy<double, bg::cs::cartesian> & pt)   {return pt.x();};
template<>
double get<1>(const point_xy<double, bg::cs::cartesian> & pt)   {return pt.y();};
template<std::size_t IDX>
void  set(         point_xy<double, bg::cs::cartesian> & pt, double v) {pt.x(v);};
template<>
void  set<1>(      point_xy<double, bg::cs::cartesian> & pt, double v) {pt.y(v);};

template<std::size_t IDX>
long double get(   const point_xy<long double, bg::cs::cartesian> & pt)   {return pt.x();};
template<>
long double get<1>(const point_xy<long double, bg::cs::cartesian> & pt)   {return pt.y();};
template<std::size_t IDX>
void  set(         point_xy<long double, bg::cs::cartesian> & pt, long double v) {pt.x(v);};
template<>
void  set<1>(      point_xy<long double, bg::cs::cartesian> & pt, long double v) {pt.y(v);};

#endif
