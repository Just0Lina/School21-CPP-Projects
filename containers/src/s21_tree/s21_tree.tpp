template <typename Key, typename Value> rb_tree<Key, Value>::~rb_tree() {
  destroy(root_);
  delete fake_node_;
}

template <typename Key, typename Value>
rb_tree<Key, Value>::rb_tree()
    : size_(0), root_(new Node<const Key, Value>{Key{}, Value{}}),
      fake_node_(root_) {}

template <typename Key, typename Value>
rb_tree<Key, Value>::rb_tree(const rb_tree<Key, Value> &m) : rb_tree() {
  for (auto &value : m) {
    insert_any(value);
  }
}

template <typename Key, typename Value>
rb_tree<Key, Value>::rb_tree(rb_tree<Key, Value> &&tree) : rb_tree() {
  root_ = tree.root_;
  std::swap(fake_node_, tree.fake_node_);
  size_ = tree.size_;
  tree.root_ = tree.fake_node_;
  tree.size_ = 0;
}

template <typename Key, typename Value>
rb_tree<Key, Value> &rb_tree<Key, Value>::operator=(rb_tree<Key, Value> &&m) {
  if (&m != this) {
    std::swap(root_, m.root_);
    std::swap(fake_node_, m.fake_node_);
    std::swap(size_, m.size_);
  }
  return *this;
}

template <typename Key, typename Value> void rb_tree<Key, Value>::clear() {
  destroy(root_);
  size_ = 0;
}

template <typename Key, typename Value>
inline void find_left(Node<const Key, Value> *&lstnd) {
  while (lstnd->left) {
    lstnd = lstnd->left;
  }
}

