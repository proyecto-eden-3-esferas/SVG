#ifndef MP_SPLINE_H
#define MP_SPLINE_H


/* The MetaPost model of curves makes it easier to draw natural objects
   such as rocks, plants, animals, anatomy, landscapes...
 * In this model, a curve is fitted through a set of points.
   Additionally, some restrictions may be set as to
   - the direction ('dir' or angle to the X-axis) of the curve at a given point
   - how taught or straightened out ("tension" in MetaPost parlance) the curve is at a given point
     (in my model I call it distance from a point to its two control points)
 * Thus I have defined a curve class called mp_spline<>
 * The way to use a mp_spline object--or its "lifecycle"-- is
   (1) load points
   (2) set dirs
   (3) set tension (distance from on-line points to its one/two control points)
   (4) output into SVG, PostScript, etc.
 * The prefix "mp_" does stand for MetaPost,
   but I am not implementing the full Hobby’s Algorithm here.
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
   (3) For a smooth curve, a point on a line has a specific direction ('dir'),
       that is, the curve passes through the point at an angle to the X-axis
   (4) A composite curve or spline is a list of on-line points,
       each supplemented with two control points
   (5) The fact that each on-line point is coupled to one or two control points
       enables translating chains of such points into cubir Bezier curves.
 * A MetaPost primer is to be found at: https://proyecto-eden-3-esferas.github.io/metapost.html
   For MetaPost curves go to: https://proyecto-eden-3-esferas.github.io/metapost.curves.html

 */

/* TODO
 [x] template argument CONTAINER should be checked by a concept
     to be index addressable (concept IndexAddressable)
 [x] open paths should set attribute 'fill' to "none"
 [ ] Members set_dir_open_second() and set_dir_open_last_but_1()
     should take points[0].dir and points[lastidx()].dir into account
 [x] As SVG "inverts" the Y coordinate, given height h,
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

#include <exception>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>


#ifdef SEPARATE_COMPILATION
#include "mp_point.h"
#else
#include "mp_point.cpp"
#endif

#include <concepts>
template <typename CONT>
concept IndexAddressable = requires(CONT cont, const CONT ccont, std::size_t i)
{
  { cont[i]}     -> std::convertible_to<typename CONT::      reference>;
  {ccont[i]}     -> std::convertible_to<typename CONT::const_reference>;
  //{cont.size()} -> std::convertible_to<          std::size_t>;
};

template <typename F = double,
          typename POINT = mp_point<F>,
          IndexAddressable CONTAINER=std::vector<POINT> >
class mp_spline {
public:
  typedef POINT point_t;
  typedef CONTAINER points_t;
  typedef geometry_2D<F> geom_t;
  typedef std::size_t size_t;
  typedef mp_spline<F,POINT,CONTAINER> mp_spline_t;
  points_t points;
  // The state interface: bools, exceptions and check_state() const:
  bool    is_closed{false};
  bool     dirs_set{false};
  bool controls_set{false};
  class dirs_not_set     : public std::exception {};
  class controls_not_set : public std::exception {};
  virtual void check_state() const;
  // Iterators: non-const begin() resets bools 'dirs_set' and 'controls_set'
  points_t::iterator begin();
  points_t::iterator   end();
  points_t::const_iterator cbegin() const;
  points_t::const_iterator   cend() const;
  // Other accessors for the container of points:
        point_t& operator[] (size_t idx)      ;
  const point_t& operator[] (size_t idx) const;
  void  clear();
  mp_spline_t& operator=(const mp_spline_t& lft);
  size_t size() const {return points.size() ;};
  bool  empty() const {return points.empty();};
  // change y-coordinate in all points in 'points': y = depth - y:
  void y_invert(F depth); // turn upside down: y = depth - y
protected:
  /* Some members taking and returning an index.
   * lastidx(IDX) returns the last valid index into points, while
   * closed_preidx(IDX) and closed_postidx(IDX) return previous and next index
     for a closed path, i.e. as if 'points' were a circular sequential container.
   *  */
  size_t lastidx()                    const {return points.size() - 1;}
  size_t closed_preidx(size_t i)      const {if(i > 0) return i-1;
                                             else return lastidx();};
  size_t closed_prepreidx(size_t i)   const {return closed_preidx(closed_preidx(i));};
  size_t closed_postidx(size_t i)     const {if(i < lastidx()) return i+1;
                                             else return 0;};
  size_t closed_postpostidx(size_t i) const {return closed_postidx(closed_postidx(i));};
  /* Members dealing with setting the 'dir' on each point in 'points'
   * This is by far hardest task.
   * If not satisfied, the user or client is encouraged to
     set the dir's manually and then readjust the control points.
   */
