#ifndef MP_CURVES_H
#define MP_CURVES_H

/* The MetaPost model of curves makes it easier to draw natural objects
   such as rocks, plants, animals, anatomy, landscapes...
 * The prefix "mp_" stands for MetaPost, but I may not implement Hobby’s Algorithm here.
 * All angles in radians. For conversions use:
   angle_addressable_base<F>::deg_to_rad(ANGLE), and
   angle_addressable_base<F>::rad_to_def(ANGLE)
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


/* class base_mp_point has no member variables
   only static member function(s):
   (1) static void set_control_of(F dr, F dist, const pair_t& pt, pair_t& ctrl):
       it takes a source point (pt), a "direction" (angle to the X-axis),
       an in/out point "ctrl" (non-const reference) and a "distance",
       and sets the in/out point so that the line from pt to ctrl
       is at an angle dir to the X-axis and is dist[ance] units long.
       NOTE: an analogous (member) function has been defined in angle_addressable_base<F>
             in header "schematics.angle.h"

   (2) ...
 */
template <typename F = double>
class base_mp_point {
public:
  typedef std::pair<F,F> pair_t;
  typedef angle_addressable_base<F> angle_addressable_base_t;
  static void set_control_of(F dr, F dist, const pair_t& pt, pair_t& ctrl) {
    ctrl.first  = pt.first  + dist*angle_addressable_base_t::cos(dr);
    ctrl.second = pt.second + dist*angle_addressable_base_t::sin(dr);
  };
};

// Partial specializations of points as references remain: UNIMPLEMENTED


