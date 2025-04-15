#include "point.h"
/*
 * class mechalink<> is a (stretchable) mechanical link
 * It generates its endpoint whenever it is requested (through a getter)
 * by adding 'dx', 'dy', and 'dz' to its initial point reference.
 * mechalink's are chained thus: each may hold a reference to another one
 */
template<typename FLOAT,
        std::size_t DIM, // typically 2 or 3
         typename POINT>
class mechalink;

class mechalink {
template<typename FLOAT = double,
         std::size_t DIM = 3, // typically 2 or 3
         typename POINT = point<FLOAT,DIM>
         //, typename CoordinateSystem = boost::geometry::cs::cartesian
         >
class mechalink {
public:
  typedef           POINT      point_type;
  typedef mechalink<R,DIM> mechalink_type;
protected:
  R dx, dy, dz
  const   mechalink_type& src;
  bool initialized;
public:
  const mechalink_type& update() const {
    /*
    pf.x() = pi.x() + dx;
    pf.y() = pi.y() + dy;
    pf.z() = pi.z() + dz;
    */
    return *this;
  };
  const point_type& get_pi() const {return pi;};
        point_type& get_pf()       {update(); return pf;};
  const point_type& get_pf() const {update(); return pf;};
  set_sep(R s);
  bool  is_initialized() const {return initialized;};
  void set_initialized(bool b = true) {initialized=b;};
protected:
  void dx(R d) {pf.x() += d;};
  void dy(R d) {pf.y() += d;};
  void dz(R d) {pf.z() += d;};
public:
  R separation() const {return sqrt(dx*dx + dy*dy + dz*dz);};
  mechalink_type& separation(R s)         {return *this;};
  mechalink_type& rotate_around_x(R rads) {return *this;}
  mechalink_type& rotate_around_y(R rads) {return *this;}
  mechalink_type& rotate_around_z(R rads) {return *this;}
public:
  mechalink(const point_type& i, point_type f) : pi(i), pf(f), initialized( true) {};
  mechalink(const point_type& i)               : pi(i), pf(i), initialized(false) {};
}
