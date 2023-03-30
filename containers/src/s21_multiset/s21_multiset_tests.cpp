#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "s21_multiset.h"

template <typename Key>
void comparison(s21::multiset<Key> &map_a, std::multiset<Key> &map_b);

TEST(constructors, init) {
  s21::multiset<int> ss;
  std::multiset<int> os;
  ASSERT_EQ(ss.empty(), os.empty());
  ASSERT_EQ(ss.size(), os.size());
}

TEST(funcs, insert) {
  s21::multiset<int> ss;
  std::multiset<int> os;
  ss.insert(5);
  os.insert(5);
  ASSERT_EQ(ss.empty(), os.empty());
  ASSERT_EQ(ss.size(), os.size());
  ss.insert(11);
  os.insert(11);
  ASSERT_EQ(ss.empty(), os.empty());
  ASSERT_EQ(ss.size(), os.size());
  ss.insert(2);
  os.insert(2);
  ASSERT_EQ(ss.empty(), os.empty());
  ASSERT_EQ(ss.size(), os.size());
}

TEST(funcs, clear) {
  s21::multiset<int> ss(
      {1, 2, 3, 4, 5, 8, 11, 22, 33, 44, 15, 23, -123, -55, -12, -63, -1000});
  std::multiset<int> os(
      {1, 2, 3, 4, 5, 8, 11, 22, 33, 44, 15, 23, -123, -55, -12, -63, -1000});
  ss.clear();
  os.clear();
  ASSERT_EQ(ss.empty(), os.empty());
}

TEST(constructors, init_list) {
  s21::multiset<int> ss({2, 3});
  std::multiset<int> os({2, 3});
  ASSERT_EQ(ss.empty(), os.empty());
  ASSERT_EQ(ss.size(), os.size());
}

TEST(iter, begin) {
  s21::multiset<int> ss({2, 3});
  std::multiset<int> os({2, 3});
  ASSERT_EQ(*ss.begin(), *os.begin());
}

TEST(iter, begin_eq_end) {
  s21::multiset<int> ss;
  std::multiset<int> os;
  ASSERT_EQ(ss.begin(), ss.end());
  ASSERT_EQ(os.begin(), os.end());
}

TEST(iter, PlusPlusOp) {
  s21::multiset<int> ss({2, 3});
  std::multiset<int> os({2, 3});
  auto sit{ss.begin()};
  auto oit{os.begin()};
  ++sit;
  ++oit;
  ASSERT_EQ(*sit, *oit);
}

TEST(iter, MinusMinusOp) {
  s21::multiset<int> ss({2, 3});
  std::multiset<int> os({2, 3});
  auto sit{ss.end()};
  auto oit(os.end());
  --sit;
  --oit;
  ASSERT_EQ(*sit, *oit);
}

TEST(iter, OpPlusPlus) {
  s21::multiset<int> ss({2, 3});
  std::multiset<int> os({2, 3});
  auto sit{ss.begin()};
  auto oit(os.begin());
  auto sold = sit++;
  auto oold = oit++;
  ASSERT_EQ(*sit, *oit);
  ASSERT_EQ(*sold, *oold);
}
TEST(iter, OpMinusMinus) {
  s21::multiset<int> ss({2, 3});
  std::multiset<int> os({2, 3});
  auto sit{--ss.end()};
  auto oit(--os.end());
  auto sold = sit--;
  auto oold = oit--;
  ASSERT_EQ(*sit, *oit);
  ASSERT_EQ(*sold, *oold);
}

TEST(iter, begin_to_end) {
  s21::multiset<int> ss({1,  2,  3,  4, 5, 5, 5, 5,  5, 8,  11, 22, 33, 44, 15,
                         11, 15, 15, 3, 3, 4, 2, 11, 8, 33, 33, 1,  1,  1});
  std::multiset<int> os({1,  2,  3,  4, 5, 5, 5, 5,  5, 8,  11, 22, 33, 44, 15,
                         11, 15, 15, 3, 3, 4, 2, 11, 8, 33, 33, 1,  1,  1});
  auto sit = ss.begin();
  auto oit = os.begin();
  for (; sit != ss.end() && oit != os.end(); ++sit, ++oit) {
    ASSERT_EQ(*sit, *oit);
  }
}

