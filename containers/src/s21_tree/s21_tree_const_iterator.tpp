
template <typename Key, typename Value>
TreeConstIterator<Key, Value>::TreeConstIterator(Node<Key, Value> *const &node,
                                                 Node<Key, Value> *const &fake)
    : iter_(node), fake_node_(fake){};

template <typename Key, typename Value>
inline bool TreeConstIterator<Key, Value>::operator!=(
    const TreeConstIterator<Key, Value> &rhs) const {
  return (iter_ != rhs.iter_);
}

template <typename Key, typename Value>
inline bool TreeConstIterator<Key, Value>::operator==(
    const TreeConstIterator<Key, Value> &rhs) const {
  return (iter_ == rhs.iter_);
}

template <typename Key, typename Value>
const Node<Key, Value> *iterPrev(const Node<Key, Value> *iter,
                                 const Node<Key, Value> *fake) {
  if (iter) {
    if (iter->left) {
      iter = iter->left;
      while (iter->right)
        iter = iter->right;
    } else if (iter != fake) {
      Key temp = iter->value.first;
      while (iter->parent && iter->value.first >= temp &&
             iter->parent->left == iter) {
        iter = iter->parent;
      }
      iter = iter->parent;
    } else if (iter->parent) {
      iter = iter->parent;
    }
  }
  return iter;
}

template <typename Key, typename Value>
const Node<Key, Value> *iterNext(const Node<Key, Value> *iter,
                                 const Node<Key, Value> *fake) {
  if (iter) {
    if (iter->right) {
      iter = iter->right;
      while (iter->left)
        iter = iter->left;
    } else if (iter != fake) {
      if (iter->parent) {
        if (iter->parent->right == iter) {
          Key temp = iter->value.first;
          while (iter->parent && iter->value.first <= temp &&
                 iter->parent->right == iter) {
            iter = iter->parent;
          }
          iter = iter->parent;
        } else {
          iter = iter->parent;
        }
      }
    }
  }
  return iter;
}

template <typename Key, typename Value>
TreeConstIterator<Key, Value> &TreeConstIterator<Key, Value>::operator++() {
  iter_ = iterNext(iter_, fake_node_);
  return *this;
}

template <typename Key, typename Value>
TreeConstIterator<Key, Value> TreeConstIterator<Key, Value>::operator++(int) {
  auto old(*this);
  iter_ = iterNext(iter_, fake_node_);
  return old;
}

template <typename Key, typename Value>
TreeConstIterator<Key, Value> &TreeConstIterator<Key, Value>::operator--() {
  iter_ = iterPrev(iter_, fake_node_);
  return *this;
}

template <typename Key, typename Value>
TreeConstIterator<Key, Value> TreeConstIterator<Key, Value>::operator--(int) {
  auto old(*this);
  iter_ = iterPrev(iter_, fake_node_);
  return old;
}

template <typename Key, typename Value>
const std::pair<Key, Value> &TreeConstIterator<Key, Value>::operator*() const {
  if (!iter_)
    throw(std::out_of_range("You can't dereference end iterator"));
  return iter_->value;
}

template <typename Key, typename Value>
const std::pair<Key, Value> *TreeConstIterator<Key, Value>::operator->() {
  return &this->iter_->value;
}