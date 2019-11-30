#ifndef MAP_H
#define MAP_H

#include <cassert>
#include <functional>
#include <utility>
#include <vector>

template <typename Key, typename Val, typename Hash=std::hash<Key>>
class Map {
private:
  // bucket holds key-value pairs, along with bucket type
  struct Bucket {
    bool filled = false;
    Key key;
    Val val;
  };

public:
  // iterator over map elements
  // 
  // iterators point to pairs whose 'first' member is the key, and 'second'
  // member is the value
  // 
  // note the value returned is a copy, not a reference
  class Iterator {
  private:
    friend class Map; // let Map access private members

    typename std::vector<Bucket *>::const_iterator it;

    Iterator(typename std::vector<Bucket *>::const_iterator it)
      : it(it) { }
  
  public:
    std::pair<Key, Val> operator*() const {
      std::pair<Key, Val> entry((*it)->key,
                                (*it)->val);
      return entry;
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
  // maximum ratio of num_elts to capacity
  static constexpr const float LOAD_FACTOR = 0.5f;

  std::size_t num_elts; // number of key-value pairs

  std::size_t capacity; // size of buckets dynamic array

  Bucket *buckets;      // dynamic array of buckets

  Hash hasher;          // hash functor

  bool has_list;        // if true, this hash table keeps track of all filled
                        // buckets in a linked list, and does not otherwise

  std::vector<Bucket *> list; // vector containing pointers to all filled
                              // buckets

  // REQUIRES: capacity > 0
  // EFFECTS: creates a Map with specified capacity
  Map(std::size_t capacity, bool has_list)
    : num_elts(0), capacity(capacity), buckets(new Bucket[capacity]),
      has_list(has_list) { 
    assert(capacity > 0);
  }

  // EFFECTS: returns the index in 'buckets' that the given key hashes to
  std::size_t hash(Key key) const {
    return hasher(key) & (capacity - 1); // capacity is a power of 2
  }

  // EFFECTS: returns a pointer to the bucket containing the given key.
  //          if the key isn't in the map, then a bucket is filled with the key
  //          and a default initialized value before being returned.
  Bucket * get(Key key) {
    // grow table if needed
    if (static_cast<float>(num_elts) / static_cast<float>(capacity)
        > LOAD_FACTOR) {
      resize(capacity * 2);
    }

    std::size_t i = hash(key);
    Bucket *p = buckets + i;

    while (p->filled) {
      if (p->key == key) {
        return p;
      }

      ++i;
      p = (i == capacity) ? buckets : p + 1;
    }

    // key was not found, insert a new entry
    if (has_list) {
      list.push_back(p);
    }

    ++num_elts;
    p->filled = true;
    p->key = key;
    p->val = Val();
    return p;
  }

  // EFFECTS: resizes the buckets array to have the new specified capacity
  void resize(std::size_t new_capacity) {
    // missing assert statement, be extra careful
    Map copy(new_capacity, false);

    for (std::size_t i = 0; i < list.size(); ++i) {
      Bucket *b = copy.get(list[i]->key);
      b->val = list[i]->val;
      list[i] = b;
    }

    capacity = new_capacity;

    Bucket *t1 = buckets;
    buckets = copy.buckets;
    copy.buckets = t1;
  }


public:
  // EFFECTS: creates a map with initial capacity 4
  Map()
    : Map(4, true) { }

  // EFFECTS: destructs map
  ~Map() {
    delete[] buckets;
  }

  // EFFECTS: returns the number of key-value pairs
  std::size_t size() const {
    return num_elts;
  }

  // EFFECTS: returns true if the given key is contained in the map
  bool contains(Key key) const {
    std::size_t i = hash(key);
    Bucket *p = buckets + i;

    while (p->filled) {
      if (p->key == key) {
        return true;
      }

      ++i;
      p = (i == capacity) ? buckets : p + 1;
    }

    return false;
  }

  // EFFECTS: returns a reference to the value corresponding to the given key.
  //          if the key isn't in the map, then an entry containing the given
  //          key and a default initialized value is created before the value
  //          is returned.
  Val & operator[](Key key) {
    return get(key)->val;
  }

  // EFFECTS: removes all key-value pairs from the map
  // NOTE: capacity is not changed by clearing
  void clear() {
    for (auto it = list.begin(); it != list.end(); ++it) {
      (*it)->filled = false;
    }
    list.clear();

    num_elts = 0;
  }

  // EFFECTS: returns an iterator pointing to the first entry in the map
  Iterator begin() const {
    return Iterator(list.begin());
  }

  // EFFECTS: returns an iterator pointing off the end of the map
  Iterator end() const {
    return Iterator(list.end());
  }
};

#endif
