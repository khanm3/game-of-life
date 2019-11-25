#ifndef MAP_H
#define MAP_H

#include <cassert>
#include <functional>
#include <utility>

template <typename Key, typename Val, typename Hash=std::hash<Key>>
class Map {
private:
  // bucket holds key-value pairs, along with bucket type
  struct Bucket {
    bool filled = false;
    Key key;
    Val val;
  };

  // linked list node holds pointer to a bucket
  struct Node {
    Bucket *bucket_ptr;
    Node *next;
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

    Node *node_ptr;   // holds a Node *

    Iterator(Node *node_ptr) : node_ptr(node_ptr) { }
  
  public:
    std::pair<Key, Val> operator*() const {
      std::pair<Key, Val> entry(node_ptr->bucket_ptr->key,
                                node_ptr->bucket_ptr->val);
      return entry;
    }

    Iterator & operator++() {
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(Iterator other) const {
      return node_ptr == other.node_ptr;
    }

    bool operator!=(Iterator other) const {
      return node_ptr != other.node_ptr;
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

  Node *first;          // linked list of filled buckets


  // REQUIRES: bucket_ptr is a pointer to a valid bucket
  // EFFECTS: pushes bucket_ptr to the front of the linked list
  void list_push_front(Bucket *bucket_ptr) {
    first = new Node{ bucket_ptr, first };
  }

  // REQUIRES: first points to a valid node
  // EFFECTS: pops the first element from the linked list
  void list_pop_front() {
    // missing assert statement, be extra careful
    Node *victim = first;
    first = first->next;
    delete victim;
  }

  // EFFECTS: clears the linked list
  void list_clear() {
    while (first) {
      list_pop_front();
    }
  }

  // REQUIRES: capacity > 0
  // EFFECTS: creates a Map with specified capacity
  Map(std::size_t capacity, bool has_list)
    : num_elts(0), capacity(capacity), buckets(new Bucket[capacity]),
      has_list(has_list), first(nullptr) { 
    assert(capacity > 0);
  }

  // EFFECTS: returns the index in 'buckets' that the given key hashes to
  std::size_t hash(Key key) const {
    return hasher(key) & (capacity - 1); // capacity is a power of 2
  }

  // EFFECTS: returns a pointer to the bucket containing the given key.
  //          if the key isn't in the map, then a bucket is filled with the key
  //          before being returned.
  Bucket * get(Key key) {
    // grow table if needed
    if (static_cast<float>(num_elts) / static_cast<float>(capacity)
        > LOAD_FACTOR) {
      resize(capacity * 2);
    }

    std::size_t i;
    for (i = hash(key); buckets[i].filled; i = (i + 1) % capacity) {
      if (buckets[i].key == key) {
        return buckets + i;
      }
    }

    // key was not found, insert a new entry
    if (has_list) {
      list_push_front(buckets + i);
    }

    ++num_elts;
    buckets[i].filled = true;
    buckets[i].key = key;
    return buckets + i;
  }

  // EFFECTS: resizes the buckets array to have the new specified capacity
  void resize(std::size_t new_capacity) {
    // missing assert statement, be extra careful
    Map copy(new_capacity, false);

    for (Node *p = first; p; p = p->next) {
      Bucket *b = copy.get(p->bucket_ptr->key);
      b->val = p->bucket_ptr->val;
      p->bucket_ptr = b;
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
    list_clear();
  }

  // EFFECTS: returns the number of key-value pairs
  std::size_t size() const {
    return num_elts;
  }

  // EFFECTS: returns true if the given key is contained in the map
  bool contains(Key key) const {
    for (std::size_t i = hash(key); buckets[i].filled; i = (i + 1) % capacity) {
      if (buckets[i].key == key) {
        return true;
      }
    }

    return false;
  }

  // EFFECTS: returns a reference to the value corresponding to the given key.
  //          if the key isn't in the map, then an entry is created before
  //          returning the corresponding value.
  Val & operator[](Key key) {
    return get(key)->val;
  }

  // EFFECTS: removes all key-value pairs from the map
  // NOTE: capacity is not changed by clearing
  void clear() {
    while (first) {
      first->bucket_ptr->filled = false;
      list_pop_front();
    }

    num_elts = 0;
  }

  // EFFECTS: returns an iterator pointing to the first entry in the map
  Iterator begin() const {
    return Iterator(first);
  }

  // EFFECTS: returns an iterator pointing off the end of the map
  Iterator end() const {
    return Iterator(nullptr);
  }
};

#endif
