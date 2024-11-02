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
 [ ] Add a CONTAINER template parameter to mp_spline<>
 [ ] Members set_dir_second() and set_dir_last_but_1()
     should take points[0].dir and points[lastidx()].dir into account
 [ ] As SVG "inverts" the Y coordinate, given height h,
     a points Y coordinate (y) should be transformed to h - y:
     y = h - y
     That change should be effected when writing to an SVG out-file.
     In file "svg.h", or in "pair-as-2D-point.h" ...
 [ ] A generalized
     <typename FUNCTION_OBJ>
     mp_spline<>::point::transform(FUNCTION_OBJ fo)
     and then
     <typename FUNCTION_OBJ>
     mp_spline<>::transform(FUNCTION_OBJ fo) {
       for (point& p : points)
         fo(p);
     }
     Such function objects should keep control points and on-line points aligned.
 */

#ifndef GEOMETRY_2D
#include "geometry_2D.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

#ifndef PAIR_AS_POINT_2D_H
#include "pair-as-2D-point.h" // transform(pair<F,F>, a, b, c, d, s, t)
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

#ifndef MP_POINT_H
#include "mp_point.h"
#endif
template <typename F = double, typename POINT = mp_point<F>, typename CONTAINER=std::vector<POINT> >
class mp_spline {
public:
  //typedef std::pair<F,F> pair_t;
  typedef POINT point_t;
  typedef CONTAINER points_t;
  typedef geometry_2D<F> geom_t;
  typedef std::size_t size_t;
  points_t points;
  points_t::iterator begin() {return points.begin();};
  points_t::iterator   end() {return points.  end();};
  // change y-coordinate in all points in 'points': y = depth - y:
  void y_invert(F depth);
protected:
  /* Some members taking and returning an index.
   * lastidx(IDX) returns the last valid index into points, while
   * closed_preidx(IDX) and closed_postidx(IDX) return previous and next index
     for a closed path, i.e. as if 'points' were a circular sequential container.
   *  */
  size_t lastidx()    const {return points.size() - 1;}
  size_t closed_preidx(size_t i) const {if(i > 0) return i-1;
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
     and correct them by k according to 2nd and last-but-1 segments.
   * The alternative would be to set the dir of 1st and last like this:
       points[0].dir         = dir_1st;
       points[lastidx()].dir = dir_last;
   */
  virtual void set_dir_open_first(F k);
  virtual void set_dir_open_last (F k);
  /* set_dir3(IDX) assumes a non-terminal
     (neither 1st nor last on an open path) point.
     and sets points[IDX].dir = angle_to_X(points[IDX - 1], points[IDX + 1])
   * set_dir5(IDX,K) works on all on-line points on a closed path
     and on points not next to a terminal on-line point.
   * Postfixes "3" and "5" refer to how many points are taken into account.
   */
  virtual void set_dir3(size_t idx);
  virtual void set_dir5(size_t idx, F k=0.22);
  //
  virtual void set_dir_second    () {set_dir3(1);};             // TO BE REFINED
  virtual void set_dir_last_but_1() {set_dir3(lastidx() - 1);}; // TO BE REFINED
public:
  void set_closed_dirs();
  // Members for setting dirs in an open spline:
  void set_inner_dirs(F k=0.22); // only on open paths
  void set_open_dirs_by_k(F k = 0.25, F kends = 0.25);
  void set_open_dirs_by_angle(F dir_1st, F dir_last);
  /* To set the controls on every point in 'points'
     you can rely on a fixed distance (from on-line point to its controls)
   */
  void set_controls_distance(F dist);
  /* Admitedly, 'set_controls_distance(F dist)' is crude,
     and the alternative is to let some member choose
     a suitable distance (for each point).
   * First, we need two functions returning the distance to adjacent points:*/
  F      dist_to_prev(size_t IDX) const;
  F      dist_to_next(size_t IDX) const;
  /* Distance from on-line point to its control defaults to:
       k * distance(pt, {next|prev}-point)
     but users are invited to overload it in derived classes
     with code that might take into account angles between segments etc.
   * Furthermore, by tweaking the k factor for an individual point
     a client may change the shape of the curve through the said point.
     (The larger k is, the larger the radius of curvature at a point.)
   */
  virtual void set_pre_by_adjacent_distance( size_t idx, F k=0.4);
  virtual void set_post_by_adjacent_distance(size_t idx, F k=0.4);
  void set_by_adjacent_distance(             size_t idx, F k=0.4);
  void set_by_adjacent_distance(                         F k=0.4);
  /* Members for printing to an SVG out-stream */
protected:
  void to_svg_p(std::ostream& o, size_t idx)          const;
  // Add curves from points[beg] to points[end] inside svg::path::p attribute:
  void to_svg_p(std::ostream& o, size_t beg, size_t end) const;
public:
  void to_svg_p_open(    std::ostream& o) const {to_svg_p(o,0, lastidx());};
  /* close_svg_p(OSTREAM) adds the closing Bezier curve
     (from last point to first) to the unclosed p attribute in svg::path
     yet it does not close the p attribute as such (no closing quotes added)*/
  void close_svg_p(std::ostream& o) const;
  void to_svg_p_closed(  std::ostream& o) const;
  /* Show both control points for a given on-line point
   * as svg::circle's at the end of control svg::line's
   * Argument 'decs' sets the number of decimal digits
   */
  void add_controls_to_svg_as_circles(std::ostream& o, std::size_t idx, F r=5.0,
                                      const std::string& attr = "class=\"bezier-control\"") const;
  void add_controls_to_svg_as_circles(std::ostream& o,                  F r=5.0,
                                      const std::string& attr = "class=\"bezier-control\"") const;
  //
  void add_controls_to_svg_as_lines(std::ostream& o,   std::size_t idx,
                                    const std::string& attr = "class=\"bezier-control\"") const;
  void add_controls_to_svg_as_lines(std::ostream& o,
                                    const std::string& attr = "class=\"bezier-control\"") const;
  //
  void add_online_to_svg_as_circle(std::ostream& o,    std::size_t idx, F r=10.0,
                                   const std::string& attr = "s=\"\" class=\"on-line-point\" fill=\"black\"") const;
  void add_online_to_svg_as_circle(std::ostream& o,                     F r=10.0,
                                   const std::string& attr = "s=\"\" class=\"on-line-point\" fill=\"black\"") const;
  // constructors:
  mp_spline() {};
  /* Unaccountably, this fails to separate compile:
      mp_spline(std::initializer_list<pair_t> il) : points(il) {};
     even though mp_spline::point has a constructor that takes a std::pair<F,F>
  */
  mp_spline(std::initializer_list<point_t>  il) : points(il) {};
  template <typename CONT>
  mp_spline(const CONT& c) : points(c.begin(), c.end()) {};
}; // class mp_spline<>

#endif
