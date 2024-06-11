CLANG     = clang++ -std=c++2b
Gplusplus =     c++ -std=c++23
%: %.cpp
	c++    -std=c++23 $<  -o $@

save_to_github:
	git push svg main

schematics.label: schematics.label.test.cpp schematics.label.h svg.h
	c++ -std=c++23 $<  -o $@
schematics.rectangle: schematics.rectangle.test.cpp schematics.rectangle.h svg.h
	c++ -std=c++23 $<  -o $@
schematics.line: schematics.line.test.cpp schematics.line.h svg.h
	c++ -std=c++23 $<  -o $@
schematics.block: schematics.block.test.cpp schematics.rectangle.h svg.h
	c++ -std=c++23 $<  -o $@
schematics.round-and-arrow: schematics.round-and-arrow.test.cpp svg.h schematics.round.h schematics.arrow.h
	c++ -std=c++23 $<  -o $@
schematics.ic: schematics.ic.test.cpp svg.h schematics.ic.h
	c++ -std=c++23 $<  -o $@
schematics.svg.arc: schematics.svg.arc.test.cpp svg.h schematics.svg.arc.h
	c++ -std=c++23 $<  -o $@
segment: segment.test.cpp svg.h segment.h schematics.twoport.h
	c++ -std=c++23 $<  -o $@
schematics.twoport: schematics.twoport.test.cpp svg.h segment.h schematics.twoport.h
	c++ -std=c++23 $<  -o $@

%.test: %.test.cpp %.h
	g++ -std=c++23 $<  -o $@
%.o: %.cpp
	g++ -c -std=c++17 $<

EXECUTABLES = schematics.rectangle schematics.line schematics.block schematics.round schematics.ic schematics.svg.arc schematics.round-and-arrow segment schematics.label

clean_executables:
	$(RM) $(EXECUTABLES)
clean_all_but_html:
	$(RM) a.out *.test *.o
	$(RM) $(EXECUTABLES)

clean_all:
	$(RM) test.html test-arc.html
	$(RM) a.out *.test *.o
	$(RM) $(EXECUTABLES)
