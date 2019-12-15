#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include "Life.h"

using namespace std;

void print_info(Life &life) {
  cout << "size\t" << life.size() << endl;
  cout << "dims\t" << life.width() << "x" << life.height() << endl;
  cout << endl;
}

int main(int argc, char **argv) {
  // parse arguments
  if (argc < 3 || argc > 4) {
    cout << "Usage: timer.exe PATTERN_FILENAME NUM_ITERATIONS [--print-info]"
         << endl;
    return 1;
  }

  bool print_info_flag = false;
  if (argc == 4) {
    if (strcmp(argv[3], "--print-info") == 0) {
      print_info_flag = true;
    }
    else {
      cout << "Usage: timer.exe PATTERN_FILENAME NUM_ITERATIONS [--print-info]"
           << endl;
      return 4;
    }
  }

  int iter = atoi(argv[2]);

  if (iter == 0) {
    cout << "Error: number of iterations must be a positive integer" << endl;
    return 2;
  }

  ifstream fin(argv[1]);
  if (!fin.is_open()) {
    cout << "Error: could not open " << argv[1] << endl;
    return 3;
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
  auto time = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();

  if (print_info_flag) {
    print_info(life);
  }

  cout << "time\t" << time << "ms" << endl;
}
