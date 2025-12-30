#include "schematics.round.h"
#include "schematics.line.h"
#include "schematics.arrow.h"


#include <fstream>
#include <vector>
using namespace std;

typedef            double float_type;
typedef         svg_shape<float_type> svg_t;
typedef angle_addressable<float_type> cir_t;
typedef          circular<float_type>    circular_component_t;
typedef slim_arrowhead<float_type> slim_arrowhead_component_t;
typedef solid_arrowhead<float_type> solid_arrowhead_component_t;
typedef       rectangular<float_type> rectangular_component_t;
typedef        elliptical<float_type>  elliptical_component_t;
typedef           twoline<float_type>                  line_t;

int main()
{

  cout << "Testing cir_t::normalize(ANGLE)...\n";
  float_type aaa1 = - 3*60;
  cir_t::normalize(aaa1);
  cout << "angle -180 becomes " << aaa1 << '\n';
  aaa1 = 1000;
  cir_t::normalize(aaa1);
  cout << "angle 1000 rads becomes " << aaa1 << '\n' << '\n';


  cout << "Test angle_addressable::get_{x|y}_rotated(x,y):\n";
  circular_component_t cc0(100,1000,1000);
  float_type x(1100), y(1000);
  cout << "cc0.get_x_rotated(1100,1000, 45)= " << cc0.get_x_rotated(1100,1000, 45) << '\n';
  cout << "cc0.get_y_rotated(1100,1000, 45)= " << cc0.get_y_rotated(1100,1000, 45) << '\n';
  cc0.rotate(x,y,45);
  cout << "cc0.rotate(x,y,45) makes x=" << x << ", and y=" << y << "\n\n";


  cout << "Test circular<>:\n";
  circular_component_t cc1(25,50,50);
  cout << "circular<> cc1 of radius 100 has x and y at angle 45: ";
  cout << cc1.xperim(45) << ',' <<  cc1.yperim(45) << '\n';
  line_t cl10(cc1.xperim(10), cc1.yperim(10), cc1.xperim(10) + 25, cc1.yperim(10));
  line_t cl30(cc1.xperim(30), cc1.yperim(30), cc1.xperim(30) + 25, cc1.yperim(30));
  line_t cl45(cc1.xperim(45), cc1.yperim(45), cc1.xperim(45) + 25, cc1.yperim(45));
  line_t cl60(cc1.xperim(60), cc1.yperim(60), cc1.xperim(60) + 25, cc1.yperim(60));
  line_t cl80(cc1.xperim(80), cc1.yperim(80), cc1.xperim(80) + 25, cc1.yperim(80));


  cout << "Test rectangular_components rc*\n";
  //rectangular_component_t rc1(30,20, 40,50), rc2(30,20, 42,52), rc3(30,20, 38,48);
  rectangular_component_t rc1(30,20, 40,50), rc2(30,20, 42,52), rc3(30,20, 38,48);
  cout << "rc1.get_trans_angle(): " << rc1.get_trans_angle() << '\n';
  cout << "rc2.get_trans_angle(): " << rc2.get_trans_angle() << '\n';
  cout << "rc3.get_trans_angle(): " << rc3.get_trans_angle() << '\n';
  cout << "Now test rectangular rc2(100,100) ::xperim(rads) and ::yperim(rads) for several rads (angles):\n";
  cout << "a = 10: " << rc2.xperim(10) << ',' <<  rc2.yperim(10) << '\n';
  cout << "a = 30: " << rc2.xperim(30) << ',' <<  rc2.yperim(30) << '\n';
  cout << "a = 45: " << rc2.xperim(45) << ',' <<  rc2.yperim(45) << '\n';
  cout << "a = 60: " << rc2.xperim(60) << ',' <<  rc2.yperim(60) << '\n';
  cout << "a = 80: " << rc2.xperim(80) << ',' <<  rc2.yperim(80) << '\n';
  line_t rl10(rc2.xperim(10), rc2.yperim(10), rc2.xperim(10) + 25, rc2.yperim(10));
  line_t rl30(rc2.xperim(30), rc2.yperim(30), rc2.xperim(30) + 25, rc2.yperim(30));
  //line_t rl45(rc2.xperim(45), rc2.yperim(45), rc2.xperim(45) + 25, rc2.yperim(45));
  line_t rl60(rc2.xperim(60), rc2.yperim(60), rc2.xperim(60)     , rc2.yperim(60) + 25);
  line_t rl80(rc2.xperim(80), rc2.yperim(80), rc2.xperim(80)     , rc2.yperim(80) + 25);


  elliptical_component_t ec2(40,25, 42,52);
  line_t el10(ec2.xperim(10), ec2.yperim(10), ec2.xperim(10) + 25, ec2.yperim(10));
  line_t el30(ec2.xperim(30), ec2.yperim(30), ec2.xperim(30) + 25, ec2.yperim(30));
  //line_t el45(ec2.xperim(45), ec2.yperim(45), ec2.xperim(45) + 25, ec2.yperim(45));
  line_t el60(ec2.xperim(60), ec2.yperim(60), ec2.xperim(60)     , ec2.yperim(60) + 25);
  line_t el80(ec2.xperim(80), ec2.yperim(80), ec2.xperim(80)     , ec2.yperim(80) + 25);


  slim_arrowhead_component_t  ah1(40, 100, 100,  45, 22);
  solid_arrowhead_component_t ah2(40, 120, 120, -45, 15);
  cout << "solid_arrowhead ah2 base is at: " << ah2.get_base_x() << ", " << ah2.get_base_y() << '\n';


//  ic<float_type> ic1(50,50,5, 3,7);

// open file "test-circular.html" to hold an SVG circular element and more:
  ofstream ofc("test-circular.html");
  ofc << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics circular svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofc, 500.0, 500.0, "black", "gray", 0.5);
      add_svg(cc1, ofc);
      add_svg(cl10, ofc);
      add_svg(cl30, ofc);
      add_svg(cl60, ofc);
      add_svg(cl80, ofc);
    close_svg(ofc);
  ofc << "</body>\n</html>";
  ofc.close();

