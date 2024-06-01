CLANG     = clang++ -std=c++2b
Gplusplus =     c++ -std=c++23
%: %.cpp
	c++    -std=c++23 $<  -o $@

save_to_github:
	git push svg main
schematics: schematics.test.cpp schematics.h schematics.svg.h schematics.round.h
	c++ -std=c++23 $<  -o $@

%.test: %.test.cpp %.h
	g++ -std=c++23 $<  -o $@
%.o: %.cpp
	g++ -c -std=c++17 $<

clean:
	$(RM)  a.out *.test schematics test.html
