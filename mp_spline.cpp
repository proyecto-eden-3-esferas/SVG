#ifndef MP_SPLINE_CPP
#define MP_SPLINE_CPP


#ifndef MP_SPLINE_H
#include "mp_spline.h"
#endif

/* Implementations of mp_spline<FLOAT>::point member functions: NONE */

/* Implementations of mp_spline<FLOAT> member functions */

/* set_dir_open_first() and set_dir_open_last()
 * correct by k according to 2nd and last but 1 segments */
template <typename F>
void mp_spline<F>::set_dir_open_first(F k) {
  F dir = geom_t::atan2(
    points[1].pt.second - points[0].pt.second,
    points[1].pt.first  - points[0].pt.first);
  F dir2nd = geom_t::atan2(
    points[2].pt.second - points[1].pt.second,
    points[2].pt.first  - points[1].pt.first);
  points[0].dir = dir - k*(dir2nd - dir);
};
template <typename F>
void mp_spline<F>::set_dir_open_last(F k) {
  F dirLast = geom_t::atan2(
    points[lastidx()].pt.second - points[lastidx() - 1].pt.second,
    points[lastidx()].pt.first  - points[lastidx() - 1].pt.first);
  F dirLastButOne = geom_t::atan2(
    points[lastidx() - 1].pt.second - points[lastidx() - 2].pt.second,
    points[lastidx() - 1].pt.first  - points[lastidx() - 2].pt.first);
  points[lastidx()].dir = dirLast - k*(dirLastButOne - dirLast);
};

template <typename F>
void mp_spline<F>::set_dir3(int idx) {
  points[idx].dir = geom_t::atan2(
    points[closed_postidx(idx)].pt.second - points[closed_preidx(idx)].pt.second,
    points[closed_postidx(idx)].pt.first  - points[closed_preidx(idx)].pt.first);
};
template <typename F>
void mp_spline<F>::set_dir5(int idx, F k) {
  points[idx].dir = geom_t::atan2(
    points[closed_postidx(idx)].pt.second - points[closed_preidx(idx)].pt.second
- k*(points[closed_preidx(idx)].pt.second - points[closed_prepreidx(idx)].pt.second)
+ k*(points[closed_postidx(idx)].pt.second - points[closed_postpostidx(idx)].pt.second),
    points[closed_postidx(idx)].pt.first  - points[closed_preidx(idx)].pt.first
- k*(points[closed_preidx(idx)].pt.first - points[closed_prepreidx(idx)].pt.first)
+ k*(points[closed_postidx(idx)].pt.first - points[closed_postpostidx(idx)].pt.first)
  );
};

template <typename F>
void mp_spline<F>::set_closed_dirs() {
  for(int i=0; i < points.size(); ++i)
    set_dir5(i);
};
template <typename F>
void mp_spline<F>::set_inner_dirs() { // only on open paths
  for(int i=2; i < lastidx() -1 ; ++i)
    set_dir5(i);
  set_dir_second();
  set_dir_last_but_1();
};
template <typename F>
void mp_spline<F>::set_open_dirs(F k) {
  set_dir_open_first(k);
  set_dir_open_last (k);
  set_inner_dirs();
};
template <typename F>
void mp_spline<F>::set_open_dirs(F dir_1st, F dir_last) {
  points[0]        .dir = dir_1st;
  points[lastidx()].dir = dir_last;
  set_inner_dirs();
};

template <typename F>
void mp_spline<F>::set_controls_distance(F dist) {
  for(point& p : points) {
    p.set_pre( dist);
    p.set_post(dist);
  }
};

// Return distance from points(IDX) to previous and next points:
template <typename F>
F mp_spline<F>::dist_to_prev(int idx) const {
  return geom_t::distance(points[idx].pt.first,
                          points[idx].pt.second,
                          points[closed_preidx(idx)].pt.first,
                          points[closed_preidx(idx)].pt.second);
}
template <typename F>
F mp_spline<F>::dist_to_next(int idx) const {
  return geom_t::distance(points[idx].pt.first,
                          points[idx].pt.second,
                          points[closed_postidx(idx)].pt.first,
                          points[closed_postidx(idx)].pt.second);
}

// Distance from on-line point to its control is k * distance(pt, {next-point|next-point})
template <typename F>
F mp_spline<F>::pre_control_dist(int idx, F k) const {
  return k * dist_to_prev(idx);
}
template <typename F>
F mp_spline<F>::post_control_dist(int idx, F k) const {
  return k * dist_to_next(idx);
}

