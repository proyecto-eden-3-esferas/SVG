#ifndef MP_CURVES_H
#define MP_CURVES_H

/* The MetaPost model of curves makes it easier to draw natural objects
   such as rocks, plants, animals, anatomy, landscapes...
 * In this model, a curve if fitted through a set of points.
   Additionally, some restrictions may be set as to
   - the direction (angle to the X-axis) of the curve at a given point
   - how taught or straightened out ("tension" in MetaPost parlance) the curve is at a given point
     (in my model I call it "distance" from a point to its two control points)
 * Thus I have defined a curve class called mp_spline<>
 * The prefix "mp_" does stand for MetaPost, but I may not implement Hobby’s Algorithm here.
 * All angles in radians. For conversions use:
   geometry_2D<F>::deg_to_rad(ANGLE), and
   geometry_2D<F>::rad_to_def(ANGLE)
 *
 * Key characteristics
   (1) A curve is defined through on-line points (points on the line).
       Another kind of points (found in Bezier curves)
       is control points, which direct the drawing of the line.
   (2) On-line points are either terminal (begin and end) or middle points
   (3) For a smooth curve, a point on a line has a specific direction,
       that is, the curve passes through the point at an angle to the X-axis
   (4) A composite curve or spline is a list of on-line points,
       supplemented with control points
   (5) Internally, an on-line point has one or two control points
       so that the containing curve may be translated into cubir Bezier curves.
 * MetaPost uses Hobby’s Algorithm, whose aim is to fit a curve to a set of points smoothly and in a controlled manner.
 * A MetaPost primer is to be found at: https://proyecto-eden-3-esferas.github.io/metapost.html
   For MetaPost curves go to: https://proyecto-eden-3-esferas.github.io/metapost.curves.html
 */

/* TODO
 * line and circle elements should bear class or id attributes for easy styling
 * maybe also path elements should bear class or id attributes for easy styling
 * distance of a control point to its on-line point should be proportional
   to distance to adjacent (next or previous) point
 *
 */

#include "schematics.angle.h"
#include "svg.h"
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>


/* A spline from points à la MetaPost
 * The way to preceed, once the on-line points are loaded, is
 * first to set the dir[ection] (angle to the X-axis) on all its points
 * then to define both control points (or just one in the case of terminal points)
 * at each spline point
 */
