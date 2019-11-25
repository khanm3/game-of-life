#include <string>
#include <cctype>
#include "life.h"

using namespace std;


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
