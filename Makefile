CXX = g++

CXXFLAGS = -Wall -Werror -pedantic --std=c++11 -g

test: Map_tests.exe Set_tests.exe Life_tests.exe
	./Map_tests.exe
	./Set_tests.exe
	./Life_tests.exe

Map_tests.exe: Map_tests.cpp Map.h
	$(CXX) $(CXXFLAGS) $< -o $@

Set_tests.exe: Set_tests.cpp Set.h
	$(CXX) $(CXXFLAGS) $< -o $@

Life_tests.exe: Life_tests.cpp Life.cpp Life.h
	$(CXX) $(CXXFLAGS) $^ -o $@

gosperglidergun: driver.exe gosperglidergun.rle
	./driver.exe < gosperglidergun.rle

glider: driver.exe glider.rle
	./driver.exe < glider.rle

driver.exe: driver.cpp Life.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@


.PHONY: clean
clean:
	rm -rvf *.exe
