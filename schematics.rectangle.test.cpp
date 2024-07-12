#include "schematics.rectangle.h"

#include <fstream>
using namespace std;

typedef                       double float_type;
typedef rectangle<            float_type> rectangle_t;

// std::ostream& operator<<(std::ostream& o, Cmp& cmp) {

int main()
{


  rectangle_t rect1(60,30, 25, 25);

// open file "test-rectangle.html" to hold an SVG element:
  ofstream ofs("test-rectangle.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.5);
      add_svg(rect1, ofs);

  // Keep adding components to the SVG file (handle='ofs')

    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
