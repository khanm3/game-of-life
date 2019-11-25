#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <utility>
#include "Map.h"
#include "Set.h"

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

private:
  // key type
  struct Pos {
    int x;
    int y;

    bool operator==(Pos other) const {
      return x == other.x && y == other.y;
    }
  };

  // hash functor for Pos
  struct PosHash {
    std::size_t operator()(Pos pos) const {
      return static_cast<std::size_t>(97 * pos.x + 199 * pos.y);
    }
  };

  int minx; // x-coordinate of min pos

  int miny; // y-coordinate of min pos

  int maxx; // x-coordinate of max pos

  int maxy; // y-coordinate of max pos

  Set<Pos, PosHash> set1;  // set 1

  Set<Pos, PosHash> set2;  // set 2

  Set<Pos, PosHash> *grid; // the set that this points to contains the
                           // state of the life object

  Set<Pos, PosHash> *aux;  // the set that this points to is used for auxiliary
                           // calculations

  Map<Pos, int, PosHash> counter; // keeps track of counts

  //EFFECTS: updates the coordinates of the min and max positions, if the
  //         given coordinates has values which exceed the current ones
  void update_minmax(Pos pos);

  //EFFECTS: returns the number of living cells neighboring the the cell
  //         at the given position
  int grid_get_num_neighbors(Pos pos) const;

  //REQUIRES: pos points to a living cell
  //EFFECTS: inserts the cell at the given position into *aux if it has
  //         exactly three living neighbors
  void grid_update_cell(Pos pos);

  //EFFECTS: inserts into counter the key-value pair (pos, 1) if pos is not
  //         already in counter, otherwise increments the integer mapped
  //         to by pos by one
  void counter_increment_cell(Pos pos);

  //REQUIRES: pos points to a living cell
  //EFFECTS: increments the counts of all cells neighboring the cell at the
  //         given position
  void counter_increment_neighbors(Pos pos);
};

std::ostream & operator<<(std::ostream &os, Life &life);

#endif
