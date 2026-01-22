#ifndef WHEEL_H
#include "wheel.h"
#endif

#ifndef GEAR_H
#include "gear.h"
#endif

#include <iostream>
#include <fstream>

typedef double float_type;
typedef angle_addressable<float_type> angle_addressable_t;
typedef wheel<float_type> wheel_t;
typedef cogwheel< float_type> cogwheel_t;

int        n0(15),  n1(10), n2(7), n3(7);
float_type r0(100), r1(100*n1/n0), r2(100*n2/n0), r3(100*n3/n0);

float_type          margink = 2.0;
float_type margin01(0.44 * (r0 + r1) / sqrt(n0 + n1));
float_type margin2( 0.44 * (r1 + r2) / sqrt(n1 + n2));
float_type angle_delay1(180/n1);
float_type angle_delay2(180/n2);

cogwheel_t g0(120,           120,           r0, margin01, n0, 0.44);
cogwheel_t g1(120 + r0 + r1, 120,           r1, margin01, n1, 0.44, angle_delay1);
cogwheel_t g2(120 + r0 + r1, 120,           r2, margin2,  n2, 0.44);
cogwheel_t g3(120 + r0 + r1, 120 + r2 + r3, r3, margin2,  n3, 0.44, angle_delay2);

using namespace std;

int main() {

  /*
  cout << "sin(30) = " << angle_addressable_t::sin(30) << '\n';
  cout << "cos(30) = " << angle_addressable_t::cos(30) << '\n';

  cout << "sin(90) = " << angle_addressable_t::sin(90) << '\n';
  cout << "cos(90) = " << angle_addressable_t::cos(90) << '\n';
  cout << "\'w0\' has coordinates (" << w0.get_cx() << ',' << w0.get_cy() << "),";
  cout << " radius: " << w0.get_radius();
  cout << ", num_parts: " << w0.get_num_parts() << " and piecemeal angle: " << w0.get_span_angle() << '\n';

  */

  cout << "Number of points per section in \'g0\': " << g0.points_per_section() << '\n';

  const wheel_t& g0ref(g0);

// open file "test-gear.html" to hold an/some SVG element(s):
  ofstream ofs("test-gear.html");
  ofs << "<!DOCTYPE html>\n";
  ofs << "<html>\n<body>\n";

  ofs << "<p>Test <code>gear</code>/<code>cogwheel</code></p>\n";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.5);

      g0ref.print_svg_circle(ofs, " fill-opacity=\"0.2\"");

      ofs << "<polygon id=\"gear0\" stroke=\"black\" fill=\"gray\" points=\"";
        cout << "g0.r=" << g0.r << " and g0.R=" << g0.R << '\n';
        //g0.print_points_in_section(ofs,0);
        //g0.print_points_in_section(ofs,1);
        g0.print_contour_points(ofs);
        //g0.print_points_in_section(ofs,2);
      ofs << "\">\n";
      ofs << "<animateTransform \
      attributeName=\"transform\"\
      begin=\"0s\"\n";
      ofs << "dur=\"" << n0 << "s\"\n";
      ofs << "type=\"rotate\" \
      from=\"0 120 120\" \
      to=\"360 120 120\" \
      repeatCount=\"indefinite\" />\n\"";
      ofs << "</polygon>\n";

      ofs << "<polygon id=\"gear1\" stroke=\"black\" fill=\"gray\" points=\"";
        //g0.print_points_in_section(ofs,0);
        //g0.print_points_in_section(ofs,1);
        g1.print_contour_points(ofs);
        //g0.print_points_in_section(ofs,2);
      ofs << "\">\n";
      ofs << "<animateTransform \
      attributeName=\"transform\"\
      begin=\"0s\"\n";
      ofs << "dur=\"" << n1 << "s\"\n";
      ofs << "type=\"rotate\" ";
      ofs << "from=\"360 " << 120 + r0 + r1 << " 120\" ";
      ofs << "to  =\"  0 " << 120 + r0 + r1 << " 120\" ";
      ofs << "repeatCount=\"indefinite\" />\n\"";
      ofs << "</polygon>\n";

      ofs << "<polygon id=\"gear2\" stroke=\"black\" fill=\"gray\" points=\"";
        //g0.print_points_in_section(ofs,0);
        //g0.print_points_in_section(ofs,1);
        g2.print_contour_points(ofs);
        //g0.print_points_in_section(ofs,2);
      ofs << "\">\n";
      ofs << "<animateTransform \
      attributeName=\"transform\"\
      begin=\"0s\"\n";
      ofs << "dur=\"" << n1 << "s\"\n";
      ofs << "type=\"rotate\" ";
      ofs << "from=\"360 " << 120 + r0 + r1 << " 120\" ";
      ofs << "to  =\"  0 " << 120 + r0 + r1 << " 120\" ";
      ofs << "repeatCount=\"indefinite\" />\n\"";
      ofs << "</polygon>\n";

      ofs << "<polygon id=\"gear3\" stroke=\"black\" fill=\"gray\" points=\"";
        //g0.print_points_in_section(ofs,0);
        //g0.print_points_in_section(ofs,1);
        g3.print_contour_points(ofs);
        //g0.print_points_in_section(ofs,2);
      ofs << "\">\n";
      ofs << "<animateTransform \
      attributeName=\"transform\"\
      begin=\"0s\"\n";
      ofs << "dur=\"" << n1 << "s\"\n";
      ofs << "type=\"rotate\" ";
      ofs << "from=\"  0 " << 120 + r0 + r1 << ' ' << 120 + r2 + r3 << "\" ";
      ofs << "to  =\"360 " << 120 + r0 + r1 << ' ' << 120 + r2 + r3 << "\" ";
      ofs << "repeatCount=\"indefinite\" />\n\"";
      ofs << "</polygon>\n";

    close_svg(ofs);

  ofs << "</body>\n</html>";
  ofs.close();

  return 0;
}
