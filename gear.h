#ifndef GEAR_H
#define GEAR_H

#ifndef WHEEL_H
#include "wheel.h"
#endif

#include <utility>
#include <vector>

/* TODO

 * [ ] global or static: F get_margin(R1, N1, R2, N2, K=0.44 {return K * (R0 + R1) / sqrt(N0 + N1);}
 *     for calculating the margin shared by two enmeshing gears
 * [ ] void animate_rotate(OSTREAM&,CLOCKWISE) {
 *       animate_rotate(OSTREAM&,CLOCKWISE, get_num_parts(), speed=1.0);
 *     }
 * [ ] Axles should be set a little further apart than R1 + R2
 * [ ] implement a constructor taking a set of points
 * [ ] void   add_angle_delay() {start_angle += 180 / get_num_parts();};
 * [ ] void   set_angle_delay() {start_angle  = 180 / get_num_parts();};
 * [ ] void reset_start_angle() {start_angle  = 0;};
 */

template <typename F = double, template <typename> typename CONT = std::vector>
class cogwheel : public wheel<F> {
public:
  typedef std::size_t size_t;
  typedef std::pair<F,F> point_t;
  typedef angle_addressable<F> angle_addressable_t;
  using angle_addressable_t::cx,  angle_addressable_t::cy;
  using angle_addressable_t::cos, angle_addressable_t::sin;
  using angle_addressable_t::get_x_rotated; // get_x_rotated(X,Y,ANGLE)
  using angle_addressable_t::get_y_rotated; // get_y_rotated(X,Y,ANGLE)
  //
  typedef wheel<F> wheel_t;
  //using wheel_t::radius;
  using wheel_t::get_span_angle;
  using wheel_t::get_num_parts;
  using wheel_t::get_start_angle;
  //
  F r, R; // r < radius < R;
  F quarter_angle;
  F diff_angle;
  /* All-important variable 'points_in_first_section' is
   * a container of the points in the first section
   * assuming 'start_angle' is 0.0.
   */
  CONT<point_t> points_in_first_section;
  void print_points_in_section(std::ostream& o = std::cout, size_t idx = 0) const;
  void print_contour_points(   std::ostream& o = std::cout)                 const;

  //
  F get_start_x(size_t n = 0) const {return cx + get_x_rotated(R, 0.0, get_start_angle() + n*get_span_angle());};
  F get_start_y(size_t n = 0) const {return cy + get_y_rotated(R, 0.0, get_start_angle() + n*get_span_angle());};
  size_t points_per_section() const {return points_in_first_section.size();};
  // Constructor(s):
  cogwheel(F cx=0.0, F cy=0.0,
           F rds=100, F margin=20,
           size_t n=16, F da_per_one = 0.33, F sa=0.0);
};

// Implementations:

template <typename F, template <typename> typename CONT>
void cogwheel<F,CONT>::print_points_in_section(std::ostream& o, size_t idx) const {
  for ( const auto& pr : points_in_first_section) {
    F angle = idx*get_span_angle() + get_start_angle();
    o << ' ' << get_x_rotated(pr.first, pr.second, angle);
    o << ' ' << get_y_rotated(pr.first, pr.second, angle);
    //o << '\n';
  }
};
template <typename F, template <typename> typename CONT>
void cogwheel<F,CONT>::print_contour_points(std::ostream& o) const {
  for (int i=0; i < get_num_parts(); ++i) {
    print_points_in_section(o, i);
  }
};

template <typename F, template <typename> typename CONT>
cogwheel<F,CONT>::cogwheel(F cx, F cy,
           F rds, F margin,
           size_t n, F da_per_one, F sa)
  : wheel<F>(cx, cy, rds, n, sa),
    r(rds - margin), R(rds + margin),
    quarter_angle(get_span_angle() / 4),
    diff_angle(quarter_angle * da_per_one),
    points_in_first_section {
      {cx + R,                                     cy},
      {cx + R * cos(  quarter_angle - diff_angle), cy + R * sin(  quarter_angle - diff_angle)},
      {cx + r * cos(  quarter_angle + diff_angle), cy + r * sin(  quarter_angle + diff_angle)},
      {cx + r * cos(3*quarter_angle - diff_angle), cy + r * sin(3*quarter_angle - diff_angle)},
      {cx + R * cos(3*quarter_angle + diff_angle), cy + R * sin(3*quarter_angle + diff_angle)}
    }
    {};


#endif
