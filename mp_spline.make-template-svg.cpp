/*
 * This is a template for making an SVG file ("%.svg").
   (Such an SVG file contains one root svg element
   made up of lines as svg:path's
 * The container of on-line points (the points the lines go through)
   may be found in another source file (*.h) or in this file.
 * When drawing complex lines, several strategies are recommended:
 (1)  split one large, complex (closed) line into several smaller, simpler ones
 (2)  when adding points for longish shapes (like branches, ropes, roads etc),
      try to recorded them in pairs of opposite ones,
      so that you may check their separation
 (2') Longish objects are easier to draw as thick lines, though
 (3)  Meeting points (i.e., where a shape meets anoter)
      should be annotated in your source file
 (4)  Resort to drawing circles around on-line points
      by defining:
        #define DRAW_ONLINE_CIRCLES
      or even draw control points (as circles and lines):
        #define DRAW_CONTROLS
 * TODO
[ ] provisions for adding text and other shapes
[x] open lines must have attribute 'fill' set to "none"
[ ] better provisions for setting parameters in mp_splie::make_{open|close}
 */

//#define DRAW_CONTROLS
#ifdef DRAW_CONTROLS
  #define DRAW_ONLINE_CIRCLES
#endif

#ifdef SEPARATE_COMPILATION
  #include "mp_spline.h"
  #include "mp_point.h"
#else
  #include "mp_spline.cpp"
  #include "mp_point.cpp"
#endif

#ifndef SVG_H
  #include "svg.h"
#endif

/* Defaults are provided for the stem, source file (*.h) and svg file (*.svg)
 * If only STEM is defined, then the others become STEM.svg.h and STEM.svg
 */


#include  <fstream>
#include <iostream>

typedef double float_type;
  typedef mp_spline<float_type> mp_spline_t;
    typedef mp_spline_t::point_t point_t;
    // let's call mp_splines just "lines":
    typedef std::vector<mp_spline_t> vector_of_lines_t;

const float_type pi(std::numbers::pi_v<float_type>);

vector_of_lines_t   open_lines({
  mp_spline_t {
   point_t( 50,350),
   point_t( 50,50),
   point_t(150,50),
   point_t(250,50),
   point_t(350,50),
   point_t(350,350)
  }
});

vector_of_lines_t closed_lines({
  mp_spline_t {
   point_t( 40,340),
   point_t( 40,40),
   point_t(140,40),
   point_t(240,40),
   point_t(340,40),
   point_t(340,340)
  }
});


mp_spline_t my_line; // to be loaded with every line in '{open|closed}_lines''

using namespace std;

int main() {

  /*
  mp_spline<float_type> my_line( vpoint1);
  my_line.set_closed_dirs();
  my_line.set_controls_by_adjacent_distance_closed(0.15);
  my_line.y_invert(600);
  */

  ofstream mpcurve("template.svg");

  open_svg(mpcurve, 400.0, 600.0, "black", "gray", 0.5);
    for(auto & l : open_lines) {
      my_line = l;
      open_svg_open_path_p(mpcurve);
      //my_line.to_svg_p(mpcurve);
        my_line.make_open(0.2, 0.2, 0.2);
        my_line.to_svg_p_open(mpcurve);
      close_svg_path(mpcurve);
#ifdef DRAW_CONTROLS
      my_line.add_controls_to_svg_as_circles(mpcurve,2.0);
      my_line.add_controls_to_svg_as_lines(  mpcurve);
#endif
#ifdef DRAW_ONLINE_CIRCLES
      my_line.add_online_to_svg_as_circle(   mpcurve,5.0);
#endif
    }

    for(auto & l : closed_lines) {
      my_line = l;
      open_svg_closed_path_p(mpcurve);
      //my_line.to_svg_p(mpcurve);
        my_line.make_closed(0.2, 0.2);
        my_line.to_svg_p_closed(mpcurve);
      close_svg_path(mpcurve);
#ifdef DRAW_CONTROLS
      my_line.add_controls_to_svg_as_circles(mpcurve,2.0);
      my_line.add_controls_to_svg_as_lines(  mpcurve);
#endif
#ifdef DRAW_ONLINE_CIRCLES
      my_line.add_online_to_svg_as_circle(   mpcurve,5.0);
#endif
    }

    close_svg(mpcurve);

  mpcurve.close();
  return 0;
}
