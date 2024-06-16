#ifndef SCHEMATICS_SQ_POLYLINE_H
#define SCHEMATICS_SQ_POLYLINE_H

#include <initializer_list>
#include <iostream>
#include <vector>

/* class sq_polyline represents a polyline whose segments are alternatively horizontal and vertical,
 * adjacents segments are at square angles
 *
 */
template <typename FLOAT=double>
class sq_polyline {
protected:
  void add_start_to_svg_path(std::ostream& o) const {o << " M " << x1 << ' ' << y1;};
  void   add_end_to_svg_path(std::ostream& o) const {o << " L " << x2 << ' ' << y2;};
public:
  FLOAT x1, y1, x2, y2; // same names as attributes of svg::line
  virtual void add_to_svg_path(std::ostream& o) const {
    add_start_to_svg_path(o);
    add_end_to_svg_path(  o);
  };
  //
  sq_polyline() = default;
  sq_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2) : x1(x1), y1(y1), x2(x2), y2(y2) {};
};

/* classes h_polyline and v_polyline draw a 2-segment polyline
 * whose first segment is a horizontal or a vertical segment
 * respectly */
template <typename FLOAT=double>
class h_polyline : public sq_polyline<FLOAT> {
public:
  typedef sq_polyline<FLOAT> sq_polyline_t;
  using sq_polyline_t::add_start_to_svg_path, sq_polyline_t::add_end_to_svg_path;
  using sq_polyline_t::x1, sq_polyline_t::y1, sq_polyline_t::x2, sq_polyline_t::y2;

  virtual void add_to_svg_path(std::ostream& o) const {
    add_start_to_svg_path(o);
    o << " H " << x2;
    add_end_to_svg_path(  o);
  };
  //
  h_polyline() = default;
  h_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2) : sq_polyline_t(x1,y1,x2,y2) {};
};
template <typename FLOAT=double>
class v_polyline : public sq_polyline<FLOAT> {
public:
  typedef sq_polyline<FLOAT> sq_polyline_t;
  using sq_polyline_t::add_start_to_svg_path, sq_polyline_t::add_end_to_svg_path;
  using sq_polyline_t::x1, sq_polyline_t::y1, sq_polyline_t::x2, sq_polyline_t::y2;

  virtual void add_to_svg_path(std::ostream& o) const {
    add_start_to_svg_path(o);
    o << " V " << y2;
    add_end_to_svg_path(  o);
  };
  //
  v_polyline() = default;
  v_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2) : sq_polyline_t(x1,y1,x2,y2) {};
};

/* classes hv_polyline and vh_polyline take an additional displacement param (d)
 * and draw three segments: the first one being a horizontal or vertical one.
 */
template <typename FLOAT=double>
class hv_polyline : public sq_polyline<FLOAT> {
public:
  typedef sq_polyline<FLOAT> sq_polyline_t;
  using sq_polyline_t::add_start_to_svg_path, sq_polyline_t::add_end_to_svg_path;
  using sq_polyline_t::x1, sq_polyline_t::y1, sq_polyline_t::x2, sq_polyline_t::y2;
  FLOAT d;
  virtual void add_to_svg_path(std::ostream& o) const {
    add_start_to_svg_path(o);
    o << " h " << d;
    o << " L " << x1 + d << ' ' << y2 << ' ';
    add_end_to_svg_path(  o);
  };
  //
  hv_polyline() = default;
  hv_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT d) : sq_polyline_t(x1,y1,x2,y2), d(d) {};
};
template <typename FLOAT=double>
class vh_polyline : public sq_polyline<FLOAT> {
public:
  typedef sq_polyline<FLOAT> sq_polyline_t;
  using sq_polyline_t::add_start_to_svg_path, sq_polyline_t::add_end_to_svg_path;
  using sq_polyline_t::x1, sq_polyline_t::y1, sq_polyline_t::x2, sq_polyline_t::y2;
  FLOAT d;
  virtual void add_to_svg_path(std::ostream& o) const {
    add_start_to_svg_path(o);
    o << " v " << d;
    o << " L " << x2 << ' ' << y1 + d << ' ';
    add_end_to_svg_path(  o);
  };
  //
  vh_polyline() = default;
  vh_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT d) : sq_polyline_t(x1,y1,x2,y2), d(d) {};
};


/* classes hvh_polyline and vhv_polyline take an additional displacement param (d)
 * and draw three segments: the first one being a horizontal or vertical one.
 */
template <typename FLOAT=double>
class hvh_polyline : public sq_polyline<FLOAT> {
public:
  typedef sq_polyline<FLOAT> sq_polyline_t;
  using sq_polyline_t::add_start_to_svg_path, sq_polyline_t::add_end_to_svg_path;
  using sq_polyline_t::x1, sq_polyline_t::y1, sq_polyline_t::x2, sq_polyline_t::y2;
  FLOAT d1, d2;
  virtual void add_to_svg_path(std::ostream& o) const {
    add_start_to_svg_path(o);
    o << " h " << d1;
    o << " v " << d2;
    o << " L " << x2 << ' ' << y1 + d2 << ' ';
    add_end_to_svg_path(  o);
  };
  hvh_polyline() = default;
  hvh_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT d1, FLOAT d2)
  : sq_polyline_t(x1,y1,x2,y2), d1(d1), d2(d2) {};
};
template <typename FLOAT=double>
class vhv_polyline : public sq_polyline<FLOAT> {
public:
  typedef sq_polyline<FLOAT> sq_polyline_t;
  using sq_polyline_t::add_start_to_svg_path, sq_polyline_t::add_end_to_svg_path;
  using sq_polyline_t::x1, sq_polyline_t::y1, sq_polyline_t::x2, sq_polyline_t::y2;
  FLOAT d1, d2;
  virtual void add_to_svg_path(std::ostream& o) const {
    add_start_to_svg_path(o);
    o << " v " << d1;
    o << " h " << d2;
    o << " L " << x1 + d2 << ' ' << y2 << ' ';
    add_end_to_svg_path(  o);
  };
  vhv_polyline() = default;
  vhv_polyline(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT d1, FLOAT d2)
  : sq_polyline_t(x1,y1,x2,y2), d1(d1), d2(d2) {};
};


#endif
