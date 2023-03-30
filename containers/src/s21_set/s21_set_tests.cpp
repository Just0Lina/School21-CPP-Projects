#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "s21_set.h"

TEST(constructors, init) {
  s21::set<int> ss;
  std::set<int> os;
  ASSERT_EQ(ss.empty(), os.empty());
  ASSERT_EQ(ss.size(), os.size());
}

TEST(funcs, insert) {
  s21::set<int> ss;
  std::set<int> os;
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
  ss.insert(2);
  os.insert(2);
  ASSERT_EQ(ss.empty(), os.empty());
  ASSERT_EQ(ss.size(), os.size());
}

TEST(constructors, init_list) {
  s21::set<int> ss({2, 3});
  std::set<int> os({2, 3});
  ASSERT_EQ(ss.empty(), os.empty());
  ASSERT_EQ(ss.size(), os.size());
}

TEST(iter, begin) {
  s21::set<int> ss({2, 3});
  std::set<int> os({2, 3});
  ASSERT_EQ(*ss.begin(), *os.begin());
}

TEST(iter, begin_eq_end) {
  s21::set<int> ss;
  std::set<int> os;
  ASSERT_EQ(ss.begin(), ss.end());
  ASSERT_EQ(os.begin(), os.end());
}

TEST(iter, PlusPlusOp) {
  s21::set<int> ss({2, 3});
  std::set<int> os({2, 3});
  auto sit{ss.begin()};
  auto oit{os.begin()};
  ++sit;
  ++oit;
  ASSERT_EQ(*sit, *oit);
}

TEST(iter, MinusMinusOp) {
  s21::set<int> ss({2, 3});
  std::set<int> os({2, 3});
  auto sit{ss.end()};
  auto oit(os.end());
  --sit;
  --oit;
  ASSERT_EQ(*sit, *oit);
}

TEST(iter, OpPlusPlus) {
  s21::set<int> ss({2, 3});
  std::set<int> os({2, 3});
  auto sit{ss.begin()};
  auto oit(os.begin());
  auto sold = sit++;
  auto oold = oit++;
  ASSERT_EQ(*sit, *oit);
  ASSERT_EQ(*sold, *oold);
}
TEST(iter, OpMinusMinus) {
  s21::set<int> ss({2, 3});
  std::set<int> os({2, 3});
  auto sit{--ss.end()};
  auto oit(--os.end());
  auto sold = sit--;
  auto oold = oit--;
  ASSERT_EQ(*sit, *oit);
  ASSERT_EQ(*sold, *oold);
}

TEST(iter, begin_to_end) {
  s21::set<int> ss(
      {1, 2, 3, 4, 5, 8, 11, 22, 33, 44, 15, 23, -123, -55, -12, -63, -1000});
  std::set<int> os(
      {1, 2, 3, 4, 5, 8, 11, 22, 33, 44, 15, 23, -123, -55, -12, -63, -1000});
  auto sit = ss.begin();
  auto oit = os.begin();
  for (; sit != ss.end() && oit != os.end(); ++sit, ++oit) {
    ASSERT_EQ(*sit, *oit);
  }
}

TEST(iter, end_to_begin) {
  s21::set<int> ss(
      {1, 2, 3, 4, 5, 8, 11, 22, 33, 44, 15, 23, -123, -55, -12, -63, -1000});
  std::set<int> os(
      {1, 2, 3, 4, 5, 8, 11, 22, 33, 44, 15, 23, -123, -55, -12, -63, -1000});
  auto sit = --ss.end();
  auto oit = --os.end();
  for (; sit != ss.begin() && oit != os.begin(); --sit, --oit) {
    ASSERT_EQ(*sit, *oit);
  }
  ASSERT_EQ(*sit, *oit);
}

template <typename Key>
void cmpSet(s21::set<Key> &s, std::set<Key> &os) {
  ASSERT_EQ(s.size(), os.size());
  ASSERT_EQ(s.empty(), os.empty());
  auto sit = s.begin();
  auto oit = os.begin();
  for (; sit != s.end() && oit != os.end(); ++sit, ++oit) {
    ASSERT_EQ(*sit, *oit);
  }
}

template <typename Key, typename Value>
void cmpSet(s21::set<Key> &s, s21::set<Key> &os) {
  ASSERT_EQ(s.size(), os.size());
  ASSERT_EQ(s.empty(), os.empty());
  auto sit = s.begin();
  auto oit = os.begin();
  for (; sit != s.end() && oit != os.end(); ++sit, ++oit) {
    ASSERT_EQ(*sit, *oit);
  }
}

