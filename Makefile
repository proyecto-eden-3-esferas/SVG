CLANG     = clang++ -std=c++2b
Gplusplus =     c++ -std=c++23
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
metapost.curves.test: metapost.curves.test.cpp metapost.curves.h schematics.angle.h
	c++ -std=c++23 $<  -o $@

%.test: %.test.cpp %.h
	g++ -std=c++23 $<  -o $@
%.o: %.cpp
	g++ -c -std=c++17 $<

EXECUTABLES = schematics.rectangle schematics.line schematics.block schematics.round schematics.ic schematics.svg.arc schematics.round-and-arrow segment schematics.label schematics.labeled_block schematics.sq_polyline-and-block schematics.twoport schematics.transistor schematics.capacitor schematics.sq_polyline metapost.curves.test

clean_executables:
	$(RM) $(EXECUTABLES)
clean_all_but_html:
	$(RM) a.out *.test *.o
	$(RM) $(EXECUTABLES)

clean_all:
	$(RM) test.html test-arc.html
	$(RM) a.out *.test *.o
	$(RM) $(EXECUTABLES)
