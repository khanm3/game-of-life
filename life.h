#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <utility>

class Life {
  //OVERVIEW: object representing the Game of Life
public:
  // EFFECTS: creates an empty life object
  Life();

  //EFFECTS: progresses the automaton by one step
  void progress();

  //REQUIRES: is contains a pattern in RLE format
  //MODIFIES: is
  //EFFECTS:  adds the pattern contained in the given input stream to the
  //          grid; the top left corner of the pattern is placed at (x, y)
  void add_rle(std::istream &is, int x, int y);

  //EFFECTS: adds a living cell at (x, y), if there isn't one there already
  void add(int x, int y);

  //EFFECTS: returns true if there's a living cell at (x, y), false otherwise
  bool get(int x, int y) const;

  //EFFECTS: returns the position of the living cell with the smallest
  //         x and y coordinates (the top left corner of the grid)
  std::pair<int, int> min_pos() const;

  //EFFECTS: returns the position of the living cell with the largest
  //         x and y coordinates (the bottom right corner of the grid)
  std::pair<int, int> max_pos() const;

  //EFFECTS: returns the width of the grid (max_x - min_x)
  int width() const;

  //EFFECTS: returns the height of the grid (max_y - max_y)
  int height() const;

  //MODIFIES: os
  //EFFECTS : prints this object to the given output stream
  void print(std::ostream &os) const;
};

#endif
