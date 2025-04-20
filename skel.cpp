#ifndef SKEL_CPP
#define SKEL_CPP

//#include "skel.h"

template<typename FLOAT,
        std::size_t DIM,
         typename POINT>
mechalink<FLOAT,DIM,POINT>& mechalink<FLOAT,DIM,POINT>::update() {
  dst = src;
  //dst.set<0>(dx);
  ::set<0>(dst, ::get<0>(dst) + dx);
  ::set<1>(dst, ::get<1>(dst) + dy);
  ::set<2>(dst, ::get<2>(dst) + dz);
  //dst.set<0>(dst.get<0>() + dx);
  /*
  dst[1] += dy;
  dst[2] += dz;
  */
  updated=true;
  return *this;
};

template<typename FLOAT,
        std::size_t DIM,
         typename POINT>
mechalink<FLOAT,DIM,POINT>& mechalink<FLOAT,DIM,POINT>::grow(FLOAT x, FLOAT y, FLOAT z) {
  children.emplace_back(new mechalink(x,y,z));
  return *children.back();
};

#endif
