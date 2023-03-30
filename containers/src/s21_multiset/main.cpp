#include <iostream>

#include "s21_multiset.h"
int main() {
  s21::multiset<int> s{1, 6, 5, 66, 22};
  s21::multiset<int> s_merge;

  s_merge.merge(s);
}