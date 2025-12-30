CLANG     = clang++ -std=c++2b
Gplusplus =     c++ -std=c++23
DropboxDir = ~/Dropbox


%: %.cpp
	c++    -std=c++23 $<  -o $@

save_to_github:
	git push svg main

schematics.angle.test: schematics.angle.test.cpp schematics.angle.h
	c++ -std=c++23 $<  -o $@
schematics.label: schematics.label.test.cpp schematics.label.h svg.h
	c++ -std=c++23 $<  -o $@
schematics.rectangle: schematics.rectangle.test.cpp schematics.rectangle.h svg.h
	c++ -std=c++23 $<  -o $@
schematics.line: schematics.line.test.cpp schematics.line.h svg.h
	c++ -std=c++23 $<  -o $@
schematics.round-and-arrow: schematics.round-and-arrow.test.cpp svg.h schematics.round.h schematics.angle.h schematics.arrow.h
	c++ -std=c++23 $<  -o $@
schematics.ic: schematics.ic.test.cpp svg.h schematics.ic.h
	c++ -std=c++23 $<  -o $@
schematics.svg.arc: schematics.svg.arc.test.cpp svg.h schematics.svg.arc.h
	c++ -std=c++23 $<  -o $@
segment: segment.test.cpp svg.h segment.h schematics.twoport.h
	c++ -std=c++23 $<  -o $@

schematics.twoport:   schematics.twoport.test.cpp   svg.h schematics.line.h schematics.angle.h schematics.twoport.h schematics.capacitor.h
	c++ -std=c++23 $<  -o $@
schematics.capacitor: schematics.twoport.test.cpp svg.h schematics.line.h schematics.angle.h schematics.twoport.h schematics.capacitor.h

schematics.block: schematics.block.test.cpp schematics.rectangle.h schematics.block.h svg.h
	c++ -std=c++23 $<  -o $@
schematics.labeled_block: schematics.labeled_block.test.cpp schematics.labeled_block.h schematics.rectangle.h schematics.block.h svg.h
	c++ -std=c++23 $<  -o $@
schematics.sq_polyline: schematics.sq_polyline.test.cpp schematics.sq_polyline.h schematics.vec_polyline.h svg.h
	c++ -std=c++23 $<  -o $@
schematics.sq_polyline-and-block: schematics.sq_polyline-and-block.test.cpp schematics.block.h schematics.sq_polyline.h schematics.vec_polyline.h svg.h
	c++ -std=c++23 $<  -o $@
schematics.transistor: schematics.transistor.test.cpp schematics.transistor.h schematics.fet.h schematics.label.h svg.h
	c++ -std=c++23 $<  -o $@

pair-as-2D-point.test: pair-as-2D-point.test.cpp pair-as-2D-point.h print-pair.h
	c++ -std=c++23 $< -o $@

point.test: point.test.cpp point.h
	c++ -std=c++23 $< -o $@

skel.test:  skel.test.cpp skel.h skel.cpp point.h
	c++ -std=c++23 $< -o $@
diagram.test:  diagram.test.cpp diagram.h diagram.cpp point.h
	c++ -std=c++23 $< -o $@
square_diagram.test:  square_diagram.test.cpp diagram.h diagram.cpp square_diagram.h point.h
	c++ -std=c++23 $< -o $@

schematics.round-graph.test: schematics.round-graph.test.cpp schematics.round.h schematics.line.h schematics.arrow.h schematics.angle.diagram.h
	c++ -std=c++23 $< -o $@

%.test: %.test.cpp %.h
	g++ -std=c++23 $<  -o $@


MP_POINT_COMMON_DEPS = mp_point.h svg.h geometry_2D.h pair-as-2D-point.h schematics.angle.h
MP_SPLINE_COMMON_DEPS = $(MP_POINT_COMMON_DEPS) mp_spline.h mp_spline.cpp


# mp_spline<> headers-only
mp_spline.test:   mp_spline.test.cpp mp_$(MP_SPLINE_COMMON_DEPS)
	c++ -std=c++23 $<  -o $@
mp_spline.%.test: mp_spline.%.test.cpp $(MP_SPLINE_COMMON_DEPS)
	c++ -std=c++23 $<  -o $@
# Infix "print-to-cout" causes compilation (of file containing main()) under switch PRINT_TO_COUT:
mp_spline.print-to-cout.test:   mp_spline.test.cpp $(MP_SPLINE_COMMON_DEPS)
	c++ -std=c++23 -DPRINT_TO_COUT $<  -o $@
