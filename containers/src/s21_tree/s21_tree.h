#ifndef S21_RBTREE_H
#define S21_RBTREE_H

#include <fstream>
#include <initializer_list>
#include <iostream>

namespace s21 {
enum node_colors { RED, BLACK };

template <typename Key, typename Value = char> struct Node {
  explicit Node(Key key, Value val = 0)
      : value(key, val), color(RED), parent(nullptr), left(nullptr),
        right(nullptr){};
  Node()
      : value(0, 0), color(RED), parent(nullptr), left(nullptr),
        right(nullptr){};
  Node(const Node &n)
      : value(n.key, n.value), color(n.color), parent(nullptr), left(nullptr),
        right(nullptr){};
  std::pair<Key, Value> value;

  enum node_colors color;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
};

template <typename Key, typename Value> class TreeIterator {
public:
  TreeIterator() = default;
  explicit TreeIterator(Node<Key, Value> *const &node,
                        Node<Key, Value> *const &fake);

  TreeIterator(const TreeIterator &iter) = default;
  TreeIterator &operator=(const TreeIterator &iter);
  std::pair<Key, Value> &operator*();
  std::pair<Key, Value> *operator->();
  TreeIterator &operator++();
  TreeIterator operator++(int);
  TreeIterator &operator--();
  TreeIterator operator--(int);
  bool operator!=(const TreeIterator &rhs) const;
  bool operator==(const TreeIterator &rhs) const;

public:
  Node<Key, Value> *iter_ = nullptr;
  const Node<Key, Value> *fake_node_ = nullptr;
};
#include "s21_tree_iterator.tpp"

template <typename Key, typename Value> class TreeConstIterator {
public:
  TreeConstIterator() = default;
  TreeConstIterator(const TreeConstIterator &it) = default;
  TreeConstIterator(TreeConstIterator &&it) = default;
  TreeConstIterator(Node<Key, Value> *const &node,
                    Node<Key, Value> *const &fake);
  explicit TreeConstIterator(const TreeIterator<Key, Value> &other)
      : iter_(other.iter_), fake_node_(other.fake_node_){};
  TreeConstIterator &operator=(TreeConstIterator &iter) = default;
  const std::pair<Key, Value> &operator*() const;
  const std::pair<Key, Value> *operator->();
  TreeConstIterator &operator++();
  TreeConstIterator operator++(int);
  TreeConstIterator &operator--();
  TreeConstIterator operator--(int);
  bool operator!=(const TreeConstIterator &rhs) const;
  bool operator==(const TreeConstIterator &rhs) const;

public:
  const Node<Key, Value> *iter_ = nullptr;
  const Node<Key, Value> *fake_node_ = nullptr;
};
#include "s21_tree_const_iterator.tpp"

template <typename Key, typename Value = char> class rb_tree {
public:
  using iterator = TreeIterator<const Key, Value>;
  using const_iterator = TreeConstIterator<const Key, Value>;
  using Node_type = Node<const Key, Value>;
  rb_tree();
  rb_tree(const rb_tree<Key, Value> &tree);
  rb_tree(rb_tree<Key, Value> &&tree);
  rb_tree &operator=(rb_tree &&m);
  ~rb_tree();
  bool insert(const std::pair<const Key, const Value> &value);
  bool insert_existing(Node_type *&new_node);
  iterator insert_any(const std::pair<const Key, Value> &value);
  void insert_any_existing(Node_type *&new_node);
  void insertion(Node_type *&new_node, Node_type *par,
                 const Node_type *pointer);
  void search(const Key &val, Node_type *&tmp) const;
  void print_func();
  void rb_delete(const Key val);
  void rb_delete(Node_type *deleting_node);
  Node_type *root();
  Key operator[](Node_type *ptr);
  void destroy(Node_type *node);
  inline Node_type *get_node(const Key &key);
  inline void change_node_relations(Node_type *new_node);
  bool get_pointer(Node_type *&pointer, Key value);
  void getting_fake_node();
  iterator begin() const;
  iterator end() const;

  bool contains(const Key &val) const;
  void clear();
  size_t size() const;
  size_t max_size() const;
  bool empty() const;
  void swap(Node_type *&root, Node_type *&fake, size_t &size);

  void ColorTree(Node_type *node, std::ofstream *stream) {
    if (!node->parent)
      *stream << " " << '_' << node->value.first << "_" << node << "[color="
              << ((node->color) ? "\"black\";];\n" : "\"red\";];\n");
    if (node->left != nullptr) {
      *stream << " " << '_' << node->left->value.first << "_" << node->left
              << " [color="
              << ((node->left->color) ? "\"black\";];\n" : "\"red\";];\n");
      ColorTree(node->left, stream);
    }

    if (node->right != nullptr) {
      *stream << " " << '_' << node->right->value.first << "_" << node->right
              << " [color="
              << ((node->right->color) ? "\"black\";];\n" : "\"red\";];\n");
      ColorTree(node->right, stream);
    }
  }

  void SaveTree(Node_type *node, std::ofstream *stream) {
    if (node->left != nullptr) {
      *stream << "  " << '_' << node->value.first << "_" << node << " -> "
              << '_' << node->left->value.first << "_" << node->left
              << std::endl;
      SaveTree(node->left, stream);
    }
    if (node->right != nullptr) {
      *stream << "  " << '_' << node->value.first << "_" << node << " -> "
              << '_' << node->right->value.first << "_" << node->right
              << std::endl;
      SaveTree(node->right, stream);
    }
  }

  void SaveTreeToDot(const std::string &file_name) {
    std::ofstream stream(file_name);
    if (stream.is_open()) {
      stream << "digraph {" << std::endl;
      ColorTree(this->root_, &stream);
      SaveTree(this->root_, &stream);
      stream << "}";
      stream.close();
    }
  }

public:
  size_t size_;
  Node_type *root_;
  Node_type *fake_node_;
  void copy_tree(rb_tree<Key, Value> *ptr);

private:
  void print(Node_type *node) const;
  void balance_fixup(Node_type *new_node);
  void balance_fixup_delete(Node_type *&node, Node_type *node_ptr);
  Node_type *transplant(Node_type *&node, Node_type *&child_node);
  Node_type *tree_max(Node_type *deleting_node);
  void deleting_node_with_one_child(Node_type *&deleting_node, Node_type *&ptr,
                                    Node_type *&ptr_parent);
  void deleting_node_with_two_children(Node_type *deleting_node,
                                       Node_type *&ptr, Node_type *&ptr_parent,
                                       int &original_color);
  void children_and_parents_switch(Node_type *node_for_change,
                                   Node_type *&node_child,
                                   Node_type *const child_for_change);
  void black_cousin_son(Node_type *cousin_son, Node_type *&cousin_other_son,
                        Node_type *cousin, Node_type *node_parent,
                        Node_type *&node);
  bool black_nephews(Node_type *cousin);
  void left_rotate(Node_type *node);
  void right_rotate(Node_type *node);
  void red_uncle(Node_type *uncle, Node_type *&node);
  void color_node(Node_type *node);
  void change_val(Node_type *&deleting_node);
  inline bool find_uncle(Node_type *node, Node_type *&uncle) const;
  inline bool red_parent_red_child(bool side, Node_type *node) const;
  void change_relations(Node_type *&child, Node_type *&node);
  void red_cousin_case(Node_type *&cousin, Node_type *&node_parent);
  void black_cousin_child(Node_type *const node_parent, Node_type *&cousin,
                          Node_type *&node);

protected:
  Node_type *minimum() const;
  Node_type *find_first(Key key, Node_type *node);
};
#include "s21_tree.tpp"

} // namespace s21

#endif
