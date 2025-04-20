#ifndef DIAGRAM_NODE_H
#define DIAGRAM_NODE_H

#include "point.h"

#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

template <typename FLOAT=double, std::size_t DIM = 2, typename POINT=point<FLOAT,DIM> >
struct diagram_node {
  typedef POINT point_type;
  typedef std::basic_string<char> string_type;
  typedef diagram_node<FLOAT,DIM,POINT> diagram_node_type;
  typedef std::vector<string_type> contents_type;
  typedef std::vector<string_type>::      iterator       iterator;
  typedef std::vector<string_type>::const_iterator const_iterator;
  point_type pt;

  contents_type contents;
  FLOAT rx, ry;
  enum shape {ellipse, rectangle};
  bool draw_border = false;
  //
  diagram_node_type& add(const string_type& str) {contents.emplace_back(str); return *this;}
  std::size_t size() const {return contents.size();}
  const_iterator cbegin() const {return contents.begin();};
  const_iterator cend()   const {return contents.end();};
  //
  const diagram_node_type& draw_svg_shape(std::istream& is) const;
  const diagram_node_type& print_svg_text(std::istream& is) const;
  //
  diagram_node()                                                                     {};
  diagram_node(const point_type& p)                         : pt(p)                  {};
  diagram_node(const point_type& p, const string_type& str) : pt(p), contents({str}) {};
};

template <typename FLOAT, std::size_t DIM, typename POINT>
const diagram_node<FLOAT,DIM,POINT>& diagram_node<FLOAT,DIM,POINT>::draw_svg_shape(std::istream& is) const {
  // draw shape
  return *this;
};
template <typename FLOAT, std::size_t DIM, typename POINT>
const diagram_node<FLOAT,DIM,POINT>& diagram_node<FLOAT,DIM,POINT>::print_svg_text(std::istream& is) const {
  // print text
  return *this;
};

#endif
