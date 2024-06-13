#include "schematics.ic.h"

typedef double float_type;
typedef     ic<float_type>  ic_t;
typedef    vic<float_type> vic_t;
typedef    hic<float_type> hic_t;

#define TEST_IC_PIN_LOCATION
#define TEST_SVG

#ifdef TEST_SVG
#include <fstream>
#endif

#include <iostream>
using namespace std;

int main() {

  ic_t   ic1( 50, 50, 20, 3, 7);
  ic_t   ic2(100,100, 20, 2, 5);
  vic_t vic1( 75, 75, 20,    5);
  vic_t hic1( 75, 75, 20, 7   );

#ifdef TEST_IC_PIN_LOCATION
  cout << "Output pin positions of 2 x 5 IC (all four sides):\n";
  for (int i = 0; i < 14; ++i) {
    cout << "  ic2 pin[" << i << "] is at x=" << ic2.xperim(i) << " and y=" << ic2.yperim(i);
    cout << ", facing: " << ic2.faces(i) << " (0=left, 1=bottom etc.)\n";
  }
  cout << "Output pin positions of 2 x 5 Vertically pinned IC (two sides):\n";
  for (int i = 0; i < 10; ++i) {
    cout << "  vic1 pin[" << i << "] is at x=" << vic1.xperim(i) << " and y=" << vic1.yperim(i);
    cout << ", facing: " << vic1.faces(i) << " (0=left, 1=bottom etc.)\n";
  }
#endif

#ifdef TEST_SVG

  ofstream ofs("test.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.5);
      add_svg(ic1, ofs);
      add_svg(ic2, ofs);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();
#endif

  return 0;

}