template <typename Key, typename Value>
void find_side(Node<const Key, Value> *node, bool &side) {
  if (node->parent) {
    if (node->parent->left &&
        node->parent->left->value.first == node->value.first)
      side = false;
    else
      side = true;
  }
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::destroy(Node<const Key, Value> *node) {
  if (fake_node_->parent)
    fake_node_->parent->right = nullptr;
  fake_node_->parent = nullptr;
  if (root_ && root_ != fake_node_) {
    Node_type *lstnd = node;
    bool side = false;
    Node_type *save_node = lstnd->parent;
    while (lstnd) {
      while (lstnd->right || lstnd->left) {
        find_left(lstnd);
        if (lstnd->right) {
          lstnd = lstnd->right;
          find_left(lstnd);
        }
      }
      save_node = lstnd->parent;
      if (save_node) {
        find_side(lstnd, side);
        if (side)
          save_node->right = nullptr;
        else
          save_node->left = nullptr;
      }
      delete lstnd;
      lstnd = save_node;
    }
    if (save_node) {
      delete save_node;
    }
    root_ = fake_node_;
  }
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::search(const Key &val, Node_type *&node_ptr) const {
  bool res = false;
  if (root_ != fake_node_) {
    node_ptr = root_;
    while (node_ptr && !res) {
      if (val > node_ptr->value.first) {
        node_ptr = node_ptr->right;
      } else if (val < node_ptr->value.first) {
        node_ptr = node_ptr->left;
      } else {
        if (node_ptr == fake_node_)
          break;
        res = true;
      }
    }
  }
  if (!res)
    node_ptr = fake_node_;
}

template <typename Key, typename Value>
bool rb_tree<Key, Value>::contains(const Key &val) const {
  Node_type *node_ptr = fake_node_;
  search(val, node_ptr);
  return node_ptr != fake_node_;
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::rb_delete(Node_type *deleting_node) {
  fake_node_->parent->right = nullptr;
  if (deleting_node && deleting_node != fake_node_) {
    Node_type *ptr = nullptr;
    Node_type *ptr_parent = nullptr;
    int original_color = deleting_node->color;
    if (deleting_node->left && deleting_node->right) {
      deleting_node_with_two_children(deleting_node, ptr, ptr_parent,
                                      original_color);
    } else {
      deleting_node_with_one_child(deleting_node, ptr, ptr_parent);
    }
    --size_;
    if (original_color == BLACK)
      balance_fixup_delete(ptr, ptr_parent);
  }
  if (fake_node_->parent) {
    fake_node_->parent->right = fake_node_;
  }
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::deleting_node_with_two_children(
    Node_type *deleting_node, Node_type *&ptr, Node_type *&ptr_parent,
    int &original_color) {
  Node_type *change_node = tree_max(deleting_node->left);
  original_color = change_node->color;
  ptr = change_node->left;
  if (change_node->parent == deleting_node) {
    ptr_parent = change_node;
  } else {
    ptr_parent = transplant(change_node, change_node->left);
    children_and_parents_switch(change_node, change_node->left,
                                deleting_node->left);
  }
  transplant(deleting_node, change_node);
  children_and_parents_switch(change_node, change_node->right,
                              deleting_node->right);
  change_node->color = deleting_node->color;
  delete deleting_node;
}

template <typename Key, typename Value>
inline void rb_tree<Key, Value>::children_and_parents_switch(
    Node_type *node_for_change, Node_type *&node_child,
    Node_type *const child_for_change) {
  node_child = child_for_change;
  node_child->parent = node_for_change;
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::deleting_node_with_one_child(
    Node_type *&deleting_node, Node_type *&ptr, Node_type *&ptr_parent) {
  if (deleting_node->left == nullptr) {
    ptr = deleting_node->right;
    ptr_parent = transplant(deleting_node, deleting_node->right);
  } else if (deleting_node->right == nullptr) {
    ptr = deleting_node->left;
    ptr_parent = transplant(deleting_node, deleting_node->left);
  }
  if (deleting_node == fake_node_->parent) {
    if (ptr == nullptr) {
      if (ptr_parent == nullptr) {
        fake_node_->parent = fake_node_;
        root_ = fake_node_;
      } else
        fake_node_->parent = ptr_parent;
    } else {
      fake_node_->parent = ptr;
    }
  }
  delete deleting_node;
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::rb_delete(const Key val) {
  Node_type *deleting_node;
  search(val, deleting_node);
  if (deleting_node) {
    rb_delete(deleting_node);
  }
}

template <typename Key, typename Value>
inline Node<const Key, Value> *rb_tree<Key, Value>::tree_max(Node_type *node) {
  while (node->right)
    node = node->right;
  return node;
}

template <typename Key, typename Value>
Node<const Key, Value> *
rb_tree<Key, Value>::transplant(Node_type *&node, Node_type *&child_node) {
  if (!node->parent) {
    root_ = child_node;
  } else if (node == node->parent->left) {
    node->parent->left = child_node;
  } else {
    node->parent->right = child_node;
  }
  if (child_node) {
    child_node->parent = node->parent;
  }
  return node->parent;
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::red_cousin_case(Node_type *&cousin,
                                          Node_type *&node_parent) {
  cousin->color = BLACK;
  node_parent->color = RED;
  if (node_parent->right == cousin) {
    left_rotate(node_parent);
    cousin = node_parent->right;
  } else {
    right_rotate(node_parent);
    cousin = node_parent->left;
  }
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::balance_fixup_delete(Node_type *&node,
                                               Node_type *node_parent) {
  while (node_parent && (!node || (node != root_ && node->color == BLACK))) {
    Node_type *cousin;
    if (node == node_parent->left) {
      cousin = node_parent->right;
    } else {
      cousin = node_parent->left;
    }
    if (cousin) {
      if (cousin->color == RED) {
        red_cousin_case(cousin, node_parent);
      }
      if (black_nephews(cousin)) {
        cousin->color = RED;
        node = node_parent;
        node_parent = node_parent->parent;
      } else {
        black_cousin_child(node_parent, cousin, node);
      }
    }
  }
  if (node)
    node->color = BLACK;
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::black_cousin_child(Node_type *const node_parent,
                                             Node_type *&cousin,
                                             Node_type *&node) {
  if (node_parent->right == cousin) {
    black_cousin_son(cousin->right, cousin->left, cousin, node_parent, node);
  } else {
    black_cousin_son(cousin->left, cousin->right, cousin, node_parent, node);
  }
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::black_cousin_son(Node_type *cousin_son,
                                           Node_type *&cousin_other_son,
                                           Node_type *cousin,
                                           Node_type *node_parent,
                                           Node_type *&node) {
  if (!cousin_son || cousin_son->color == BLACK) {
    cousin_other_son->color = BLACK;
    cousin->color = RED;
    if (node_parent->right == cousin) {
      right_rotate(cousin);
      cousin = node_parent->right;
      cousin_son = cousin->right;
      cousin_other_son = cousin->left;
    } else {
      left_rotate(cousin);
      cousin = node_parent->left;
      cousin_son = cousin->left;
      cousin_other_son = cousin->right;
    }
  }
  cousin->color = node_parent->color;
  node_parent->color = BLACK;
  if (cousin_son)
    cousin_son->color = BLACK;
  if (node_parent->right == cousin) {
    left_rotate(node_parent);
  } else {
    right_rotate(node_parent);
  }
  node = root_;
}

template <typename Key, typename Value>
inline Node<const Key, Value> *rb_tree<Key, Value>::root() {
  return root_;
}

template <typename Key, typename Value>
inline Key rb_tree<Key, Value>::operator[](Node_type *ptr) {
  return ptr->value.first;
}

template <typename Key, typename Value>
inline bool rb_tree<Key, Value>::black_nephews(Node_type *cousin) {
  return (!cousin->left || cousin->left->color == BLACK) &&
         (!cousin->right || cousin->right->color == BLACK);
}

template <typename Key, typename Value>
TreeIterator<const Key, Value>
rb_tree<Key, Value>::insert_any(const std::pair<const Key, Value> &value) {
  Node_type *par = nullptr;
  Node_type *pointer = root_;
  while (pointer && pointer != fake_node_) {
    par = pointer;
    if (get_pointer(pointer, value.first))
      break;
  }
  Node_type *new_node = new Node<const Key, Value>{value.first, value.second};
  insertion(new_node, par, pointer);
  return TreeIterator<const Key, Value>(new_node, fake_node_);
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::insert_any_existing(Node_type *&new_node) {
  Node_type *par = nullptr;
  Node_type *pointer = root_;
  change_node_relations(new_node);
  while (pointer && pointer != fake_node_) {
    par = pointer;
    if (get_pointer(pointer, new_node->value.first))
      break;
  }
  insertion(new_node, par, pointer);
}

template <typename Key, typename Value>
bool rb_tree<Key, Value>::insert_existing(Node_type *&new_node) {
  Node_type *par = nullptr;
  Node_type *pointer = root_;
  change_node_relations(new_node);
  while (pointer && pointer != fake_node_) {
    par = pointer;
    if (new_node->value.first == pointer->value.first) {
      return false;
    }
    if (get_pointer(pointer, new_node->value.first))
      break;
  }
  insertion(new_node, par, pointer);
  return true;
}

template <typename Key, typename Value>
bool rb_tree<Key, Value>::insert(
    const std::pair<const Key, const Value> &value) {
  Node_type *par = nullptr;
  Node_type *pointer = root_;
  while (pointer && pointer != fake_node_) {
    par = pointer;
    if (value.first == pointer->value.first) {
      return false;
    }
    if (get_pointer(pointer, value.first))
      break;
  }
  Node_type *new_node = new Node<const Key, Value>{value.first, value.second};
  insertion(new_node, par, pointer);
  return true;
}

template <typename Key, typename Value>
inline void
rb_tree<Key, Value>::change_node_relations(Node<const Key, Value> *new_node) {
  new_node->left = new_node->right = new_node->parent = nullptr;
  new_node->color = RED;
}

template <typename Key, typename Value>
inline bool rb_tree<Key, Value>::get_pointer(Node<const Key, Value> *&pointer,
                                             Key value) {
  int ret = 0;
  if (value < pointer->value.first) {
    pointer = pointer->left;
  } else if (pointer->right != fake_node_) {
    pointer = pointer->right;
  } else {
    ret = 1;
  }
  return ret;
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::insertion(Node_type *&new_node,
                                    Node<const Key, Value> *par,
                                    const Node<const Key, Value> *pointer) {
  ++size_;
  new_node->parent = par;
  if (!par) {
    root_ = new_node;
    fake_node_->parent = new_node;
    root_->right = fake_node_;
  } else if (new_node->value.first < par->value.first) {
    par->left = new_node;
  } else {
    par->right = new_node;
    if (par == pointer || pointer == fake_node_) {
      fake_node_->parent = new_node;
      par->right->right = fake_node_;
    }
  }
  balance_fixup(new_node);
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::balance_fixup(Node_type *node) {
  fake_node_->parent->right = nullptr;
  while (node->parent && node->parent->color == RED) {
    Node_type *uncle;
    bool uncle_side = find_uncle(node, uncle);
    if (uncle && uncle->color == RED) {
      red_uncle(uncle, node);
    } else {
      if (red_parent_red_child(uncle_side, node)) {
        node = node->parent;
        if (!uncle_side)
          left_rotate(node);
        else
          right_rotate(node);
      }
      color_node(node);
      if (!uncle_side)
        right_rotate(node->parent->parent);
      else
        left_rotate(node->parent->parent);
    }
  }
  if (fake_node_->parent->right) {
    fake_node_->parent = fake_node_->parent->right;
  }
  fake_node_->parent->right = fake_node_;
  root_->color = BLACK;
}

template <typename Key, typename Value>
inline bool rb_tree<Key, Value>::red_parent_red_child(bool uncle_side,
                                                      Node_type *node) const {
  return (!uncle_side && node == node->parent->right) ||
         (uncle_side && node == node->parent->left);
}

template <typename Key, typename Value>
bool rb_tree<Key, Value>::find_uncle(Node_type *node, Node_type *&uncle) const {
  bool flag = 0;
  if (node->parent == node->parent->parent->left) {
    uncle = node->parent->parent->right;
  } else {
    uncle = node->parent->parent->left;
    flag = 1;
  }
  return flag;
}

template <typename Key, typename Value>
inline void rb_tree<Key, Value>::color_node(Node_type *node) {
  node->parent->color = BLACK;
  node->parent->parent->color = RED;
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::red_uncle(Node_type *uncle, Node_type *&node) {
  node->parent->color = BLACK;
  uncle->color = BLACK;
  node->parent->parent->color = RED;
  node = node->parent->parent;
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::change_relations(Node_type *&child,
                                           Node_type *&node) {
  child->parent = node->parent;
  if (!node->parent)
    root_ = child;
  else if (node == node->parent->left)
    node->parent->left = child;
  else
    node->parent->right = child;
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::left_rotate(Node_type *node) {
  Node_type *child = node->right;
  node->right = child->left;
  if (child->left)
    child->left->parent = node;
  change_relations(child, node);
  child->left = node;
  node->parent = child;
}

template <typename Key, typename Value>
void rb_tree<Key, Value>::right_rotate(Node_type *node) {
  Node_type *child = node->left;
  node->left = child->right;
  if (child->right)
    child->right->parent = node;
  change_relations(child, node);
  child->right = node;
  node->parent = child;
}

template <typename Key, typename Value>
inline size_t rb_tree<Key, Value>::size() const {
  return size_;
}

template <typename Key, typename Value>
inline size_t rb_tree<Key, Value>::max_size() const {
  return SIZE_MAX / sizeof(Node<const Key, Value>) / 2;
}

template <typename Key, typename Value>
Node<const Key, Value> *rb_tree<Key, Value>::minimum() const {
  Node<const Key, Value> *iter = root_;
  if (!empty()) {
    while (iter && iter->left != nullptr)
      iter = iter->left;
  }
  return iter;
}

template <typename Key, typename Value>
typename rb_tree<Key, Value>::iterator rb_tree<Key, Value>::begin() const {
  return rb_tree<Key, Value>::iterator(minimum(), fake_node_);
}

template <typename Key, typename Value>
inline typename rb_tree<Key, Value>::iterator rb_tree<Key, Value>::end() const {
  return TreeIterator(fake_node_, fake_node_);
}

template <typename Key, typename Value>
inline bool rb_tree<Key, Value>::empty() const {
  return root_ == fake_node_;
}

template <typename Key, typename Value>
Node<const Key, Value> *rb_tree<Key, Value>::get_node(const Key &key) {
  Node<const Key, Value> *search_node;
  search(key, search_node);
  if (!search_node) {
    throw std::out_of_range("Error: out of range");
  }
  return search_node;
}

template <typename Key, typename Value>
inline void rb_tree<Key, Value>::swap(Node_type *&root, Node_type *&fake,
                                      size_t &size) {
  std::swap(root_, root);
  std::swap(fake_node_, fake);
  std::swap(size_, size);
}

template <typename Key, typename Value>
Node<const Key, Value> *rb_tree<Key, Value>::find_first(Key key,
                                                        Node_type *start) {
  if (root_ != fake_node_) {
    if (start) {
      while (start && start->value.first < key) {
        if (key >= start->value.first) {
          start = start->right;
        } else {
          start = start->left;
        }
      }
      Node_type *temp = nullptr;
      if (start && start->left)
        temp = find_first(key, start->left);
      if (temp && temp->value.first >= key && temp != start)
        return temp;
    }
  }
  return (start) ? start : fake_node_;
}
