
#include "../s21_list/s21_list.h"

template <typename Key, typename Value>
map<Key, Value>::map(
    std::initializer_list<std::pair<const Key, Value>> const &list) {
  for (auto i = list.begin(); i != list.end(); ++i) {
    insert(*i);
  }
}

template <typename Key, typename Value>
map<Key, Value>::map(const map<Key, Value> &m) : rb_tree<Key, Value>(m) {}

template <typename Key, typename Value>
map<Key, Value>::map(map<Key, Value> &&m) : rb_tree<Key, Value>(std::move(m)) {}

template <typename Key, typename Value> map<Key, Value>::~map() {}

template <typename Key, typename Value>
map<Key, Value> &map<Key, Value>::operator=(map<Key, Value> &&m) {
  if (&m != this)
    rb_tree<Key, Value>::swap(m.root_, m.fake_node_, m.size_);
  return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::begin() const {
  return map<Key, Value>::iterator(this->minimum(), this->fake_node_);
}

template <typename Key, typename Value>
inline void map<Key, Value>::swap(map<Key, Value> &other) {
  rb_tree<Key, Value>::swap(other.root_, other.fake_node_, other.size_);
}

template <typename Key, typename Value>
Value &map<Key, Value>::at(const Key &key) {
  Node<const Key, Value> *search_node;
  rb_tree<Key, Value>::search(key, search_node);
  if (!search_node) {
    throw std::out_of_range("Error: out of range");
  }
  return search_node->value.second;
}

template <typename Key, typename Value>
Value &map<Key, Value>::operator[](const Key &key) {
  Node<const Key, Value> *search_node;
  rb_tree<Key, Value>::search(key, search_node);
  return search_node->value.second;
}

template <typename Key, typename Value>
void map<Key, Value>::erase(typename map<Key, Value>::iterator pos) {
  this->rb_delete(pos.iter_);
}

template <typename Key, typename Value>
void map<Key, Value>::merge(map<Key, Value> &other) {
  s21::list<Node<const Key, Value> *> l;
  for (auto i = other.begin(); i != other.end(); ++i)
    l.push_back(i.iter_);

  for (auto i = l.begin(); i != l.end();) {
    bool insertion = this->insert_existing(*i);
    if (insertion)
      l.erase(i++);
    else
      ++i;
  }

  other.root_ = other.fake_node_;
  other.size_ = 0;

  for (auto i = l.begin(); i != l.end(); ++i)
    other.insert_existing(*i);
}

template <typename Key, typename Value>
typename std::pair<typename map<Key, Value>::iterator, bool>
map<Key, Value>::insert(const Key &key, const Value &obj) {
  bool insertion = rb_tree<Key, Value>::insert(std::pair<Key, Value>(key, obj));
  auto iter = this->get_node(key);
  return std::pair<typename map<Key, Value>::iterator, bool>(
      map<Key, Value>::iterator(iter, this->fake_node_), insertion);
}

template <typename Key, typename Value>
typename std::pair<typename map<Key, Value>::iterator, bool>
map<Key, Value>::insert(const std::pair<const Key, Value> &value) {
  bool insertion = rb_tree<Key, Value>::insert(value);
  auto iter = this->get_node(value.first);
  return std::pair<typename map<Key, Value>::iterator, bool>(
      map<Key, Value>::iterator(iter, this->fake_node_), insertion);
}

template <typename Key, typename Value>
typename std::pair<typename map<Key, Value>::iterator, bool>
map<Key, Value>::insert_or_assign(const Key &key, const Value &obj) {
  bool insertion = rb_tree<Key, Value>::insert(std::pair<Key, Value>(key, obj));
  if (insertion == false) {
    Node<const Key, Value> *node_ptr = nullptr;
    this->search(key, node_ptr);
    node_ptr->value.second = obj;
  }
  map<Key, Value>::iterator iter(this->get_node(key), this->fake_node_);
  return std::pair<typename map<Key, Value>::iterator, bool>(iter, insertion);
}

template <typename Key, typename Value>
template <typename... Args>
vector<std::pair<typename map<Key, Value>::iterator, bool>>
map<Key, Value>::emplace(Args &&...args) {
  vector<std::pair<map<Key, Value>::iterator, bool>> v;
  v.reserve(sizeof...(args));
  size_t i = 0;
  ((v[i++] = (insert(args))), ...);
  return v;
}
