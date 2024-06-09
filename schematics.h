#ifndef SCHEMATICS_H
#define SCHEMATICS_H

/* Files and Classes in Schematics
 * Several subhierarchies are defined:
 * (1) angle_addressable<> and its children:
 *     circular, elliptical, and rectangular
 *     (location on perimeter by angle)
 *     In "schematics.round.cpp"
 * (2) 'oneline' (1-dimensional line) and 'twoline'
 *     Actually, a twoline built by compounding two oneline's.
 *     Points are produced through interpolation
 *     In "schematics.line.cpp"
 * (3) 'ic_side', for an Integrated Circuit Side
 *     It (protect-ly) inherits from 'twoline'
 *     Points are located through a whole number index
 *     In "schematics.ic.cpp"
 * (4) 'ic', an IC with pins on all four sides,
 *     'vic', an IC with pins on   vertical sides, and
 *     'hic', an IC with pins on horizontal sides,
 *     In "schematics.ic.cpp"
 * NOTE: An 'ic_rectangle' can be defined by compounding ic_side's.
 * TODO:
 * (1) define a non-Axis parallel rectangular
 * (2) handle negative constructor parameters in rectangular<>
 * (3) define a rectangle with (x,y) being the coordinates of its top left-hand corner
 * (4) define 'ic'
 * (5) define poliline<>, then arrow<>
 */

#endif
