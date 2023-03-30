template <typename Key, typename Value>
SetIterator<Key, Value>::SetIterator() : TreeConstIterator<Key, Value>() {}

template <typename Key, typename Value>
SetIterator<Key, Value>::SetIterator(Node<Key, Value> *const &node,
                                     Node<Key, Value> *const &fake)
    : TreeConstIterator<Key, Value>(node, fake) {}

template <typename Key, typename Value>
SetIterator<Key, Value>::SetIterator(const TreeIterator<Key, Value> &iter)
    : TreeConstIterator<Key, Value>(iter) {}

template <typename Key, typename Value>
SetIterator<Key, Value>::SetIterator(const TreeConstIterator<Key, Value> &iter)
    : TreeConstIterator<Key, Value>(iter) {}

template <typename Key, typename Value>
SetIterator<Key, Value> &
SetIterator<Key, Value>::operator=(const SetIterator<Key, Value> &it) {
  this->iter_ = it.iter_;
  this->fake_node_ = it.fake_node_;
  return *this;
}

template <typename Key, typename Value>
inline const Key &SetIterator<Key, Value>::operator*() const {
  return this->iter_->value.first;
}

template <typename Key, typename Value>
inline bool
SetIterator<Key, Value>::operator==(const SetIterator<Key, Value> &iter) const {
  return this->iter_ == iter.iter_;
}

template <typename Key, typename Value>
inline bool
SetIterator<Key, Value>::operator!=(const SetIterator<Key, Value> &iter) const {
  return this->iter_ != iter.iter_;
}

template <typename Key, typename Value>
SetIterator<Key, Value> &SetIterator<Key, Value>::operator++() {
  TreeConstIterator<Key, Value>::operator++();
  return *this;
}

template <typename Key, typename Value>
SetIterator<Key, Value> SetIterator<Key, Value>::operator++(int) {
  return SetIterator<Key, Value>(
      TreeConstIterator<Key, Value>::operator++(int()));
}

template <typename Key, typename Value>
SetIterator<Key, Value> &SetIterator<Key, Value>::operator--() {
  TreeConstIterator<Key, Value>::operator--();
  return *this;
}

template <typename Key, typename Value>
SetIterator<Key, Value> SetIterator<Key, Value>::operator--(int) {
  return SetIterator<Key, Value>(
      TreeConstIterator<Key, Value>::operator--(int()));
}
