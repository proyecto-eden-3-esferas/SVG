#include "schematics.h"
#include "schematics.svg.h"

//#define DRAW_CIRCULAR_COMPONENT_PERIM
#ifndef DRAW_CIRCULAR_COMPONENT_PERIM
#define DRAW_RECTANGULAR_COMPONENT_PERIM
#endif

#undef DRAW_RECTANGULAR_COMPONENT_PERIM

#ifndef DRAW_CIRCULAR_COMPONENT_PERIM
#ifndef DRAW_RECTANGULAR_COMPONENT_PERIM
#define DRAW_ELLIPTICAL_COMPONENT_PERIM
#endif
#endif

#define TEST_POLYLINE_POINT_LOCATIONS

#define TEST_IC_PIN_LOCATION

#include <fstream>
using namespace std;

typedef                       double float_type;
typedef          angle_addressable<   float_type> cir_t; // instead of former longish name 'component_t'
typedef circular<   float_type>    circular_component_t;
typedef rectangular<float_type> rectangular_component_t;
typedef rectangle<            float_type> rectangle_t;
typedef polyline<             float_type>  polyline_t;
typedef polygone<             float_type>  polygone_t;
typedef  elliptical<float_type>  elliptical_component_t;
typedef               twoline<float_type>                  line_t;
typedef                    ic<float_type>                    ic_t;
// std::ostream& operator<<(std::ostream& o, Cmp& cmp) {

