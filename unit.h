#ifndef UNIT_H
#define UNIT_H

#include <numbers>

/* The purposes of a unit class is:
 (1) to enforce that the right unit is passed into functions, as in:
     float_t fun(deg_t(30.0))
 (2) to effect conversions within a given system:
     - between radians and sexagesimal angles
     - between between hours, minits and seconds
     or between different systems:
     - between fahrenheit and celsius
     - between feet and meters
 *   PROCEDURE:
 (1) Some tag classes are defined.
     They are used for partial specialization of unit<TAG,FLOAT>.
     For instance, we might define a type:
       typedef unit<rad_tag,double> radian_t;
 (2) Constructors taking a numerical argument are declared explicit
     to avoid conversions.
 (3) A function taking a numerical value meant as an angle in radians
     would then be declared like this:
       <type> fun(..., unit<radian_t> a, ...)
 (4) You may declare conversion constructors, that is,
     constructors that take an object in different units, as in
       fahrenheit::fahrenheit(const celsius& c);
 */



class deg_tag    {};
class rad_tag    {};

class fahrenheit_tag {};
class    celsius_tag {};
class     kelvin_tag {};

class linear_tag {};
class  hz_tag {};

class rgb_tag {};
class cmy_tag {};
class cmyk_tag {};


template <typename TAG = linear_tag, typename F = double>
class unit {
  F val;
public:
  operator       F&()       {return value;};
  operator const F () const {return value;};
  //
  unit()             {};
  explicit unit(F v) : val(F) {};
};

/* Partial specializations for dealing with angles
 */
template <typename F = double>
class unit<deg_tag,F> {
  F val;
public:
  typedef unit<rad_tag,F> rad_t;
  operator       F&()       {return value;};
  operator const F&() const {return value;};
//operator       rad_t&          ; // {return value;};
  operator const rad_t& () const {return value * std::numbers::pi_v<F> / 180.0;};
  //
  unit()                      {};
  explicit unit(F v) : val(F) {};
  explicit unit(rad_t r) : val(r * 180.0 / std::numbers::pi_v<F> ) {};
}; // unit<deg_tag>

template <typename F = double>
class unit<rad_tag,F> {
  F val;
public:
  typedef unit<deg_tag,F> deg_t;
  operator       F&()       {return value;};
  operator const F&() const {return value;};
//operator       rad_t&          ; // {return value;};
  operator const deg_t  () const {return value * 180 / std::numbers::pi_v<F>;};
  //
  unit()             {};
  explicit unit(F v) : val(F) {};
  explicit unit(rad_t r) : val(r * std::numbers::pi_v<F> / 180.0 ) {};
}; // unit<rad_tag>

/* Partial specializations for dealing with temperatures
 * Conversion formula:
 *   °C = (°F - 32) × 5/9
 *   °F = °C x 9/5 + 32
 *   K  = °C + 273.15
 */

template <typename F = double>
class unit<celsius_tag,F> { // a Celsius class
  F val;
public:
  typedef unit<fahrenheit_tag,F> fahrenheit_t;
  operator       F&()       {return value;};
  operator const F&() const {return value;};
//operator       rad_t&          ; // {return value;};
  operator const fahrenheit_t () const {return (value * 9 / 5)  +  32.0;};
  //
  unit()             {};
  explicit unit(F v) : val(F) {};
  explicit unit(fahrenheit_t f) : val( (f - 32.0) * 5 / 9 ) {};
}; // unit<celsius_tag>

#endif
