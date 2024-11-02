#ifndef PRINT_MP_POINT_H
#define PRINT_MP_POINT_H

#ifndef SETPRECISION
#define SETPRECISION 1
#endif

#ifndef PRINT_PAIR_H
/* Include global functions for printing:
   a plain std::pair, and
*/
#include "print-pair.h"
#endif

template <typename F = double>
std::ostream& operator<<(std::ostream& o, const mp_point<F>& p) {
  o << std::fixed << std::setprecision(SETPRECISION);
  o <<'(' <<  p.pt.first << ',';
#ifndef NO_SPACE_AFTER_COMMA
  o << ' ';
#endif
  o << p.pt.second << ',';
#ifndef NO_SPACE_AFTER_COMMA
  o << ' ';
#endif
  o << (p.dir  / std::numbers::pi_v<float_t>) * 180  << ')'
    << " with controls: " << p.prept << " and " << p.postpt;
  return o;
};
#endif
