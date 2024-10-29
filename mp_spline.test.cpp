//#define DEBUG

#ifdef SEPARATE_COMPILATION
#include "mp_spline.h"
#else
#include "mp_spline.cpp"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

#include  <fstream>
#include <iostream>

#ifdef PRINT_TO_COUT
#ifndef PRINT_PAIR_H
/* Include global functions for printing:
   (1) a plain std::pair, and
   (2) a mp_spline::point */
#include "print-pair.h"
#endif
#endif


#define TEST_SET_DIR5


typedef double float_type;
  typedef mp_spline<float_type> mp_spline_t;
    typedef mp_spline_t::point point_t;
    typedef mp_spline_t::pair_t pair_t;
  typedef angle_addressable_base<float_type> angle_addressable_base_t;

const float_type pi(std::numbers::pi_v<float_type>);


using namespace std;

int main() {

#ifdef PRINT_TO_COUT
  cout << "atan2( -1, -1) = " << 180 * atan2(-1,-1) / pi << "\n";
  cout << "atan2( +1, -1) = " << 180 * atan2(+1,-1) / pi << "\n";
  cout << "atan2( -1, +1) = " << 180 * atan2(-1,+1) / pi << "\n\n";
#endif

#ifdef TEST_SET_DIR5
  vector<point_t> vpoint1({point_t( 50,350),
                           point_t( 50,50),
                           point_t(150,50),
                           point_t(250,50),
                           point_t(350,50),
                           point_t(350,350)
  });

#else
  vector<point_t> vpoint1({point_t(100,100), point_t(120.0,100.0), point_t(140.0,110.0),
                           point_t(120.0,120.0),
                           point_t(115.0,115.0),
                           point_t(100.0,120.0)
                         , point_t( 90.0,110.0)
  });
#endif

#ifdef PRINT_TO_COUT
  cout << "Print all points (x,y,dir):\n";
  for(auto item : vpoint1) {cout << item << std::endl;}
#endif

  mp_spline<double> mps1, mps11(vpoint1);

#ifdef PRINT_TO_COUT
  cout << "Print all points in \'mps11\':\n";
  for ( auto item : mps11) { cout << item << std::endl;}
#endif

  mps11.set_open_dirs();

#ifdef PRINT_TO_COUT
  cout << "Print all points in \'mps11\' after setting its dirs as open:\n";
  for ( auto item : mps11) { cout << item << std::endl;}
#endif


  mps11.set_closed_dirs();
#ifdef TEST_SET_DIR5
  //mps11.set_controls_distance(33.0);
  mps11.set_by_adjacent_distance(0.15);
#else
  mps11.set_by_adjacent_distance(0.4);
#endif

#ifdef PRINT_TO_COUT
  cout << "Print all points in \'mps11\' after setting its dirs as closed:\n";
  for ( auto item : mps11) { cout << item << std::endl;}
#endif

  ofstream mpcurve("mpcurve.html");
  mpcurve << "<!DOCTYPE html>\n<html>\n<body>\n";
  mpcurve << "\n<p>Draw list of points \'mps11\' as a closed path:</p>\n";
  open_svg(mpcurve, 400.0, 400.0, "black", "gray", 0.5);
    open_svg_path_p(mpcurve);
      //mps11.to_svg_p(mpcurve);
      mps11.to_svg_p_closed(mpcurve);
    close_svg_path(mpcurve);
    mps11.add_controls_to_svg_as_circles(mpcurve,2.0);
    mps11.add_control_to_svg_as_line(  mpcurve);
    mps11.add_online_to_svg_as_circle( mpcurve,5.0);
  close_svg(mpcurve);

  // Now write the same to "mpcurve_closed_svg"
  ofstream mpcurve_closed_svg("mpcurve-closed.svg");
  open_svg(mpcurve_closed_svg, 400.0, 400.0, "black", "gray", 0.5);
    open_svg_path_p(mpcurve_closed_svg);
      //mps11.to_svg_p(mpcurve_closed_svg);
      mps11.to_svg_p_closed(mpcurve_closed_svg);
    close_svg_path(mpcurve_closed_svg);
    mps11.add_controls_to_svg_as_circles(mpcurve_closed_svg,2.0);
    mps11.add_control_to_svg_as_line(  mpcurve_closed_svg);
    mps11.add_online_to_svg_as_circle( mpcurve_closed_svg,5.0);
  close_svg(mpcurve_closed_svg);
  mpcurve_closed_svg.close();

  mpcurve << "\n<p>Now draw the same list of points as an open path:</p>\n";
  open_svg(mpcurve, 400.0, 600.0, "black", "gray", 0.5);
    open_svg_path_p(mpcurve);
      mps11.set_open_dirs();
      mps11.set_by_adjacent_distance(0.4);
      //mps11.to_svg_p(mpcurve);
      mps11.to_svg_p_open(mpcurve);
    close_svg_path(mpcurve);
    mps11.add_controls_to_svg_as_circles(mpcurve,2.0);
    mps11.add_control_to_svg_as_line(  mpcurve);
    mps11.add_online_to_svg_as_circle( mpcurve,5.0);
  close_svg(mpcurve);

  ofstream mpcurve_open_svg("mpcurve-open.svg");
  // Now write the same to "mpcurve_open_svg"
  open_svg(mpcurve_open_svg, 400.0, 600.0, "black", "gray", 0.5);
    open_svg_path_p(mpcurve_open_svg);
      mps11.set_open_dirs();
      mps11.set_by_adjacent_distance(0.4);
      //mps11.to_svg_p(mpcurve_open_svg);
      mps11.to_svg_p_open(mpcurve_open_svg);
    close_svg_path(mpcurve_open_svg);
    mps11.add_controls_to_svg_as_circles(mpcurve_open_svg,2.0);
    mps11.add_control_to_svg_as_line(  mpcurve_open_svg);
    mps11.add_online_to_svg_as_circle( mpcurve_open_svg,5.0);
  close_svg(mpcurve_open_svg);
  mpcurve_open_svg.close();

  mpcurve << "\n</body>\n</html>";
  mpcurve.close();

  return 0;
}
