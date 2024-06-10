#include "schematics.twoport.h"

#ifndef SVG_H
#include "svg.h"
#endif

#include <iostream>
#include <fstream>


typedef twoport<double> twoport_t;

#define PI 3.14159265

using namespace std;

int main()
{

  twoport_t tp1({100.0, 100.0}, {200.0, 100.0}, "resistor H", 0.1);
  twoport_t tp2({250.0, 150.0}, {250.0,  25.0}, "resistor 2", 0.1);
  twoport_t tp3({ 25.0,  25.0}, {125.0, 125.0}, "resistor 3", 0.1);
  tp1.set_width(44.0);
  tp2.set_width(44.0);
  tp3.set_width(44.0);
  cout << "tp3 has angle to the X axis: " << tp3.get_angle() * 180 / PI << '\n';

  // open file "test.html" to hold an SVG element:
  ofstream ofs("test.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "gray", 0.2);
      add_svg(tp1, ofs);
      add_svg(tp2, ofs);
      add_svg(tp3, ofs);
      //add_svg(l80, ofs);

  // Keep adding components to the SVG file (handle='ofs')
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