protected:
  /* set_dir_open_first_by_k() and set_dir_open_last_by_k()
     set the first and last points in an open path,
     and correct them by k according to 2nd and last-but-1 segments.
   */
  virtual void set_dir_open_first_by_k(F k);
  virtual void set_dir_open_last_by_k (F k);
  virtual void set_dir_open_second    () {set_dir3(1);};             // TO BE REFINED
  virtual void set_dir_open_last_but_1() {set_dir3(lastidx() - 1);}; // TO BE REFINED
  /* set_dir3(IDX) assumes a non-terminal
     (neither 1st nor last on an open path) point.
     and sets points[IDX].dir = angle_to_X(points[IDX - 1], points[IDX + 1])
   * set_dir5(IDX,K) works on all on-line points on a closed path
     and on points not next to a terminal on-line point (all but four).
   * Postfixes "3" and "5" refer to how many points are taken into account.
   */
  virtual void set_dir3(size_t idx);
  virtual void set_dir5(size_t idx, F k=0.3);
  //
public:
  void set_closed_dirs(F k=0.3);
  // Members for setting dirs in an open spline:
  void set_inner_dirs(F k=0.3); // only on open paths
  /* You may set dir's in an open path by factor k and kends,
     where k is forwarded to set_inner_dirs(), and
     kends is forwarded into set_dir_open_{first|last}(),
   * or you may set the fist and last angle */
  void set_open_dirs_by_k_kends(                        F k = 0.25, F kends = 0.25);
  void set_open_dirs_by_angles_k(F dir_1st, F dir_last, F k = 0.25);
  /* To set the controls on every point in 'points'
     you can rely on a fixed distance (from on-line point to its controls). */
  void set_controls_by_distance_open(  F dist); // Too coarse, hence DEPRECATED
  void set_controls_by_distance_closed(F dist); // Too coarse, hence DEPRECATED
  /* The alternative to 'set_controls_by_distance_{open|closed}(DIST)'
     is to let some member choose a suitable distance (for each point).
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
  virtual void set_pre_control_by_adjacent_distance( size_t idx, F k=0.4);
  virtual void set_post_control_by_adjacent_distance(size_t idx, F k=0.4);
  void set_control_by_adjacent_distance(             size_t idx, F k=0.4);
  void set_controls_by_adjacent_distance_closed(                 F k=0.4);
  void set_controls_by_adjacent_distance_open(                   F k=0.4);
  /* Members for printing to an SVG out-stream */
protected:
  void to_svg_p(std::ostream& o, size_t idx)             const;
  // Add curves from points[beg] to points[end] inside svg::path::p attribute:
  void to_svg_p(std::ostream& o, size_t beg, size_t end) const;
  void close_svg_p(std::ostream& o) const; // adds Bézier from last to first;
                                           // use only on closed paths
public:
  void to_svg_p_open(    std::ostream& o) const {to_svg_p(o,0, lastidx());};
  /* close_svg_p(OSTREAM) adds the closing Bezier curve
     (from last point to first) to the unclosed p attribute in svg::path
     yet it does not close the p attribute as such (no closing quotes added)*/
  void to_svg_p_closed(  std::ostream& o) const;
  void to_svg_p(std::ostream& o)          const;
  /*
   * Show control points for a given on-line point
   * as svg::circle's at the end of control svg::line's
   */
protected:
  void add_pre_control_to_svg_as_circle(std::ostream& o, std::size_t idx, F r=5.0,
                                      const std::string& attr = "class=\"bezier-control\"") const;
  void add_post_control_to_svg_as_circle(std::ostream& o, std::size_t idx, F r=5.0,
                                      const std::string& attr = "class=\"bezier-control\"") const;
