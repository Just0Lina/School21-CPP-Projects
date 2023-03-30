template <typename T>
s21::queue<T>::queue() : size_(0), front_node_(nullptr), back_node_(nullptr){};

template <typename T>
s21::queue<T>::queue(std::initializer_list<T> const &items)
    : size_(items.size()), front_node_(nullptr), back_node_(nullptr) {
  Node **temp = &front_node_;
  auto i = items.begin();
  auto end = items.end() - 1;
  while (i != end) {
    *temp = new Node{*i++, nullptr};
    temp = &(*temp)->next_;
  }
  *temp = new Node{*i, nullptr};
  back_node_ = *temp;
}

template <typename T>
s21::queue<T>::queue(const queue &q)
    : size_(q.size_), front_node_(nullptr), back_node_(nullptr) {
  if (!q.empty()) {
    Node **dst_ptr = &front_node_;
    Node *src_ptr = q.front_node_;
    while (src_ptr != q.back_node_) {
      *dst_ptr = new Node{src_ptr->value_, nullptr};
      dst_ptr = &(*dst_ptr)->next_;
      src_ptr = src_ptr->next_;
    }
    *dst_ptr = new Node{src_ptr->value_, nullptr};
    back_node_ = *dst_ptr;
  }
}

template <typename T>
s21::queue<T>::queue(queue &&q)
    : size_(q.size_), front_node_(q.front_node_), back_node_(q.back_node_) {
  q.front_node_ = q.back_node_ = nullptr;
  q.size_ = 0;
}

template <typename T> s21::queue<T>::~queue() { destroy(); }

template <typename T> s21::queue<T> &s21::queue<T>::operator=(queue &&q) {
  destroy();
  front_node_ = q.front_node_;
  back_node_ = q.back_node_;
  size_ = q.size_;
  q.front_node_ = q.back_node_ = nullptr;
  q.size_ = 0;
  return *this;
}

template <typename T> inline bool s21::queue<T>::empty() const {
  return front_node_ == nullptr;
}

template <typename T> inline size_t s21::queue<T>::size() const {
  return size_;
}

template <typename T> inline const T &s21::queue<T>::front() const {
  return front_node_->value_;
}

template <typename T> inline const T &s21::queue<T>::back() const {
  return back_node_->value_;
}

template <typename T> void s21::queue<T>::push(const T &val) {
  if (!empty())
    back_node_ = back_node_->next_ = new Node{val, nullptr};
  else
    back_node_ = front_node_ = new Node{val, nullptr};
  ++size_;
}

template <typename T> void s21::queue<T>::pop() {
  if (!empty()) {
    --size_;
    Node *temp = front_node_->next_;
    delete front_node_;
    front_node_ = temp;
    if (!front_node_)
      back_node_ = nullptr;
  }
}

template <typename T> void s21::queue<T>::swap(queue &other) {
  std::swap(size_, other.size_);
  std::swap(front_node_, other.front_node_);
  std::swap(back_node_, other.back_node_);
}

template <typename T>
template <typename... Args>
void s21::queue<T>::emplace_back(Args &&...args) {
  (push(args), ...);
}

template <typename T> inline void s21::queue<T>::destroy() {
  while (!empty()) {
    Node *ptr = front_node_->next_;
    delete (front_node_);
    front_node_ = ptr;
  }
}
