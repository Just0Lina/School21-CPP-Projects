
template <typename Key, typename Value>
TreeIterator<Key, Value>::TreeIterator(Node<Key, Value> *const &node,
                                       Node<Key, Value> *const &fake)
    : iter_(node), fake_node_(fake){};

template <typename Key, typename Value>
TreeIterator<Key, Value> &
TreeIterator<Key, Value>::operator=(const TreeIterator<Key, Value> &iter) {
  iter_ = iter.iter_;
  fake_node_ = iter.fake_node_;
  return *this;
}

template <typename Key, typename Value>
inline bool TreeIterator<Key, Value>::operator!=(
    const TreeIterator<Key, Value> &rhs) const {
  return (iter_ != rhs.iter_);
}

template <typename Key, typename Value>
inline bool TreeIterator<Key, Value>::operator==(
    const TreeIterator<Key, Value> &rhs) const {
  return (iter_ == rhs.iter_);
}

template <typename Key, typename Value>
Node<Key, Value> *iterPrev(Node<Key, Value> *iter,
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
Node<Key, Value> *iterNext(Node<Key, Value> *iter,
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
TreeIterator<Key, Value> &TreeIterator<Key, Value>::operator++() {
  iter_ = iterNext(iter_, fake_node_);
  return *this;
}

template <typename Key, typename Value>
TreeIterator<Key, Value> TreeIterator<Key, Value>::operator++(int) {
  auto old(*this);
  iter_ = iterNext(iter_, fake_node_);
  return old;
}

template <typename Key, typename Value>
TreeIterator<Key, Value> &TreeIterator<Key, Value>::operator--() {
  iter_ = iterPrev(iter_, fake_node_);
  return *this;
}

template <typename Key, typename Value>
TreeIterator<Key, Value> TreeIterator<Key, Value>::operator--(int) {
  auto old(*this);
  iter_ = iterPrev(iter_, fake_node_);
  return old;
}

template <typename Key, typename Value>
std::pair<Key, Value> &TreeIterator<Key, Value>::operator*() {
  if (!iter_)
    throw(std::out_of_range("You can't dereference end iterator"));
  return iter_->value;
}

template <typename Key, typename Value>
std::pair<Key, Value> *TreeIterator<Key, Value>::operator->() {
  return &this->iter_->value;
}