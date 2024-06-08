#ifndef SCHEMATICS_LINE_H
#define SCHEMATICS_LINE_H

/* Classes oneline<FLOAT> and twoline<FLOAT> define
   one- and two-dimensional "lines"
 * They make use of static interpolate(BEG,END,K)
   to interpolate between beginning and end by a factor k
 * Class oneline<>, a one-dimensional line,
   holds its beginning and ending as single floats,
   and has a  static FLOAT interpolate(BEG,END, K) member
 * Currently, I don't know what these classes would be good for.
 */
template <typename FLOAT=double>
class oneline {
public:
  typedef FLOAT float_t;
  static float_t interpolate(float_t b, float_t e, float_t k) {
    return b*(1 - k) + e*k;
  };
  float_t get_beg() const {return beg;};
  float_t get_end() const {return end;};
  const float_t beg, end;
  float_t get(float_t k) const {return interpolate(beg,end,k);};
  oneline(float_t b, float_t e) : beg(b), end(e) {};
};
/* class twoline<>
 * holds two oneline's (named 'x' and 'y')
 * and represents a line in 2-space
 */
template <typename FLOAT = double>
struct twoline {
public:
  typedef FLOAT float_t;
  typedef oneline<FLOAT> oneline_t;
  oneline_t x,y;
  float_t get_xbeg() const {return x.get_beg();};
  float_t get_ybeg() const {return y.get_beg();};
  float_t get_xend() const {return x.get_end();};
  float_t get_yend() const {return y.get_end();};
  float_t get_x(float_t k) const {return x.get(k);};
  float_t get_y(float_t k) const {return y.get(k);};
  twoline(float_t xb, float_t yb, float_t xe, float_t ye) : x(xb,xe), y(yb,ye) {};
};

#endif
