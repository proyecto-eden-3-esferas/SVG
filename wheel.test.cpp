#ifndef WHEEL_H
#include "wheel.h"
#endif


#include <iostream>
#include <fstream>

typedef double float_type;
typedef angle_addressable<float_type> angle_addressable_t;
typedef wheel<float_type> wheel_t;

wheel_t    w0(200, 200, 100,     8);

using namespace std;

int main() {

  cout << "sin(30) = " << angle_addressable_t::sin(30) << '\n';
  cout << "cos(30) = " << angle_addressable_t::cos(30) << '\n';

  cout << "sin(90) = " << angle_addressable_t::sin(90) << '\n';
  cout << "cos(90) = " << angle_addressable_t::cos(90) << '\n';

  cout << "\'w0\' has coordinates (" << w0.get_cx() << ',' << w0.get_cy() << "),";
  cout << " radius: " << w0.get_radius();
  cout << ", num_parts: " << w0.get_num_parts() << " and piecemeal angle: " << w0.get_span_angle() << '\n';

  const wheel_t& w0ref(w0);

  w0ref.add_svg(         cout);
  w0ref.print_svg_part(  cout, 0);
  w0ref.print_svg_circle(cout);

  cout << "\nOutput to std::cout an element for animated rotation, clockwise:\n";
  w0ref.animate_rotate(cout, wheel_t::clockwise);
  cout << "\nNext, output to std::cout an element for animated rotation, anticlockwise:\n";
  w0ref.animate_rotate(cout, wheel_t::anticlockwise);


// open file "test-wheel.html" to hold an/some SVG element(s):
  ofstream ofs("test-wheel.html");
  ofs << "<!DOCTYPE html>\n";
  ofs << "<html>\n<body>\n";

  ofs << "<p>Test wheel::print_svg_part(0..2) and wheel::print_svg_circle()</p>\n";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.5);
      w0ref.print_svg_part(  ofs, 0);
      w0ref.print_svg_part(  ofs, 1);
      w0ref.print_svg_part(  ofs, 2);
      //w0ref.print_svg_part(  ofs, 3);
      w0ref.print_svg_circle(ofs);
    close_svg(ofs);

  ofs << "<p>Test wheel::add_svg() and wheel::print_svg_circle()</p>\n";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.5);
      w0ref.add_svg(         ofs);
      w0ref.print_svg_circle(ofs);
      // translate, rotate, and increment variable 'num_parts', then call w0ref.add_svg() again:
      w0.translate(20,20);
      w0.rotate(10);
      w0.set_num_parts(w0.get_num_parts() + 1);
      w0ref.add_svg(         ofs);
    close_svg(ofs);


  ofs << "</body>\n</html>";
  ofs.close();

  return 0;
}