public:
  void add_control_to_svg_as_circle(  std::ostream& o, std::size_t idx, F r=5.0,
                                      const std::string& attr = "class=\"bezier-control\"") const;
  void add_controls_to_svg_as_circles(std::ostream& o,                  F r=5.0,
                                      const std::string& attr = "class=\"bezier-control\"") const;
  //
protected:
  void add_pre_control_to_svg_as_line(std::ostream& o,   std::size_t idx,
                                    const std::string& attr = "class=\"bezier-control\"") const;
  void add_post_control_to_svg_as_line(std::ostream& o,   std::size_t idx,
                                    const std::string& attr = "class=\"bezier-control\"") const;
public:
  void add_control_to_svg_as_line(  std::ostream& o,   std::size_t idx,
                                    const std::string& attr = "class=\"bezier-control\"") const;
  void add_controls_to_svg_as_lines(std::ostream& o,
                                    const std::string& attr = "class=\"bezier-control\"") const;
  //
  void add_online_to_svg_as_circle(std::ostream& o,    std::size_t idx, F r=10.0,
                                   const std::string& attr = "s=\"\" class=\"on-line-point\" fill=\"black\"") const;
  void add_online_to_svg_as_circle(std::ostream& o,                     F r=10.0,
                                   const std::string& attr = "s=\"\" class=\"on-line-point\" fill=\"black\"") const;
  /* Make a spline_loaded with points either open or closed
   * by setting its dir's, then its controls */
  void make_open(F dir1st, F dirLast, F kdir, F kctrls);
  void make_open(F kends,             F kdir, F kctrls);
  void make_closed(                   F kdir, F kctrls);
  /*
   * Constructors
   */
  // constructors that may only cause the points to be loaded:
  mp_spline() {};
  mp_spline(std::initializer_list<point_t>  il) : points(il) {};
  /*
  template <typename CONT>
  mp_spline(const CONT& c) : points(c.cbegin(), c.cend()) {};
  */
  /* Some constructors are provided which besides loading the points,
   * also set the spline as open or clsoed, set dir's and set controls
   * A contructor taking 4/3 float parameters constructs an open  line, whereas
   * a contructor taking 2/1 float parameters constructs a closed line
   */
  mp_spline(std::initializer_list<point_t>  il, F dir1st, F dirLast, F kdir, F kctrls);
  mp_spline(std::initializer_list<point_t>  il, F kends,             F kdir, F kctrls);
  mp_spline(std::initializer_list<point_t>  il,                      F kdir, F kctrls);
  // The same three as above, only points get loaded from a container of type CONT
  template <typename CONT>
  mp_spline(const CONT& c, F dir1st, F dirLast, F kdir, F kctrls)
  : points(c.begin(), c.end()), is_closed(false), dirs_set(true), controls_set(true) {
    set_open_dirs_by_angles_k(             dir1st, dirLast, kdir);
    set_controls_by_adjacent_distance_open(kctrls);
  };
  template <typename CONT>
  mp_spline(const CONT& c, F kends,              F kdir, F kctrls)
  : points(c.begin(), c.end()), is_closed(false), dirs_set(true), controls_set(true) {
    set_open_dirs_by_k_kends(              kdir, kends);
    set_controls_by_adjacent_distance_open(kctrls);
  };
  template <typename CONT>
  mp_spline(const CONT& c,                       F kdir, F kctrls)
  : points(c.begin(), c.end()), is_closed(true), dirs_set(true), controls_set(true) {
    set_closed_dirs(                         kdir  );
    set_controls_by_adjacent_distance_closed(kctrls);
  };

  template <typename CONT>
  mp_spline(const CONT& c)
  : points(c.begin(), c.end()) {
  };

  // constructors which load the points, set dir's and set controls (closed):
  // NOTE: their {bodies}; are the same
  /*
  mp_spline(std::initializer_list<point_t>  il) : points(il) {};
  template <typename CONT>
  mp_spline(const CONT& c) : points(c.begin(), c.end()) {};
  */
}; // class mp_spline<>

#endif
