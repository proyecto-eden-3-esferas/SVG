#ifndef SKEL_H
#define SKEL_H

#include "point.h"
#include <array>

/*
 * class mechalink<> is a (stretchable) mechanical link
 * It generates its endpoint whenever it is requested (through a getter)
   by adding 'dx', 'dy', and 'dz' to its initial point reference.
 * mechalink<> objects are chained thus:
 * each may hold a reference ('src') to another, previous one
 */

template<typename FLOAT,
        std::size_t DIM, // typically 2 or 3
         typename POINT>
class mechalink; // forward declaration

template<typename FLOAT = double,
         std::size_t DIM = 3, // typically 2 or 3
         typename POINT = std::array<FLOAT,DIM>
         //, typename CoordinateSystem = boost::geometry::cs::cartesian
         >
class mechalink {
public:
  typedef                     POINT      point_type;
  typedef mechalink<FLOAT,DIM,POINT> mechalink_type;
protected:
  const   mechalink_type *src; //     source point
              point_type  dst; // destination link
  bool updated; // false if dx, dy or dz have changed, yet dst remains the same
  FLOAT dx, dy, dz;
public:
  mechalink_type& set_dx(FLOAT x) {dx=x; updated=false; return *this;};
  mechalink_type& set_dy(FLOAT y) {dy=y; updated=false; return *this;};
  mechalink_type& set_dz(FLOAT z) {dz=z; updated=false; return *this;};
  mechalink_type& update(); // {return *this;}; // DUMMY IMPLEMENTATION
  const mechalink_type& get_src() const {return src;};
  const     point_type& get_src_point();
            point_type& get_dst()       {update(); return dst;};
  const     point_type& get_dst() const {update(); return dst;};
  void set_sep(FLOAT s) {};  // DUMMY IMPLEMENTATION
  bool  is_initialized() const {return !(src==nullptr);};
public:
  // FLOAT separation() const {return sqrt(dx*dx + dy*dy + dz*dz);};
  mechalink_type& separation(FLOAT s)         {return *this;}; // DUMMY IMPLEMENTATION
  mechalink_type& rotate_around_x(FLOAT rads) {return *this;}; // DUMMY IMPLEMENTATION
  mechalink_type& rotate_around_y(FLOAT rads) {return *this;}; // DUMMY IMPLEMENTATION
  mechalink_type& rotate_around_z(FLOAT rads) {return *this;}; // DUMMY IMPLEMENTATION
public:
  mechalink(FLOAT x=0.0, FLOAT y=0.0, FLOAT z=0.0) : src(nullptr), dst{x,y,z}, updated(true),
            dx(x), dy(y), dz(z) {};
  mechalink(const mechalink_type& ml,
            FLOAT x=0.0, FLOAT y=0.0, FLOAT z=0.0) : src(    &ml),             updated(false),
            dx(x), dy(y), dz(z) {update();};
};

#endif
