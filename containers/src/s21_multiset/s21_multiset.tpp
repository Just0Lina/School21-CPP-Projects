#include "../s21_list/s21_list.h"

namespace s21 {
template <typename Key, typename Value>
multiset<Key, Value>::multiset() : set<Key, Value>() {}

template <typename Key, typename Value> multiset<Key, Value>::~multiset() {}

template <typename Key, typename Value>
multiset<Key, Value>::multiset(std::initializer_list<Key> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename Key, typename Value>
multiset<Key, Value>::multiset(const multiset<Key, Value> &m) {
  for (auto value : m) {
    insert(value);
  }
}

template <typename Key, typename Value>
typename multiset<Key, Value>::iterator
multiset<Key, Value>::insert(const Key &value) {
  return iterator(
      rb_tree<Key, Value>::insert_any(std::pair<Key, Value>(value, Value{})));
}

template <typename Key, typename Value>
multiset<Key, Value>::multiset(multiset<Key, Value> &&m) {
  this->root_ = m.root_;
  std::swap(this->fake_node_, m.fake_node_);
  this->size_ = m.size_;
  m.root_ = m.fake_node_;
  m.size_ = 0;
}

template <typename Key, typename Value>
typename multiset<Key, Value>::iterator
multiset<Key, Value>::find(const Key &key) {
  Node<const Key, Value> *node_ptr = this->fake_node_;
  this->search(key, node_ptr);
  if (node_ptr != this->fake_node_)
    return iterator(node_ptr, this->fake_node_);
  else
    return this->end();
}

template <typename Key, typename Value>
size_t multiset<Key, Value>::count(const Key &key) {
  auto first = iterator(this->find_first(key, this->root_), this->fake_node_);
  size_t count = 0;
  for (; first != this->end() && *first == key; ++first, ++count) {
  }
  return count;
}

template <typename Key, typename Value>
multiset<Key, Value> &
multiset<Key, Value>::operator=(multiset<Key, Value> &&m) {
  if (&m != this) {
    rb_tree<Key, Value>::swap(m.root_, m.fake_node_, m.size_);
  }
  return *this;
}

template <typename Key, typename Value>
typename std::pair<typename multiset<Key, Value>::iterator,
                   typename multiset<Key, Value>::iterator>
multiset<Key, Value>::equal_range(const Key &key) {
  auto first = iterator(this->find_first(key, this->root_), this->fake_node_);
  auto second = first;
  while (second != this->end() && *second == key)
    ++second;

  return std::pair<typename multiset<Key, Value>::iterator,
                   typename multiset<Key, Value>::iterator>(first, second);
}

template <typename Key, typename Value>
typename multiset<Key, Value>::iterator
multiset<Key, Value>::lower_bound(const Key &value) {
  Node<const Key, Value> *node_ptr = this->find_first(value, this->root_);
  iterator it(node_ptr, this->fake_node_);
  return it;
}

template <typename Key, typename Value>
typename multiset<Key, Value>::iterator
multiset<Key, Value>::upper_bound(const Key &value) {
  auto it = lower_bound(value);
  if (it.iter_)
    while (*it <= value) {
      ++it;
    }
  return it;
}

template <typename Key, typename Value>
template <typename... Args>
vector<typename multiset<Key, Value>::iterator>
multiset<Key, Value>::emplace(Args &&...args) {
  vector<multiset<Key, Value>::iterator> v(sizeof...(args));
  size_t i = 0;
  ((v[i++] = (insert(args))), ...);
  return v;
}

template <typename Key, typename Value>
void multiset<Key, Value>::erase(typename multiset<Key, Value>::iterator pos) {
  this->rb_delete(const_cast<Node<const Key, Value> *>(pos.iter_));
}

template <typename Key, typename Value>
inline void multiset<Key, Value>::swap(multiset<Key, Value> &other) {
  rb_tree<Key, Value>::swap(other.root_, other.fake_node_, other.size_);
}

template <typename Key, typename Value>
void multiset<Key, Value>::merge(multiset<Key, Value> &other) {
  s21::list<Node<const Key, Value> *> l;
  for (auto i = other.begin(); i != other.end(); ++i)
    l.push_back(const_cast<Node<const Key, Value> *>(i.iter_));

  for (auto i = l.begin(); i != l.end(); ++i) {
    this->insert_any_existing(*i);
  };
  other.fake_node_->parent = nullptr;
  other.root_ = other.fake_node_;
  other.size_ = 0;
}

} // namespace s21