TEST(iter, end_to_begin) {
  s21::multiset<int> ss({1,  2,  3,  4, 5, 5, 5, 5,  5, 8,  11, 22, 33, 44, 15,
                         11, 15, 15, 3, 3, 4, 2, 11, 8, 33, 33, 1,  1,  1});
  std::multiset<int> os({1,  2,  3,  4, 5, 5, 5, 5,  5, 8,  11, 22, 33, 44, 15,
                         11, 15, 15, 3, 3, 4, 2, 11, 8, 33, 33, 1,  1,  1});
  ss.SaveTreeToDot("tree.dot");
  auto sit = --ss.end();
  auto oit = --os.end();
  for (; sit != ss.begin() && oit != os.begin(); --sit, --oit) {
    ASSERT_EQ(*sit, *oit);
  }
  ASSERT_EQ(*sit, *oit);
}

TEST(constructors, copy) {
  s21::multiset<int> s({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  s21::multiset<int> s_copy(s);
  std::multiset<int> os({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  std::multiset<int> os_copy(os);
  comparison(s, os);
  comparison(s_copy, os_copy);
  comparison(s, os);
}

TEST(constructors, move) {
  s21::multiset<int> s({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  s21::multiset<int> s_move(std::move(s));
  std::multiset<int> os({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  std::multiset<int> os_move(std::move(os));
  comparison(s, os);
  comparison(s_move, os_move);
}

TEST(constructors, oper_move) {
  s21::multiset<int> s({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  s21::multiset<int> s_move({1, 5, 3, 2});
  std::multiset<int> os({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  std::multiset<int> os_move({1, 5, 3, 2});
  s_move = std::move(s);
  os_move = std::move(os);
  comparison(s_move, os_move);
}

TEST(lookup, contains) {
  s21::multiset<int> s({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  ASSERT_TRUE(s.contains(55));
  ASSERT_TRUE(s.contains(11));
  ASSERT_FALSE(s.contains(int{}));

  s21::multiset<int> empty;
  ASSERT_FALSE(s.contains(int{}));
}

TEST(insert, ins1) {
  s21::multiset<int> ss;
  std::multiset<int> os;
  ss.insert(33);
  ss.insert(34);
  ss.insert(33);
  os.insert(33);
  os.insert(34);
  os.insert(33);
  comparison(ss, os);
}

TEST(funcs, insert_return) {
  s21::multiset<int> s({1, 6, 5, 66, 22});
  auto p = s.insert(67);
  ASSERT_EQ(*p, *(--s.end()));
  p = s.insert(1);
  ASSERT_EQ(*p, *(++s.begin()));
}

TEST(funcs, max_size) {
  s21::multiset<int> s;
  std::multiset<int> os;
  ASSERT_EQ(s.max_size(), os.max_size());
}

TEST(lookup, find) {
  s21::multiset<int> s({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  auto it = s.find(12);
  ASSERT_EQ(*it, 12);
  it = s.find(0);
  ASSERT_TRUE(it == s.end());
  it = s.find(1111111);
  ASSERT_TRUE(it == s.end());
}

TEST(lookup, find2) {
  s21::multiset<int> ss({1, 6, 5, 77, 22, 3, 55, 12, 12, 12, 15, 11});
  std::multiset<int> os({1, 6, 5, 77, 22, 3, 55, 12, 12, 12, 15, 11});

  auto it1 = ss.find(12);
  auto it2 = os.find(12);

  for (; it1 != ss.end() && it2 != os.end(); ++it1, ++it2) {
    ASSERT_EQ(*it1, *it2);
  }
}

TEST(funcs, equal_range) {
  s21::multiset<int> ss({1,  2,  3,  4, 5, 5, 5, 5,  5, 8,  11, 22, 33, 44, 15,
                         11, 15, 15, 3, 3, 4, 2, 11, 8, 33, 33, 1,  1,  1});
  std::multiset<int> os({1,  2,  3,  4, 5, 5, 5, 5,  5, 8,  11, 22, 33, 44, 15,
                         11, 15, 15, 3, 3, 4, 2, 11, 8, 33, 33, 1,  1,  1});
  auto sit = ss.equal_range(5);
  auto oit = os.equal_range(5);
  auto it1 = sit.first;
  auto it2 = oit.first;
  for (; it1 != sit.second && it2 != oit.second; ++it1, ++it2) {
    ASSERT_EQ(*it1, *it2);
  }
}

TEST(funcs, lower_bound) {
  s21::multiset<int> ss(
      {1, 2, 3, 4, 5, 5, 5, 5, 5, 8, 11, 22, 33, 5, 5, 44, 15});
  std::multiset<int> os(
      {1, 2, 3, 4, 5, 5, 5, 5, 5, 8, 11, 22, 33, 5, 5, 44, 15});
  auto sit = ss.lower_bound(5);
  auto oit = os.lower_bound(5);
  for (; sit != ss.end() && oit != os.end(); ++sit, ++oit) {
    ASSERT_EQ(*sit, *oit);
  }
}

TEST(funcs, lower_bound2) {
  s21::multiset<int> ss(
      {1, 2, 3, 4, 5, 5, 5, 5, 5, 8, 11, 22, 33, 5, 5, 44, 15});
  std::multiset<int> os(
      {1, 2, 3, 4, 5, 5, 5, 5, 5, 8, 11, 22, 33, 5, 5, 44, 15});
  auto sit = ss.lower_bound(9);
  auto oit = os.lower_bound(9);
  for (; sit != ss.end() && oit != os.end(); ++sit, ++oit) {
    ASSERT_EQ(*sit, *oit);
  }
}

TEST(funcs, upper_bound) {
  s21::multiset<int> ss(
      {1, 2, 3, 4, 5, 5, 5, 5, 5, 8, 11, 22, 33, 5, 5, 44, 15});
  std::multiset<int> os(
      {1, 2, 3, 4, 5, 5, 5, 5, 5, 8, 11, 22, 33, 5, 5, 44, 15});
  auto sit = ss.upper_bound(5);
  auto oit = os.upper_bound(5);
  for (; sit != ss.end() && oit != os.end(); ++sit, ++oit) {
    ASSERT_EQ(*sit, *oit);
  }
}

TEST(funcs, upper_bound2) {
  s21::multiset<int> ss(
      {1, 2, 3, 4, 5, 5, 5, 5, 5, 8, 11, 22, 33, 5, 5, 44, 15});
  std::multiset<int> os(
      {1, 2, 3, 4, 5, 5, 5, 5, 5, 8, 11, 22, 33, 5, 5, 44, 15});
  auto sit = ss.upper_bound(7);
  auto oit = os.upper_bound(7);
  for (; sit != ss.end() && oit != os.end(); ++sit, ++oit) {
    ASSERT_EQ(*sit, *oit);
  }
}

TEST(funcs, count1) {
  s21::multiset<int> ss(
      {1, 2, 3, 4, 5, 5, 5, 5, 5, 8, 11, 22, 33, 5, 5, 44, 15});
  std::multiset<int> os(
      {1, 2, 3, 4, 5, 5, 5, 5, 5, 8, 11, 22, 33, 5, 5, 44, 15});
  auto sit = ss.count(5);
  auto oit = os.count(5);
  ASSERT_EQ(sit, oit);
}

TEST(funcs, count2) {
  s21::multiset<int> ss({1, 2, 3, 4, 8, 11, 22, 33, 44, 15});
  std::multiset<int> os({1, 2, 3, 4, 8, 11, 22, 33, 44, 15});
  auto sit = ss.count(5);
  auto oit = os.count(5);
  ASSERT_EQ(sit, oit);
}

TEST(funcs, erase_begin) {
  s21::multiset<int> s({1, 6, 5, 66, 22, 111, 223, 512, 33});
  std::multiset<int> os({1, 6, 5, 66, 22, 111, 223, 512, 33});
  for (size_t size = s.size(); size > 0; --size) {
    s.erase(s.begin());
    os.erase(os.begin());
    comparison(s, os);
  }
}

TEST(funcs, erase_end) {
  s21::multiset<int> s({1, 6, 5, 66, 22, 111, 223, 512, 33});
  std::multiset<int> os({1, 6, 5, 66, 22, 111, 223, 512, 33});
  for (size_t size = s.size(); size > 0; --size) {
    s.erase(--(s.end()));
    os.erase(--(os.end()));
    comparison(s, os);
  }
}

TEST(funcs, erase_middle) {
  s21::multiset<int> s({1, 6, 5, 66, 22, 111, 223, 512, 33});
  std::multiset<int> os({1, 6, 5, 66, 22, 111, 223, 512, 33});
  for (size_t size = 0; size < 3; ++size) {
    s.erase(++(++(s.begin())));
    os.erase(++(++(os.begin())));
    comparison(s, os);
  }
}

TEST(funcs, swap) {
  s21::multiset<int> s({1, 6, 5, 66, 22});
  s21::multiset<int> s_swap;
  std::multiset<int> os({1, 6, 5, 66, 22});
  std::multiset<int> os_swap;
  s_swap.swap(s);
  os_swap.swap(os);
  comparison(s_swap, os_swap);
  comparison(s, os);
}

TEST(funcs, emplace_normal_value) {
  s21::multiset<int> l({1, 5, 6, 2, 3, 4, 5, 22, 11, 5, 1});
  std::multiset<int> sl({1, 5, 6, 2, 3, 4, 5, 22, 11, 5, 1});
  l.emplace(1, 999, 3, 4, 5);
  for (auto k : {1, 999, 3, 4, 5}) sl.insert(k);
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  comparison(l, sl);
}

TEST(funcs, emplace_empty) {
  s21::multiset<int> l({});
  std::multiset<int> sl({});
  l.emplace(1, -2, 3, 4, 5);
  for (auto k : {1, -2, 3, 4, 5}) sl.insert(k);
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  comparison(l, sl);
}

TEST(funcs, emplace_empty_insert) {
  s21::multiset<int> l({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  std::multiset<int> sl({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  l.emplace();
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  comparison(l, sl);
}

TEST(funcs, emplace_empty_all) {
  s21::multiset<int> l({});
  std::multiset<int> sl({});
  l.emplace();
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  comparison(l, sl);
}

TEST(funcs, merge_empty) {
  s21::multiset<int> s{1, 6, 5, 66, 22};
  s21::multiset<int> s_merge;
  std::multiset<int> os{1, 6, 5, 66, 22};
  std::multiset<int> os_merge;
  s_merge.merge(s);
  os_merge.merge(os);
  comparison(s_merge, os_merge);
  comparison(s, os);
}

TEST(funcs, merge_no_repetition) {
  s21::multiset<int> s({1, 6, 5, 66, 22});
  s21::multiset<int> s_merge({2, 52, 50, 51, 44, 23});
  std::multiset<int> os({1, 6, 5, 66, 22});
  std::multiset<int> os_merge({2, 52, 50, 51, 44, 23});

  s_merge.merge(s);
  os_merge.merge(os);
  comparison(s_merge, os_merge);
  comparison(s, os);
}

TEST(funcs, merge_repetition) {
  s21::multiset<int> s({1, 6, 5, 66, 22, 50, 51, 44, 23, 2});
  s21::multiset<int> s_merge({2, 52, 50, 51, 44, 23, 66, 66});
  std::multiset<int> os({1, 6, 5, 66, 22, 50, 51, 44, 23, 2});
  std::multiset<int> os_merge({2, 52, 50, 51, 44, 23, 66, 66});

  s_merge.merge(s);
  os_merge.merge(os);
  comparison(s_merge, os_merge);
  comparison(s, os);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template <typename Key>
void comparison(s21::multiset<Key> &mset_a, std::multiset<Key> &mset_b) {
  ASSERT_EQ(mset_a.size(), mset_b.size());
  typename s21::multiset<Key>::iterator it1 = mset_a.begin();
  typename std::multiset<Key>::iterator it2 = mset_b.begin();
  for (; it1 != mset_a.end(); ++it1, ++it2) {
    ASSERT_EQ(*it1, *it2);
  }
}