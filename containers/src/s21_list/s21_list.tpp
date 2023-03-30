template <typename T>
s21::list<T>::list()
    : size_(0), fake_node_(new Node{}), front_node_(fake_node_),
      back_node_(fake_node_){};

template <typename T>
s21::list<T>::list(size_type n)
    : size_(n), fake_node_(new Node{}), front_node_(fake_node_),
      back_node_(fake_node_) {
  if (n > 0) {
    Node **iter = &front_node_;
    Node *temp = nullptr;
    for (size_t i = 0; i < n - 1; ++i) {
      temp = *iter = new Node{T(), nullptr, temp};
      iter = &(*iter)->next_;
    }
    *iter = new Node{T(), fake_node_, temp};
    back_node_ = *iter;
    fake_node_->prev_ = back_node_;
  }
}

template <typename T>
s21::list<T>::list(std::initializer_list<T> const &items)
    : size_(items.size()), fake_node_(new Node{}), front_node_(fake_node_),
      back_node_(fake_node_) {
  if (items.size()) {
    Node **iter = &front_node_;
    Node *temp = nullptr;

    auto i = items.begin();
    auto end = items.end() - 1;
    while (i != end) {
      temp = *iter = new Node{*i, nullptr, temp};
      ++i;
      iter = &(*iter)->next_;
    }
    *iter = new Node{*i, fake_node_, temp};
    back_node_ = *iter;
    fake_node_->prev_ = back_node_;
  }
}

template <typename T>
s21::list<T>::list(const list &l)
    : size_(l.size_), fake_node_(new Node{}), front_node_(fake_node_),
      back_node_(fake_node_) {
  Node **dst_ptr = &front_node_;
  Node *src_ptr = l.front_node_;
  Node *temp = nullptr;

  while (src_ptr != l.back_node_) {
    temp = *dst_ptr = new Node{src_ptr->value_, nullptr, temp};
    dst_ptr = &(*dst_ptr)->next_;
    src_ptr = src_ptr->next_;
  }

  back_node_ = *dst_ptr = new Node{src_ptr->value_, fake_node_, temp};
  fake_node_->prev_ = back_node_;
}

template <typename T>
s21::list<T>::list(list &&l)
    : size_(l.size_), fake_node_(l.fake_node_), front_node_(l.front_node_),
      back_node_(l.back_node_) {
  l.fake_node_ = new Node{};
  l.front_node_ = l.fake_node_;
  l.back_node_ = l.fake_node_;
  l.size_ = 0;
}

template <typename T> s21::list<T>::~list() {
  clear();
  if (fake_node_)
    delete fake_node_;
}

template <typename T> inline const T &s21::list<T>::front() const {
  return front_node_->value_;
}

template <typename T> inline const T &s21::list<T>::back() const {
  return back_node_->value_;
}

template <typename T> inline size_t s21::list<T>::size() const { return size_; }
template <typename T> inline unsigned long s21::list<T>::max_size() const {
  return SIZE_MAX / sizeof(Node) / 2;
}

template <typename T> inline bool s21::list<T>::empty() const {
  return front_node_ == fake_node_;
}

template <typename T> s21::list<T> &s21::list<T>::operator=(list &&l) {
  std::swap(size_, l.size_);
  std::swap(fake_node_, l.fake_node_);
  std::swap(front_node_, l.front_node_);
  std::swap(back_node_, l.back_node_);
  return *this;
}

template <typename T> void s21::list<T>::push_back(const T &val) {
  fake_node_->prev_ = new Node{val, fake_node_, nullptr};
  Node *temp = back_node_;
  back_node_ = fake_node_->prev_;
  if (empty()) {
    front_node_ = back_node_;
  } else {
    temp->next_ = back_node_;
    back_node_->prev_ = temp;
  }
  ++size_;
}

template <typename T> void s21::list<T>::pop_back() {
  if (!empty()) {
    --size_;
    fake_node_->prev_ = back_node_->prev_;
    if (back_node_->prev_)
      back_node_->prev_->next_ = fake_node_;
    delete back_node_;
    if (fake_node_->prev_)
      back_node_ = fake_node_->prev_;
    else
      back_node_ = front_node_ = fake_node_;
  }
}

template <typename T> inline void s21::list<T>::push_front(const T &val) {
  ++size_;
  if (empty()) {
    front_node_ = back_node_ = fake_node_->prev_ =
        new Node{val, fake_node_, nullptr};
  } else {
    front_node_->next_->prev_ = front_node_ =
        new Node{val, front_node_, nullptr};
  }
}

template <typename T> inline void s21::list<T>::pop_front() {
  if (!empty()) {
    --size_;
    Node *temp = front_node_->next_;
    delete front_node_;
    front_node_ = temp;
    if (fake_node_ == front_node_)
      back_node_ = front_node_;
    else
      front_node_->prev_ = nullptr;
  }
}

template <typename T> inline void s21::list<T>::swap(list &other) {
  std::swap(size_, other.size_);
  std::swap(fake_node_, other.fake_node_);
  std::swap(front_node_, other.front_node_);
  std::swap(back_node_, other.back_node_);
}

