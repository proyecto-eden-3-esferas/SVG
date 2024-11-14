/*
 * Drawing neuron from file:
     Neuron-dendrites-axon-cell_brain-physiology_QBIc.jpg
 *
 * TODO
 [ ] The outline of the neuron should be split into small closed and open lines
 */

//
#ifndef AXON_INC
  #define AXON_INC 75
#endif

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
   point_t( 233, 306), // stem of upward dendrite tapers 5u to 3u wide
   point_t( 222, 219),
   point_t( 223, 110) // top or tip, and fork
  }),
  mp_spline_t ({
   point_t( 223, 110), // bottom of top-left branching
   point_t( 208,  93),
   point_t( 181, 72), // fork
   point_t( 162, 65), // fork
   point_t( 141,  67),
   point_t( 113,  34),
   point_t( 114,  25)
  }),
  mp_spline_t ({
   point_t( 162, 65),
   point_t( 160, 51),
   point_t( 144, 27),
   point_t( 139, 10)
  }),
  mp_spline_t ({
   point_t(181, 72),
   point_t(183, 42),
   point_t(200, 33),
   point_t(208, 22),
   point_t(223, 22)
  }),

  mp_spline_t ({
   point_t( 223, 110), // bottom of top-right branching
   point_t( 245,  96),
   point_t( 280,  83),
   point_t( 284,  58), // fork
   point_t( 297,  42), // fork
   point_t( 334,  34),
   point_t( 351,  31),
   point_t( 364,  18) }),
 mp_spline_t ({
   point_t( 284,  58), // fork
   point_t( 269,  31),
   point_t( 251,  16) }),
 mp_spline_t ({
   point_t( 297,  42),
   point_t( 327,  44),
   point_t( 362,  63) }),

 mp_spline_t ({ // dendrite leftwards
   point_t( 206, 376),
   point_t( 180, 378),
   point_t( 166, 392),
   point_t( 158, 426),
   point_t( 150, 444), // fork leftwards
   point_t( 124, 463), // fork downwards
   point_t(  89, 468),
   point_t(  39, 493)
 }),
 mp_spline_t ({ // fork leftwards
   point_t( 150, 444),
   point_t( 130, 438),
   point_t(  84, 436),
   point_t(  75, 410)
 }),
 mp_spline_t ({ // fork downwards
   point_t( 124, 463),
   point_t( 112, 500),
   point_t( 107, 539)
 }),
 mp_spline_t({
   point_t( 262, 376), // dendrite down- rightwards
   point_t( 270, 396),
   point_t( 274, 418),
   point_t( 282, 435), // fork rightwards
   point_t( 313, 460),
   point_t( 337, 482), // fork downwards
   point_t( 363, 516),
   point_t( 385, 530),
   point_t( 401, 575)
 }),
 mp_spline_t({
   point_t( 282, 435),
   point_t( 324, 415),
   point_t( 358, 417), // fork rightwards and up
   point_t( 385, 428),
   point_t( 417, 444)
 }),
 mp_spline_t({
   point_t( 358, 417), // subdendrite rightwards and up
   point_t( 382, 401),
   point_t( 403, 395)
 }),
 mp_spline_t({
   point_t( 337, 482), // subdendrite downwards
   point_t( 330, 509),
   point_t( 333, 534),
   point_t( 339, 555),
   point_t( 331, 580),
   point_t( 305, 598)
 })
});

vector_of_lines_t  closed_lines({
  mp_spline_t ({
   point_t( 235, 306),
   point_t( 248, 322),
   point_t( 262, 339),
   point_t( 268, 350),
   point_t( 268, 359),
   point_t( 262, 376), // dendrite down- rightwards
   point_t( 254, 378),
   point_t( 232, 381),
   // axon
   point_t( 227, 381),
   point_t( 206, 376), // fork leftwards
   point_t( 200, 368),
   point_t( 210, 352),
   point_t( 216, 339),
   point_t( 223, 319)
  }),
  mp_spline_t({ // nucleus
    point_t(239,336),
    //point_t(240,338), // commented out to prevent an inlet/dent
    point_t(245,341),
    point_t(247,351),
    point_t(241,363),
    point_t(233,356),
    point_t(229,342)
  })
});

vector_of_lines_t  axon_lines({
  mp_spline_t ({ // axon stem
   point_t( 230, 381),
   point_t( 223, 420),
   point_t( 234, 449),
   point_t( 236, 466),
   point_t( 223, 521 + AXON_INC), // fork down- rightwards (thick)
   point_t( 203, 551 + AXON_INC),
   point_t( 175, 565 + AXON_INC), // fork downwards
   point_t( 133, 570 + AXON_INC + AXON_INC)
  }),
  mp_spline_t ({
   point_t( 223, 521 + AXON_INC),
   point_t( 247, 557 + AXON_INC),
   point_t( 265, 574 + AXON_INC), // fork leftwards
   point_t( 280, 614 + AXON_INC),
   point_t( 301, 637 + AXON_INC + AXON_INC) /*, fork
   point_t( 216, 339),
   point_t( 223, 319)*/
  })
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

  open_svg(mpcurve, 450.0, 700.0 + AXON_INC + AXON_INC, "black", "gray", 0.5);

    for(auto & l : open_lines) {
      my_line = l;
      open_svg_open_path_p(mpcurve, "stroke-width=\"4\" stroke=\"gray\"", 1);
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

    for(auto & l : axon_lines) {
      my_line = l;
      open_svg_open_path_p(mpcurve, "stroke-width=\"2\" stroke=\"gray\"", 1);
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
      open_svg_closed_path_p(mpcurve, "stroke-width=\"1\"", 1);
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
