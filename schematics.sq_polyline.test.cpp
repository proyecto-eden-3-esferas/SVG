#include "schematics.sq_polyline.h"

typedef h_polyline<double> h_polyline_t;
typedef v_polyline<double> v_polyline_t;

typedef hv_polyline<double> hv_polyline_t;
typedef vh_polyline<double> vh_polyline_t;

typedef hvh_polyline<double> hvh_polyline_t;
typedef vhv_polyline<double> vhv_polyline_t;

#include "schematics.vec_polyline.h"
typedef vec_polyline<double, std::vector<double> > vec_polyline_t;

using namespace std;

int main() {

  h_polyline_t    hpl1(10,10,  80, 80);
  v_polyline_t    vpl1(15,15, 115,115);

  hv_polyline_t     hvpl1(40,40,  100,100,  100);
  vh_polyline_t     vhpl1(30,30,   90, 90,   35);

  hvh_polyline_t     hvhpl1(40,40,  100,100,  100,100);
  vhv_polyline_t     vhvpl1(30,30,   90, 90,   35,100);



  vec_polyline_t sqpl1(20, 20, 80, 80, {60.0, -30.0});

  cout << "adding \'hpl1\': p attribute bit is: ";
  hpl1.add_to_svg_path(cout);
  cout << "\nadding \'vpl1\': p attribute bit is: ";
  vpl1.add_to_svg_path(cout);

  cout << "\n\nadding \'hvpl1\': p attribute bit is: ";
  hvpl1.add_to_svg_path(cout);

  cout << "\nadding \'vhpl1\': p attribute bit is: ";
  vhpl1.add_to_svg_path(cout);

  cout << "\n\nadding \'sqpl1\': p attribute bit is: ";
  sqpl1.add_to_svg_path(cout);
  cout << '\n';

  return 0;
}
