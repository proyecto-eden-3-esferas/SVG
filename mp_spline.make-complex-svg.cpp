/*
 * This is a template for making an SVG file ("%.svg")
   holding an SVG root element made up of lines
   from a source file %.svg.h
   (Defaults to "test-lines.svg")
 * TODO
   - provisions for adding text and other shapes
   - open lines must have attribute 'fill' set to "none"
   - provisions for setting parameters in mp_splie::make_{open|close}
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

#ifndef SVG_FILE
  #define SVG_FILE test-lines.svg
#endif


#include  <fstream>
#include <iostream>

typedef double float_type;
  typedef mp_spline<float_type> mp_spline_t;
    typedef mp_spline_t::point_t point_t;
    // let's call mp_splines just "lines":
    typedef std::vector<mp_spline_t> vector_of_lines_t;

const float_type pi(std::numbers::pi_v<float_type>);

#include "test-lines.two-vectors-of-lines.h"
/* The following variables must have been defined in STEM.svg.h:
     vector_of_lines_t   open_lines;
     vector_of_lines_t closed_lines; */

mp_spline_t my_line;

using namespace std;

int main() {

  /*
  mp_spline<float_type> my_line( vpoint1);
  my_line.set_closed_dirs();
  my_line.set_controls_by_adjacent_distance_closed(0.15);
  my_line.y_invert(600);
  */

  ofstream mpcurve("test-lines.svg");

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