template <typename T> void s21::list<T>::merge(list &other) {
  size_ += other.size_;
  if (!empty()) {
    if (!other.empty()) {
      other.fake_node_->prev_ = other.back_node_->next_ = nullptr;
      fake_node_->prev_ = back_node_->next_ = nullptr;
      Node *src_ptr = other.front_node_;
      Node *dst_ptr = front_node_;
      while (src_ptr && dst_ptr) {
        if (dst_ptr->value_ > src_ptr->value_) {
          src_ptr->prev_ = dst_ptr->prev_;
          src_ptr->prev_->next_ = src_ptr;
          dst_ptr->prev_ = src_ptr;
          Node *temp_src = src_ptr->next_;
          src_ptr->next_ = dst_ptr;
          src_ptr = temp_src;
        } else {
          dst_ptr = dst_ptr->next_;
        }
      }
      if (src_ptr) {
        back_node_->next_ = src_ptr;
        src_ptr->prev_ = back_node_;
        back_node_ = other.back_node_;
      }
    }
  } else {
    swap(other);
  }
  back_node_->next_ = fake_node_;
  fake_node_->prev_ = back_node_;
  other.back_node_ = other.front_node_ = other.fake_node_;
  other.size_ = 0;
}

template <typename T> void s21::list<T>::reverse() {
  if (!empty()) {
    Node *back = back_node_;
    back_node_ = front_node_;
    front_node_ = back;
    for (size_t i = size_; i >= 1; --i) {
      Node *next = back->next_;
      back->next_ = back->prev_;
      back->prev_ = next;
      back = back->next_;
    }
    back_node_->next_ = fake_node_;
    fake_node_->prev_ = back_node_;
  }
}

template <typename T> void s21::list<T>::unique() {
  if (!empty()) {
    Node *temp = front_node_;
    while (temp && temp->next_) {
      if (temp->next_ == fake_node_)
        break;
      Node *temp_next_node = temp->next_;
      if (temp->value_ == temp_next_node->value_) {
        temp_next_node = temp->next_->next_;
        delete (temp->next_);
        temp->next_ = temp_next_node;
        if (temp_next_node != fake_node_)
          temp_next_node->prev_ = temp;
        else
          back_node_ = temp;
        --size_;
      } else
        temp = temp_next_node;
    }
    fake_node_->prev_ = back_node_;
  }
}

template <typename T> void s21::list<T>::sort() {
  if (!empty()) {
    for (size_t i = 0; i < size_ - 1; ++i) {
      Node *curr = front_node_;
      for (size_t j = 0; j < size_ - i - 1; ++j) {
        if (curr->next_ && curr->value_ > curr->next_->value_) {
          Node *left = curr;
          Node *right = curr->next_;
          Node *temp = curr->prev_;

          if (left != front_node_)
            left->prev_->next_ = right;
          else
            front_node_ = right;

          if (right != back_node_)
            right->next_->prev_ = left;
          else
            back_node_ = left;

          left->prev_ = right;
          right->prev_ = temp;
          temp = right->next_;
          right->next_ = left;
          left->next_ = temp;
          curr = left;
        } else {
          curr = curr->next_;
        }
      }
    }
    fake_node_->prev_ = back_node_;
    back_node_->next_ = fake_node_;
  }
}

template <typename T> inline void s21::list<T>::clear() {
  while (front_node_ != fake_node_) {
    Node *ptr = front_node_->next_;
    delete (front_node_);
    front_node_ = ptr;
  }
  size_ = 0;
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::begin() const {
  return iterator(front_node_);
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::end() const {
  return iterator(fake_node_);
}

template <typename T>
void s21::list<T>::splice(s21::list<T>::const_iterator pos,
                          s21::list<T> &other) {
  if (!other.empty()) {
    iterator it(const_cast<Node *>(pos.pos_));
    size_ += other.size_;
    Node *temp = it.pos_->prev_;
    it.pos_->prev_ = other.back_node_;
    other.back_node_->next_ = it.pos_;
    if (temp) {
      temp->next_ = other.front_node_;
      other.front_node_->prev_ = temp;
    }
    if (pos.pos_ == front_node_)
      front_node_ = other.front_node_;
    if (pos.pos_ == fake_node_)
      back_node_ = other.back_node_;
    other.back_node_ = other.front_node_ = other.fake_node_;
    other.size_ = 0;
  }
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::insert(s21::list<T>::iterator it,
                                                     const T &value) {
  Node *temp = it.pos_->prev_;

  it.pos_->prev_ = new Node{value, it.pos_, it.pos_->prev_};
  if (temp)
    temp->next_ = it.pos_->prev_;
  if (it.pos_ == fake_node_)
    back_node_ = it.pos_->prev_;
  if (it.pos_ == front_node_)
    front_node_ = it.pos_->prev_;
  it.pos_ = it.pos_->prev_;
  ++size_;

  return it;
}

template <typename T>
template <typename... Args>
typename s21::list<T>::iterator s21::list<T>::emplace(const_iterator pos,
                                                      Args &&...args) {
  (insert(iterator(const_cast<Node *>(pos.pos_)), args), ...);
  return iterator(front_node_);
}

template <typename T>
template <typename... Args>
void s21::list<T>::emplace_back(Args &&...args) {
  (push_back(args), ...);
}

template <typename T>
template <typename... Args>
void s21::list<T>::emplace_front(Args &&...args) {
  iterator iter(front_node_);
  (insert(iter, args), ...);
}

template <typename T> void s21::list<T>::erase(s21::list<T>::iterator pos) {
  if (pos.pos_ != fake_node_) {
    if (pos.pos_ == front_node_) {
      front_node_ = front_node_->next_;
      front_node_->prev_ = nullptr;
    } else if (pos.pos_ == back_node_) {
      back_node_ = back_node_->prev_;
      back_node_->next_ = fake_node_;
      fake_node_->prev_ = back_node_;
    } else {
      pos.pos_->prev_->next_ = pos.pos_->next_;
      pos.pos_->next_->prev_ = pos.pos_->prev_;
    }
    delete pos.pos_;
    --size_;
  }
}
