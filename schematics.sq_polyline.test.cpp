#include "schematics.sq_polyline.h"

typedef sq_polyline<double, std::vector<double> > hv_polyline_t;

int main() {

  hv_polyline_t hvpl1(20, 20, 80, 80, {60.0, -30.0});


  return 0;
}