template <typename F = double>
class mp_spline {
public:
  /* Define inner class 'point'.
   * An 'mp_spline' object has a sequential container of such points */
  class point {
  public:
    typedef geometry_2D<F> geom_t;
    typedef std::pair<F,F> pair_t;
    typedef             F   dir_t;
    pair_t pt, prept, postpt; // on-line point plus its 2 control points
    dir_t  dir;
  protected:
    void set_control(      F dist, pair_t& ctrl) const {
      geom_t::set_angle_dist_from_of(dir, dist, pt, ctrl);};
    void set_control(F dr, F dist, pair_t& ctrl) const {
      geom_t::set_angle_dist_from_of( dr, dist, pt, ctrl);};
    void set_pre( F dr, F dist) {
      geom_t::set_angle_dist_from_of( dr + std::numbers::pi_v<F>, dist, pt, prept);};
    void set_post(F dr, F dist) {geom_t::set_angle_dist_from_of( dr, dist, pt, postpt);};
  public:
    void set_dir(F dr) {dir=dr;};
    void set_pre(       F dist) {
      geom_t::set_angle_dist_from_of(dir + std::numbers::pi_v<F>, dist, pt, prept);};
    void set_post(      F dist) {
      geom_t::set_angle_dist_from_of(dir, dist, pt, postpt);};
    // Constructor(s):
    point(const point& p) = default;
    point(const pair_t& p, dir_t d=0.0) : pt(p),     dir(d) {};
    point(F x, F y,        dir_t d=0.0) : pt({x,y}), dir(d) {};
    point(const pair_t& p, const pair_t& pr, const pair_t& po, dir_t d=0.0)
    : pt(p),     prept(pr), postpt(po), dir(d)
    {};
    point(F x, F y,        const pair_t& pr, const pair_t& po, dir_t d=0.0)
    : pt({x,y}), prept(pr), postpt(po), dir(d)
    {};
  }; // inner class point<>
public:
  typedef std::pair<F,F> pair_t;
  typedef point point_t;
  typedef std::vector<point_t> points_t;
  typedef geometry_2D<F> geom_t;
  points_t points;
  points_t::iterator begin() {return points.begin();};
  points_t::iterator   end() {return points.  end();};
  bool has_dirs; // useful at all?
protected:
  /* const */ bool closed;
  /* lastidx(IDX) returns the last valid index into points, while
   * closed_preidx(IDX) and closed_postidx(IDX) return previous and next index
     for a closed path, i.e. as if 'points' were a circular sequential container.
   *  */
  F lastidx()    const {return points.size() - 1;}
  F closed_preidx( F i) const {if(i > 0) return i-1;
                               else return lastidx();};
  F closed_prepreidx(F i)   const {return closed_preidx(closed_preidx(i));};
  F closed_postidx(F i) const {if(i < lastidx()) return i+1;
                               else return 0;};
  F closed_postpostidx(F i) const {return closed_postidx(closed_postidx(i));};
public:
  bool is_closed() const {return  closed;}
  bool is_open  () const {return !closed;}
  virtual void set_open  () {closed=false;}
  virtual void set_closed() {closed=true;}
  /* The all-important virtual member function set_dir(IDX).
   * It could be virtual-ly specialized by taking more points (before and after)
     into account. In that case, open paths should
     have their start and end points' directions defined
   * If not satisfied, the user or client might set the dir's manually
     and then readjust the control points.
   */
protected:
  /* set_dir_open_first() and set_dir_open_last()
   * set the first and last points in an open path,
   * and correct by k according to 2nd and last but 1 segments */
  virtual void set_dir_open_first(F k);
  virtual void set_dir_open_last (F k);
  /* set_dir3(IDX) assumes a closed path,
   * so it should not be called on terminal points,
   * that is start and finish points of an open path.
   * set_dir5(IDX,K) works on all on-line points on a closed path
   * and on points not next to a terminal on-line point.
   */
  virtual void set_dir3(int idx);
  virtual void set_dir5(int idx, F k=0.22);
  virtual void set_dir2nd        () {}; // as yet UNIMPLEMENTED
  virtual void set_dir_last_but_1() {}; // as yet UNIMPLEMENTED
public:
  void set_closed_dirs() {
    for(int i=0; i < points.size(); ++i)
      set_dir5(i);
  };
  // Members for setting dirs in an open spline:
  void set_inner_dirs() {
    for(int i=2; i < lastidx() -1 ; ++i)
      set_dir5(i);
    set_dir3(            1); // should take points[0        ].dir into account, though
    set_dir3(lastidx() - 1); // should take points[lastidx()].dir into account, though
  };
  void set_open_dirs(F k = 0.33) {
    set_dir_open_first(k);
    set_dir_open_last (k);
    set_inner_dirs();
  };
  /* To set the controls on every point in 'points'
   * you can rely on a fixed distance (from on-line point to its controls)
   * or let some member function estimate a distance (for each point)
   */
  void set_controls(F dist);
  /* Distance from on-line point to its control is k * distance(pt, next-point)
   * Functions: set_{pre_|post_}by_adjacent_distance([IDX, ] K)
   */
  void set_pre_by_adjacent_distance(int idx, F k=0.4);
  void set_post_by_adjacent_distance(int idx, F k=0.4);
  void set_by_adjacent_distance(int idx, F k=0.4);
  void set_by_adjacent_distance(F k=0.4);
  //
  virtual F  pre_control_dist(int IDX, F k=0.2) const {return 0.5;}; // UNIMPLEMENTED
  virtual F post_control_dist(int IDX, F k=0.2) const {return 0.5;}; // UNIMPLEMENTED
  void set_controls_by_factor(F k=0.2);
protected:
  // Add curves from points[beg] to points[end] inside svg::path::p attribute:
  void to_svg_p(std::ostream& o, int beg, int end) const;
public:
  void to_svg_p_open(    std::ostream& o) const {to_svg_p(o,0, lastidx());};
  /* close_svg_p(OSTREAM) adds the closing Bezier curve
     (from last point to first) to the unclosed p attribute in svg::path
     yet it does not close the p attribute as such (no closing quotes added)*/
  void close_svg_p(std::ostream& o) const;
  void to_svg_p_closed(  std::ostream& o) const {
    to_svg_p(o, 0, lastidx());
    close_svg_p(o);
  };
  /* Show both control points for a given on-line point
   * as svg::circle's at the end of control svg::line's
   */
  void add_control_to_svg_as_circle(std::ostream& o,
                                    std::size_t idx,
                                    F r=5.0,
                                    const std::string& attr = "class=\"bezier-control\"") const;
  void add_control_to_svg_as_line(std::ostream& o,
                                  std::size_t idx,
                                  const std::string& attr = "class=\"bezier-control\"") const;
  // constructors:
  mp_spline() : closed(false) {};
  mp_spline(std::initializer_list<pair_t> il,               bool clsd=false)
  : points(il), has_dirs(false), closed(clsd) {};
  mp_spline(std::initializer_list<mp_spline<F>::point>  il, bool clsd=false)
  : points(il), has_dirs( true), closed(clsd) {};
  template <typename CONTAINER>
  mp_spline(const CONTAINER& c,                             bool clsd=false)
  : points(c.begin(), c.end()), has_dirs(true), closed(clsd) {};
}; // class mp_spline<>

