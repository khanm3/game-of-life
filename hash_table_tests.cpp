#include "hash_table.h"
#include "unit_test_framework.h"

#include <iostream>
#include <utility>

using namespace std;

TEST(test_map_size) {
    Map<int, int> map;
    map[0];
    map[1];
    ASSERT_EQUAL(map.size(), 2);
}

TEST(test_map_key_value_pair) {
    Map<int, int> map;
    map[0] = 1;
    ASSERT_EQUAL(map[0], 1);
}

TEST(test_map_unique_keys) {
    Map<int, int> map;
    map[0] = 1;
    map[0] = 2;
    ASSERT_EQUAL(map.size(), 1);
}

TEST(test_map_contains) {
    Map<int, int> map;
    map[0];
    ASSERT_TRUE(map.contains(0));
    ASSERT_FALSE(map.contains(1));
}

TEST(test_map_clear) {
    Map<int, int> map;
    map[0] = 100;
    map.clear();
    ASSERT_EQUAL(map.size(), 0);
    ASSERT_EQUAL(map[0], 100); // tests private interface
}

TEST(test_map_grow) {
    Map<int, int> map;
    map[0];
    map[1];
    map[2];
    ASSERT_EQUAL(map.size(), 3);
}

TEST(test_map_iteration) {
    Map<int, int> map;
    map[0] = 10;
    map[1] = 11;
    map[2] = 12;
    for (auto it = map.begin(); it != map.end(); ++it) {
        pair<int, int> entry = *it;
        cout << entry.first << ":" << entry.second << " ";
    }
    cout << endl;
}

TEST_MAIN()
