template <typename T>
ListConstIterator<T>::ListConstIterator(const ListIterator<T> &iter) {
  this->pos_ = iter.pos_;
};

template <typename T> const T &ListConstIterator<T>::operator*() const {
  return this->pos_->value_;
}

template <typename T>
inline ListConstIterator<T> &ListConstIterator<T>::operator++() {
  if (pos_->next_)
    pos_ = pos_->next_;
  return (*this);
}

template <typename T>
inline ListConstIterator<T> ListConstIterator<T>::operator++(int) {
  ListConstIterator<T> old(*this);
  if (pos_->next_)
    pos_ = pos_->next_;
  return old;
}

template <typename T>
inline ListConstIterator<T> &ListConstIterator<T>::operator--() {
  if (pos_->prev_)
    pos_ = pos_->prev_;
  return (*this);
}

template <typename T>
inline ListConstIterator<T> ListConstIterator<T>::operator--(int) {
  ListConstIterator<T> old(*this);
  if (pos_->prev_)
    pos_ = pos_->prev_;
  return old;
}

template <typename T>
inline bool
ListConstIterator<T>::operator!=(const ListConstIterator<T> &rhs) const {
  return (pos_ != rhs.pos_);
}

template <typename T>
inline bool
ListConstIterator<T>::operator==(const ListConstIterator<T> &rhs) const {
  return (pos_ == rhs.pos_);
}
