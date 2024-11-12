//#define DEBUG

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

#include  <fstream>
#include <iostream>


typedef double float_type;
  typedef mp_spline<float_type> mp_spline_t;
    typedef mp_spline_t::point_t point_t;

const float_type pi(std::numbers::pi_v<float_type>);


using namespace std;

int main() {


  vector<point_t> vpoint1({point_t( 50,350),
                           point_t( 50,50),
                           point_t(150,50),
                           point_t(250,50),
                           point_t(350,50),
                           point_t(350,350)
  });

  mp_spline<     float_type> mps11( vpoint1);

  mps11.set_closed_dirs();

  mps11.set_controls_by_adjacent_distance_closed(0.15);

  mps11.y_invert(600);

  ofstream mpcurve("mpcurve.html");
  mpcurve << "<!DOCTYPE html>\n<html>\n<body>\n";
  mpcurve << "\n<p>Draw list of points \'mps11\' as a closed path:</p>\n";
  open_svg(mpcurve, 400.0, 600.0, "black", "gray", 0.5);
    open_svg_closed_path_p(mpcurve);
      //mps11.to_svg_p(mpcurve);
      mps11.to_svg_p_closed(mpcurve);
    close_svg_path(mpcurve);
    mps11.add_controls_to_svg_as_circles(mpcurve,2.0);
    mps11.add_controls_to_svg_as_lines(  mpcurve);
    mps11.add_online_to_svg_as_circle(   mpcurve,5.0);
  close_svg(mpcurve);

  // Now write the same to "mpcurve_closed_svg"
  ofstream mpcurve_closed_svg("mpcurve-closed.svg");
  open_svg(mpcurve_closed_svg, 400.0, 600.0, "black", "gray", 0.5);
    open_svg_closed_path_p(mpcurve_closed_svg);
      //mps11.to_svg_p(mpcurve_closed_svg);
      mps11.to_svg_p_closed(mpcurve_closed_svg);
    close_svg_path(mpcurve_closed_svg);
    mps11.add_controls_to_svg_as_circles(mpcurve_closed_svg,2.0);
    mps11.add_controls_to_svg_as_lines(  mpcurve_closed_svg);
    mps11.add_online_to_svg_as_circle( mpcurve_closed_svg,5.0);
  close_svg(mpcurve_closed_svg);
  mpcurve_closed_svg.close();

  mpcurve << "\n<p>Now draw the same list of points as an open path:</p>\n";
  mpcurve << "\n<p>NOTE: The top-control points are out of alignment; they are meaningless and without a function\
 as they lie outside the line.</p>\n";
  open_svg(mpcurve, 400.0, 600.0, "black", "gray", 0.5);
    open_svg_open_path_p(mpcurve);
      mps11.set_open_dirs_by_k_kends();
      mps11.set_controls_by_adjacent_distance_open(0.4);
      //mps11.to_svg_p(mpcurve);
      mps11.to_svg_p_open(mpcurve);
    close_svg_path(mpcurve);
    mps11.add_controls_to_svg_as_circles(mpcurve,2.0);
    mps11.add_controls_to_svg_as_lines(  mpcurve);
    mps11.add_online_to_svg_as_circle( mpcurve,5.0);
  close_svg(mpcurve);

  ofstream mpcurve_open_svg("mpcurve-open.svg");
  // Now write the same to "mpcurve_open_svg"
  open_svg(mpcurve_open_svg, 400.0, 600.0, "black", "gray", 0.5);
    open_svg_open_path_p(mpcurve_open_svg);
      //mps11.set_open_dirs_by_k_kends();
      //mps11.set_by_adjacent_distance(0.4);
      mps11.to_svg_p_open(mpcurve_open_svg);
    close_svg_path(mpcurve_open_svg);
    mps11.add_controls_to_svg_as_circles(mpcurve_open_svg,2.0);
    mps11.add_controls_to_svg_as_lines(  mpcurve_open_svg);
    mps11.add_online_to_svg_as_circle( mpcurve_open_svg,5.0);
  close_svg(mpcurve_open_svg);
  mpcurve_open_svg.close();

  mpcurve << "\n</body>\n</html>";
  mpcurve.close();

  return 0;
}
