#ifndef LIFE_H
#define LIFE_H

#include <iostream>

class Grid {
 public:
  virtual void add(int x, int y);
  virtual void add_rle(std::istream &is, int x, int y) final;
};

#endif