/* Implementations of mp_spline<FLOAT> member functions */

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

/* set_dir_open_first() and set_dir_open_last()
 * correct by k according to 2nd and last but 1 segments */
template <typename F>
void mp_spline<F>::set_dir_open_first(F k) {
  points[0].dir = geom_t::atan2(
    points[1].pt.second - points[0].pt.second
 - k*(points[2].pt.second - points[1].pt.second),
    points[1].pt.first  - points[0].pt.first)
 - k*(points[2].pt.first  - points[1].pt.first);
};
template <typename F>
void mp_spline<F>::set_dir_open_last (F k) {
  points[lastidx()].dir = geom_t::atan2(
    points[lastidx()].pt.second - points[lastidx() - 1].pt.second
 - k*(points[lastidx()-1].pt.second - points[lastidx() - 2].pt.second),
    points[lastidx()  ].pt.first  - points[lastidx() - 1].pt.first)
 - k*(points[lastidx()-1].pt.first  - points[lastidx() - 2].pt.first);
};


template <typename F>
void mp_spline<F>::set_controls(F dist) {
  for(point& p : points) {
    p.set_pre( dist);
    p.set_post(dist);
  }
};
/* Distance from on-line point to its control is k * distance(pt, next-point)
 * Functions: set_{pre_|post_}by_adjacent_distance([IDX, ] K)
 */
template <typename F>
void mp_spline<F>::set_pre_by_adjacent_distance(int idx, F k) {
  points[idx].set_pre(k * geom_t::distance(points[idx].pt.first,
                                           points[idx].pt.second,
                                           points[closed_preidx(idx)].pt.first,
                                           points[closed_preidx(idx)].pt.second));
};
template <typename F>
void mp_spline<F>::set_post_by_adjacent_distance(int idx, F k) {
  points[idx].set_post(k * geom_t::distance(points[idx].pt.first,
                                            points[idx].pt.second,
                                            points[closed_postidx(idx)].pt.first,
                                            points[closed_postidx(idx)].pt.second));
};
template <typename F>
void mp_spline<F>::set_by_adjacent_distance(int idx, F k) {
  set_pre_by_adjacent_distance(idx,k);
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
void mp_spline<F>::set_controls_by_factor(F k) {
  for(int i = 0; i < points.size(); ++i) {
    points[i].set_pre(  pre_control_dist(i,k));
    points[i].set_post(post_control_dist(i,k));
  }
};

// Add curves from points[beg] to points[end] inside svg::path::p attribute:
template <typename F>
void mp_spline<F>::to_svg_p(std::ostream& o, int beg, int end) const {
  o << "M " << points[beg].pt.first << ' ' << points[beg].pt.second;
  for(int i=beg; i < end; ++i) {
    o << "C " << points[i].postpt.first << ' ' << points[i].postpt.second;
    o << ", " << points[i+1].prept.first << ' ' << points[i+1].prept.second;
    o << ", " << points[i+1].pt.first << ' ' << points[i+1].pt.second;
  }
};

template <typename F>
void mp_spline<F>::close_svg_p(std::ostream& o) const {
  o << " C " << points[lastidx()].postpt.first << ' ' << points[lastidx()].postpt.second;
  o << ", "  << points[0].prept.first << ' ' << points[0].prept.second;
  o << ", "  << points[0].pt.first << ' ' << points[0].pt.second;
};

template <typename F>
void mp_spline<F>::add_control_to_svg_as_circle(std::ostream& o,
                                    std::size_t idx,
                                    F r,
                                    const std::string& attr) const
  {
    o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
    o << "<circle ";
    if(attr.length() > 0)
      o << attr << ' ';
    o << "cx=\"" << points[idx].prept.first  <<'\"';
    o <<        " cy=\"" << points[idx].prept.second <<'\"';
    o <<         " r=\"" << r <<"\"/>\n";
    o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
    o << "<circle ";
    if(attr.length() > 0)
      o << attr << ' ';
    o <<        "cx=\"" << points[idx].postpt.first  <<'\"';
    o <<        " cy=\"" << points[idx].postpt.second <<'\"';
    o <<         " r=\"" << r <<"\"/>\n";
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

#endif
