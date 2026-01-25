#ifndef NUMERICAL_H
#define NUMERICAL_H

/* Class numerical<> for non-trigonometric numerics
 * Its (only) child, 'geometry_2d' has no template specializations
   and adds member functions:
   - normalize
   - normalized
   - distance
   - angle
   - deg_to_rad
   - rad_to_deg
   whereas its grandchild uses degrees.
 * None of these classes has member variables.
   Thus, all member functions are declared static.
 */

/* Named types are deemed unnecessary for members of class 'numerical''
#ifndef NAMED_TYPE_H
#include "NamedType.h"
#endif
*/

#include <cmath>
#include <numbers>
//#include <utility>

template <typename FLOAT = double>
class numerical {
public:
  typedef FLOAT float_t;
  static float_t   abs(float_t dbl) {return ::fabs(dbl);};
  static float_t  sqrt(float_t dbl) {return ::sqrt(dbl);};
};

template <>
class numerical<float> {
public:
  static float   abs(float f) {return ::fabsf(f);};
  static float  sqrt(float f) {return ::sqrtf(f);};
};

template <>
class numerical<long double> {
public:
  static long double   abs(long double ld) {return ::fabsl(ld);};
  static long double  sqrt(long double ld) {return ::sqrt(ld);};
};

#endif
