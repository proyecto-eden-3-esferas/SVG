//#include "schematics.rectangle.h"
//#include "svg.h"

#define TEST_IC_PIN_LOCATION


#ifndef SCHEMATICS_LABELED_BLOCK_H
#include "schematics.labeled_block.h"
#endif

typedef        double float_type;
typedef svg_shape<float_type> svg_t;
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

  float_type label_raise{  0.0};
  float_type label_spacing{8.0};
  labeled_block_t lbl1 (100,100,  60,20,
                        4, 3, 5, 2,
                        label_spacing, label_raise); // 14 ports

  string_container_t sc2({"clock", "p1", "p2", "p3", "p4", "p5", "gnd",
                          "p7", "p8", "p9", "p10", "p11", "p12", "Vcc"});
  labeled_block_t lbl2 (100,100,  100,200,
                        7, 0, 7, 0,
                        sc2.begin(), sc2.end(),
                        label_spacing, label_raise); // 14 ports
  labeled_block_t lbl3 (400,100,  100,200,
                        4, 3, 4, 3,
                        sc2.begin(), sc2.end(),
                        label_spacing, label_raise); // 14 ports
  cout << "Now \'lbl2\' stores " << lbl2.strings.size() << " string(s)\n";
  cout << "Now \'lbl3\' stores " << lbl3.strings.size() << " string(s)\n";

  cout << "\nNow test port positions through xperim(IDX) and yperim(IDX), with " << lbl1.size() << " port(s)\n";
  for(int i=0; i < lbl1.size(); ++i)
    cout << "position: " << lbl1.xperim(i) << ", " << lbl1.yperim(i) << '\n';

  cout << "Now write <code>labeled_block</code> objects as SVG through references into file \"test-labeled_block.html\"\n";
  const svg_t* p1 = & lbl1;
  const svg_t* p2 = & lbl2;
  const svg_t* p3 = & lbl3;

  // open file "test-labeled_block.html" to hold an SVG element:
  ofstream ofs("test-labeled_block.html");
  ofs << "<!DOCTYPE html>\n<html>\n<body>\n";
  ofs << "<p>Testing objects of class <code>labeled_block</code> through a reference.</p>\n"; //<svg stroke=\"black\">\n  ";
    open_svg(ofs, 500.0, 500.0, "black", "yellow", 0.25);
      p2->add_svg(ofs, " fill=\"black\" fill-opacity=\"1.0\"");
      p3->add_svg(ofs, " fill=\"black\" fill-opacity=\"1.0\"");
      //p3->add_svg(ofs);
    close_svg(ofs);
  ofs << "</body>\n</html>";
  ofs.close();


  return 0;
}
