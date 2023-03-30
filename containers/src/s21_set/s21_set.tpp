namespace s21 {

template <typename Key, typename Value> set<Key, Value>::set(){};

template <typename Key, typename Value>
set<Key, Value>::set(std::initializer_list<Key> const &list) {
  for (auto i = list.begin(); i != list.end(); ++i) {
    insert(*i);
  }
}

template <typename Key, typename Value>
set<Key, Value>::set(const set<Key, Value> &m) : map<Key, Value>(m) {}

template <typename Key, typename Value>
set<Key, Value>::set(set<Key, Value> &&m) : map<Key, Value>(std::move(m)) {}

template <typename Key, typename Value> set<Key, Value>::~set() {}

template <typename Key, typename Value>
set<Key, Value> &set<Key, Value>::operator=(set<Key, Value> &&m) {
  if (this != &m)
    rb_tree<Key, Value>::swap(m.root_, m.fake_node_, m.size_);
  return *this;
}

template <typename Key, typename Value>
typename std::pair<typename set<Key, Value>::iterator, bool>
set<Key, Value>::insert(const Key &value) {
  bool success =
      rb_tree<Key, Value>::insert(std::pair<Key, Value>(value, Value{}));
  auto iter = this->get_node(value);
  return std::pair<set<Key, Value>::iterator, bool>(
      set<Key, Value>::iterator(iter, this->fake_node_), success);
}

template <typename Key, typename Value>
void set<Key, Value>::erase(set<Key, Value>::iterator pos) {
  this->rb_delete(const_cast<Node<const Key, Value> *>(pos.iter_));
}

template <typename Key, typename Value>
inline void set<Key, Value>::swap(set<Key, Value> &other) {
  rb_tree<Key, Value>::swap(other.root_, other.fake_node_, other.size_);
}

template <typename Key, typename Value>
typename set<Key, Value>::iterator set<Key, Value>::find(const Key &key) const {
  Node<const Key, Value> *search_node = this->fake_node_;
  this->search(key, search_node);
  return set<Key, Value>::iterator(search_node, this->fake_node_);
}

template <typename Key, typename Value>
typename set<Key, Value>::iterator set<Key, Value>::begin() const {
  return set<Key, Value>::iterator(this->minimum(), this->fake_node_);
}

template <typename Key, typename Value>
typename set<Key, Value>::iterator set<Key, Value>::end() const {
  return set<Key, Value>::iterator(this->fake_node_, this->fake_node_);
}

template <typename Key, typename Value>
void set<Key, Value>::merge(set &other) {
  map<Key, Value>::merge(other);
}

template <typename Key, typename Value>
template <typename... Args>
vector<std::pair<typename set<Key, Value>::iterator, bool>>
set<Key, Value>::emplace(Args &&...args) {
  vector<std::pair<typename set<Key, Value>::iterator, bool>> v(
      sizeof...(args));
  size_t i = 0;
  ((v[i++] = (insert(args))), ...);
  return v;
}

} // namespace s21
