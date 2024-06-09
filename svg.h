#ifndef SVG_H
#define SVG_H


/* SVG Helping Functions
 * Remember to define attribute 'stroke' (as black or some non-white colour)
 * in the svg opening tag, or in each svg shape
 * Sometimes you want to define fill to, possibly inside specific svg shapes
 * You rarely want to define <svg stroke="black" fill="black"
 * as the filling will hide a lot of detail
 */

#include <iostream>
#include <string>

// Define an indentation string, typically 2 spaces ("  ")
#ifndef SVG_FILE_INDENT_STR
#define SVG_FILE_INDENT_STR "  "
#endif

/* Open and close an SVG element
 * open_svg(OUT&, width, height, STROKECOLOUR, FILLCOLOUR, FILLOPACITY)
   sets enough attributes to show the contained shapes suitably.
 * Both functions output indentation string (SVG_FILE_INDENT_STR) twice
 */
template<typename F = double, typename OUT = std::ostream>
OUT& open_svg(OUT& o, F w = 200.0, F h = 200.0,
                                   const std::string& strk = "black",
                                   const std::string&  fll = "gray",
                                   F                   fllopct = 0.5) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  o << "<svg width=\"" << w << "\" height=\"" << h;
  o << "\" stroke=\"" << strk << "\" fill=\"" << fll << "\" fill-opacity=\"" << fllopct << "\">\n";
  return o;
}
template<typename OUT = std::ostream>
OUT& close_svg(OUT& o) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << "</svg>\n";
  return o;
};

/* 'add_svg_unclosed(SVG_ELEM&, OUT&)' leaves the tag add_svg_unclosed
   so that further attributes may be added.
 * Remember to close tag with 'close_standalone_tag(OUT&)'
   after adding those new attributes.
 * If you do not need to add further attributes, use 'add_svg(T&,OUT&)'
 * Remember to add 'close_standalone_tag(OUT&)'
 */
template<typename OUT = std::ostream>
OUT & close_standalone_tag(OUT& o = std::cout) {o << "/>\n"; return o;};
template<typename T, typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const T& t, OUT& o = std::cout) {o << "UNDEFINED WHATEVER!!!\n"; return o;};
template<typename T, typename F = double, typename OUT = std::ostream>
OUT & add_svg(const T& t, OUT& o = std::cout) {
  o << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR << SVG_FILE_INDENT_STR;
  add_svg_unclosed(t,o);
  return close_standalone_tag(o);
};


#endif
