#include "schematics.twoport.h"
#include "schematics.capacitor.h"

#ifndef SVG_H
#include "svg.h"
#endif

#include <iostream>
#include <fstream>


typedef twoport<double> twoport_t;
typedef capacitor<double> capacitor_t;
typedef polarized_capacitor<double> polarized_capacitor_t;

#define PI 3.14159265

using namespace std;

int main()
{

  twoport_t   tp1( 100.0, 100.0, 200.0, 100.0, "resistor H",  44.0);
  twoport_t   tpc1(100.0,  50.0, 200.0,  50.0, "resistor HC", 44.0);
  twoport_t   tp2(250.0, 150.0, 250.0,  25.0, "resistor 2", 44.0);
  twoport_t   tp3( 25.0,  25.0, 125.0, 125.0, "resistor 3", 44.0);
  capacitor_t            cp1(100.0, 150.0, 200.0, 150.0,         "C1", 44.0, 6.0);
  polarized_capacitor_t pcp1(120.0, 170.0, 220.0, 170.0,          "p", 44.0, 5.0, 44.0);

  //tp1.set_width(44.0);
  //tp2.set_width(44.0);
  //tp3.set_width(44.0);
  cout << "tp3 has angle to the X axis: " << tp3.get_angle() * 180 / PI << '\n';

  // open file "test.html" to hold an SVG element:
  ofstream ofs("test.twoport.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.2);
      add_svg(tp1, ofs);
      add_svg(tpc1, ofs);
      //tpc1.add_circle_to_svg(ofs, 22.0, 150.0, 50.0);
      //tpc1.add_circle_to_svg(ofs, 22.0);
      add_svg(tp2, ofs);
      add_svg(tp3, ofs);
      add_svg(cp1, ofs);
      add_svg(pcp1, ofs);
      //add_svg(l80, ofs);

  // Keep adding components to the SVG file (handle='ofs')
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
