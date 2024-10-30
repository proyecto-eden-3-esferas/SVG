#ifndef PAIR_AS_POINT_2D_H
#define PAIR_AS_POINT_2D_H

/* This header-only file defines some global operators and functions
   to handle pairs of numbers (std::pair<FLOAT,FLOAT>) as 2D points.
 *
 */

#include <utility>

template <typename F = double, typename FF=F>
std::pair<F,F>& operator*=(std::pair<F,F>& pt, FF k);
template <typename F = double, typename FF = F>
std::pair<F,F>& operator+=(std::pair<F,F>& pt, F k);

template <typename F, typename FF>
std::pair<F,F>& operator*=(std::pair<F,F>& pt, FF k) {
  pt.first *= k;
  pt.second *= k;
  return pt;
}
template <typename F, typename FF>
std::pair<F,F>& operator+=(std::pair<F,F>& pt, const std::pair<FF,FF>& const_pt) {
  pt.first  += const_pt.first;
  pt.second += const_pt.second;
  return pt;
}

/* Global functions for transforming std::pair<F,F> as 2D-points.
 *
*/
template <typename F, typename D>
F get_y_invert(const std::pair<F,F>& pt, D depth=0)  {return depth - pt.second;};
template <typename F, typename D>
void y_invert(std::pair<F,F>& pt, D depth=0) {pt.second = depth - pt.second;};
template <typename F, typename D, typename CONT>
void y_invert_in(CONT& cont, D depth) {
  for(auto & pt : cont)
    pt.second = depth - pt.second;
};

#endif
