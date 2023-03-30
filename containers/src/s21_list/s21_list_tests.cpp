#include <gtest/gtest.h>

#include <iostream>
#include <list>

#include "s21_list.h"

template <typename T>
void check_lists(s21::list<T> &l, std::list<T> &sl) {
  ASSERT_EQ(l.size(), sl.size());
  ASSERT_EQ(l.front(), sl.front());
  ASSERT_EQ(l.back(), sl.back());
  auto i = l.begin();
  auto j = sl.begin();
  for (; i != l.end() && j != sl.end(); ++i, ++j) {
    ASSERT_EQ(*i, *j);
  }
  i = l.end();
  j = sl.end();
  --i;
  --j;
  for (; i != l.begin() && j != sl.begin(); --i, --j) {
    ASSERT_EQ(*i, *j);
  }
  if (!l.empty() && !sl.empty()) ASSERT_EQ(*i, *j);
}

template <typename T>
void show(const std::list<T> &l) {
  for (auto i = l.begin(); i != l.end(); ++i) std::cout << *i << ' ';
  std::cout << std::endl;
}

template <typename T>
void showback(const std::list<T> &l) {
  auto i = l.end();
  for (--i; i != l.begin(); --i) std::cout << *i << ' ';
  std::cout << *i << '\n';
}

TEST(init, def) {
  s21::list<int> l;
  std::list<int> ll;
  ASSERT_EQ(l.front(), ll.front());
  ASSERT_EQ(l.back(), ll.back());
}

TEST(init, init_list) {
  s21::list<int> l({1, 2, 3, 4, 5, 6});
  std::list<int> ll({1, 2, 3, 4, 5, 6});
  ASSERT_EQ(l.size(), ll.size());
  while (!l.empty()) {
    check_lists(l, ll);
    l.pop_front();
    ll.pop_front();
  }
}

TEST(init, copy) {
  s21::list<int> l({1, 2});
  s21::list<int> l_copy(l);
  std::list<int> sl({1, 2});
  std::list<int> sl_copy(sl);
  check_lists(l, sl);
  check_lists(l_copy, sl_copy);
}

TEST(iterator, begin_eq) {
  s21::list<int> l({1, 2, 3, 4, 5});
  ASSERT_FALSE(l.begin() != l.begin());
}

TEST(iterator, begin) {
  s21::list<int> l({1, 2, 3, 4, 5});
  std::list<int> ll({1, 2, 3, 4, 5});
  ASSERT_EQ(*l.begin(), *ll.begin());
}

TEST(iterator, end_prev) {
  s21::list<int> l({1, 2, 3, 4, 5});
  std::list<int> ll({1, 2, 3, 4, 5});
  auto i = l.end();
  auto j = ll.end();
  --i;
  --j;
  ASSERT_EQ(*i, *j);
}

TEST(iterator, minus) {
  s21::list<int> l({1, 2, 3, 4, 5});
  std::list<int> ll({1, 2, 3, 4, 5});
  auto i = l.end();
  auto j = ll.end();
  i--;
  j--;
  ASSERT_EQ(*i, *j);
}

TEST(iterator, plus) {
  s21::list<int> l({1, 2, 3, 4, 5});
  std::list<int> ll({1, 2, 3, 4, 5});
  auto i = l.begin();
  auto j = ll.begin();
  i++;
  j++;
  ASSERT_EQ(*i, *j);
}

TEST(iterator, const_dereference) {
  s21::list<int> l({1, 2, 3, 4, 5});
  std::list<int> ll({1, 2, 3, 4, 5});
  s21::list<int>::const_iterator i(l.begin());
  std::list<int>::const_iterator j = ll.begin();
  i++;
  j++;
  ASSERT_EQ(*i, *j);
}

TEST(init, same_lists) {
  s21::list<int> l({1, 7, 6, 5, 4, 3, 2, 1});
  std::list<int> ll({1, 7, 6, 5, 4, 3, 2, 1});
  auto i = l.begin();
  auto j = ll.begin();
  for (; i != l.end() && j != ll.end(); ++i, ++j) {
    ASSERT_EQ(*i, *j);
  }
}

TEST(init, same_lists_backwards) {
  s21::list<int> l({1, 7, 6, 5, 4, 3, 2, 1});
  std::list<int> ll({1, 7, 6, 5, 4, 3, 2, 1});
  auto i = l.end();
  auto j = ll.end();
  --i;
  --j;
  for (; i != l.begin() && j != ll.begin(); --i, --j) ASSERT_EQ(*i, *j);
  ASSERT_EQ(*i, *j);
}

