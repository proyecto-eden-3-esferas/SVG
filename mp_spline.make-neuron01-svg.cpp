/*
 * Drawing neuron from file:
     Neuron-dendrites-axon-cell_brain-physiology_QBIc.jpg
 *
 * TODO
 [ ] The outline of the neuron should be split into small closed and open lines
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
  mp_spline_t ({
   point_t( 50,350),
   point_t( 50,50),
   point_t(150,50),
   point_t(250,50),
   point_t(350,50),
   point_t(350,350)
  })
});

vector_of_lines_t  closed_lines({
  mp_spline_t ({ // body and dendrites
   point_t( 227, 308), // top of body, root of upward dendrite
   point_t( 221, 117),
   point_t( 208,  93),
   point_t( 141,  67),
   point_t( 113,  34),
   point_t( 114,  25), // tip of thick dendrite
   point_t( 132,  55),
   point_t( 140,  59),
   point_t( 161, 63), // at root of thin upward branching
   point_t( 165, 65),
   point_t( 178, 67),
   point_t( 182, 72),
   point_t( 181, 71),
   point_t( 183, 38),
   point_t( 197, 31),
   point_t( 208, 22),
   point_t( 222, 20),
   point_t( 223, 20),
   point_t( 211, 24),
   point_t( 202, 32),
   point_t( 197, 36),
   point_t( 186, 42),
   point_t( 185, 71),
   point_t( 188, 71),
   point_t( 205, 83),
   point_t( 219, 92),
   point_t( 225, 108),
   /* right branching of upward dendrite
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   */
   point_t( 230, 117),
   point_t( 228, 151),
   point_t( 230, 208),
   point_t( 233, 259),
   point_t( 235, 306),
   point_t( 248, 322),
   point_t( 262, 339),
   point_t( 268, 350),
   point_t( 268, 359),
   point_t( 262, 376),
   /* dendrite down- leftwards
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   */
   point_t( 254, 378),
   point_t( 232, 381),
   // axon
   point_t( 227, 381),
   point_t( 206, 376),
   /* dendrite down- leftwards
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   */
   point_t( 200, 368),
   point_t( 210, 352),
   point_t( 216, 339),
   point_t( 223, 319)
   /*
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0),
   point_t( 0, 0)
   *7
  }),
  mp_spline_t ( {
   /*
   point_t( 40,340),
   point_t( 40,40),
   point_t(140,40),
   point_t(240,40),
   point_t(340,40),
   point_t(340,340)
   */
  } )
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

  ofstream mpcurve("neuron01.svg");

  open_svg(mpcurve, 450.0, 700.0, "black", "gray", 0.5);
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
