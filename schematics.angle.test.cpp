#ifndef SCHEMATICS_ANGLE_H
#include "schematics.angle.h"
#endif

#include <iostream>

typedef float float_type;
typedef angle_addressable_base<float_type> geo_t;

using namespace std;

int main() {

  cout << "distance from (100, 100) to (130, 140) = " << geo_t::distance(100,100, 130,140) << std::endl;
  cout << "sqrt(49.0) = " << geo_t::sqrt(49.0) << std::endl;
  cout << "normalized(7rads), where 7 rads is " << geo_t::rad_to_deg(7.0) << "degrees: ";
  cout << geo_t::normalized(7.0) << "rads, or " << geo_t::rad_to_deg(geo_t::normalized(7.0)) << " degrees." << std::endl;

  float_type a7rads(7.0);
  geo_t::normalize(a7rads);
  cout << "Now a7rads is " << a7rads << std::endl;

  return 0;
}
