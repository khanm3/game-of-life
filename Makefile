CXX = g++

CXXFLAGS = -Wall -Werror -pedantic --std=c++11 -g

hash_table_tests.exe: hash_table_tests.cpp hash_table.h
	$(CXX) $(CXXFLAGS) $< -o $@

gosperglidergun: driver.exe gosperglidergun.rle
	./driver.exe < gosperglidergun.rle

glider: driver.exe glider.rle
	./driver.exe < glider.rle

driver.exe: life.cpp driver.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@


.PHONY: clean
clean:
	rm -rvf *.exe
