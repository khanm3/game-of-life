#ifndef SET_H
#define SET_H

#include "Map.h"

template <typename Key, typename Hash=std::hash<Key>>
class Set {
public:
  // iterator class over set elements
  //
  // iterators point to keys
  //
  // note that the key returned by a dereference is a copy
  class Iterator {
  private:
    friend class Set;

    typename Map<Key, bool, Hash>::Iterator it;

    Iterator(typename Map<Key, bool, Hash>::Iterator it) : it(it) { }

  public:
    Key operator*() const {
      std::pair<Key, bool> entry = *it;
      return entry.first;
    }

    Iterator & operator++() {
      ++it;
      return *this;
    }

    bool operator==(Iterator other) const {
      return it == other.it;
    }

    bool operator!=(Iterator other) const {
      return it != other.it;
    }
  };


private:
  // a set is represented by a map of the same key type and bool value type
  Map<Key, bool, Hash> map;


public:
  // EFFECTS: creates a set with initial capacity 4
  Set() { }

  // EFFECTS: returns the numbers of keys
  std::size_t size() const {
    return map.size();
  }

  // EFFECTS: returns true if the given key is in the set
  bool contains(Key key) const {
    return map.contains(key);
  }

  // EFFECTS: inserts the given key into the set
  void insert(Key key) {
    map[key];
  }

  // EFFECTS: removes all keys from the set
  // NOTE: clearing the set does not change its capacity
  void clear() {
    map.clear();
  }

  // EFFECTS: returns an iterator pointing to the first key in the set
  Iterator begin() const {
    return Iterator(map.begin());
  }

  // EFFECTS: returns an iterator pointing off the end of the set
  Iterator end() const {
    return Iterator(map.end());
  }
};

#endif
