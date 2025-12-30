/*
 *
 * TODO
 [ ] move global ::angle() up into "schematics.angle.h"
 [ ] move functions into file "schematics.angle.diagram.h"
 [ ] parameterize the definition of arrow markers (color, size, opacity...)
 [ ] implement some curved line/arrow
 */

#ifndef SCHEMATICS_ROUND_H
#include "schematics.round.h"
#endif

#include "schematics.arrow.h"

#include "schematics.angle.diagram.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

typedef            double float_type;
typedef std::pair<float_type, float_type>     point_t;
typedef          circular<float_type>      circular_t;
typedef       rectangular<float_type>   rectangular_t;
typedef        elliptical<float_type>    elliptical_t;

typedef slim_arrowhead<float_type>   slim_arrowhead_t;
typedef solid_arrowhead<float_type> solid_arrowhead_t;


const float_type r{9.0};           // radius of circles ~ vertices
const float_type w{20*r}, h{20*r}; // width and height of viewport

// define a vector of vertices as circles:
std::vector<circular_t> circles {
  {r, 0.1*w, 0.1*h},
  {r, 0.5*w, 0.3*h},
  {r, 0.9*w, 0.1*h},

  {r, 0.1*w, 0.9*h},
//{r, 0.5*w, 0.7*h},
  {r, 0.9*w, 0.9*h}
};

using namespace std;

int main()
{

  cout << "angle between 1st and 2nd circles is: " << angle(circles[0], circles[1]) << '\n';

// open file "test-round-graph.html" to hold an SVG circular element and more:
  ofstream ofc("test-round-graph.html");
  ofc << "<!DOCTYPE html>\n<html>\n<body>\n<p>Here goes some schematics circular svg...</p>\n"; //<svg stroke=\"black\">\n  ";

    ofc << "<p>This is an undirected graph:</p>\n";
    open_svg(ofc, w, h, "black", "lightgray", 0.5);
      for(auto & c : circles)
        add_svg(c, ofc);
      //add_svg_line(circles[0], circles[1], angle(circles[0], circles[1]), ofc);
      for(int i=0; i < circles.size(); ++i)
        for(int j=i+1; j < circles.size(); ++j)
          add_svg_line(circles[i], circles[j], ofc);
    close_svg(ofc);


    ofc << "<p>Testing a solid and then a stick arrow head as <code>&lt;marker&gt;</code>:</p>\n";
    open_svg(ofc, w, h, "black", "lightgray", 0.5);
      ofc << "<defs>\n";
      ofc <<  solid_arrowhead_marker << '\n';
      ofc << hollow_arrowhead_marker << '\n';
      ofc <<  stick_arrowhead_marker << "\n</defs>\n";
      for(auto & c : circles)
        add_svg(c, ofc);
      add_svg_arrow(circles[0], circles[4], ofc, "solid-arrow");
      add_svg_arrow(circles[1], circles[3], ofc, "stick-arrow");
      add_svg_arrow(circles[2], circles[0], ofc, "hollow-arrow");
    close_svg(ofc);


  ofc << "</body>\n</html>";
  ofc.close();

  return 0;
}
