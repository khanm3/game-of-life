#include <string>
#include <cctype>
#include <limits>
#include "Life.h"

using namespace std;

Life::Life()
  : minx(0), miny(0), maxx(0), maxy(0), grid(&set1), aux(&set2) { }

void Life::progress() {
  // reset min positions
  minx = numeric_limits<int>::max();
  miny = numeric_limits<int>::max();
  maxx = numeric_limits<int>::min();
  maxy = numeric_limits<int>::min();

  // for every living cell, update it and increment its neighbors
  for (auto it = grid->begin(); it != grid->end(); ++it) {
    Pos pos = *it;
    grid_update_cell(pos);
    counter_increment_neighbors(pos);
  }

  // process entries in counter to find dead cells that become alive
  for (auto it = counter.begin(); it != counter.end(); ++it) {
    pair<Pos, int> entry = *it;
    if (entry.second == 3 && !aux->contains(entry.first)) {
      aux->insert(entry.first);
      update_minmax(entry.first);
    }
  }

  // if there are no entries in the new state set, then min positions should
  // be re-reset accordingly
  if (aux->size() == 0) {
    minx = miny = maxx = maxy = 0;
  }

  // switch grid and aux pointers
  if (grid == &set1) {
    grid = &set2;
    aux = &set1;
  }
  else {
    grid = &set1;
    aux = &set2;
  }

  // clear aux and counter
  aux->clear();
  counter.clear();
}

void Life::add_rle(istream &is, int x, int y) {
  // skip comments
  char c;
  string s;
  while (is.get(c) && c == '#') {
    getline(is, s);
  }

  // skip "="
  is >> s;

  // get integer up to ","
  getline(is, s, ',');

  // skip "y ="
  is >> s >> s;

  // get integer up to ","
  getline(is, s, ',');

  // skip "rule = B3/S23"
  is >> s >> s >> s;

  // parse rle
  int x0 = x, count = 1;

  while (is.get(c)) {
    // add *count* alive cells
    if (c == 'o') {
      for (int i = 0; i < count; ++i) {
        add(x + i, y);
      }

      x += count;
      count = 1;
    }
    // skip *count* cells
    else if (c == 'b') {
      x += count;
      count = 1;
    }
    // skip *count* lines
    else if (c == '$') {
      x = x0;
      y += count;
      count = 1;
    }
    // parse run count
    else if (isdigit(c)) {
      s = c;
      while (isdigit(is.peek())) {
        is.get(c);
        s += c;
      }
      count = stoi(s);
    }
  }
}

void Life::add(int x, int y) {
  grid->insert({x, y});
  update_minmax({x, y});
}

bool Life::get(int x, int y) const {
  return grid->contains({x, y});
}

pair<int, int> Life::min_pos() const {
  return {minx, miny};
}

pair<int, int> Life::max_pos() const  {
  return {maxx, maxy};
}

int Life::width() const {
  return maxx - minx + 1;
}

int Life::height() const {
  return maxy - miny + 1;
}

void Life::print(ostream &os) const {
  for (int y = miny; y <= maxy; ++y) {
    for (int x = minx; x <= maxx; ++x) {
      if (get(x, y)) {
        os << "O";
      }
      else {
        os << ".";
      }
    }
    os << endl;
  }
}

void Life::update_minmax(Pos pos) {
  int x = pos.x, y = pos.y;

  if (x < minx) {
    minx = x;
  }
  if (x > maxx) {
    maxx = x;
  }

  if (y < miny) {
    miny = y;
  }
  if (y > maxy) {
    maxy = y;
  }
}

int Life::grid_get_num_neighbors(Pos pos) const {
  int x = pos.x, y = pos.y;
  int count = 0;

  if (grid->contains({x - 1, y})) ++count;
  if (grid->contains({x + 1, y})) ++count;
  if (grid->contains({x - 1, y - 1})) ++count;
  if (grid->contains({x    , y - 1})) ++count;
  if (grid->contains({x + 1, y - 1})) ++count;
  if (grid->contains({x - 1, y + 1})) ++count;
  if (grid->contains({x    , y + 1})) ++count;
  if (grid->contains({x + 1, y + 1})) ++count;

  return count;
}

void Life::grid_update_cell(Pos pos) {
  int count = grid_get_num_neighbors(pos);

  if (count == 2 || count == 3) {
    aux->insert(pos);
    update_minmax(pos);
  }
}

void Life::counter_increment_cell(Pos pos) {
  if (!counter.contains(pos)) {
    counter[pos] = 1;
  }
  else {
    ++counter[pos];
  }
}

void Life::counter_increment_neighbors(Pos pos) {
  int x = pos.x, y = pos.y;

  counter_increment_cell({x - 1, y});
  counter_increment_cell({x + 1, y});
  counter_increment_cell({x - 1, y - 1});
  counter_increment_cell({x    , y - 1});
  counter_increment_cell({x + 1, y - 1});
  counter_increment_cell({x - 1, y + 1});
  counter_increment_cell({x    , y + 1});
  counter_increment_cell({x + 1, y + 1});
}

std::ostream & operator<<(std::ostream &os, Life &life) {
  life.print(os);
  return os;
}
