#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Life.h"

using namespace std;

int num_generations(string &input) {
  if (input.empty()) {
    return 1;
  }

  try {
    return stoi(input);
  }
  catch (invalid_argument &e) {
    return 0;
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: driver.exe PATTERN_FILENAME" << endl;
    return 1;
  }

  ifstream fin(argv[1]);
  if (!fin.is_open()) {
    cout << "Error: could not open " << argv[1] << endl;
    return 2;
  }

  Life life;
  life.add_rle(fin, 0, 0);
  cout << "Generation 0" << endl;
  cout << life << endl;

  string s;
  int n = 0;
  while (getline(cin, s)) {
    int count = num_generations(s);

    if (count > 0) {
      for (int i = 0; i < count; ++i) {
        life.progress();
        ++n;
      }

      cout << endl;
      cout << "Generation " << n << endl;
      cout << life << endl;
    }
  }
}
