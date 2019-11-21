#ifndef LIFE_H
#define LIFE_H

#include <iostream>

class Life {
 public:
  void add(int x, int y);
  void add_rle(std::istream &is, int x, int y);
};

#endif
