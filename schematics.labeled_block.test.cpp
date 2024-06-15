//#include "schematics.rectangle.h"
//#include "svg.h"

#define TEST_IC_PIN_LOCATION


#ifndef SCHEMATICS_LABELED_BLOCK_H
#include "schematics.labeled_block.h"
#endif

typedef        double float_type;
typedef labeled_block<float_type> labeled_block_t;
typedef std::vector<std::string> string_container_t;

#ifdef DRAW_LINES
#include "schematics.line.h"
typedef twoline<float_type> line_t;
#endif

#include <fstream>
using namespace std;

int main()
{

  labeled_block_t lbl1 (100,100,  60,20,  4, 3, 5, 2); // 14 ports

  string_container_t sc2({"clock", "p1", "p2", "p3", "p4", "p5", "gnd",
                          "p7", "p8", "p9", "p10", "p11", "p12", "Vcc"});
  labeled_block_t lbl2 (100,100,  100,200,  7, 0, 7, 0, sc2.begin(), sc2.end()); // 14 ports
  labeled_block_t lbl3 (400,100,  100,200,  4, 3, 4, 3, sc2.begin(), sc2.end()); // 14 ports
  cout << "Now \'lbl2\' stores " << lbl2.strings.size() << " string(s)\n";
  cout << "Now \'lbl3\' stores " << lbl3.strings.size() << " string(s)\n";

  cout << "\nNow test port positions through xperim(IDX) and yperim(IDX), with " << lbl1.size() << " port(s)\n";
  for(int i=0; i < lbl1.size(); ++i)
    cout << "position: " << lbl1.xperim(i) << ", " << lbl1.yperim(i) << '\n';

  // open file "test.labeled_block.html" to hold an SVG element:
  ofstream ofs("test.labeled_block.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics svg...</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "yellow", 0.25);
  // Keep adding components to the SVG file (handle='ofs')
      add_svg(lbl2,  ofs);
      add_svg(lbl3,  ofs);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
