#ifndef MP_SPLINE_H
#define MP_SPLINE_H

/* The MetaPost model of curves makes it easier to draw natural objects
   such as rocks, plants, animals, anatomy, landscapes...
 * In this model, a curve is fitted through a set of points.
   Additionally, some restrictions may be set as to
   - the direction (angle to the X-axis) of the curve at a given point
   - how taught or straightened out ("tension" in MetaPost parlance) the curve is at a given point
     (in my model I call it "distance" from a point to its two control points)
 * Thus I have defined a curve class called mp_spline<>
 * The way to use a mp_spline object--or its "lifecycle"-- is
   (1) load points
   (2) set dirs
   (3) set tension (distance from on-line points to its one/two control points)
   (4) output into SVG, PostScript, etc.
 * The prefix "mp_" does stand for MetaPost, but I may not implement Hobby’s Algorithm here.
 * All angles in radians. For conversions use:
   geometry_2D<F>::deg_to_rad(ANGLE), and
   geometry_2D<F>::rad_to_def(ANGLE)
 *
 * Key characteristics
   (1) A curve is defined through on-line points (points on the line).
       Another kind of points (found in Bezier curves)
       is control points, which direct the drawing of the line.
   (2) On-line points are either terminal (begin and end) or middle points.
       All points in a closed path are middle points.
       One might also consider "next-points", that is second and last-but-one points in open paths.
   (3) For a smooth curve, a point on a line has a specific direction,
       that is, the curve passes through the point at an angle to the X-axis
   (4) A composite curve or spline is a list of on-line points,
       supplemented with control points
   (5) The fact that each on-line point is couple to one or two control points
       enables translating chains of such points into cubir Bezier curves.

 * MetaPost uses Hobby’s Algorithm, whose aim is to fit a curve to a set of points smoothly and in a controlled manner.
 * A MetaPost primer is to be found at: https://proyecto-eden-3-esferas.github.io/metapost.html
   For MetaPost curves go to: https://proyecto-eden-3-esferas.github.io/metapost.curves.html

 */

/* TODO
 * Line and circle elements should bear class or id attributes for easy styling
 * Maybe also path elements should bear class or id attributes for easy styling
 * Members set_dir_second() and set_dir_last_but_1()
   should take points[0].dir and points[lastidx()].dir into account
 * distance of a control point to its on-line point should be proportional
   to distance to adjacent (next or previous) point
 * virtual F  pre_control_dist(int IDX, F k=0.2) const
   should return k*geom_t*distance(points[IDX], points[IDX - 1])
 * virtual F  post_control_dist(int IDX, F k=0.2) const
   should return k*geom_t*distance(points[IDX], points[IDX + 1])
 */
#ifndef SCHEMATICS_ANGLE_H
#include "schematics.angle.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>


/* A spline from points à la MetaPost
 * The way to preceed, once the on-line points are loaded, is
   first to set the dir[ection] (angle to the X-axis) on all its points
   then to define both control points (or just one in the case of terminal points)
   at each spline point.
 * Main parts:
   (1) an inner mp_spline<>::point class and a container of points
   (2) members for setting dir's (angles to the X-axis at each point)
   (3) members for setting control points based on desired distance
       from an on-line point to its control points
   (4) members for printing control points as Bezier curves
 *
 */
