#ifndef PRINT_PAIR_H
#define PRINT_PAIR_H

/* Define global functions for printing:
   (1) a plain std::pair, and
   (2) a mp_spline::point
*  It applies two defines:
   (1) SETPRECISION: number of digits after decimal point
   (2) NO_SPACE_AFTER_COMMA: if it is left undefined (default),
                             a space is added after printed commas
                             (when they are meant as separators)
*/

#ifndef MP_SPLINE_H
#include "mp_spline.h"
#endif

/* Set the number of decimal digits printed; here default is set to 1
 * Set differently adding a switch like:
     -DSETPRECISION=2
   for 2 digits, and so on.
 */
#ifndef SETPRECISION
#define SETPRECISION 1
#endif

#include <iomanip>
#include <iostream>
#include <utility>

template <typename F, typename S>
std::ostream& operator<<(std::ostream& o, const typename std::pair<F,S>& p) {
  o << std::fixed << std::setprecision(SETPRECISION);
  o << '(' << p.first << ',';
#ifndef NO_SPACE_AFTER_COMMA
  o << ' ';
#endif
  o << p.second << ')';
  return o;
};
template <typename F = double>
std::ostream& operator<<(std::ostream& o, const typename mp_spline<F>::point& p) {
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
