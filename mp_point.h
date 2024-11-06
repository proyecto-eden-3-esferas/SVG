#ifndef MP_POINT_H
#define MP_POINT_H

#ifndef GEOMETRY_2D
#include "geometry_2D.h"
#endif

/* A complex point comprising:
   (1) an on-line point (a point on a curve) as a pair
   (2) two control points as pairs
   (3) the intended angle of the fitting curve to the X-axix
       (at the on-line point)
 * TODO:
   [ ] rotations that keep all three points aligned
 */

template <typename F=double>
class mp_point {
  public:
  typedef geometry_2D<F> geom_t;
  typedef std::pair<F,F> pair_t;
  typedef             F   dir_t;
  pair_t pt, prept, postpt; // on-line point plus its 2 control points
  dir_t  dir; // angle of resulting Bezier curve at on-line point 'pt'
protected:
  void set_control(F dr, F dist, pair_t& ctrl) const;
  //void set_control(      F dist, pair_t& ctrl) const {set_control(dir,dist,ctrl);};
  void set_pre(    F dr, F dist);
  void set_post(   F dr, F dist);
public:
  void set_pre(       F dist);
  void set_post(      F dist);
  /* Transformations
   * Linear transformations are based on the PostScript 6-parameter model
     (Only the parameters are rearranged:
      first scale params, then skew params, and last displacement.)
   * member transform(PARAMS) relies on global function ::transform(POINT, PARAMS),
     defined in "pair-as-2D-point.h"
   * Non linear transformations might be achieved through function objects.
   */
  void change_dir(F angle);   // change 'dir' to angle       and adjust control points
  void rotate(F delta_angle); // rotate 'dir' by delta angle and adjust control points
  void transform(F scl_x, F scl_y, F sk_x, F sk_y, F dx, F dy);
  void scale(F k);
  void scale(F kx, F ky);
  void y_invert(F depth);
  // Constructor(s):
  mp_point(const mp_point& p) = default;
  mp_point(const pair_t& p, dir_t d=0.0) : pt(p),     dir(d) {};
  mp_point(F x, F y,        dir_t d=0.0) : pt({x,y}), dir(d) {};
  mp_point(const pair_t& p, const pair_t& pr, const pair_t& po, dir_t d=0.0)
  : pt(p),     prept(pr), postpt(po), dir(d)
  {};
  mp_point(F x, F y,        const pair_t& pr, const pair_t& po, dir_t d=0.0)
  : pt({x,y}), prept(pr), postpt(po), dir(d)
  {};
}; // class mp_point<FLOAT>
#endif