TEST(constructors, copy) {
  s21::set<int> s({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  s21::set<int> s_copy(s);
  std::set<int> os({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  std::set<int> os_copy(os);
  cmpSet(s, os);
  cmpSet(s_copy, os_copy);
  cmpSet(s, os);
}

TEST(constructors, move) {
  s21::set<int> s({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  s21::set<int> s_move(std::move(s));
  std::set<int> os({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  std::set<int> os_move(std::move(os));
  cmpSet(s, os);
  cmpSet(s_move, os_move);
}

TEST(constructors, oper_move) {
  s21::set<int> s({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  s21::set<int> s_move({1, 5, 3, 2});
  std::set<int> os({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  std::set<int> os_move({1, 5, 3, 2});
  s_move = std::move(s);
  os_move = std::move(os);
  cmpSet(s_move, os_move);
}

TEST(lookup, constains) {
  s21::set<int> s({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  ASSERT_TRUE(s.contains(55));
  ASSERT_TRUE(s.contains(11));
  ASSERT_FALSE(s.contains(int{}));

  s21::set<int> empty;
  ASSERT_FALSE(s.contains(int{}));
}

TEST(lookup, find) {
  s21::set<int> s({1, 6, 5, 77, 22, 3, 55, 12, 15, 11});
  auto it = s.find(12);
  ASSERT_EQ(*it, 12);
  it = s.find(0);
  ASSERT_TRUE(it == s.end());
  it = s.find(1111111);
  ASSERT_TRUE(it == s.end());
}

TEST(funcs, insert_return) {
  s21::set<int> s({1, 6, 5, 66, 22});
  auto p = s.insert(67);
  ASSERT_EQ(*p.first, *(--s.end()));
  ASSERT_TRUE(p.second);
  p = s.insert(1);
  ASSERT_EQ(p.first, s.begin());
  ASSERT_FALSE(p.second);
}

TEST(funcs, erase_begin) {
  s21::set<int> s({1, 6, 5, 66, 22, 111, 223, 512, 33});
  std::set<int> os({1, 6, 5, 66, 22, 111, 223, 512, 33});
  for (size_t size = s.size(); size > 0; --size) {
    s.erase(s.begin());
    os.erase(os.begin());
    cmpSet(s, os);
  }
}

TEST(funcs, erase_end) {
  s21::set<int> s({1, 6, 5, 66, 22, 111, 223, 512, 33});
  std::set<int> os({1, 6, 5, 66, 22, 111, 223, 512, 33});
  for (size_t size = s.size(); size > 0; --size) {
    s.erase(--(s.end()));
    os.erase(--(os.end()));
    cmpSet(s, os);
  }
}

TEST(funcs, erase_middle) {
  s21::set<int> s({1, 6, 5, 66, 22, 111, 223, 512, 33});
  std::set<int> os({1, 6, 5, 66, 22, 111, 223, 512, 33});
  for (size_t size = 0; size < 3; ++size) {
    s.erase(++(++(s.begin())));
    os.erase(++(++(os.begin())));
    cmpSet(s, os);
  }
}

TEST(funcs, max_size) {
  s21::set<int> s({1, 6, 5, 66, 22});
  std::set<int> os({1, 6, 5, 66, 22});
  ASSERT_EQ(s.max_size(), os.max_size());
}

TEST(funcs, emplace_normal_value) {
  s21::set<int> l({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  std::set<int> sl({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  l.emplace(1, -2, 3, 4, 5);
  for (auto k : {1, -2, 3, 4, 5}) sl.insert(k);
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  cmpSet(l, sl);
}

TEST(funcs, emplace_empty) {
  s21::set<int> l({});
  std::set<int> sl({});
  l.emplace(1, -2, 3, 4, 5);
  for (auto k : {1, -2, 3, 4, 5}) sl.insert(k);
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  cmpSet(l, sl);
}

TEST(funcs, emplace_empty_insert) {
  s21::set<int> l({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  std::set<int> sl({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  l.emplace();
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  cmpSet(l, sl);
}

TEST(funcs, emplace_empty_all) {
  s21::set<int> l({});
  std::set<int> sl({});
  l.emplace();
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  cmpSet(l, sl);
}

TEST(funcs, clear) {
  s21::set<int> ss(
      {1, 2, 3, 4, 5, 8, 11, 22, 33, 44, 15, 23, -123, -55, -12, -63, -1000});
  std::set<int> os(
      {1, 2, 3, 4, 5, 8, 11, 22, 33, 44, 15, 23, -123, -55, -12, -63, -1000});
  ss.clear();
  os.clear();
  ASSERT_EQ(ss.empty(), os.empty());
}

TEST(funcs, swap) {
  s21::set<int> s({1, 6, 5, 66, 22});
  s21::set<int> s_swap;
  std::set<int> os({1, 6, 5, 66, 22});
  std::set<int> os_swap;
  s_swap.swap(s);
  os_swap.swap(os);
  cmpSet(s_swap, os_swap);
  cmpSet(s, os);
}

TEST(funcs, merge_no_repetition) {
  s21::set<int> s({1, 6, 5, 66, 22});
  s21::set<int> s_merge({2, 52, 50, 51, 44, 23});
  std::set<int> os({1, 6, 5, 66, 22});
  std::set<int> os_merge({2, 52, 50, 51, 44, 23});
  s_merge.merge(s);
  os_merge.merge(os);
  cmpSet(s_merge, os_merge);
  cmpSet(s, os);
}

TEST(funcs, merge_empty) {
  s21::set<int> s{1, 6, 5, 66, 22};
  s21::set<int> s_merge;
  std::set<int> os{1, 6, 5, 66, 22};
  std::set<int> os_merge;
  s_merge.merge(s);
  os_merge.merge(os);
  cmpSet(s_merge, os_merge);
  cmpSet(s, os);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}