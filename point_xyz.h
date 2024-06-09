#ifndef POINT_XYZ_H
#define POINT_XYZ_H

// Follows bg::model::d3::point_xyz in <boost/geometry/geometries/point_xyz.hpp>

#include <array>
#include <iostream> // for std::size_t

#include <boost/geometry/core/cs.hpp>

/* class point<> is to behave just like (same interface as)
 * boost::geometry::model::d2::point_xyz
 */
template<typename FLOAT = double,
         //std::size_t DIM = 3, // typically 2 or 3
         typename CoordinateSystem = boost::geometry::cs::cartesian>
class point_xyz {
  FLOAT first, second, third;
public:
  FLOAT const & x() const {return  first;}; // Get x-value.
  FLOAT const & y() const {return second;}; // Get y-value.
  FLOAT const & z() const {return  third;}; // Get z-value.
  void x(FLOAT const & v) {first  = v;};
  void y(FLOAT const & v) {second = v;};
  void z(FLOAT const & v) { third = v;};
  // constructors:
  point_xyz() = default;
  //point_xyz(FLOAT const & x, FLOAT const & y) : first(x), second(y) {}
  point_xyz(FLOAT const & x, FLOAT const & y, FLOAT const & z) : first(x), second(y), third(z) {}
};

namespace bg = boost::geometry;
// Overrides of global set<INDEX> and get<INDEX>:

template<std::size_t IDX>
float get(   const point_xyz<float, bg::cs::cartesian> & pt)   {return pt.x();};
template<>
float get<1>(const point_xyz<float, bg::cs::cartesian> & pt)   {return pt.y();};
template<>
float get<2>(const point_xyz<float, bg::cs::cartesian> & pt)   {return pt.z();};
template<std::size_t IDX>
void  set(         point_xyz<float, bg::cs::cartesian> & pt, float v) {pt.x(v);};
template<>
void  set<1>(      point_xyz<float, bg::cs::cartesian> & pt, float v) {pt.y(v);};
template<>
void  set<2>(      point_xyz<float, bg::cs::cartesian> & pt, float v) {pt.z(v);};

template<std::size_t IDX>
double get(   const point_xyz<double, bg::cs::cartesian> & pt)   {return pt.x();};
template<>
double get<1>(const point_xyz<double, bg::cs::cartesian> & pt)   {return pt.y();};
template<>
double get<2>(const point_xyz<double, bg::cs::cartesian> & pt)   {return pt.z();};
template<std::size_t IDX>
void  set(         point_xyz<double, bg::cs::cartesian> & pt, double v) {pt.x(v);};
template<>
void  set<1>(      point_xyz<double, bg::cs::cartesian> & pt, double v) {pt.y(v);};
template<>
void  set<2>(      point_xyz<double, bg::cs::cartesian> & pt, double v) {pt.z(v);};

template<std::size_t IDX>
long double get(   const point_xyz<long double, bg::cs::cartesian> & pt)   {return pt.x();};
template<>
long double get<1>(const point_xyz<long double, bg::cs::cartesian> & pt)   {return pt.y();};
template<>
long double get<2>(const point_xyz<long double, bg::cs::cartesian> & pt)   {return pt.z();};
template<std::size_t IDX>
void  set(         point_xyz<long double, bg::cs::cartesian> & pt, long double v) {pt.x(v);};
template<>
void  set<1>(      point_xyz<long double, bg::cs::cartesian> & pt, long double v) {pt.y(v);};
template<>
void  set<2>(      point_xyz<long double, bg::cs::cartesian> & pt, long double v) {pt.z(v);};




#endif
