//#define DEBUG
#include "metapost.curves.h"
#ifndef SVG_H
#include "svg.h"
#endif

#define TEST_SET_DIR5

typedef double float_type;
  typedef mp_spline<float_type> mp_spline_t;
    typedef mp_spline_t::point point_t;
    typedef mp_spline_t::pair_t pair_t;
  typedef angle_addressable_base<float_type> angle_addressable_base_t;

const float_type pi(std::numbers::pi_v<float_type>);

#include  <fstream>
#include <iostream>

/* Define global functions for printing:
   (1) a plain std::pair, and
   (2) a mp_spline::point */
template <typename F, typename S>
std::ostream& operator<<(std::ostream& o, const typename std::pair<F,S>& p) {
  o << '(' << p.first << ',' << p.second << ')';
  return o;
};
template <typename F = double>
std::ostream& operator<<(std::ostream& o, const typename mp_spline<F>::point& p) {
  o << '(' <<  p.pt.first << ',' << p.pt.second << ','
           << (p.dir  / std::numbers::pi_v<float_t>) * 180  << ')'
    << " with controls: " << p.prept << " and " << p.postpt;
  return o;
};

using namespace std;

int main() {

  cout << "atan2( -1, -1) = " << 180 * atan2(-1,-1) / pi << "\n";
  cout << "atan2( +1, -1) = " << 180 * atan2(+1,-1) / pi << "\n";
  cout << "atan2( -1, +1) = " << 180 * atan2(-1,+1) / pi << "\n\n";

  vector<pair_t> vpair1({pair_t({100,100}), pair_t({120,100.0}), pair_t({140.0,110.0}),
                         pair_t({120.0,120.0}), pair_t({110.0,110.0}), pair_t({100.0,120.0})
                       , pair_t({ 90.0,110.0})
  });
  cout << "Print all pairs (x,y):\n";
  for(auto item : vpair1) {cout << item << std::endl;}
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
  cout << "Print all points (x,y,dir):\n";
  for(auto item : vpoint1) {cout << item << std::endl;}

  mp_spline<double> mps1, mps11(vpoint1);
  // mp_spline<double> mps1(vpair1);

  cout << "Print all points in \'mps11\':\n";
  for ( auto item : mps11) { cout << item << std::endl;}

  mps11.set_open_dirs();
  cout << "Print all points in \'mps11\' after setting its dirs as open:\n";
  for ( auto item : mps11) { cout << item << std::endl;}


  mps11.set_closed_dirs();
#ifdef TEST_SET_DIR5
  //mps11.set_controls(33.0);
  mps11.set_by_adjacent_distance(0.15);
#else
  mps11.set_controls(5.0);
#endif
  cout << "Print all points in \'mps11\' after setting its dirs as closed:\n";
  for ( auto item : mps11) { cout << item << std::endl;}

  ofstream mpcurve("mpcurve.html");
  mpcurve << "<!DOCTYPE html>\n<html>\n<body>\n";
  mpcurve << "\nDraw list of points \'mps11\' as a closed path:\n";

  open_svg(mpcurve, 400.0, 400.0, "black", "gray", 0.5);
    open_svg_path_p(mpcurve);
      //mps11.to_svg_p(mpcurve);
      mps11.to_svg_p_closed(mpcurve);
    close_svg_path(mpcurve);
#ifndef TEST_SET_DIR5
    for(int i=0; i < mps11.points.size(); ++i) {
      mps11.add_control_to_svg_as_circle(mpcurve,i,2.0);
      mps11.add_control_to_svg_as_line(  mpcurve,i);
    }
#endif
  close_svg(mpcurve);

  mpcurve << "\nNow draw the same list of points as an open path:\n";
  open_svg(mpcurve, 400.0, 400.0, "black", "gray", 0.5);
    open_svg_path_p(mpcurve);
      mps11.set_open_dirs();
      //mps11.to_svg_p(mpcurve);
      mps11.to_svg_p_open(mpcurve);
    close_svg_path(mpcurve);
#ifndef TEST_SET_DIR5
    for(int i=0; i < mps11.points.size(); ++i) {
      mps11.add_control_to_svg_as_circle(mpcurve,i,2.0);
      mps11.add_control_to_svg_as_line(  mpcurve,i);
    }
#endif
  close_svg(mpcurve);

  mpcurve << "\n</body>\n</html>";
  mpcurve.close();

  return 0;
}
