#include "Set.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_set_size) {
    Set<int> set;
    set.insert(0);
    set.insert(1);
    ASSERT_EQUAL(set.size(), 2);
}

TEST(test_set_unique_keys) {
    Set<int> set;
    set.insert(0);
    set.insert(0);
    ASSERT_EQUAL(set.size(), 1);
}

TEST(test_set_contains) {
    Set<int> set;
    set.insert(0);
    ASSERT_TRUE(set.contains(0));
    ASSERT_FALSE(set.contains(1));
}

TEST(test_set_clear) {
    Set<int> set;
    set.insert(0);
    set.clear();
    ASSERT_EQUAL(set.size(), 0);
}

TEST(test_set_grow) {
    Set<int> set;
    set.insert(0);
    set.insert(1);
    set.insert(2);
    ASSERT_EQUAL(set.size(), 3);
}

TEST(test_set_iteration) {
    Set<int> set;
    set.insert(0);
    set.insert(1);
    set.insert(2);

    for (auto it = set.begin(); it != set.end(); ++it) {
        int key = *it;
        cout << key << " ";
    }
    cout << endl;
}

TEST_MAIN()
