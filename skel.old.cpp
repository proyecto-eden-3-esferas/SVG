#ifndef SKEL_CPP
#define SKEL_CPP

//#include "skel.h"

template<typename FLOAT,
        std::size_t DIM,
         typename POINT>
mechalink<FLOAT,DIM,POINT>& mechalink<FLOAT,DIM,POINT>::update() {
  if(src==nullptr) {
    dst[0] = dx;
    dst[1] = dy;
    dst[2] = dz;
  } else {
    dst = this->get_src_point();
    dst[0] += dx;
    dst[1] += dy;
    dst[2] += dz;
  }
  updated=true;
  return *this;
};

template<typename FLOAT,
        std::size_t DIM,
         typename POINT>
const mechalink<FLOAT,DIM,POINT>::point_type& mechalink<FLOAT,DIM,POINT>::get_src_point() {
  if(src==nullptr)
    return dst; // raise an exception instead
  else
    return src->dst;
};

#endif
