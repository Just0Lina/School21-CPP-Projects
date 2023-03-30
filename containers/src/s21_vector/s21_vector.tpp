
template <typename T>
vector<T>::vector() : size_(0), capacity_(0), arr_(nullptr) {}

template <typename T> vector<T>::vector(size_t n) : size_(n), capacity_(n) {
  memory_allocation();
}

template <typename T>
vector<T>::vector(const vector &other)
    : size_(other.size_), capacity_(other.size_) {
  memory_allocation();
  copy_vector(other);
}

template <typename T>
vector<T>::vector(vector &&other)
    : size_(other.size_), capacity_(other.capacity_), arr_(other.arr_) {
  other.arr_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  arr_ = new value_type[items.size()];
  int i = 0;
  for (value_type x : items) {
    arr_[i] = x;
    ++i;
  }
  size_ = i;
  capacity_ = i;
}

template <typename T> vector<T>::~vector() { destroy_vector(); }

template <typename T> void vector<T>::memory_allocation() {
  arr_ = new T[capacity_]();
}

template <typename T> void vector<T>::copy_vector(const vector &other) {
  for (size_t i = 0; i < size_; ++i) {
    arr_[i] = other.arr_[i];
  }
}

template <typename T> void vector<T>::destroy_vector() {
  if (arr_ != nullptr)
    delete[] arr_;
}

template <typename T> vector<T> &vector<T>::operator=(vector &&other) {
  if (this == &other) {
    size_ = 0;
    capacity_ = 0;
    return *this;
  }
  if (size_ != other.size_ || capacity_ != other.capacity_) {
    destroy_vector();
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.size_ = 0;
    other.capacity_ = 0;
    memory_allocation();
  }
  copy_vector(other);
  return *this;
}

template <typename T> T &vector<T>::at(size_t pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Error: out of range");
  }
  return arr_[pos];
}

template <typename T> T &vector<T>::operator[](size_t pos) { return arr_[pos]; }

template <typename T> const T &vector<T>::operator[](size_t pos) const {
  return arr_[pos];
}

template <typename T> T *vector<T>::data() { return &arr_[0]; }

template <typename T> const T *vector<T>::data() const { return &arr_[0]; }

template <typename T> bool vector<T>::empty() const {
  return (arr_ == nullptr);
}

template <typename T> size_t vector<T>::size() const { return size_; }

template <typename T> size_t vector<T>::capacity() const { return capacity_; }

template <typename T> void vector<T>::reserve(size_t new_size) {
  if (new_size > capacity_) {
    T *buff = new T[new_size];
    for (size_t i = 0; i < size_; ++i)
      buff[i] = arr_[i];
    delete[] arr_;
    arr_ = buff;
    capacity_ = new_size;
  }
}

template <typename T> void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    value_type *buff = new value_type[size_];
    for (size_t i = 0; i < size_; ++i)
      buff[i] = arr_[i];
    delete[] arr_;
    arr_ = buff;
    capacity_ = size_;
  }
}

template <typename T> void vector<T>::clear() {
  for (size_t i = 0; i < size_; ++i) {
    arr_[i] = T();
  }
  size_ = 0;
}

template <typename T> void vector<T>::shift(const T *pos, size_t len) {
  if (len && pos >= arr_ && pos <= arr_ + capacity_) {
    if (size_ + len <= capacity_) {
      size_ += len;
      T *src = arr_ + size_;
      T *dst = src + len;
      while (dst != pos) {
        *dst = *src;
        --dst;
        --src;
      }

    } else {
      capacity_ = size_ = size_ + len;
      T *buf = new T[size_];
      T *dst = buf;
      T *src = arr_;
      while (src != pos) {
        *dst = *src;
        ++dst;
        ++src;
      }
      dst += len;
      while (dst != buf + size_) {
        *dst = *src;
        ++dst;
        ++src;
      }
      delete[] arr_;
      arr_ = buf;
    }
  }
}

template <typename T>
T *vector<T>::insert(iterator pos, const_reference value) {
  if (arr_ == nullptr) {
    reserve(1);
    arr_[size_] = value;
    pos = &arr_[size_ + 1];
  } else {
    size_t position = pos - begin();
    if (size_ < capacity_) {
      arr_[position] = value;
    } else {
      capacity_ *= 2;
      T *buff = new T[capacity_]();
      size_t i = 0;
      for (; i < position; ++i) {
        buff[i] = arr_[i];
      }
      size_t j = i;
      ++i;
      if (position != capacity_) {
        for (; j < size_; ++i, ++j) {
          buff[i] = arr_[j];
        }
      }
      buff[position] = value;
      delete[] arr_;
      arr_ = buff;
    }
    pos = &arr_[position + 1];
  }
  ++size_;
  return pos;
}

template <typename T> void vector<T>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename T> void vector<T>::pop_back() { erase(&arr_[size() - 1]); }

template <typename T> void vector<T>::erase(iterator pos) {
  if (pos != end()) {
    std::move(pos + 1, end(), pos);
  }
  --size_;
}

template <typename T> size_t vector<T>::max_size() const {
  return SIZE_MAX / sizeof(T) / 2;
}

template <typename T> const T &vector<T>::front() const { return arr_[0]; }

template <typename T> T &vector<T>::front() { return arr_[0]; }

template <typename T> T &vector<T>::back() { return arr_[size_ - 1]; }

template <typename T> const T &vector<T>::back() const {
  return arr_[size_ - 1];
}

template <typename T> T *vector<T>::begin() const { return &arr_[0]; }

template <typename T> T *vector<T>::end() const { return &arr_[size_]; }

template <typename T> void vector<T>::swap(vector &other) {
  std::swap(arr_, other.arr_);
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
}

template <typename T>
template <typename... Args>
T *s21::vector<T>::emplace(T *pos, Args &&...args) {
  size_t iter = 0;
  if (pos >= begin() && pos <= end()) {
    iter = pos - arr_;
    size_t size = sizeof...(args);
    shift(pos, size);
    pos = arr_ + iter;
    ((*pos++ = args), ...);
  }
  return &arr_[iter];
}

template <typename T>
template <typename... Args>
void s21::vector<T>::emplace_back(Args &&...args) {
  if (capacity_ < size_ + sizeof...(args)) {
    reserve(size_ + sizeof...(args));
  }
  T *iter = end();
  ((*iter++ = args), ...);
  size_ += sizeof...(args);
}