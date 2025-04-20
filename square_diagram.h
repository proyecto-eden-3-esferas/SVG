#ifndef SQUARE_DIAGRAM_H
#define SQUARE_DIAGRAM_H

#include "diagram.h"
#include <vector>

template <typename FLOAT=double, typename DIANODE=diagram_node<FLOAT,2,point<FLOAT,2>> >
class square_diagram {
  FLOAT side_width;
  std::size_t num_sqrs_per_side;
  FLOAT margin_percent;
public:
  typedef DIANODE diagram_node_type;
  typedef square_diagram<FLOAT,DIANODE> square_diagram_type;
  std::vector<diagram_node_type> nodes;
  square_diagram_type& add(const diagram_node_type& dn) {nodes.emplace_back(nd);};
  // constructors:
  square_diagram(FLOAT w, std::size_t n = 4, FLOAT m=0.1) : side_width(w), num_sqrs_per_side(n), margin_percent(m) {};
}

#endif
