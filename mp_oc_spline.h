#ifndef MP_OC_SPLINE_H
#define MP_OC_SPLINE_H

/* Class mp_oc_spline<> is a child of mp_spline<>, and
   stores its closed-ness in a protected bool variable ('closed').
 * Another possibility is to derive
   - a class mp_o_spline<> (open),   with no fill colour; and
   - a class mp_c_spline<> (closed), with a fill colour.
 *
 */
template <typename F = double>
class mp_oc_spline : public mp_spline<F> {
public:
  typedef mp_spline<F> mp_spline_t;
protected:
  bool closed;
public:
  bool is_closed() const {return  closed;}
  bool is_open  () const {return !closed;}
  virtual void set_open  () {closed=false;}
  virtual void set_closed() {closed=true;}
  // constructors:
  mp_oc_spline() : closed(false) {};
  mp_oc_spline(std::initializer_list<pair_t> il,                 bool clsd=false)
  : mp_spline_t(il),                 closed(clsd) {};
  mp_oc_spline(std::initializer_list<mp_oc_spline<F>::point> il, bool clsd=false)
  : mp_spline_t(il),                 closed(clsd) {};
  template <typename CONTAINER>
  mp_oc_spline(const CONTAINER& c,                               bool clsd=false)
  : mp_spline_t(c.begin(), c.end()), closed(clsd) {};
}; // class mp_oc_spline<>
}

#endif