TEST(init, move) {
  std::cout << "HERE\n";
  s21::list<int> l({1, 6, 5, 2, 3, 5, 1});
  s21::list<int> l_move(std::move(l));
  std::list<int> sl({1, 6, 5, 2, 3, 5, 1});
  std::list<int> sl_move(std::move(sl));
  ASSERT_EQ(l_move.size(), sl_move.size());
  ASSERT_EQ(l.size(), sl.size());
  check_lists(l_move, sl_move);
  check_lists(l, sl);
}

TEST(operator, move) {
  s21::list<int> l({1, 6, 5, 2, 3, 5, 1});
  s21::list<int> l_move;
  l_move = std::move(l);
  std::list<int> sl({1, 6, 5, 2, 3, 5, 1});
  std::list<int> sl_move;
  sl_move = std::move(sl);
  check_lists(l, sl);
  check_lists(l_move, sl_move);
}

TEST(push, back) {
  s21::list<int> l;
  std::list<int> sl;
  l.push_back(5);
  sl.push_back(5);
  check_lists(l, sl);
  l.push_back(10);
  sl.push_back(10);
  check_lists(l, sl);
}

TEST(push, front) {
  s21::list<int> l;
  std::list<int> sl;
  l.push_front(5);
  sl.push_front(5);
  check_lists(l, sl);
  l.push_front(10);
  sl.push_front(10);
  check_lists(l, sl);
}

TEST(push, for_front) {
  s21::list<int> l;
  std::list<int> sl;
  for (int i = 0; i < 100; ++i) {
    l.push_front(i);
    sl.push_front(i);
    check_lists(l, sl);
  }
}

TEST(push, for_back) {
  s21::list<int> l;
  std::list<int> sl;
  for (int i = 0; i < 100; ++i) {
    l.push_back(i);
    sl.push_back(i);
    check_lists(l, sl);
  }
}

TEST(pop, front) {
  s21::list<int> l({1, 2, 4, 5, 2, 1});
  std::list<int> sl({1, 2, 4, 5, 2, 1});
  check_lists(l, sl);
  l.pop_front();
  sl.pop_front();
  check_lists(l, sl);
}

TEST(pop, back) {
  s21::list<int> l({1, 2, 4, 5, 2, 1});
  std::list<int> sl({1, 2, 4, 5, 2, 1});
  check_lists(l, sl);
  l.pop_back();
  sl.pop_back();
  check_lists(l, sl);
}

TEST(pop, back_one) {
  s21::list<int> l({1});
  std::list<int> sl({1});
  check_lists(l, sl);
  l.pop_back();
  sl.pop_back();
  check_lists(l, sl);
}

TEST(pop, for_front) {
  s21::list<int> l({1, 2, 4, 5, 2, 1});
  std::list<int> sl({1, 2, 4, 5, 2, 1});
  for (int i = 0; i < l.size(); --i) {
    l.pop_front();
    sl.pop_front();
    check_lists(l, sl);
  }
}

TEST(pop, for_back) {
  s21::list<int> l({1, 2, 4, 5, 2, 1});
  std::list<int> sl({1, 2, 4, 5, 2, 1});
  for (int i = 0; i < l.size(); --i) {
    l.pop_back();
    sl.pop_back();
    check_lists(l, sl);
  }
}

TEST(funcs, clear) {
  s21::list<int> l({1, 5, 3, 5, 6, 2, 623, 31, 56});
  std::list<int> sl({1, 16, 12, 6, 123, 2, 6, 7});
  l.clear();
  sl.clear();
  ASSERT_EQ(l.size(), sl.size());
  ASSERT_EQ(l.empty(), sl.empty());
}

TEST(funcs, max_size) {
  std::list<int> sl;
  s21::list<int> l;
  std::list<std::string> ssl;
  s21::list<std::string> ll;
  ASSERT_EQ(sl.max_size(), l.max_size());
  ASSERT_EQ(ssl.max_size(), ll.max_size());
}

TEST(funcs, swap) {
  s21::list<int> l({1, 5, 6, 3, 2, 6});
  s21::list<int> l_swap({9, 7, 5, 4, 3, 3, 3, 2, 1, 2, 5});
  std::list<int> sl({1, 5, 6, 3, 2, 6});
  std::list<int> sl_swap({9, 7, 5, 4, 3, 3, 3, 2, 1, 2, 5});
  check_lists(l, sl);
  check_lists(l_swap, sl_swap);
  l.swap(l_swap);
  sl.swap(sl_swap);
  check_lists(l, sl);
  check_lists(l_swap, sl_swap);
}

TEST(funcs, swap_empty) {
  s21::list<int> l;
  s21::list<int> l_swap;
  std::list<int> ll;
  std::list<int> ll_swap;
  check_lists(l, ll);
  l.swap(l_swap);
  ll.swap(ll_swap);
  check_lists(l_swap, ll_swap);
  check_lists(l, ll);
}

