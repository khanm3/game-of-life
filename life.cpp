#include <string>
#include <cctype>
#include "life.h"

using namespace std;

Life::Life()
  : minx(0), miny(0), maxx(0), maxy(0), grid(&set1), aux(&set2) { }

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
  int width = stoi(s);

  // skip "y ="
  is >> s >> s;

  // get integer up to ","
  getline(is, s, ',');
  int height = stoi(s);

  // skip "rule = B3/S23"
  is >> s >> s >> s;

  // DEBUG: print values of x and y
  cout << "x = " << width << ", y = " << height << endl;

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
  cout << "Added (" << x << ", " << y << ")" << endl;

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
