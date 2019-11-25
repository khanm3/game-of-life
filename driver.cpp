#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Life.h"

using namespace std;

bool is_number(string &s) {
  for (auto it = s.begin(); it < s.end(); ++it) {
    if (!isdigit(*it)) {
      return false;
    }
  }
  return true;
}

int num_generations(string &input) {
  if (input == "") {
    return 1;
  }
  else if (is_number(input)) {
    int n = stoi(input);

    return n > 0 ? n : 0;
  }
  else {
    return 0;
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: ./interactive.exe FILE" << endl;
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
