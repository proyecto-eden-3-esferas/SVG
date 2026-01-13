#ifndef SVG_PATH_H
#define SVG_PATH_H

#include <iostream>
template<typename F = double>
class svg_path {
public:
  virtual void add_to_svg_path(std::ostream& o = std::cout) const = 0;
  bool is_abs; // is absolute (uppercase), not relative (lowercase) command
  //
  bool is_absolute() const {return  is_abs;};
  bool is_relative() const {return !is_absolute();};
//protected:
  void make_absolute() {is_abs = true;};
  void make_relative() {is_abs = false;};
  // Constructor(s)
  svg_path(bool ia = true) : is_abs(ia) {};
};

#endif
