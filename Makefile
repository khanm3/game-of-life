CXX = g++

CXXFLAGS = -Wall -Werror -pedantic --std=c++11 -g

gosperglidergun: driver.exe gosperglidergun.rle
	./driver.exe < gosperglidergun.rle

glider: driver.exe glider.rle
	./driver.exe < glider.rle

driver.exe: life.cpp driver.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@


.PHONY: clean
clean:
	rm -rvf *.exe
