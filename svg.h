#ifndef SVG_H
#define SVG_H

/* SVG Interface Struct svg_shape<FLOAT> and Helping Functions
 * Remember to define attribute 'stroke' (as black or some non-white colour)
   in the svg opening tag, or in each svg shape
 * Sometimes you want to define 'fill' , possibly inside specific svg shapes
 * You rarely want to define <svg stroke="black" fill="black"
   as the filling will hide a lot of detail
 * TODO
   [ ] write and import a light html headers-only file for HTML/XML (light-html.h)
   [ ] then close_standalone_tag(OSTREAM, ATTRS) should be moved to "light-html.h"
   [ ] Implement adding attributes (class, id, stroke-width) to svg elements.
       This might be realized as the last input argument
       to global functions and constructors, as in:
       FUNCTION(..., const std::string & attr = "")
 */

#include <iomanip> // for std::setprecision(INT)
#include <iostream>
#include <string>

#ifndef SVG_PLAIN_SHAPES_H
#include "svg.plain-shapes.h"
#endif

template <typename F = double>
struct svg_shape {
  virtual void add_svg_unclosed(    std::ostream& o = std::cout) const = 0;
  virtual void add_svg(             std::ostream& o = std::cout, const std::string& attrs = "") const
  {
    add_svg_unclosed(o);
    close_standalone_tag(o,attrs);
  };
  void close_standalone_tag(std::ostream& o = std::cout, const std::string& attrs = "") const
  {
    if(attrs.length() > 0)
      o << ' ' << attrs << ' ';
    o << "/>\n";
  };
};


// Define an indentation string, typically 2 spaces ("  ")
#ifndef SVG_FILE_INDENT_STR
#define SVG_FILE_INDENT_STR "  "
#endif


/* Open and close an SVG element
 * open_svg(OUT&, width, height, STROKECOLOUR, FILLCOLOUR, FILLOPACITY)
   sets enough attributes to show the contained shapes suitably.
 * Both functions output indentation string (SVG_FILE_INDENT_STR) twice
 */
template <typename F = double, typename OUT = std::ostream>
void open_svg(OUT& o, F w = 200.0, F h = 200.0,
                                   const std::string& strk = "black",
                                   const std::string&  fll = "gray",
                                   F                   fllopct = 0.5,
                                   std::size_t decimals=2) // decimal digits (after the point)
{
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << std::fixed << std::setprecision(decimals);
  o << "<svg width=\"" << w << "\" height=\"" << h;
  o << "\" stroke=\"" << strk << "\" fill=\"" << fll << "\" fill-opacity=\"" << fllopct << "\">\n";
  //return o; // void return type
}

/*
 * open_svg_path_p(OUT_STREAM,ATTR,DECIMALS) outputs: <path ATTR d="
   whereas
   open_svg_open_path_p( OUT_STREAM,ATTR,DECIMALS) also sets attribute fill="none"
 * Finally,
   open_svg_closed_path_p(OUT,ATTRS,DECS) == open_svg_path_p(OUT,ATTRS,DECS)
 * REMEMBER: These three global functions print: <path [...] d="
   and expect another global function (close_svg_path(OSTREAM))
   to close the self-standing element like this: "/>
 */
template <typename F = double, typename OUT = std::ostream>
void open_svg_path_p(OUT& o, const std::string & attrs="", int decimals = 2) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << std::fixed << std::setprecision(decimals);
  if(attrs.length() > 0)
    o << "<path " << attrs << " d=\"";
  else
    o << "<path d=\"";
  //return o; // void return type
};
template <typename F = double, typename OUT = std::ostream>
void open_svg_open_path_p(OUT& o, const std::string & attrs="", int decimals = 2) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << std::fixed << std::setprecision(decimals);
  if(attrs.length() > 0)
    o << "<path class=\"open\" fill=\"none\" " << attrs << " d=\"";
  else
    o << "<path class=\"open\" fill=\"none\" d=\"";
  //return o; // void return type
};
template <typename F = double, typename OUT = std::ostream>
void open_svg_closed_path_p(OUT& o, const std::string & attrs="", int decimals = 2) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << std::fixed << std::setprecision(decimals);
  if(attrs.length() > 0)
    o << "<path class=\"closed\" " << attrs << " d=\"";
  else
    o << "<path class=\"closed\" d=\"";
  //return o; // void return type
};
//
template <typename OUT = std::ostream>
void close_svg_path(OUT& o = std::cout) {
  o << "\"/>\n";
  //return o; // void return type
};

template <typename OUT = std::ostream>
void close_svg(OUT& o) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << "</svg>\n";
  //return o; // void return type
};

/* 'add_svg_unclosed(SVG_ELEM&, OUT&)' leaves the tag unclosed
   so that further attributes may be added.
 * Remember to close tag with 'close_standalone_tag(OUT&)'
   after adding those new attributes.
 * If you do not need to add further attributes, use 'add_svg(T&,OUT&)'
 * Remember to add 'close_standalone_tag(OUT&)' after calling add_svg_unclosed()
 */
template <typename T, typename F = double, typename OUT = std::ostream>
void add_svg_unclosed(const T& t, OUT& o = std::cout) {o << "UNDEFINED WHATEVER!!!\n";};
template <typename OUT = std::ostream>
void close_standalone_tag(OUT& o = std::cout, const std::string& attrs = "") {
  if(attrs.length() > 0)
    o << ' ' << attrs << ' ';
  o << "/>\n";
};
template <typename T, typename F = double, typename OUT = std::ostream>
void add_svg(const T& t, OUT& o = std::cout) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_svg_unclosed(t,o);
  close_standalone_tag(o);
};

#endif
