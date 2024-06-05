CLANG     = clang++ -std=c++2b
Gplusplus =     c++ -std=c++23
%: %.cpp
	c++    -std=c++23 $<  -o $@

save_to_github:
	git push svg main
schematics: schematics.test.cpp schematics.h schematics.svg.h
	c++ -std=c++23 $<  -o $@
schematics.block: schematics.block.test.cpp schematics.h schematics.svg.h
	c++ -std=c++23 $<  -o $@
schematics.round: schematics.round.test.cpp schematics.h schematics.svg.h schematics.round.h
	c++ -std=c++23 $<  -o $@
schematics.ic: schematics.ic.test.cpp schematics.h schematics.svg.h schematics.ic.h
	c++ -std=c++23 $<  -o $@
schematics.svg.arc: schematics.svg.arc.test.cpp schematics.h schematics.svg.h schematics.svg.arc.h
	c++ -std=c++23 $<  -o $@

%.test: %.test.cpp %.h
	g++ -std=c++23 $<  -o $@
%.o: %.cpp
	g++ -c -std=c++17 $<

clean:
	$(RM)  a.out *.test
	$(RM) schematics schematics.block schematics.round schematics.ic schematics.svg.arc test.html test-arc.html