/* A spline from points.
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
  class point : public base_mp_point<F> {
  public:
    typedef base_mp_point<F> base_t;
    typedef std::pair<F,F> pair_t;
    typedef             F   dir_t;
    using base_t::set_control_of;
    /*
    using angle_addressable_base<F>::set_angle_dist_from_of;
    would make a neat drop-in substitute but fails to compile
    because angle_addressable_base<F>’ is not a parent.
    So you have to code:
      typedef angle_addressable_base<F> geom_t;
    Then you can call geom_t::set_angle_dist_from_of(ARGS)
    instead of set_control_of(ARGS) and make do without ugly ::base_mp_point<F>
    */
    pair_t pt, prept, postpt; // on-line point plus its 2 control points
    dir_t  dir;
  protected:
    void set_control(      F dist, pair_t& ctrl) const {set_control_of(dir, dist, pt, ctrl);};
    void set_control(F dr, F dist, pair_t& ctrl) const {set_control_of( dr, dist, pt, ctrl);};
    void set_pre( F dr, F dist) {set_control_of( dr + std::numbers::pi_v<F>, dist, pt, prept);};
    void set_post(F dr, F dist) {set_control_of( dr, dist, pt, postpt);};
  public:
    void set_dir(F dr) {dir=dr;};
    void set_pre(       F dist) {set_control_of(dir + std::numbers::pi_v<F>, dist, pt, prept);};
    void set_post(      F dist) {set_control_of(dir, dist, pt, postpt);};
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
  typedef angle_addressable_base<F> angle_addressable_base_t;
  points_t points;
  points_t::iterator begin() {return points.begin();};
  points_t::iterator   end() {return points.  end();};
  bool has_dirs;
  /* lastidx(IDX) returns the last valid index into points, while
   * preidx(IDX) and postidx(IDX) return previous and next index
     as if 'points' was a circular sequential container.
   *  */
  F lastidx()    const {return points.size() - 1;}
  F preidx( F i) const {if(i > 0) return i-1;
                        else return lastidx();};
  F postidx(F i) const {if(i < lastidx()) return i+1;
                        else return 0;};
  /* The all-important member function set_dir(IDX).
   * It could be specialized by taking more points (before and after)
     into account.
   * If not satisfied, the user or client might set the dir's manually
     and then readjust the control points.
   */
  virtual void set_dir(int pre, int idx, int post); // Defined, yet DEPRECATED
  virtual void set_dir(int idx) {
    points[idx].dir = angle_addressable_base_t::atan2(
      points[postidx(idx)].pt.second - points[preidx(idx)].pt.second,
      points[postidx(idx)].pt.first  - points[preidx(idx)].pt.first);
  };
  void set_closed_dirs() {
    for(int i=0; i < points.size(); ++i)
    set_dir(i);
  };
  // Members for setting dirs in an open spline:
  void set_inner_dirs() {
    for(int i=1; i < lastidx(); ++i)
      //set_dir(i-1, i, i+1);
      set_dir(i);
  };
  /* set_open_first() and set_open_last()
   * correct by k according to 2nd and last but 1 segments */
  virtual void set_open_first(F k) {
    points[0].dir = angle_addressable_base_t::atan2(
      points[1].pt.second - points[0].pt.second
 - k*(points[2].pt.second - points[1].pt.second),
      points[1].pt.first  - points[0].pt.first)
 - k*(points[2].pt.first  - points[1].pt.first);
  };
  virtual void set_open_last (F k) {
    points[lastidx()].dir = angle_addressable_base_t::atan2(
      points[lastidx()].pt.second - points[lastidx() - 1].pt.second
 - k*(points[lastidx()-1].pt.second - points[lastidx() - 2].pt.second),
      points[lastidx()  ].pt.first  - points[lastidx() - 1].pt.first)
 - k*(points[lastidx()-1].pt.first  - points[lastidx() - 2].pt.first);
  };
  void set_open_dirs(F k = 0.33) {
    set_inner_dirs();
    set_open_first(k);
    set_open_last (k);
  };
  /* To set the controls on every point in 'points'
   * you can rely on a fixed distance (from on-line point to its controls)
   * or let some member function estimate a distance (for each point)
   */
  void set_controls(F dist) {
    for(point& p : points) {
      p.set_pre( dist);
      p.set_post(dist);
    }
  };
  virtual F  pre_control_dist(int IDX, F k=0.2) const {return 0.5;}; // UNIMPLEMENTED
  virtual F post_control_dist(int IDX, F k=0.2) const {return 0.5;}; // UNIMPLEMENTED
  void set_controls_by_factor(F k=0.2) {
    for(int i = 0; i < points.size(); ++i) {
      points[i].set_pre(  pre_control_dist(i,k));
      points[i].set_post(post_control_dist(i,k));
    }
  };
  // Add curves from points[beg] to points[end] inside svg::path::p attribute:
  void          to_svg_p(  std::ostream& o, int beg, int end)      const {
    o << "M " << points[beg].pt.first << ' ' << points[beg].pt.second;
    for(int i=beg; i < end; ++i) {
      o << "C " << points[i].postpt.first << ' ' << points[i].postpt.second;
      o << ", " << points[i+1].prept.first << ' ' << points[i+1].prept.second;
      o << ", " << points[i+1].pt.first << ' ' << points[i+1].pt.second;
    }
  };
  /* close_svg_p(OSTREAM) adds the closing Bezier curve
     (from last point to first) to the unclosed p attribute in svg::path
     yet it does not close the p attribute as such (no closing quotes added)*/
  void          close_svg_p(std::ostream& o) const {
      o << " C " << points[lastidx()].postpt.first << ' ' << points[lastidx()].postpt.second;
      o << ", "  << points[0].prept.first << ' ' << points[0].prept.second;
      o << ", "  << points[0].pt.first << ' ' << points[0].pt.second;
  };
  void to_svg_p_closed(  std::ostream& o) const {
    to_svg_p(o, 0, lastidx());
    close_svg_p(o);
  };

  void add_control_to_svg_as_circle(std::ostream& o, std::size_t idx, F r=5.0) const {
    o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
    o << "<circle cx=\"" << points[idx].prept.first  <<'\"';
    o <<        " cy=\"" << points[idx].prept.second <<'\"';
    o <<         " r=\"" << r <<"\"/>\n";
    o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
    o << "<circle cx=\"" << points[idx].postpt.first  <<'\"';
    o <<        " cy=\"" << points[idx].postpt.second <<'\"';
    o <<         " r=\"" << r <<"\"/>\n";
  };
  void add_control_to_svg_as_line(std::ostream& o, std::size_t idx) const {
    o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
    o << "<line x1=\"" << points[idx].prept.first  <<'\"';
    o <<      " y1=\"" << points[idx].prept.second <<'\"';
    o <<      " x2=\"" << points[idx].pt.first <<'\"';
    o <<      " y2=\"" << points[idx].pt.second << "\"/>\n";
    o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
    o << "<line x1=\"" << points[idx].postpt.first  <<'\"';
    o <<      " y1=\"" << points[idx].postpt.second <<'\"';
    o <<      " x2=\"" << points[idx].pt.first <<'\"';
    o <<      " y2=\"" << points[idx].pt.second << "\"/>\n";
  };

  // constructors:
  mp_spline() = default;
  mp_spline(std::initializer_list<pair_t> il)               : points(il), has_dirs(false) {};
  mp_spline(std::initializer_list<mp_spline<F>::point>  il) : points(il), has_dirs( true) {};
  template <typename CONTAINER>
  mp_spline(const CONTAINER& c) : points(c.begin(), c.end()), has_dirs(true) {};
}; // class mp_spline<>


template <typename F>
void mp_spline<F>::set_dir(int pre, int idx, int post) { // DEPRECATED
  F preangle = angle_addressable_base_t::atan2(
                 points[idx].pt.second - points[pre].pt.second,
                 points[idx].pt.first  - points[pre].pt.first);
  F postangle = angle_addressable_base_t::atan2(
                 points[post].pt.second  - points[idx].pt.second,
                 points[post].pt.first   - points[idx].pt.first);
  points[idx].dir = (preangle + postangle) / 2;
#ifdef DEBUG
  std::cout << "for idx=" << idx << " preangle=" << 180 * preangle / std::numbers::pi_v<F>;
  std::cout << ", and postangle=" << 180 * postangle / std::numbers::pi_v<F>;
  std::cout << ", resulting in \'dir\'=" << 180 * points[idx].dir / std::numbers::pi_v<F> << std::endl;
#endif
};

#endif
