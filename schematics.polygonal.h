#ifndef POLYGONAL_H
#define POLYGONAL_H

#ifndef SCHEMATICS_ANGLE_H
#include "schematics.angle.h"
#endif

#ifndef SVG_H
#include "svg.h"
#endif

#include <utility>

/* Write class polygonal derived from angle_addressable<> and svg_shape<>
 * [ ] it will be initialized with vertex coordinates
 * [ ] it will calculate its center (cx,xy) from such vertex coordinates
 * [ ] it will be hard work to implement xperim(DEGS) and yperim(DEGS)
 * [ ] it keeps track of which angle interval matches each side
 * [ ] you start by writing "protected: unsigned int which(DEGS) const;",
 *     that returns which side
 */
template <typename FLOAT = double>
class polygonal : public angle_addressable<FLOAT>, public svg_shape<FLOAT> {
public:
  typedef angle_addressable<FLOAT> cir_t;
  typedef FLOAT float_t;
  typedef std::pair<float_t,float_t> range_t;
  //
  using cir_t::cx, cir_t::cy;
  /*
  virtual float_t xperim(float_t degs) const = 0;
  virtual float_t yperim(float_t degs) const = 0;
  void add_svg_unclosed(std::ostream& o = std::cout, const std::string& attrs = "") const override;
  */
  //
  // polygonal(float_t ra, float_t x=0, float_t y=0) : cir_t(x,y), r(ra) {};
};

#endif
