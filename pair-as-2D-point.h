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

#endif