template <typename F = double>
class mp_spline {
public:
  /* Inner class 'point'.
   * Each point holds an on-line point (pt), a dir[ection] or angle (dir), and its two control points (prept and postpt) */
  class point {
  public:
    typedef geometry_2D<F> geom_t;
    typedef std::pair<F,F> pair_t;
    typedef             F   dir_t;
    pair_t pt, prept, postpt; // on-line point plus its 2 control points
    dir_t  dir;
  protected:
    void set_control(F dr, F dist, pair_t& ctrl) const {
      geom_t::set_angle_dist_from_of( dr, dist, pt, ctrl);};
    void set_control(      F dist, pair_t& ctrl) const {set_control(dir,dist,ctrl);};
    void set_pre( F dr, F dist) {set_control(dr  + std::numbers::pi_v<F>,dist,prept);};
    void set_post(F dr, F dist) {set_control(dr                         ,dist,postpt);};
  public:
    void set_pre(       F dist) {set_pre(dir,dist);};
    void set_post(      F dist) {set_post(dir,dist);};
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
  typedef std::size_t size_t;
  points_t points;
  points_t::iterator begin() {return points.begin();};
  points_t::iterator   end() {return points.  end();};
protected:
  /* Some members taking and returning an index.
   * lastidx(IDX) returns the last valid index into points, while
   * closed_preidx(IDX) and closed_postidx(IDX) return previous and next index
     for a closed path, i.e. as if 'points' were a circular sequential container.
   *  */
  size_t lastidx()    const {return points.size() - 1;}
  size_t closed_preidx( size_t i) const {if(i > 0) return i-1;
                               else return lastidx();};
  size_t closed_prepreidx(size_t i)   const {return closed_preidx(closed_preidx(i));};
  size_t closed_postidx(size_t i) const {if(i < lastidx()) return i+1;
                               else return 0;};
  size_t closed_postpostidx(size_t i) const {return closed_postidx(closed_postidx(i));};
  /* Members dealing with setting the 'dir' on each point in 'points'
   * The hardest task.
   * The all-important virtual member function set_dir(IDX).
   * It could be virtual-ly specialized by taking more points (before and after)
     into account. In that case, open paths should
     have their start and end points' directions defined
   * If not satisfied, the user or client might set the dir's manually
     and then readjust the control points.
   */
protected:
  /* set_dir_open_first() and set_dir_open_last()
     set the first and last points in an open path,
     and correct by k according to 2nd and last but 1 segments.
   * The alternative would be to set the dir of 1st and last like this:
       points[0].dir         = dir_1st;
       points[lastidx()].dir = dir_last;
   */
  virtual void set_dir_open_first(F k);
  virtual void set_dir_open_last (F k);
  /* set_dir3(IDX) assumes a non-terminal
     (neither 1st nor last on an open path) point.
   * set_dir5(IDX,K) works on all on-line points on a closed path
     and on points not next to a terminal on-line point.
   * Postfixes "3" and "5" refer to how many points are taken into account.
   */
  virtual void set_dir3(int idx);
  virtual void set_dir5(int idx, F k=0.22);
  //
  virtual void set_dir_second    () {set_dir3(1);};             // TO BE REFINED
  virtual void set_dir_last_but_1() {set_dir3(lastidx() - 1);}; // TO BE REFINED
public:
  void set_closed_dirs();
  // Members for setting dirs in an open spline:
  void set_inner_dirs(); // only on open paths
  void set_open_dirs(F k = 0.25);
  void set_open_dirs(F dir_1st, F dir_last);
  /* To set the controls on every point in 'points'
   * you can rely on a fixed distance (from on-line point to its controls)
   * or let some member function estimate a distance (for each point)
   */
  void set_controls_distance(F dist);
  /* Distance from on-line point to its control is k * distance(pt, next-point)
   * Functions: set_[pre_|post_]by_adjacent_distance([IDX, ] K)
   * rely on {pre|post}_control_dist(int IDX, F k=0.2)
   */
  virtual F  pre_control_dist(int IDX, F k=1.0) const;
  virtual F post_control_dist(int IDX, F k=1.0) const;
  void set_pre_by_adjacent_distance( int idx, F k=0.4);
  void set_post_by_adjacent_distance(int idx, F k=0.4);
  void set_by_adjacent_distance(     int idx, F k=0.4);
  void set_by_adjacent_distance(              F k=0.4);
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
  void add_control_to_svg_as_circle(std::ostream& o,
                                    F r=5.0,
                                    const std::string& attr = "class=\"bezier-control\"") const;
  //
  void add_control_to_svg_as_line(std::ostream& o,
                                  std::size_t idx,
                                  const std::string& attr = "class=\"bezier-control\"") const;
  void add_control_to_svg_as_line(std::ostream& o,
                                  const std::string& attr = "class=\"bezier-control\"") const;
  //
  void add_online_to_svg_as_circle(std::ostream& o,
                                   std::size_t idx,
                                   F r=10.0,
                                   const std::string& attr = "s=\"\" class=\"on-line-point\" fill=\"black\"") const;
  void add_online_to_svg_as_circle(std::ostream& o,
                                   F r=10.0,
                                   const std::string& attr = "s=\"\" class=\"on-line-point\" fill=\"black\"") const;
  // constructors:
  mp_spline() {};
  /* Unaccountably, this fails to separate compile:
      mp_spline(std::initializer_list<pair_t> il) : points(il) {};
     even though mp_spline::point has a constructor that takes a std::pair<F,F>
  */
  mp_spline(std::initializer_list<mp_spline<F>::point>  il) : points(il) {};
  template <typename CONTAINER>
  mp_spline(const CONTAINER& c) : points(c.begin(), c.end()) {};
}; // class mp_spline<>

#endif
