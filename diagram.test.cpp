#include "diagram_node.h"

// This is just a syntax test:
template <typename FLOAT=double, std::size_t DIM = 2, typename POINT=point<FLOAT,DIM> >
using points_container_type = std::vector<POINT>;


int main() {

  points_container_type<float,2> pc0;

  return 0;
}
