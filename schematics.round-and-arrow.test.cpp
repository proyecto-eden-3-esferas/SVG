#include "schematics.round.h"
#include "schematics.line.h"
#include "schematics.arrow.h"

/* Class transistor,
 * The pins are:
 * (0) emitter
 * (1) base
 * (2) collector
 * (3) emitter-side start of cord
 * (4) collector-side start of cord
 * (5) from 0
 * (6) from 1
 * (7) from 2
 */
/*
template <typename FLOAT = double>
class transistor : public circular<FLOAT> {
public:
  typedef          circular<FLOAT> circular_t;
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  typedef std::size_t size_t;
  F apow, abase;
  F x_of_pin(size_t idx) const;
  F y_of_pin(size_t idx) const {return 0.0;};
  transistor(float_t ra, float_t x=0, float_t y=0,
             float_t ap = cir_t(deg_to_rads(120)),
             float_t ab = cir_t(deg_to_rads(60))) :
    circular_t(ra,x,y), apow(ap), abase(ab) {};
};
template <typename FLOAT>
FLOAT transistor<FLOAT>::x_of_pin(size_t idx) const {
  switch (idx) {
    case 0: return circular_t::x + circular_t::r * cir_t::cos(apow);
    case 1: return circular_t::x + circular_t::r * cir_t::cos(abase);
    case 2: return circular_t::x - circular_t::r
    case 3: return circular_t::x + circular_t::r * cir_t::cos(abase);
    case 4: return circular_t::x + circular_t::r * cir_t::cos(apow);
    // Inside the transistor circle, along the base, top to bottom:
    case 5: return circular_t::x + circular_t::r * cir_t::cos(abase);
    case 6: return circular_t::x + circular_t::r * cir_t::cos(abase);
    case 7: return circular_t::x + circular_t::r * cir_t::cos(abase);
  }
};
*/

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


#include <fstream>
using namespace std;

typedef            double float_type;
typedef angle_addressable<float_type> cir_t; // instead of former longish name 'component_t'
typedef          circular<float_type>    circular_component_t;
typedef slim_arrowhead<float_type> slim_arrowhead_component_t;
typedef solid_arrowhead<float_type> solid_arrowhead_component_t;
typedef       rectangular<float_type> rectangular_component_t;
typedef        elliptical<float_type>  elliptical_component_t;
typedef           twoline<float_type>                  line_t;

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

  slim_arrowhead_component_t ah1(40, 100, 100, a10);

  solid_arrowhead_component_t ah2(40, 120, 120, a10);
  cout << "solid_arrowhead ah2 base is at: " << ah2.get_base_x() << ", " << ah2.get_base_y() << '\n';


//  ic<float_type> ic1(50,50,5, 3,7);

// open file "test.html" to hold an SVG element:
  ofstream ofs("test.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.5);
      add_svg(cc1, ofs);
      add_svg(ec2, ofs);
      add_svg(l10, ofs);
      add_svg(l30, ofs);
      add_svg(l60, ofs);
      add_svg(ah1, ofs);

      ah1.cx += 50; ah1.cy+=33;
      ah1.rotate_by(a10);
      add_svg(ah1, ofs);

      ah1.cx += 50; ah1.cy+=33;
      ah1.rotate_by(a10);
      add_svg(ah1, ofs);

      add_svg(ah2, ofs);
      //add_svg(l80, ofs);

  // Keep adding components to the SVG file (handle='ofs')
      add_svg(rc2,ofs);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
