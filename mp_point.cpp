#ifndef MP_POINT_CPP
#define MP_POINT_CPP

#ifndef MP_POINT_H
#include "mp_point.h"
#endif

#ifndef PAIR_AS_POINT_2D_H
#include "pair-as-2D-point.h"
#endif

template <typename F>
void mp_point<F>::set_control(F dr, F dist, pair_t& ctrl) const {
    geom_t::set_angle_dist_from_of( dr, dist, pt, ctrl);};
template <typename F>
void mp_point<F>::set_pre(    F dr, F dist) {set_control(dr  + std::numbers::pi_v<F>,dist,prept);};
template <typename F>
void mp_point<F>::set_post(   F dr, F dist) {set_control(dr                         ,dist,postpt);};

template <typename F>
void mp_point<F>::set_pre(       F dist) {set_pre(dir,dist);};
template <typename F>
void mp_point<F>::set_post(      F dist) {set_post(dir,dist);};
  /* Transformations
   * Linear transformations are based on the PostScript 6-parameter model
     (Only the parameters are rearranged:
      first scale params, then skew params, and last displacement.)
   * member transform(PARAMS) relies on global function ::transform(POINT, PARAMS),
     defined in "pair-as-2D-point.h"
   * Non linear transformations might be achieved through function objects.
   */
template <typename F>
void mp_point<F>::transform(F scl_x, F scl_y, F sk_x, F sk_y, F dx, F dy) {
    ::transform(pt,     scl_x, scl_y, sk_x, sk_y, dx, dy);
    ::transform(prept,  scl_x, scl_y, sk_x, sk_y, dx, dy);
    ::transform(postpt, scl_x, scl_y, sk_x, sk_y, dx, dy);
  };
template <typename F>
void mp_point<F>::scale(F k)        {transform(k, k,  0,0, 0,0);};
template <typename F>
void mp_point<F>::scale(F kx, F ky) {transform(kx,ky, 0,0, 0,0);};
template <typename F>
void mp_point<F>::y_invert(F depth) {transform(1,-1, 0,0, 0,depth);};
/*
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
*/
#endif
