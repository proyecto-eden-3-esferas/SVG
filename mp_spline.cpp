#ifndef MP_SPLINE_CPP
#define MP_SPLINE_CPP


#ifndef MP_POINT_H
#include "mp_point.h"
#endif

#ifndef MP_SPLINE_H
#include "mp_spline.h"
#endif

#ifndef PAIR_AS_POINT_2D_H
#include "pair-as-2D-point.h"
#endif


/* Implementations of mp_spline<FLOAT,POINT,CONTAINER> member functions */


template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::check_state() const {
  // First make sure dir's have been set:
  if(!dirs_set)
    throw dirs_not_set();
  // Then make sure dir's have been set:
  if(!controls_set)
    throw controls_not_set();
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::clear() {
  points.clear();
  is_closed    = false;
  dirs_set     = false;
  controls_set = false;
};
template <typename F, typename POINT, typename CONTAINER>
mp_spline<F,POINT,CONTAINER>& mp_spline<F,POINT,CONTAINER>::operator=(const mp_spline_t& lft) {
  points       = lft.points;
  is_closed    = lft.is_closed;
  dirs_set     = lft.dirs_set;
  controls_set = lft.controls_set;
  return *this;
};


template <typename F, typename POINT, typename CONTAINER>
CONTAINER::iterator mp_spline<F,POINT,CONTAINER>::begin() {dirs_set=false; controls_set=false;
                                                           return points.begin();};
template <typename F, typename POINT, typename CONTAINER>
CONTAINER::iterator mp_spline<F,POINT,CONTAINER>::end()   {return points.end();};
template <typename F, typename POINT, typename CONTAINER>
CONTAINER::const_iterator mp_spline<F,POINT,CONTAINER>::cbegin() const {return points.cbegin();};
template <typename F, typename POINT, typename CONTAINER>
CONTAINER::const_iterator mp_spline<F,POINT,CONTAINER>::cend()   const {return points.  cend();};


template <typename F, typename POINT, typename CONTAINER>
POINT& mp_spline<F,POINT,CONTAINER>::operator[] (std::size_t idx) {
  return points[idx];
};
template <typename F, typename POINT, typename CONTAINER>
const POINT& mp_spline<F,POINT,CONTAINER>::operator[] (std::size_t idx) const {
  return points[idx];
};

template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::y_invert(F depth) {
  check_state();
  for(point_t & p : points)
    p.y_invert(depth);
};

/* set_dir_open_first_by_k() and set_dir_open_last_by_k()
 * correct by k according to 2nd and last but 1 segments */
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_dir_open_first_by_k(F k) {
  F dir = geom_t::atan2(
    points[1].pt.second - points[0].pt.second,
    points[1].pt.first  - points[0].pt.first);
  F dir2nd = geom_t::atan2(
    points[2].pt.second - points[1].pt.second,
    points[2].pt.first  - points[1].pt.first);
  points[0].dir = dir - k*(dir2nd - dir);
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_dir_open_last_by_k(F k) {
  F dirLast = geom_t::atan2(
    points[lastidx()].pt.second - points[lastidx() - 1].pt.second,
    points[lastidx()].pt.first  - points[lastidx() - 1].pt.first);
  F dirLastButOne = geom_t::atan2(
    points[lastidx() - 1].pt.second - points[lastidx() - 2].pt.second,
    points[lastidx() - 1].pt.first  - points[lastidx() - 2].pt.first);
  points[lastidx()].dir = dirLast - k*(dirLastButOne - dirLast);
};

template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_dir3(std::size_t idx) {
  points[idx].dir = geom_t::atan2(
    points[closed_postidx(idx)].pt.second - points[closed_preidx(idx)].pt.second,
    points[closed_postidx(idx)].pt.first  - points[closed_preidx(idx)].pt.first);
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_dir5(std::size_t idx, F k) {
  points[idx].dir = geom_t::atan2(
    points[closed_postidx(idx)].pt.second - points[closed_preidx(idx)].pt.second
- k*(points[closed_preidx(idx)].pt.second - points[closed_prepreidx(idx)].pt.second)
+ k*(points[closed_postidx(idx)].pt.second - points[closed_postpostidx(idx)].pt.second),
    points[closed_postidx(idx)].pt.first  - points[closed_preidx(idx)].pt.first
- k*(points[closed_preidx(idx)].pt.first - points[closed_prepreidx(idx)].pt.first)
+ k*(points[closed_postidx(idx)].pt.first - points[closed_postpostidx(idx)].pt.first)
  );
};

template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_closed_dirs(F k) {
  for(int i=0; i < points.size(); ++i)
    set_dir5(i,k);
  is_closed    = true;
  dirs_set     = true;
  controls_set = false;
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_inner_dirs(F k) { // only on open paths
  for(int i=2; i < lastidx() -1 ; ++i)
    set_dir5(i,k);
  set_dir_open_second();
  set_dir_open_last_but_1();
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_open_dirs_by_k_kends(F k, F kends) {
  set_dir_open_first_by_k(kends);
  set_dir_open_last_by_k (kends);
  set_inner_dirs(k);
  is_closed    = false;
  dirs_set     = true;
  controls_set = false;
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_open_dirs_by_angles_k(F dir_1st, F dir_last, F k) {
  points[0]        .dir = dir_1st;
  points[lastidx()].dir = dir_last;
  set_inner_dirs(k);
  is_closed    = false;
  dirs_set     = true;
  controls_set = false;
};


template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_controls_by_distance_open(F dist) {
  if(!dirs_set)
    throw dirs_not_set();
  points[0].set_post(dist);
  for(int i = 1; i < lastidx() - 1; ++i) {
    points[i].set_pre( dist);
    points[i].set_post(dist);
  }
  points[lastidx()].set_pre(dist);
  // is_closed    = false; // UNNECESSARY?
  controls_set = true;
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_controls_by_distance_closed(F dist) {
  if(!dirs_set)
    throw dirs_not_set();
  for(point_t& p : points) {
    p.set_pre( dist);
    p.set_post(dist);
  }
  // is_closed = true // UNNECESSARY?
  controls_set = true;
};

// Return distance from points(IDX) to previous and next points:
template <typename F, typename POINT, typename CONTAINER>
F mp_spline<F,POINT,CONTAINER>::dist_to_prev(std::size_t idx) const {
  return geom_t::distance(points[idx].pt.first,
                          points[idx].pt.second,
                          points[closed_preidx(idx)].pt.first,
                          points[closed_preidx(idx)].pt.second);
}
template <typename F, typename POINT, typename CONTAINER>
F mp_spline<F,POINT,CONTAINER>::dist_to_next(std::size_t idx) const {
  return geom_t::distance(points[idx].pt.first,
                          points[idx].pt.second,
                          points[closed_postidx(idx)].pt.first,
                          points[closed_postidx(idx)].pt.second);
}

template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_pre_control_by_adjacent_distance(std::size_t idx, F k) {
  points[idx].set_pre(k * dist_to_prev(idx));
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_post_control_by_adjacent_distance(std::size_t idx, F k) {
  points[idx].set_post(k * dist_to_next(idx));
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_control_by_adjacent_distance(std::size_t idx, F k) {
  set_pre_control_by_adjacent_distance( idx,k);
  set_post_control_by_adjacent_distance(idx,k);
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_controls_by_adjacent_distance_closed(F k) {
  if(!dirs_set)
    throw dirs_not_set();
  for(int i=0; i < points.size(); ++i) {
    set_pre_control_by_adjacent_distance( i,k);
    set_post_control_by_adjacent_distance(i,k);
  }
  // is_closed = true // UNNECESSARY?
  controls_set = true;
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::set_controls_by_adjacent_distance_open(F k) {
  if(!dirs_set)
    throw dirs_not_set();
  set_post_control_by_adjacent_distance(0,k);
  set_pre_control_by_adjacent_distance(lastidx(),k);
  for(int i=1; i < (points.size() - 1); ++i)
    set_control_by_adjacent_distance(i,k);
  // is_closed = false // UNNECESSARY?
  controls_set = true;
};

// Members printing to an SVG::path p attribute:

template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::to_svg_p(std::ostream& o, std::size_t idx) const {
  // check_state(); // is this overkill?
  o << "C " << points[idx].postpt.first << ' ' << points[idx].postpt.second;
  o << ", " << points[idx+1].prept.first << ' ' << points[idx+1].prept.second;
  o << ", " << points[idx+1].pt.first << ' ' << points[idx+1].pt.second;
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::to_svg_p(std::ostream& o) const {
  if(is_closed)
    to_svg_p_closed(o);
  else
    to_svg_p_open(o);
};

// Add curves from points[beg] to points[end] inside svg::path::p attribute:
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::to_svg_p(std::ostream& o, std::size_t beg, std::size_t end) const {
  check_state();
  o << "M " << points[beg].pt.first << ' ' << points[beg].pt.second;
  for(int i=beg; i < end; ++i)
    to_svg_p(o,i);
};

template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::close_svg_p(std::ostream& o) const {
  check_state();
  o << " C " << points[lastidx()].postpt.first << ' ' << points[lastidx()].postpt.second;
  o << ", "  << points[0].prept.first << ' ' << points[0].prept.second;
  o << ", "  << points[0].pt.first << ' ' << points[0].pt.second;
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::to_svg_p_closed(  std::ostream& o) const {
  check_state();
  to_svg_p(o, 0, lastidx());
  close_svg_p(o);
};

template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::add_pre_control_to_svg_as_circle(std::ostream& o,
                                    std::size_t idx,
                                    F r,
                                    const std::string& attr) const
{
  check_state();
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_circle_to_svg(o, points[idx].prept.first, points[idx].prept.second, r, attr);
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::add_post_control_to_svg_as_circle(std::ostream& o,
                                    std::size_t idx,
                                    F r,
                                    const std::string& attr) const
{
  check_state();
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_circle_to_svg(o, points[idx].postpt.first, points[idx].postpt.second, r, attr);
};

template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::add_control_to_svg_as_circle(std::ostream& o,
                                    std::size_t idx,
                                    F r,
                                    const std::string& attr) const
{
  check_state();
  add_pre_control_to_svg_as_circle( o,idx,r,attr);
  add_post_control_to_svg_as_circle(o,idx,r,attr);
  /*
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_circle_to_svg(o, points[idx].prept.first, points[idx].prept.second, r, attr);
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_circle_to_svg(o, points[idx].postpt.first, points[idx].postpt.second, r, attr);
  */
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::add_controls_to_svg_as_circles(std::ostream& o,
                                    F r,
                                    const std::string& attr) const
{
  check_state();
  if(is_closed) {
    for(int i = 0; i <= lastidx(); ++i)
      add_control_to_svg_as_circle(o,i,r,attr);
  } else {
    for(int i = 1; i <= lastidx(); ++i)
      add_pre_control_to_svg_as_circle(o,i,r,attr);
    for(int i = 0; i <  lastidx(); ++i)
      add_post_control_to_svg_as_circle(o,i,r,attr);
  } // else
};



template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::add_pre_control_to_svg_as_line(std::ostream& o,
                                              std::size_t idx,
                                              const std::string& attr) const {
  check_state();
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_line_to_svg(o, points[idx].prept.first,
                     points[idx].prept.second,
                     points[idx].pt.first,
                     points[idx].pt.second, attr);
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::add_post_control_to_svg_as_line(std::ostream& o,
                                              std::size_t idx,
                                              const std::string& attr) const {
  check_state();
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_line_to_svg(o, points[idx].postpt.first,
                     points[idx].postpt.second,
                     points[idx].pt.first,
                     points[idx].pt.second, attr);
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::add_control_to_svg_as_line(std::ostream& o,
                                              std::size_t idx,
                                              const std::string& attr) const {
  check_state();
  add_pre_control_to_svg_as_line( o,idx,attr);
  add_post_control_to_svg_as_line(o,idx,attr);
};

template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::add_controls_to_svg_as_lines(std::ostream& o,
                                              const std::string& attr) const {
  check_state();
  if(is_closed) {
  for(int i = 0; i < points.size(); ++i)
    add_control_to_svg_as_line(o,i,attr);
  } else {
    for(int i = 1; i <= lastidx(); ++i)
      add_pre_control_to_svg_as_line(o,i,attr);
    for(int i = 0; i <  lastidx(); ++i)
      add_post_control_to_svg_as_line(o,i,attr);
  } // else
};

template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::add_online_to_svg_as_circle(std::ostream& o,
                                    std::size_t idx,
                                    F r,
                                    const std::string& attr) const
{
  check_state();
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_circle_to_svg(o, points[idx].pt.first, points[idx].pt.second, r, attr);
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::add_online_to_svg_as_circle(std::ostream& o,
                                               F r,
                                               const std::string& attr) const
{
  check_state();
  for(int i = 0; i < points.size(); ++i)
    add_online_to_svg_as_circle(o,i,r,attr);
}

// make_{open|closed} (ARGS)
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::make_open(F dir1st, F dirLast, F kdir, F kctrls) {
  set_open_dirs_by_angles_k(                   dir1st,   dirLast,   kdir);
  set_controls_by_adjacent_distance_open(kctrls);
  is_closed    = false;
  dirs_set     = true;
  controls_set = true;
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::make_open(F kends,             F kdir, F kctrls) {
  set_open_dirs_by_k_kends(                           kdir, kends);
  set_controls_by_adjacent_distance_open(                                   kctrls);
  is_closed    = false;
  dirs_set     = true;
  controls_set = true;
};
template <typename F, typename POINT, typename CONTAINER>
void mp_spline<F,POINT,CONTAINER>::make_closed(                   F kdir, F kctrls) {
  set_closed_dirs(                                                  kdir);
  set_controls_by_adjacent_distance_closed(                                  kctrls);
  is_closed    = true;
  dirs_set     = true;
  controls_set = true;
};

// Compilable constructors:

template <typename F, typename POINT, typename CONTAINER>
mp_spline<F,POINT,CONTAINER>::mp_spline(std::initializer_list<POINT>  il, F dir1st, F dirLast, F kdir, F kctrls)
  : points(il), is_closed(false), dirs_set(true), controls_set(true) {
    set_open_dirs_by_angles_k(             dir1st, dirLast, kdir);
    set_controls_by_adjacent_distance_open(kctrls);
  };
template <typename F, typename POINT, typename CONTAINER>
mp_spline<F,POINT,CONTAINER>::mp_spline(std::initializer_list<POINT>  il, F kends,              F kdir, F kctrls)
  : points(il), is_closed(false), dirs_set(true), controls_set(true) {
    set_open_dirs_by_k_kends(              kdir, kends);
    set_controls_by_adjacent_distance_open(kctrls);
  };
template <typename F, typename POINT, typename CONTAINER>
mp_spline<F,POINT,CONTAINER>::mp_spline(std::initializer_list<POINT>  il,                       F kdir, F kctrls)
  : points(il), is_closed(true), dirs_set(true), controls_set(true) {
    set_closed_dirs(                         kdir  );
    set_controls_by_adjacent_distance_closed(kctrls);
  };

#endif