mp_spline.%.print-to-cout.test: mp_spline.%.test.cpp $(MP_SPLINE_COMMON_DEPS)
	c++ -std=c++23 -DPRINT_TO_COUT $<  -o $@

# mp_spline<> separate compilation
mp_spline.o: mp_spline.ins.cpp $(MP_SPLINE_COMMON_DEPS)
	date
	c++ -c -std=c++23 $< -o $@
	date
mp_point.o: mp_point.ins.cpp mp_point.cpp $(MP_POINT_COMMON_DEPS)
	date
	c++ -c -std=c++23 $< -o $@
	date
mp_spline.test.o:   mp_spline.test.cpp $(MP_SPLINE_COMMON_DEPS)
	date
	g++ -DSEPARATE_COMPILATION -DPRINT_TO_COUT -c -std=c++23 $<
	date
mp_spline.%.test.o: mp_spline.%.test.cpp $(MP_SPLINE_COMMON_DEPS)
	date
	g++ -DSEPARATE_COMPILATION -DPRINT_TO_COUT -c -std=c++23 $<
	date



MP_COMMON_OBJ = mp_spline.o mp_point.o
# "mp_spline.sep.test.cpp" should be generated from "mp_spline.test.cpp" + macro SEPARATE_COMPILATION
mp_spline.sep.test:                    mp_spline.test.o                 $(MP_COMMON_OBJ)
	c++ -std=c++23                 mp_spline.test.o                 $(MP_COMMON_OBJ) -o $@
mp_spline.%.sep.test:                  mp_spline.%.test.o               $(MP_COMMON_OBJ)
	c++ -std=c++23                 mp_spline.%.test.o               $(MP_COMMON_OBJ) -o $@

# Executables that make an '%.svg file' (on execution) are built from 'mp_spline.make-%-svg.cpp'
mp_spline.make-%-svg.o: mp_spline.make-%-svg.cpp $(MP_SPLINE_COMMON_DEPS)
	date
	g++ -DSEPARATE_COMPILATION -DPRINT_TO_COUT -c -std=c++23 $< #-DSVG_FILE="%.svg"
	date
mp_spline.make-%-svg:   mp_spline.make-%-svg.o   $(MP_COMMON_OBJ)
	date
	c++ -std=c++23  $<   $(MP_COMMON_OBJ) -o $@
#	rm              $<
	date


mp_spline.make-complex-svg.o: mp_spline.make-complex-svg.cpp test-lines.two-vectors-of-lines.h $(MP_SPLINE_COMMON_DEPS)
	date
	g++ -DSEPARATE_COMPILATION -DPRINT_TO_COUT -c -std=c++23 $<
	date
mp_spline.make-complex-svg: mp_spline.make-complex-svg.o $(MP_COMMON_OBJ)
	date
	c++ -std=c++23      mp_spline.make-complex-svg.o $(MP_COMMON_OBJ) -o $@
#	rm                  mp_spline.make-complex-svg.o
	date

mp_spline.%.sep.print-to-cout.test:    mp_spline.%.print-to-cout.test.o $(MP_COMMON_OBJ)
	c++ -std=c++23 -DPRINT_TO_COUT mp_spline.%.print-to-cout.test.o $(MP_COMMON_OBJ) -o $@
# Pass macro DSEPARATE_COMPILATION when compiling object files:
%.print-to-cout.test.o: %.test.cpp


%.o: %.cpp
	date
	g++ -DSEPARATE_COMPILATION -DPRINT_TO_COUT -c -std=c++23 $<
	date


RESOLVE = xmllint --xinclude
svg.my-images.html: svg.my-images.inc.html *.svg
	$(RESOLVE) --output $@   $<


EXECUTABLES = schematics.rectangle schematics.line schematics.block schematics.round schematics.ic schematics.svg.arc schematics.round-and-arrow segment schematics.label schematics.labeled_block schematics.sq_polyline-and-block schematics.twoport schematics.transistor schematics.capacitor schematics.sq_polyline

EXECUTABLES_TEST = mp_spline.test mp_spline.sep.test pair-as-2D-point.test

#HTMLS =

clean_executables:
	$(RM) a.out *.test
	$(RM) $(EXECUTABLES)
	$(RM) mp_spline.make-*-svg
	$(RM) mp_spline.make-*-svg.o

clean_all_but_html:
	$(RM) a.out *.test *.o
	$(RM) $(EXECUTABLES)

clean_all:
	make clean_executables
	$(RM) *.o

save_to_Dropbox:
	cp --update *.html *.xhtml *.h *.cpp *.svg $(DropboxDir)/SVG/
