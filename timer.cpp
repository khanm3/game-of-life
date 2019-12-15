#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <cstring>
#include "Life.h"

using namespace std;

void usage() {
  cout << "Usage: timer.exe PATTERN_FILENAME NUM_ITERATIONS [--print-info]"
       << endl;
}

void print_info(Life &life) {
  cout << "size\t" << life.size() << endl;
  cout << "dims\t" << life.width() << "x" << life.height() << endl;
  cout << endl;
}

int main(int argc, char **argv) {
  // parse arguments
  if (argc < 3 || argc > 4) {
    usage();
    return 1;
  }

  bool print_info_flag = false;
  if (argc == 4) {
    if (strcmp(argv[3], "--print-info") == 0) {
      print_info_flag = true;
    }
    else {
      usage();
      return 1;
    }
  }

  int iter;

  try {
    iter = stoi(argv[2]);
  }
  catch (invalid_argument &e) {
    cout << "Error: converting " << argv[2] << " to an int: "
         << e.what() << endl;
    return 1;
  }

  if (iter < 1) {
    cout << "Error: number of iterations must be a positive integer" << endl;
    return 1;
  }

  ifstream fin(argv[1]);
  if (!fin.is_open()) {
    cout << "Error: could not open " << argv[1] << endl;
    return 1;
  }

  // conduct test
  Life life;
  life.add_rle(fin, 0, 0);

  if (print_info_flag) {
    print_info(life);
  }

  auto t1 = chrono::high_resolution_clock::now();

  for (int i = 0; i < iter; ++i) {
    life.progress();
  }

  auto t2 = chrono::high_resolution_clock::now();
  auto diff = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
  auto m = diff / 60000;
  auto s = (diff % 60000) / 1000;
  auto ms = diff % 1000;

  if (print_info_flag) {
    print_info(life);
  }

  cout << "time\t" << m << "m" << s << ".";
  cout.fill('0');
  cout.width(3);
  cout << ms << "s" << endl;
  
}