TEST(funcs, merge) {
  s21::list<int> l({1, 5, 7, 11, 55});
  s21::list<int> l_merge({1, 7, 9, 22, 54, 55, 56});
  std::list<int> sl({1, 5, 7, 11, 55});
  std::list<int> sl_merge({1, 7, 9, 22, 54, 55, 56});
  l.merge(l_merge);
  sl.merge(sl_merge);
  check_lists(l, sl);
  check_lists(l_merge, sl_merge);
}

TEST(funcs, merge_empty) {
  s21::list<int> l;
  s21::list<int> ll({1, 2, 3, 4, 5});
  std::list<int> sl;
  std::list<int> ssl({1, 2, 3, 4, 5});
  l.merge(ll);
  sl.merge(ssl);
  check_lists(l, sl);
  check_lists(ll, ssl);
}

TEST(funcs, reverse) {
  s21::list<int> l({1, 5, 7, 11, 55});
  std::list<int> sl({1, 5, 7, 11, 55});
  l.reverse();
  sl.reverse();
  check_lists(l, sl);
}

TEST(funcs, reverse_empty) {
  s21::list<int> l;
  std::list<int> sl;
  l.reverse();
  sl.reverse();
  check_lists(l, sl);
}

TEST(funcs, unique) {
  s21::list<int> l({1, 1, 2, 3, 2, 5, 5, 5, 5, 5, 5, 1, 3, 5, 5});
  std::list<int> sl({1, 1, 2, 3, 2, 5, 5, 5, 5, 5, 5, 1, 3, 5, 5});
  l.unique();
  sl.unique();
  check_lists(l, sl);
}

TEST(funcs, sort) {
  s21::list<int> l({1, 6, 7, 42, 5, 6, 2, 5, 67, 7, 1, 2, 4, 2, 11});
  std::list<int> sl({1, 6, 7, 42, 5, 6, 2, 5, 67, 7, 1, 2, 4, 2, 11});
  l.sort();
  sl.sort();
  check_lists(l, sl);
}

TEST(funcs, sort_small) {
  s21::list<int> l({2, 1});
  std::list<int> sl({2, 1});
  l.sort();
  sl.sort();
  check_lists(l, sl);
}

TEST(funcs, sort_empty) {
  s21::list<int> l;
  std::list<int> sl;
  l.sort();
  sl.sort();
  check_lists(l, sl);
}

TEST(funcs, splice_empty) {
  s21::list<int> l({});
  s21::list<int> ll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  std::list<int> sl({});
  std::list<int> sll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  auto i = l.end();
  auto j = sl.end();
  l.splice(s21::list<int>::const_iterator(i), ll);
  sl.splice(j, sll);
  check_lists(l, sl);
}

