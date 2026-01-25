#ifndef GEOMETRY_2D_H
#include "geometry_2d.h"
#endif

#include <iostream>

// Instantiate an instance of each 'geometry_2d' specialization:
geometry_2d<float> gf;
geometry_2d<double> gd;
geometry_2d<long double> gl;


typedef float float_type;
typedef geometry_2d<float_type> geometry_2d_t;

geometry_2d_t g2d0;

using namespace std;

int main() {

  return 0;
}
