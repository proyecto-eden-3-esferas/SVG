#include <fstream>
#include <iostream>


#include "schematics.sq_polyline.h"
#ifndef SCHEMATICS_BLOCK_H
#include "schematics.block.h"
#endif

typedef  double float_type;
typedef   block<float_type> block_t;

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

  block_t bl1(100,200,  60,100,  4, 0, 4, 0);
  block_t bl2(300,200,  60,100,  4, 0, 4, 0);
  std::vector<vec_polyline_t> v;
  for(int i=0; i < 4; ++i) {
    v.emplace_back(vec_polyline_t(bl1.xperim(i), bl1.yperim(i),
                                  bl2.xperim(i), bl2.yperim(i),
                                  { -(i+1)*10, -50 -(i+1)*10, 200}));
  }

  h_polyline_t    hpl1(100, 100,  180, 22);
  v_polyline_t    vpl1(100, 100,  180, 18);

  hv_polyline_t     hvpl1(40,40,  100,100,  100);
  vh_polyline_t     vhpl1(30,30,   90, 90,   35);

  hvh_polyline_t     hvhpl1(40,40,  100,100,  100,100);
  vhv_polyline_t     vhvpl1(30,30,   90, 90,   35,100);


  const double halfsep = 100 / 8;
  vec_polyline_t sqpl1(20, 20, 80, 80, {60.0, -30.0});
  vec_polyline_t sqpl2(160,100+halfsep, 360,100+halfsep, {20.0, -30.0, 200});

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



  // open file "test.html" to hold an SVG element:
  ofstream ofs("test.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "yellow", 0.25);
  // Keep adding components to the SVG file (handle='ofs')
      add_svg(bl1,  ofs);
      add_svg(bl2,  ofs);

      open_svg_path_p(ofs);
        //hpl1.add_to_svg_path(ofs);
        //vpl1.add_to_svg_path(ofs);
        //hvpl1.add_to_svg_path(ofs);
        //vhpl1.add_to_svg_path(ofs);
        for(const auto p : v) {
          p.add_to_svg_path(ofs);
        }
        hvhpl1.add_to_svg_path(ofs);
        vhvpl1.add_to_svg_path(ofs);
        //sqpl1.add_to_svg_path(ofs);
        sqpl2.add_to_svg_path(ofs);
        ofs << " fill=\"none\"";
      close_svg_path(ofs);

    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