TEST(funcs, splice_end) {
  s21::list<int> l({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  s21::list<int> ll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  std::list<int> sl({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  std::list<int> sll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  auto i = l.end();
  auto j = sl.end();
  l.splice(s21::list<int>::const_iterator(i), ll);
  sl.splice(j, sll);
  check_lists(l, sl);
}
TEST(funcs, splice_start) {
  s21::list<int> l({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  s21::list<int> ll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  std::list<int> sl({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  std::list<int> sll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  auto i = l.begin();
  auto j = sl.begin();
  l.splice(s21::list<int>::const_iterator(i), ll);
  sl.splice(j, sll);
  check_lists(l, sl);
}

TEST(funcs, splice_middle) {
  s21::list<int> l({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  s21::list<int> ll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  std::list<int> sl({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  std::list<int> sll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  auto i = l.begin();
  auto j = sl.begin();
  ++i;
  ++j;
  ++i;
  ++j;
  l.splice(s21::list<int>::const_iterator(i), ll);
  sl.splice(j, sll);
  check_lists(l, sl);
}

TEST(funcs, insert_start) {
  s21::list<int> l({1, 2});
  std::list<int> sl({1, 2});
  auto i = l.begin();
  auto j = sl.begin();
  l.insert(i, 5);
  sl.insert(j, 5);
  check_lists(l, sl);
}

TEST(funcs, insert_middle) {
  s21::list<int> l({1, 2, 3});
  std::list<int> sl({1, 2, 3});
  auto i = l.begin();
  auto j = sl.begin();
  ++i;
  ++j;
  l.insert(i, 5);
  sl.insert(j, 5);
  check_lists(l, sl);
}

TEST(funcs, insert_end) {
  s21::list<int> l({1, 2, 3});
  std::list<int> sl({1, 2, 3});
  auto i = l.end();
  auto j = sl.end();
  l.insert(i, 5);
  sl.insert(j, 5);
  check_lists(l, sl);
}

TEST(funcs, insert_empty) {
  s21::list<int> l;
  std::list<int> sl;
  auto i = l.begin();
  auto j = sl.begin();
  l.insert(i, 5);
  sl.insert(j, 5);
  check_lists(l, sl);
}

TEST(funcs, erase_start) {
  s21::list<int> l({1, 2});
  std::list<int> sl({1, 2});
  auto i = l.begin();
  auto j = sl.begin();
  l.erase(i);
  sl.erase(j);
  check_lists(l, sl);
}

TEST(funcs, erase_middle) {
  s21::list<int> l({1, 2, 3});
  std::list<int> sl({1, 2, 3});
  auto i = l.begin();
  auto j = sl.begin();
  ++i;
  ++j;
  l.erase(i);
  sl.erase(j);
  check_lists(l, sl);
}

TEST(funcs, erase_back_node) {
  s21::list<int> l({1, 2, 3});
  std::list<int> sl({1, 2, 3});
  auto i = l.end();
  auto j = sl.end();
  --i;
  --j;
  l.erase(i);
  sl.erase(j);
  check_lists(l, sl);
}

TEST(funcs, emplace_normal_value) {
  s21::list<int> l({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  std::list<int> sl({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  auto i = l.begin();
  auto j = sl.begin();
  ++(++(++(++i)));
  ++(++(++(++j)));
  l.emplace(s21::list<int>::const_iterator(i), 1, -2, 3, 4, 5);
  for (auto k : {1, -2, 3, 4, 5}) sl.insert(j, k);
  check_lists(l, sl);
}

TEST(funcs, emplace_empty) {
  s21::list<int> l({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  std::list<int> sl({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  auto i = l.begin();
  auto j = sl.begin();
  ++(++(++(++i)));
  ++(++(++(++j)));
  l.emplace(s21::list<int>::const_iterator(i));
  check_lists(l, sl);
}

TEST(funcs, emplace_empty_list) {
  s21::list<int> l({});
  std::list<int> sl({});
  auto i = l.begin();
  auto j = sl.begin();
  l.emplace(s21::list<int>::const_iterator(i), 1, 2, 3, 4, 5);
  for (auto k : {1, 2, 3, 4, 5}) sl.insert(j, k);
  check_lists(l, sl);
}

TEST(funcs, emplace_empty_all) {
  s21::list<int> l({});
  std::list<int> sl({});
  auto i = l.begin();
  l.emplace(s21::list<int>::const_iterator(i));
  check_lists(l, sl);
}

TEST(funcs, emplace_minus) {
  s21::list<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::list<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  auto i = l.end();
  auto j = sl.end();
  --(--(--(--i)));
  --(--(--(--j)));
  l.emplace(s21::list<int>::const_iterator(i), 1, 2, 33);
  for (auto k : {1, 2, 33}) sl.insert(j, k);
  check_lists(l, sl);
}

TEST(funcs, emplace_back_normal_value) {
  s21::list<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::list<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_back(-1, 2, 33);

  auto j = sl.end();
  for (auto k : {-1, 2, 33}) sl.insert(j, k);

  check_lists(l, sl);
}

TEST(funcs, emplace_back_empty) {
  s21::list<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::list<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_back();
  check_lists(l, sl);
}

TEST(funcs, emplace_back_empty_list) {
  s21::list<int> l({});
  std::list<int> sl({});
  l.emplace_back(1, 2, 3, 4, 5);

  auto j = sl.end();
  for (auto k : {1, 2, 3, 4, 5}) sl.insert(j, k);

  check_lists(l, sl);
}

TEST(funcs, emplace_back_empty_all) {
  s21::list<int> l({});
  std::list<int> sl({});
  l.emplace_back();

  check_lists(l, sl);
}

TEST(funcs, emplace_front_normal_value) {
  s21::list<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::list<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_front(-1, 2, 33);

  auto j = sl.begin();
  for (auto k : {-1, 2, 33}) sl.insert(j, k);

  check_lists(l, sl);
}

TEST(funcs, emplace_front_empty) {
  s21::list<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::list<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_front();
  check_lists(l, sl);
}

TEST(funcs, emplace_front_empty_list) {
  s21::list<int> l({});
  std::list<int> sl({});
  l.emplace_front(1, 2, 3, 4, 5);

  auto j = sl.begin();
  for (auto k : {1, 2, 3, 4, 5}) sl.insert(j, k);

  check_lists(l, sl);
}

TEST(funcs, emplace_front_empty_all) {
  s21::list<int> l({});
  std::list<int> sl({});
  l.emplace_front();

  check_lists(l, sl);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
