#include <sstream>
#include "life.h"
#include "unit_test_framework.h"

using namespace std;

TEST(test_life_add_rle_glider) {
    istringstream is(
        "#N Glider\n"
        "#O Richard K. Guy\n"
        "#C The smallest, most common, and first discovered spaceship. "
        "Diagonal, has period 4 and speed c/4.\n"
        "#C www.conwaylife.com/wiki/index.php?title=Glider\n"
        "x = 3, y = 3, rule = B3/S23\n"
        "bob$2bo$3o!\n"
    );

    ostringstream os;

    string correct =
    ".O.\n"
    "..O\n"
    "OOO\n";

    Life life;
    life.add_rle(is, 0, 0);

    life.print(os);

    ASSERT_EQUAL(os.str(), correct);
}

TEST(test_life_glider_print_ten_generations) {
    istringstream is(
        "#N Glider\n"
        "#O Richard K. Guy\n"
        "#C The smallest, most common, and first discovered spaceship. "
        "Diagonal, has period 4 and speed c/4.\n"
        "#C www.conwaylife.com/wiki/index.php?title=Glider\n"
        "x = 3, y = 3, rule = B3/S23\n"
        "bob$2bo$3o!\n"
    );

    Life life;
    life.add_rle(is, 0, 0);

    cout << "Generation 0" << endl;
    life.print(cout);
    cout << endl;

    for (int i = 1; i <= 10; ++i) {
        cout << "Generation " << i << endl;
        life.progress();
        life.print(cout);
        cout << endl;
    }
}

TEST_MAIN()
