template <class T> s21::stack<T>::stack() : top_node_(nullptr), size_(0){};

template <class T>
s21::stack<T>::stack(const stack &s) : top_node_(nullptr), size_(s.size_) {
  Node *src_ptr = s.top_node_;
  Node **dst_ptr = &top_node_;
  while (src_ptr) {
    *dst_ptr = new Node{src_ptr->value_, *dst_ptr};
    src_ptr = src_ptr->next_;
    dst_ptr = &((*dst_ptr)->next_);
  }
}
template <class T>
s21::stack<T>::stack(std::initializer_list<T> const &items)
    : top_node_(nullptr), size_(items.size()) {
  for (auto i : items)
    top_node_ = new Node{i, top_node_};
}

template <class T>
s21::stack<T>::stack(stack &&other)
    : top_node_(other.top_node_), size_(other.size_) {
  other.top_node_ = nullptr;
  other.size_ = 0;
}

template <class T> s21::stack<T>::~stack() { destroy(); }

template <class T> void s21::stack<T>::push(const_reference val) {
  top_node_ = new Node{val, top_node_};
  ++size_;
}

template <class T> void s21::stack<T>::pop() {
  if (!empty()) {
    Node *ptr = top_node_->next_;
    delete top_node_;
    top_node_ = ptr;
    --size_;
  }
}

template <class T> inline bool s21::stack<T>::empty() const {
  return top_node_ == nullptr;
}

template <class T> inline size_t s21::stack<T>::size() const { return size_; }

template <class T> void s21::stack<T>::swap(stack &other) {
  size_t tempSize = size_;
  size_ = other.size_;
  other.size_ = tempSize;

  Node *tempTop = top_node_;
  top_node_ = other.top_node_;
  other.top_node_ = tempTop;
}

template <class T> inline const T &s21::stack<T>::top() const {
  return top_node_->value_;
}

template <class T> s21::stack<T> &s21::stack<T>::operator=(stack<T> &&other) {
  destroy();
  size_ = other.size_;
  top_node_ = other.top_node_;
  other.top_node_ = nullptr;
  other.size_ = 0;
  return *this;
}

template <class T>
s21::stack<T> &s21::stack<T>::operator=(const stack<T> &other) {
  Node *src_ptr = other.top_node_;
  Node **dst_ptr = &top_node_;
  for (; *dst_ptr && src_ptr;
       dst_ptr = &(*dst_ptr)->next_, src_ptr = src_ptr->next_) {
    (*dst_ptr)->value_ = src_ptr->value_;
  }
  if (src_ptr) {
    for (; src_ptr; dst_ptr = &(*dst_ptr)->next_, src_ptr = src_ptr->next_) {
      (*dst_ptr) = new Node{src_ptr->value_, nullptr};
    }
  } else {
    while (*dst_ptr) {
      src_ptr = (*dst_ptr)->next_;
      delete (*dst_ptr);
      *dst_ptr = nullptr;
      dst_ptr = &src_ptr;
    }
  }
  size_ = other.size_;
  return *this;
}

template <class T> inline void s21::stack<T>::destroy() {
  while (!empty()) {
    Node *ptr = top_node_->next_;
    delete (top_node_);
    top_node_ = ptr;
  }
}

template <typename T>
template <typename... Args>
void s21::stack<T>::emplace_front(Args &&...args) {
  (push(args), ...);
}
