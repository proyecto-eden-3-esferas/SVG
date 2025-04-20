#ifndef POINT_H
#define POINT_H

#include <array>
#include <iostream> // for std::size_t

#include <boost/geometry/core/cs.hpp>

/* class point<> is to behave just like (same interface as)
 * boost::geometry::model::point
 */
template<typename FLOAT = double,
         std::size_t DIM = 3, // typically 2 or 3
         typename CoordinateSystem = boost::geometry::cs::cartesian>
class point {
  std::array<FLOAT,DIM> coordinates;
public:
  template<std::size_t IDX>
  FLOAT const  & get() const {return coordinates[IDX];}; // Get a coordinate.
  template<std::size_t IDX>
  void set(FLOAT const & value) {coordinates[IDX] = value;}; // Set a coordinate.
  // constructors:
  point() = default; // Default constructor, no initialization.
  point(FLOAT const & v0)                                     : coordinates{v0} {};
  point(FLOAT const & v0, FLOAT const & v1)                   : coordinates{v0, v1} {};
  point(FLOAT const & v0, FLOAT const & v1, FLOAT const & v2) : coordinates{v0,v1,v2} {};
};
// partial specialization for DIM=2
template<typename FLOAT,
         typename CoordinateSystem>
class point<FLOAT,2,CoordinateSystem> {
  std::array<FLOAT,2> coordinates;
public:
  template<std::size_t IDX>
  FLOAT const  & get() const {return coordinates[IDX];}; // Get a coordinate.
  template<std::size_t IDX>
  void set(FLOAT const & value) {coordinates[IDX] = value;}; // Set a coordinate.
  // constructors:
  point() = default; // Default constructor, no initialization.
  point(FLOAT const & v0)                                     : coordinates{v0} {};
  point(FLOAT const & v0, FLOAT const & v1)                   : coordinates{v0, v1} {};
};


namespace bg = boost::geometry;

// Overrides of global set<INDEX> and get<INDEX>
template<std::size_t IDX>
float get(const point<float, 2, bg::cs::cartesian> & pt)   {return pt.get<IDX>();};
template<std::size_t IDX>
void  set(      point<float, 2, bg::cs::cartesian> & pt, float v) {pt.set<IDX>(v);};
template<std::size_t IDX>
float get(const point<float, 3, bg::cs::cartesian> & pt)   {return pt.get<IDX>();};
template<std::size_t IDX>
void  set(      point<float, 3, bg::cs::cartesian> & pt, float v) {pt.set<IDX>(v);};

template<std::size_t IDX>
double get(const point<double, 2, bg::cs::cartesian> & pt)   {return pt.get<IDX>();};
template<std::size_t IDX>
void  set(      point<double, 2, bg::cs::cartesian> & pt, double v) {pt.set<IDX>(v);};
template<std::size_t IDX>
double get(const point<double, 3, bg::cs::cartesian> & pt)   {return pt.get<IDX>();};
template<std::size_t IDX>
void  set(      point<double, 3, bg::cs::cartesian> & pt, double v) {pt.set<IDX>(v);};

template<std::size_t IDX>
long double get(const point<long double, 2, bg::cs::cartesian> & pt)   {return pt.get<IDX>();};
template<std::size_t IDX>
void  set(      point<long double, 2, bg::cs::cartesian> & pt, long double v) {pt.set<IDX>(v);};
template<std::size_t IDX>
long double get(const point<long double, 3, bg::cs::cartesian> & pt)   {return pt.get<IDX>();};
template<std::size_t IDX>
void  set(      point<long double, 3, bg::cs::cartesian> & pt, long double v) {pt.set<IDX>(v);};

#endif