// open file "test-elliptical.html" to hold an SVG elliptical element and more:
  ofstream ofe("test-elliptical.html");
  ofe << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics elliptical svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofe, 500.0, 500.0, "black", "gray", 0.5);
      add_svg(ec2, ofe);
      add_svg(el10, ofe);
      add_svg(el30, ofe);
      add_svg(el60, ofe);
      add_svg(el80, ofe);
    close_svg(ofe);
  ofe << "</body>\n</html>";
  ofe.close();

// open file "test-rectangular.html" to hold an SVG rectangular element and more:
  ofstream ofr("test-rectangular.html");
  ofr << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics rectangular svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofr, 500.0, 500.0, "black", "gray", 0.5);
      add_svg(rc1,  ofr);
      add_svg(rc3,  ofr);
      add_svg(rc2,  ofr);
      add_svg(rl10, ofr);
      add_svg(rl30, ofr);
      add_svg(rl60, ofr);
      add_svg(rl80, ofr);
    close_svg(ofr);
  ofr << "</body>\n</html>";
  ofr.close();


  std::vector<const svg_t*> vector_of_refs(0);
  vector_of_refs.emplace_back(&cc1);
  vector_of_refs.emplace_back(&ec2);
  vector_of_refs.emplace_back(&rc1);
  vector_of_refs.emplace_back(&rc2);
  vector_of_refs.emplace_back(&rc3);
  vector_of_refs.emplace_back(&ah1);
  vector_of_refs.emplace_back(&ah2);
  // open file "test-round-and-arrow.html" to print an assortment angle_addressable<> elements:
  ofstream ofall("test-round-and-arrow.html");
  ofall << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics arrowhead svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofall, 500.0, 500.0, "black", "gray", 0.5);
      for(const svg_t * ptr : vector_of_refs)
        ptr->add_svg(ofall);
    close_svg(ofall);
  ofall << "</body>\n</html>";
  ofall.close();


  // open file "test-arrowhead.html" to hold an SVG arrowhead element and more:
  ofstream ofah("test-arrowhead.html");
  ofah << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics arrowhead svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofah, 500.0, 500.0, "black", "gray", 0.5);
      add_svg(ah1, ofah);

      ah1.cx += 50; ah1.cy+=33;
      ah1.rotate_by(22);
      add_svg(ah1, ofah);

      ah1.cx += 50; ah1.cy+=33;
      ah1.rotate_by(22);
      add_svg(ah1, ofah);

      add_svg(ah2, ofah);
      //add_svg(l80, ofah);

    close_svg(ofah);
  ofah << "</body>\n</html>";
  ofah.close();


  return 0;
}