int main()
{

  float_type a10(cir_t::deg_to_rads(10));
  float_type a30(cir_t::deg_to_rads(30));
  float_type a45(cir_t::deg_to_rads(45));
  float_type a60(cir_t::deg_to_rads(60));
  float_type a80(cir_t::deg_to_rads(80));

  cout << "Test circular<>:\n";
  circular_component_t cc1(25,50,50);
  cout << "circular<> cc1 of radius 100 has x and y at angle 45: ";
  cout << cc1.xperim(a45) << ',' <<  cc1.yperim(a45) << '\n';
#ifdef DRAW_CIRCULAR_COMPONENT_PERIM
  line_t l10(cc1.xperim(a10), cc1.yperim(a10), cc1.xperim(a10) + 25, cc1.yperim(a10));
  line_t l30(cc1.xperim(a30), cc1.yperim(a30), cc1.xperim(a30) + 25, cc1.yperim(a30));
  line_t l45(cc1.xperim(a45), cc1.yperim(a45), cc1.xperim(a45) + 25, cc1.yperim(a45));
  line_t l60(cc1.xperim(a60), cc1.yperim(a60), cc1.xperim(a60) + 25, cc1.yperim(a60));
  line_t l80(cc1.xperim(a80), cc1.yperim(a80), cc1.xperim(a80) + 25, cc1.yperim(a80));
#endif

  cout << "Test rectangular_components rc*\n";
  //rectangular_component_t rc1(30,20, 40,50), rc2(30,20, 42,52), rc3(30,20, 38,48);
  rectangular_component_t rc1(30,20, 40,50), rc2(30,20, 42,52), rc3(30,20, 38,48);
  cout << "rc1.trans_angle: " << cir_t::rads_to_deg(rc1.trans_angle) << '\n';
  cout << "rc2.trans_angle: " << cir_t::rads_to_deg(rc2.trans_angle) << '\n';
  cout << "rc3.trans_angle: " << cir_t::rads_to_deg(rc3.trans_angle) << '\n';
  cout << "Now test rectangular rc2(100,100) ::xperim(rads) and ::yperim(rads) for several rads (angles):\n";
  cout << "a = 10: " << rc2.xperim(cir_t::deg_to_rads(10)) << ',' <<  rc2.yperim(cir_t::deg_to_rads(10)) << '\n';
  cout << "a = 30: " << rc2.xperim(cir_t::deg_to_rads(30)) << ',' <<  rc2.yperim(cir_t::deg_to_rads(30)) << '\n';
  cout << "a = 45: " << rc2.xperim(a45) << ',' <<  rc2.yperim(a45) << '\n';
  cout << "a = 60: " << rc2.xperim(cir_t::deg_to_rads(60)) << ',' <<  rc2.yperim(cir_t::deg_to_rads(60)) << '\n';
  cout << "a = 80: " << rc2.xperim(cir_t::deg_to_rads(80)) << ',' <<  rc2.yperim(cir_t::deg_to_rads(80)) << '\n';
#ifdef DRAW_RECTANGULAR_COMPONENT_PERIM
  line_t l10(rc2.xperim(a10), rc2.yperim(a10), rc2.xperim(a10) + 25, rc2.yperim(a10));
  line_t l30(rc2.xperim(a30), rc2.yperim(a30), rc2.xperim(a30) + 25, rc2.yperim(a30));
  //line_t l45(rc2.xperim(a45), rc2.yperim(a45), rc2.xperim(a45) + 25, rc2.yperim(a45));
  line_t l60(rc2.xperim(a60), rc2.yperim(a60), rc2.xperim(a60)     , rc2.yperim(a60) - 25);
  line_t l80(rc2.xperim(a80), rc2.yperim(a80), rc2.xperim(a80)     , rc2.yperim(a80) - 25);
#endif

  elliptical_component_t ec2(40,25, 42,52);
#ifdef DRAW_ELLIPTICAL_COMPONENT_PERIM
  line_t l10(ec2.xperim(a10), ec2.yperim(a10), ec2.xperim(a10) + 25, ec2.yperim(a10));
  line_t l30(ec2.xperim(a30), ec2.yperim(a30), ec2.xperim(a30) + 25, ec2.yperim(a30));
  //line_t l45(ec2.xperim(a45), ec2.yperim(a45), ec2.xperim(a45) + 25, ec2.yperim(a45));
  line_t l60(ec2.xperim(a60), ec2.yperim(a60), ec2.xperim(a60)     , ec2.yperim(a60) - 25);
  line_t l80(ec2.xperim(a80), ec2.yperim(a80), ec2.xperim(a80)     , ec2.yperim(a80) - 25);
#endif

  rectangle_t rect1(60,30, ec2.xperim(-a10), ec2.yperim(-a10));

  ic<float_type> ic1(50,50,5, 3,7);

// open file "test.html" to hold an SVG element:
  ofstream ofs("test.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.5);
      add_svg(cc1, ofs);
      add_svg(ec2, ofs);
      add_svg(rect1, ofs);
      add_svg(l10, ofs);
      add_svg(l30, ofs);
      add_svg(l60, ofs);
      //add_svg(l80, ofs);

  cout << "Test twoline<>:\n";
  line_t l1(-100,25,100,25);
  cout << "Interpolate components of l1(-100,25,100,25) for several \'k\':\n";
  cout << "For \'k\' = 0.25, components are: " << l1.get_x(0.25) << ", " << l1.get_y(0.25) << '\n';
  cout << "For \'k\' = 0.66, components are: " << l1.get_x(0.66) << ", " << l1.get_y(0.66) << '\n';
  line_t l2(-100,25, 100,0);
  cout << "Interpolate components of l2(-100,25, 100,0) for several \'k\':\n";
  cout << "For \'k\' = 0.25, components are: " << l2.get_x(0.25) << ", " << l2.get_y(0.25) << '\n';
  cout << "For \'k\' = 0.66, components are: " << l2.get_x(0.66) << ", " << l2.get_y(0.66) << '\n';

  ic_t             ic3(1000,1000, 5, 2, 5);
  vic<float_type> vic3(1000,1000, 5, 2, 5);

  // polyline_t pll1;
  polygone_t pll1;
  pll1.push_back( 100,  100);
  pll1.push_back(130, 110);
  pll1.push_back(130, 90);
  pll1.push_back( 100, 100);
#ifdef TEST_POLYLINE_POINT_LOCATIONS
  cout << "Output polyline_t \'pll1\' point locations:\n";
  for(auto pt : pll1.points)
    cout << "x=" << pt.first << ", y=" << pt.second << '\n';
#endif

  // Keep adding components to the SVG file (handle='ofs')
      add_svg(l2,ofs);
      add_svg(rc2,ofs);
      add_svg(pll1, ofs);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();

#ifdef TEST_IC_PIN_LOCATION
  cout << "Output pin positions of 2 x 5 IC (all four sides):\n";
  for (int i = 0; i < 14; ++i) {
    cout << "  ic3 pin[" << i << "] is at x=" << ic3.xperim(i) << " and y=" << ic3.yperim(i);
    cout << ", facing: " << ic3.faces(i) << " (0=left, 1=bottom etc.)\n";
  }
  cout << "Output pin positions of 2 x 5 Vertically pinned IC (two sides):\n";
  for (int i = 0; i < 10; ++i) {
    cout << "  vic3 pin[" << i << "] is at x=" << vic3.xperim(i) << " and y=" << vic3.yperim(i);
    cout << ", facing: " << vic3.faces(i) << " (0=left, 1=bottom etc.)\n";
  }
#endif

  return 0;
}
