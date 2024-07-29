# SVG

**ESPAÑOL:** SVG es un lenguaje sencillo para dibujar formas en una página web mediante órdenes. Me queda por redactar una introducción y explicación detallada en castellano. [Este directorio](https://github.com/proyecto-eden-3-esferas/SVG/) contiene ejemplos de páginas web (`.html`), código fuente en C++ (`.h` y, para pruebas y prototipos, `.cpp`)

**ENGLISH:** [This web directory](https://github.com/proyecto-eden-3-esferas/SVG/) contains SVG examples, templates, a Makefile for linux and cursory tutorials - for block diagrams, electronic schematics, music notation, flow charts etc. Some SVG images should be generated by means of code (C++).


## Sections

- General TODOs

- A Geometry Library

- Diagrammes, Schematics and Electronics

- Diagrammes, Schematics and Electronics TODOs

- Music Notation TODOs

- Inclusion of SVG Files



## General TODOs

[ ] bool shape::is_in(X,Y)
[ ] angle_addressable::svg_label_unclosed(OSTREAM&, STRINGVIEW)
[x] Change return type of SVG functions from OUTSTREAM& to void.
[x] Comment out `return o;`
    through `sed --in-place 's/^  return o;/  \/\/return o; \/\/ void return type/g' *.h *.cpp`
[x] Test the thus modified files

[ ] signals four narrowing conversions from int to double, as in `((-(i + 1)) * 10)`

[ ] Write buffer, then diode, then schottky...
[ ] Write multiplexer
[ ] Write Arithmetic-Logic Unit (ALU), possibly derived from class block

[x] A segment class (same interface as `boost::geometry::model::segment`)

[x] Arrows (from `class polygon`?) To be named `solid_arrowhead` and `slim_arrowhead`. What about their being derived from a `triangle` class, itself derived from `angle_addressable`? Or the other way round: derive other triangular schematic symbols (diodes, buffers, OpAmp's etc) from `solid_arrowhead`.


[x] There is some code duplication in class `ic`, you see? Look at the following member prototypes:
```
virtual float_t xperim(size_t idx) const;
virtual float_t yperim(size_t idx) const;
enum facing {lt, bt, rt, tp};
virtual facing faces(size_t idx) const;
```
Now, the implementations of `xperim(IDX)` and `yperim(IDX)` should use `virtual facing faces(size_t idx)`. Also, if `{x|y}perim(IDX)` are so defiend, only `faces(IDX)` needs to be virtual.

[x] block should be tested through members {x|y}perim(IDX)

[ ] Add `FLOAT raise` parameter to global function specialization:

[ ] In "schematics.sq_polyline.h", write classes that take start and end points by reference. Name them `ref_??_polyline`...

```
template<typename F = double, typename OUT = std::ostream>
OUT & add_svg_unclosed(const labeled_block<F>& lblk, OUT& o = std::cout)
```
so as to raise the baseline of the labels above the lines connecting to the ports on `lblk`.

Actually, this is effected by *subtracting* `raise` from the y coordinate.

[x] ic should be derived from block, which will take some re-coding

[ ] The text in labels is not filled with black. It this a matter of styling ala CSS?


[ ] global function `OUT & add_svg_unclosed(const twoport<FLOAT,POINT>& tp, OUT& o = std::cout)` (in *schematics.twoport.h*) prints a caption, then draws a rectangle. To avoid duplication of code I have to create a temporary `label` object from the `twoport` parameter, as I explain in a comment in the source file.

One solution is for `twoport` to be derived from `label` or to *contain* a `label`. And it is a *scalable* solution: just think about all the labels that a `block` in a block diagram or an `ic` in a schematic diagram might need.

No, as regards `block`'s, I want them to hold one std::string per port (ports are drawn as pins or as the start of lines on the rectangle that matches them). Exactly, `block`'s are large objects in memory, are likely to be used often, and will probably have a lot of children (will probably be derived from often).

[ ] Perhaps the rule for pin placement on a `block`'s side (which calculates its *x* and *y* coordinates) should be made virtual and still a default implementation be provided.

[ ] A bezier class, to be derived from class `segment`

[ ] An arc class, to be derived from class `segment` (a same functionality class, `svg_arc`, has already been implemented in "schematics.svg.arc.h")

[ ] Transistor as a circle, derived from `class circular`. It was being implemented in "schematics.round.test.cpp" and might move into a file of its own, say "schematics.transistor.h")

[ ] `class twoport` is currently defined in its own file ("schematics.twoport.h") and tested in "segment.test.cpp" because it is derived from segment.

[ ] `slim_arrowhead::rotate_to(ABSOLUTE_ANGLE)` and `slim_arrowhead::rotate_by(RELATIVE_ANGLE)` work as if angles grew clockwise. This is ultimately due to the fact that in SVG the *y* coordinate grows downwards.

[x] Two-Ports: these might bear a label with their function(resistor, inductor, capacitor, diode, fuse, switch etc.) and their drawings might be completed afterwards. To be derived from class `segment`, to which a `width` or a `rel_width` is added. (A relative width says how wide the rectangle is compared to its length. Using relative widths makes it easier to calculate the corners of the rectangle.)

[x] Implement `float_type twoport::get_angle() const`

[x] Labels: delve into attributes of the svg::text element as well as svg::tspan contained in an svg::text element


[x] static members `angle_addressable::deg_to_rads(FLOAT)` and `angle_addressable::rads_to_deg(FLOAT)`
    should be renamed to
    `angle_addressable::deg_to_rad(FLOAT)` and `angle_addressable::rad_to_deg(FLOAT)` for consistency.
    (just change "rads" to "rad")

[x] Some point classes sharing their interface with boost::geometry for future interoperability. "point_xyz.h" unwritten yet.

[x] Blocks

[x] Inclusion of SVG Files (See longish section "Inclusion of SVG Files" below, in here file "README.md")




## A Geometry Library

### The Class Hierarchy

- Global functions in *svg.h*

  - OUT& open_svg(OUT& o, F w = 200.0, F h = 200.0,
                  STROKE = "black",
                  FILL = "gray",
                  FILL-OPACITY = 0.5);
  - OUT& open_svg_path_p(OUT& o);
  - OUT& close_svg_path(OUT& o = std::cout);
  - OUT & close_standalone_tag(OUT& o = std::cout);
  - OUT & add_svg_unclosed(const T& t, OUT& o = std::cout);
  - OUT & add_svg(const T& t, OUT& o = std::cout);

- Classes for straight 1-D and 2-D lines, polylines and polygons in *schematics.line.h*

- Class `rectangle` in *schematics.rectangle.h* is an SVG rectangle and the parent of classes `block` and `ic` in *schematics.ic.h*, with children `vic` (vertical IC) and `hic` (horizontal IC)

- Class `twoport` is currently derived from `segment` in *segment.h*

- In *schematics.arrow.h* are defined `slim_arrowhead`, derived from `circular` (in order to use cx, cy, r etc.), and its trivial child `solid_arrowhead`

- Classes in *schematics.round.h* (`circular`, `elliptical`, and `rectangular`) are derived from `angle_addressable` in *schematics.angle.h*. These derived classes produce x,y coordinates through members `xperim(RADS)` and `yperim(RADS)`.


### Classes and Functions with the Same Interface as those in Boost Geometry

I set out to code some classes and functions with the same interface as those in Boost Geometry. That will automatically make all calls relieant on these classes compatible with Boost Geometry.

These classes are to be held in files without a `schematics` prefix.


### For SVG, but also for PostScript, among other formats


### Following SVG Structure

If you want a C++ library to handle objects meant to be turned into SVG shapes, then why not write classes that follow SVG structure closely? If a circle has a radius(r), and two coordinates for its centre, then it would be straightforward to implement your SVG circle class with member variables {r, cx, cy}

### Points and Rectangles

One of the first items one will need is a point class, followed closely by rectangle class...

### Segments

> In geometry, a line segment is a part of a line that is bounded by two distinct end points, and contains every point on the line between its end points.

(Wikipedia)

### Boost.Geometry

The prestigious, STL-compatible headers-only Boost library contains Geometry, a geometry library. To use Boost.Geometry one needs to comply with some rules. You can write your own classes, but for them to interoperate with the library you need to register them. Whenever you build an executable, the tool chain spends some 12 seconds doing some internal paperwork. And since it is headers-only, separate compilation proves very work-intensive: you have to write the header files plus code to compile every foreseeable instantiation of template classes and template functions.


## Diagrammes, Schematics and Electronics

Components are divided into (1) those located or placed by their centre of gravity (circles, ellipses..., all of them children of angle_addressable<>) and (2) those located by their upper left-hand corner coordinates, such as rectangle and its derived classes (block, ic...)

### Blocks and IC's

An IC has a fixed separation between pins, whereas on a block in a block diagram the separation should discretionary.

Both `ic` (in *schematics.ic.h*) and `block` (in *schematics.rectangle.h*) are derived from `rectangle`.

### Diagrammes, Schematics and Electronics TODOs

[ ] develop block diagrams

[ ] triangles for op-amps, buffers, diodes... (with a centre cx,cy, and therefore a child of angle_addressable<>, or with upper left-hand corner coordinates, and therefore a child of rectangle<>)

[X] coils (see file "SVG-coil.html")

[ ] Resistors

[ ] Transistors

[ ] Buses (actually, bus-markers as skewed segments across lines with a multiplicity number, or some other scheme like increased stroke-width)

## Music Notation TODOs

[x] Pentagrams, tetragrams...

[ ] Notes


## Inclusion of SVG Files

Sometimes you will want to view SVG drawings on their own, as an independent file in your web browser or SVG viewer. Some other times, you will want your graphic to be integrated in a larger document, which contains paragraphs of text, or other content that SVG cannot display easily.

Here, we shall be discussin various ways of integrating SVG within HTML and other document types. There are two
fundamental approaches:

(1) you can include the image within the HTML markup in an `<img>` element (recommended when the image is a fundamental part of the page’s content),

(2) or you can insert the image as a CSS style property of another element (recommended when the image is primarily decorative).

### Drawbacks to including SVG as an image

- The image will be rendered (rasterized) separately from the main web page, and there is no way to
communicate between the two.

- Styles defined on the main web page will have no effect on the SVG. You may need to define a default font size within your SVG code if your graphic includes text or defines lengths relative to the font size.

- Furthermore, scripts running on the main web page will not be able to discover or modify any of the SVG’s document structure.

- Most web browsers will not load files referenced from an SVG used as an image; this includes other image files, external scripts, and even webfont files. Depending on the browser and the user’s security settings, scripts defined within the SVG file may not run, and URL fragments (the part of the URL after #, which indicates which part of the file you’re interested in) may be ignored.

On the bright side, animation is supported within images (in browsers that support it in SVG in general).

### Including SVG in an `<img>` Element

The HTML `<img>` element defines a space into which the browser should draw an external image file. The image file to use is specified with the src (source) attribute. Including an SVG image within an `<img>` element is as simple as setting the source to point to the location of your SVG file.

You should also
provide a description with an alt and/or a title attribute so that users
who cannot see the image can still understand what it represents.
For example:
```
<img src="cat.svg" title="Cat Image"
alt="Stick Figure of a Cat" />
```

The height and width of the image can be set using attributes or CSS properties (which take precedence). Other CSS properties control the placement of the image within the web page. If you do not specify dimensions for the `<img>` element, the intrinsic dimensions of the image file are used. If you specify only one of height or width, the other dimension is scaled proportionally so that the aspect ratio (the ratio of width to height) matches the intrinsic dimensions.

If the root `<svg>` element in the file has explicit height and width attributes, those are used as the intrinsic dimensions of the file. If one of height or width is specified, but not both, and the `<svg>` has a viewBox attribute, then the viewBox will be used to calculate the aspect ratio and the image will be scaled to match the specified dimension. Otherwise, if the `<svg>` has a viewBox attribute but no dimensions, then the height and width parts of the viewBox are treated as lengths in pixels.

If neither the `<img>` element nor the root `<svg>` element has any information about the size of the image, the browser should apply the default HTML size for embedded content, 150 pixels tall and 300 pixels wide, but it is best not to rely on this.

### Including SVG in CSS

Various CSS style properties accept a URL to an image file as a
value. The most commonly used is the background-image property,
which draws the image (or multiple layered images) behind the text
content of the element being styled.

By default, a background image is drawn at its intrinsic dimensions
and repeated in both the horizontal and vertical direction to fill up
the dimensions of the element.

If there are no intrinsic dimensions, the SVG will be scaled to 100% of the height and width of the element. The size can be set explicitly using the background-size property, and repeat patterns and image position can be set using background-repeat and background-position:

```
div.background-cat {
  background-image: url("cat.svg");
  background-size: 100% 100%;
}
```
In addition to background images, SVG files can be used in CSS as a list-image (used to create decorative bulleted lists) or border-image (used to create fanciful borders).


### SVG as an Application

To integrate an external SVG file into an HTML page without the
limitations of treating the SVG as an image, you can use an embedded object.

The `<object>` element is the general-purpose way of embedding external files in HTML (version 4 and up) and XHTML documents. It can be used to embed images, similar to `<img>`, or to embed separate HTML/XML documents, similar to an `<iframe>`. More importantly, it can also be used to embed files of any arbitrary type, so long as the browser has an application (a browser plug-in or extension) to interpret that file type. Using an object to embed your SVG can make your graphic available to users of older browsers that cannot display SVG directly, so long as they have an SVG plug-in.

The `type` attribute of the `<object>` element indicates the type of file you’re embedding. The attribute should be a valid Internet media type (commonly known as a MIME type). For SVG, use `type="image/svg+xml".`

The browser uses the file type to determine how (or if) it can display the file, without having to download it first. The location of the file itself is specified by the data attribute. The `alt` and `title` attributes work the same as for images.

Any content between the start tag and the end tag the two will be rendered only if the object data itself cannot be displayed. This can be used to specify a fallback image or some warning text to display if the browser doesn’t have any way of displaying SVG.

The following code displays both a text explanation and a raster image in browsers that don’t support SVG:
```
<object data ="cat.svg" type="image/svg+xml"
        title="Cat Object" alt="Stick Figure of a Cat" >
  <!-- As a fallback, include text or a raster image file -->
  <p>No SVG support! Here's a substitute:</p>
  <img src="cat.png" title="Cat Fallback"
       alt="A raster rendering of a Stick Figure of a Cat" />
</object>
```

### `<object>` versus `<embed>`

Prior to the introduction of the `<object>` element, some browsers used the non-standard `<embed>` element for the same purpose. It has now been adopted into the standards, so you can use `<embed>` instead of an `<object>` element if you’re worried about supporting older browsers. For even wider support, use `<embed>` as the fallback content inside the `<object>` tags.

There are two important differences between `<embed>` and `<object>`: first, the source data file is specified using a `src` attribute, not `data`; second, the `<embed>` element cannot have any child content, so there is no fallback option if the embed fails.

Although not adopted into the specifications, most browsers also support the optional `pluginspage` attribute on `<embed>` elements, which gives the URL of a page where users can download a plug-in for rendering the file type if they don’t have one installed.

When you include an SVG file as an embedded object (whether with `<object>` or `<embed>`), the external file is rendered in much the same way as if it was included in an `<img>` element: it is scaled to fit the width and height of the embedding element, and it does not inherit any styles declared in the parent document.

Unlike with images, however, the embedded SVG can include external files, and scripts can communicate between the object and the parent page.

### Foreign Objects in SVG

One way of mixing content is to insert sections of HTML (or other) content within your SVG. The SVG specifications define a way of embedding such “foreign” content within a specified region of the graphic.

The `<foreignObject>` element defines a rectangular area into which the web browser (or other SVG viewer) should draw the child XML content. The browser is responsible for determining how to draw that content. The child content is often XHTML (XML-compliant HTML) code, but it could be any form of XML that the SVG viewer is capable of displaying. The type of content is defined by declaring the XML namespace on the child content using the `xmlns` attribute.

The rectangular drawing area is defined by the `x`, `y`, `width`, and `height` attributes of the `<foreignObject>` element, in a manner similar to the `<use>` or `<image>` elements.

The rectangle is evaluated in the local SVG coordinate system, and so is subject to coordinate system transformations or other SVG effects. The child XML document is rendered normally into a rectangular frame, and then the result is manipulated like any other SVG graphic.

The `<foreignObject>` element has great potential for creating mixed SVG/XHTML documents, but is currently not well supported. Internet Explorer (at least up to version 11) does not support it at all, and there are bugs and inconsistencies in the other browsers’ implementations.

If you want to define fallback content in case the SVG viewer cannot display foreign content, you can use the `<switch>` element in combination with the `requiredFeatures` attribute, as shown in the example below.

The `<switch>` element instructs the SVG viewer to draw only the first direct child element (and all of its children) for which the `requiredFeatures`, `requiredExtensions`, and `systemLanguage` test attributes either evaluate to true or are absent. When testing for required features, you use one of the URL strings given in the specifications; `<foreignObject>` support is part of the Extensibility feature.

Unfortunately, there is no consistent, cross-browser way to specify which type of foreign object is required. Maybe you want to use the MathML language to display a formula for your chart, with a plain-text version as a fallback for browsers that don’t understand MathML. The `requiredExtensions` attribute is supposed to indicate what type of added capability is needed, but the SVG 1.1 specifications did not clearly describe how the extensions should be identified— except to say that it should be with a URL. Firefox uses the XML namespace URL, but other browsers do not.

#### Example: the `<foreignObject>` element, with a `<switch>`
```
<g transform="skewX(20)">
  <switch>
  <!-- select one child element -->
    <foreignObject x="1em" y="25%" width="10em" height="50%"
      requiredFeatures=
      "http://www.w3.org/TR/SVG11/feature#Extensibility">
      <body xmlns="http://www.w3.org/1999/xhtml">
        <p>This is an XHTML paragraph embedded within an SVG!
        So this text will wrap nicely around multiple lines,
        but it will still be skewed from the SVG transform.</p>
      </body>
    </foreignObject>
    <text x="1em" y="25%" dy="1em">This SVG text won't wrap,
    so it will get cut off...</text>
  </switch>
</g>
```
