#ifndef SKEL_H
#define SKEL_H

#include "point.h"
#include <vector>



/*
 * class mechalink<> is a (stretchable) mechanical link
 * It generates its endpoint whenever it is requested (through a getter. say)
   by adding 'dx', 'dy', and 'dz' to its initial point reference ('src')
 * Each mechalink<> object holds references to its follow-up mechalink<>'s
   so that changes in position and rotation may cascade
 * mechalink<> objects are chained thus:
 * each holds a reference ('src') to a preceding point, possibly inside
 */

template<typename FLOAT,
        std::size_t DIM, // typically 2 or 3
         typename POINT>
class mechalink; // forward declaration

template<typename FLOAT = double,
         std::size_t DIM = 3, // typically 2 or 3
         typename POINT = point<FLOAT,DIM>
        >
class mechalink {
public:
  typedef                     POINT      point_type;
  typedef mechalink<FLOAT,DIM,POINT> mechalink_type;
  typedef std::vector<mechalink_type*> children_type;
protected:
  const point_type & src; // source point
        point_type   dst; // destination point
  bool updated; // false if dx, dy or dz have changed, yet dst remains the same
  FLOAT dx, dy, dz;
  children_type children;
  FLOAT angle;
public:
  mechalink_type& set_dx(FLOAT x) {dx=x; updated=false; return *this;};
  mechalink_type& set_dy(FLOAT y) {dy=y; updated=false; return *this;};
  mechalink_type& set_dz(FLOAT z) {dz=z; updated=false; return *this;};
  mechalink_type& update();
  const mechalink_type& get_src() const {return src;};
            point_type& get_dst()       {update(); return dst;};
  const     point_type& get_dst() const {update(); return dst;};
  void set_sep(FLOAT s) {};  // DUMMY IMPLEMENTATION
public:
  // FLOAT separation() const {return sqrt(dx*dx + dy*dy + dz*dz);};
  mechalink_type& separation(FLOAT s)         {return *this;}; // DUMMY IMPLEMENTATION
  mechalink_type& rotate_around_x(FLOAT rads) {return *this;}; // DUMMY IMPLEMENTATION
  mechalink_type& rotate_around_y(FLOAT rads) {return *this;}; // DUMMY IMPLEMENTATION
  mechalink_type& rotate_around_z(FLOAT rads) {return *this;}; // DUMMY IMPLEMENTATION
  mechalink_type& grow(FLOAT x=0.0, FLOAT y=0.0, FLOAT z=0.0);
public:
  mechalink(const mechalink_type& ml,
            FLOAT x=0.0, FLOAT y=0.0, FLOAT z=0.0) : src(ml.get_dst()),
            dx(x), dy(y), dz(z)
            {update();};
  mechalink(const point_type& pt,
            FLOAT x=0.0, FLOAT y=0.0, FLOAT z=0.0) : src(pt),
            dx(x), dy(y), dz(z)
            {update();};
}; // class mechalink<>


#endif
