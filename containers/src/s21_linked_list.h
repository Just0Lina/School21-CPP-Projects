#ifndef S21_LINKEDLIST_H
#define S21_LINKEDLIST_H
namespace s21 {

template <typename T>
struct Node {
  T value_;
  struct Node* next_;
};
}  // namespace s21
#endif