template <typename F>
void mp_spline<F>::set_pre_by_adjacent_distance(int idx, F k) {
  points[idx].set_pre(pre_control_dist(idx,k));
};
template <typename F>
void mp_spline<F>::set_post_by_adjacent_distance(int idx, F k) {
  points[idx].set_post(post_control_dist(idx,k));
};
template <typename F>
void mp_spline<F>::set_by_adjacent_distance(int idx, F k) {
  set_pre_by_adjacent_distance( idx,k);
  set_post_by_adjacent_distance(idx,k);
};
template <typename F>
void mp_spline<F>::set_by_adjacent_distance(F k) {
  for(int i=0; i < points.size(); ++i) {
    set_pre_by_adjacent_distance( i,k);
    set_post_by_adjacent_distance(i,k);
  }
};

template <typename F>
void mp_spline<F>::to_svg_p(std::ostream& o, int idx) const {
  o << "C " << points[idx].postpt.first << ' ' << points[idx].postpt.second;
  o << ", " << points[idx+1].prept.first << ' ' << points[idx+1].prept.second;
  o << ", " << points[idx+1].pt.first << ' ' << points[idx+1].pt.second;
};
// Add curves from points[beg] to points[end] inside svg::path::p attribute:
template <typename F>
void mp_spline<F>::to_svg_p(std::ostream& o, int beg, int end) const {
  o << "M " << points[beg].pt.first << ' ' << points[beg].pt.second;
  for(int i=beg; i < end; ++i)
    to_svg_p(o,i);
};

template <typename F>
void mp_spline<F>::close_svg_p(std::ostream& o) const {
  o << " C " << points[lastidx()].postpt.first << ' ' << points[lastidx()].postpt.second;
  o << ", "  << points[0].prept.first << ' ' << points[0].prept.second;
  o << ", "  << points[0].pt.first << ' ' << points[0].pt.second;
};

template <typename F>
void mp_spline<F>::add_controls_to_svg_as_circles(std::ostream& o,
                                    std::size_t idx,
                                    F r,
                                    const std::string& attr) const
{
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_circle_to_svg(o, points[idx].prept.first, points[idx].prept.second, r, 2, attr);
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_circle_to_svg(o, points[idx].postpt.first, points[idx].postpt.second, r, 2, attr);
};
template <typename F>
void mp_spline<F>::add_controls_to_svg_as_circles(std::ostream& o,
                                    F r,
                                    const std::string& attr) const
{
  for(int i = 0; i < points.size(); ++i)
    add_controls_to_svg_as_circles(o,i,r,attr);
};

template <typename F>
void mp_spline<F>::add_control_to_svg_as_line(std::ostream& o,
                                              std::size_t idx,
                                              const std::string& attr) const {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << "<line ";
  if(attr.length() > 0)
    o << attr << ' ';
  o << "x1=\"" << points[idx].prept.first  <<'\"';
  o <<      " y1=\"" << points[idx].prept.second <<'\"';
  o <<      " x2=\"" << points[idx].pt.first <<'\"';
  o <<      " y2=\"" << points[idx].pt.second << "\"/>\n";
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << "<line ";
  if(attr.length() > 0)
    o << attr << ' ';
  o << "x1=\"" << points[idx].postpt.first  <<'\"';
  o <<      " y1=\"" << points[idx].postpt.second <<'\"';
  o <<      " x2=\"" << points[idx].pt.first <<'\"';
  o <<      " y2=\"" << points[idx].pt.second << "\"/>\n";
};
template <typename F>
void mp_spline<F>::add_control_to_svg_as_line(std::ostream& o,
                                              const std::string& attr) const {
  for(int i = 0; i < points.size(); ++i)
    add_control_to_svg_as_line(o,i,attr);
};

template <typename F>
void mp_spline<F>::add_online_to_svg_as_circle(std::ostream& o,
                                    std::size_t idx,
                                    F r,
                                    const std::string& attr) const
{
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_circle_to_svg(o, points[idx].pt.first, points[idx].pt.second, r, 2, attr);
};
template <typename F>
void mp_spline<F>::add_online_to_svg_as_circle(std::ostream& o,
                                               F r,
                                               const std::string& attr) const
{
  for(int i = 0; i < points.size(); ++i)
    add_online_to_svg_as_circle(o,i,r,attr);
}

#endif
