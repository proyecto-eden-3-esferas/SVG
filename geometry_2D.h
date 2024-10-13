#ifndef GEOMETRY_2D
#define GEOMETRY_2D

#ifndef SCHEMATICS_ANGLE_H
#include "schematics.angle.h"
#endif

// Remember that angle_addressable_base<> handles angles in radians!

template <typename F>
using geometry_2D = angle_addressable_base<F>;

#endif
