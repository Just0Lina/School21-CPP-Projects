template <typename T> ListIterator<T>::ListIterator() : pos_(nullptr){};

template <typename T>
ListIterator<T>::ListIterator(D_Node<T> *pos) : pos_(pos){};

template <typename T> inline T &ListIterator<T>::operator*() {
  if (!pos_->next_)
    throw(std::out_of_range("You can't dereference end iterator"));
  return pos_->value_;
}

template <typename T> inline ListIterator<T> &ListIterator<T>::operator++() {
  if (pos_->next_)
    pos_ = pos_->next_;
  return (*this);
}

template <typename T> inline ListIterator<T> ListIterator<T>::operator++(int) {
  ListIterator old{pos_};
  if (pos_->next_)
    pos_ = pos_->next_;
  return old;
}

template <typename T> inline ListIterator<T> &ListIterator<T>::operator--() {
  if (pos_->prev_)
    pos_ = pos_->prev_;
  return (*this);
}

template <typename T> inline ListIterator<T> ListIterator<T>::operator--(int) {
  ListIterator old{pos_};
  if (pos_->prev_)
    pos_ = pos_->prev_;
  return old;
}

template <typename T>
inline bool ListIterator<T>::operator!=(const ListIterator<T> &rhs) const {
  return (pos_ != rhs.pos_);
}

template <typename T>
inline bool ListIterator<T>::operator==(const ListIterator<T> &rhs) const {
  return (pos_ == rhs.pos_);
}
