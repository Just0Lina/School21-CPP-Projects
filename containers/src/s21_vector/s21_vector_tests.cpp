#include <gtest/gtest.h>

#include <vector>

#include "s21_vector.h"
using s21::vector;
template <class T, class Allocator = std::allocator<T>>
using Vector = std::vector<T>;
template <typename T>
void comparison(vector<T> &vec_a, Vector<T> &vec_b);

TEST(Constructor, cons1) {
  vector<int> vec_a;
  Vector<int> vec_b;
  comparison(vec_a, vec_b);
}

TEST(Constructor, cons2) {
  vector<int> vec_a(5);
  Vector<int> vec_b(5);
  comparison(vec_a, vec_b);
}

TEST(Constructor, cons3) {
  vector<int> vec_a(2);
  vec_a.push_back(4);
  vector<int> vec_b(vec_a);
  Vector<int> vec_c(2);
  vec_c.push_back(4);
  Vector<int> vec_d(vec_c);
  comparison(vec_a, vec_c);
  comparison(vec_b, vec_d);
}

TEST(Constructor, cons6) {
  vector<int> vec_a(2);
  vec_a.push_back(4);
  vec_a.reserve(6);

  vector<int> vec_b(vec_a);
  Vector<int> vec_c(2);
  vec_c.push_back(4);
  vec_c.reserve(6);
  Vector<int> vec_d(vec_c);

  comparison(vec_a, vec_c);
  comparison(vec_b, vec_d);
}

TEST(Constructor, cons4) {
  vector<int> vec_a(2);
  vec_a.push_back(4);
  vector<int> vec_b(std::move(vec_a));
  Vector<int> vec_c(2);
  vec_c.push_back(4);
  Vector<int> vec_d(std::move(vec_c));
  comparison(vec_a, vec_c);
  comparison(vec_b, vec_d);
}

TEST(Constructor, cons5) {
  vector<int> vec_a{1, 2, 3};
  Vector<int> vec_b{1, 2, 3};
  comparison(vec_a, vec_b);
}

TEST(PushBack, push1) {
  vector<int> vec_a(2);
  vec_a.push_back(5);
  vec_a.push_back(4);
  vec_a.push_back(3);
  vec_a.push_back(3);

  Vector<int> vec_b(2);
  vec_b.push_back(5);
  vec_b.push_back(4);
  vec_b.push_back(3);
  vec_b.push_back(3);

  comparison(vec_a, vec_b);
}

TEST(Max_size, max_size1) {
  vector<int> vec_a{1, 2, 3};
  Vector<int> vec_b{1, 2, 3};
  ASSERT_EQ(vec_a.max_size(), vec_b.max_size());
  comparison(vec_a, vec_b);
}

TEST(At, at1) {
  vector<double> vec_a(2);
  vec_a.push_back(5);

  Vector<double> vec_b(2);
  vec_b.push_back(5);

  ASSERT_EQ(vec_a.at(1), vec_b.at(1));
}

TEST(Brackets, brackets1) {
  vector<int> vec_a(2);
  vec_a.push_back(5);

  Vector<int> vec_b(2);
  vec_b.push_back(5);

  comparison(vec_a, vec_b);
}

TEST(Brackets, brackets2) {
  vector<int> vec_a(2);
  vec_a.push_back(5);
  const vector<int> vec_c = vec_a;

  Vector<int> vec_b(2);
  vec_b.push_back(5);
  const Vector<int> vec_d = vec_b;

  size_t size = vec_c.size();
  ASSERT_EQ(size, vec_d.size());

  ASSERT_EQ(vec_c.capacity(), vec_d.capacity());
  for (size_t i = 0; i < size; ++i) {
    ASSERT_EQ(vec_c[i], vec_d[i]);
  }
}

TEST(Back, back1) {
  vector<int> vec_a(2);
  vec_a.push_back(5);
  Vector<int> vec_b(2);
  vec_b.push_back(5);

  ASSERT_EQ(vec_a.back(), vec_b.back());
}

TEST(Back, back2) {
  vector<int> vec_a(2);
  vec_a.push_back(5);
  vec_a.push_back(4);

  Vector<int> vec_b(2);
  vec_b.push_back(5);
  vec_b.push_back(4);

  ASSERT_EQ(vec_a.back(), vec_b.back());
}

TEST(Size, size1) {
  vector<int> vec_a(2);
  vec_a.push_back(5);
  vec_a.push_back(4);

  Vector<int> vec_b(2);
  vec_b.push_back(5);
  vec_b.push_back(4);

  ASSERT_EQ(vec_a.size(), vec_b.size());
}

TEST(Capacity, capacity1) {
  vector<int> vec_a(2);
  vec_a.push_back(5);
  vec_a.push_back(4);

  Vector<int> vec_b(2);
  vec_b.push_back(5);
  vec_b.push_back(4);

  ASSERT_EQ(vec_a.capacity(), vec_b.capacity());
}

TEST(Empty, empty1) {
  vector<int> vec_a;
  Vector<int> vec_b;
  ASSERT_EQ(vec_a.empty(), vec_b.empty());
}

TEST(Insert, insert1) {
  vector<int> vec_a;
  vec_a.insert(vec_a.begin(), 4);
  Vector<int> vec_b;
  vec_b.insert(vec_b.begin(), 4);

  comparison(vec_a, vec_b);
}

TEST(Insert, insert2) {
  vector<int> vec_a(4);
  vec_a.insert(vec_a.begin(), 4);
  Vector<int> vec_b(4);
  vec_b.insert(vec_b.begin(), 4);

  comparison(vec_a, vec_b);
}

TEST(Insert, insert3) {
  vector<int> vec_a(4);
  vec_a.insert(vec_a.end(), 4);
  Vector<int> vec_b(4);
  vec_b.insert(vec_b.end(), 4);

  comparison(vec_a, vec_b);
}

TEST(Insert, insert4) {
  vector<int> vec_a;
  vec_a.reserve(5);
  vec_a.insert(vec_a.begin(), 4);
  Vector<int> vec_b;
  vec_b.reserve(5);
  vec_b.insert(vec_b.begin(), 4);

  comparison(vec_a, vec_b);
}

TEST(Insert, insert6) {
  vector<int> vec_a;
  vec_a.insert(vec_a.end(), 4);
  vec_a.insert(vec_a.end() - 1, 3);

  Vector<int> vec_b;
  vec_b.insert(vec_b.end(), 4);
  vec_b.insert(vec_b.end() - 1, 3);
  comparison(vec_a, vec_b);
}

TEST(Front, front1) {
  vector<int> vec_a(2);
  vec_a.push_back(5);
  vec_a.push_back(4);

  Vector<int> vec_b(2);
  vec_b.push_back(5);
  vec_b.push_back(4);

  ASSERT_EQ(vec_a.front(), vec_b.front());
}

TEST(Insert, insert5) {
  vector<int> vec_a(3);
  vec_a.insert(vec_a.begin() + 1, 4);
  vec_a.insert(vec_a.end() - 1, 3);

  Vector<int> vec_b(3);
  vec_b.insert(vec_b.begin() + 1, 4);
  vec_b.insert(vec_b.end() - 1, 3);

  comparison(vec_a, vec_b);
}

TEST(Shrink_to_fit, shrink_to_fit1) {
  vector<int> vec_a(3);
  vec_a.reserve(100);
  vec_a.push_back(5);
  vec_a.push_back(4);
  vec_a.push_back(4);
  vec_a.shrink_to_fit();

  Vector<int> vec_b(3);
  vec_b.reserve(100);
  vec_b.push_back(5);
  vec_b.push_back(4);
  vec_b.push_back(4);
  vec_b.shrink_to_fit();

  comparison(vec_a, vec_b);
}

TEST(Erase, erase1) {
  vector<int> vec_a(2);
  vec_a.push_back(4);
  vec_a.erase(vec_a.begin() + 1);

  Vector<int> vec_b(2);
  vec_b.push_back(4);
  vec_b.erase(vec_b.begin() + 1);

  comparison(vec_a, vec_b);
}

TEST(Erase, erase2) {
  vector<int> vec_a(2);
  vec_a.push_back(4);
  vec_a.erase(vec_a.begin());

  Vector<int> vec_b(2);
  vec_b.push_back(4);
  vec_b.erase(vec_b.begin());

  comparison(vec_a, vec_b);
}

TEST(Erase, erase3) {
  vector<int> vec_a(2);
  vec_a.push_back(4);
  vec_a.erase(vec_a.begin());

  Vector<int> vec_b(2);
  vec_b.push_back(4);
  vec_b.erase(vec_b.begin());

  comparison(vec_a, vec_b);
}

TEST(Compare, compare1) {
  vector<int> vec_a(2);
  vec_a.push_back(4);
  vector<int> vec_c(4);
  vec_c.push_back(4);
  vec_c = std::move(vec_a);

  Vector<int> vec_b(2);
  vec_b.push_back(4);
  Vector<int> vec_d(4);
  vec_d.push_back(4);
  vec_d = std::move(vec_b);

  comparison(vec_a, vec_b);
  comparison(vec_c, vec_d);
}

TEST(Compare, compare2) {
  vector<int> vec_a(2);
  vec_a.push_back(4);

  Vector<int> vec_b(2);
  vec_b.push_back(4);

  vec_a = std::move(vec_a);
  vec_b = std::move(vec_b);
  comparison(vec_a, vec_b);
}

TEST(Push, push4) {
  vector<int> vec_a(2);
  vec_a.push_back(5);
  vec_a.push_back(4);
  vec_a.clear();

  Vector<int> vec_b(2);
  vec_b.push_back(5);
  vec_b.push_back(4);
  vec_b.clear();
  comparison(vec_a, vec_b);
}

TEST(Swap, swap1) {
  vector<int> vec_a(2);
  vec_a.push_back(5);
  vec_a.push_back(4);

  vector<int> vec_c(5);
  vec_c.push_back(6);
  vec_c.push_back(3);

  vec_a.swap(vec_c);
  Vector<int> vec_b(2);
  vec_b.push_back(5);
  vec_b.push_back(4);

  Vector<int> vec_d(5);
  vec_d.push_back(6);
  vec_d.push_back(3);
  vec_b.swap(vec_d);
  comparison(vec_a, vec_b);
  comparison(vec_c, vec_d);
}

TEST(Reserve, reserve1) {
  vector<int> vec_a(2);
  vec_a.push_back(4);
  vec_a.reserve(5);
  Vector<int> vec_b(2);
  vec_b.push_back(4);
  vec_b.reserve(5);

  comparison(vec_a, vec_b);
}

TEST(PopBack, pop_back1) {
  vector<int> vec_a(2);
  vec_a.push_back(5);
  vec_a.push_back(4);
  vec_a.push_back(3);
  vec_a.pop_back();

  Vector<int> vec_b(2);
  vec_b.push_back(5);
  vec_b.push_back(4);
  vec_b.push_back(3);
  vec_b.pop_back();

  comparison(vec_a, vec_b);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template <typename T>
void comparison(vector<T> &vec_a, Vector<T> &vec_b) {
  size_t size = vec_a.size();
  ASSERT_EQ(size, vec_b.size());

  ASSERT_EQ(vec_a.capacity(), vec_b.capacity());
  for (size_t i = 0; i < size; ++i) {
    ASSERT_EQ(vec_a[i], vec_b[i]);
  }
}

TEST(funcs, emplace_normal_value) {
  s21::vector<int> l({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  std::vector<int> sl({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  auto i = l.begin();
  auto j = sl.begin();
  ++(++(++(++i)));
  ++(++(++(++j)));
  l.emplace(i, 1, -2, 3, 4, 5);
  size_t diff = j.base() - sl.begin().base();
  for (auto m : {1, -2, 3, 4, 5}) sl.insert((sl.begin() + diff++), m);
  ASSERT_EQ(l.size(), sl.size());
  i = l.begin();
  for (auto m = sl.begin(); m != sl.end(); ++m, ++i) {
    ASSERT_EQ(*i, *m);
  }
}

TEST(funcs, emplace_empty) {
  s21::vector<int> l({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  std::vector<int> sl({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  auto i = l.begin();
  ++(++(++(++i)));
  l.emplace(i);
  comparison(l, sl);
}

TEST(funcs, emplace_empty_list) {
  s21::vector<int> l;
  std::vector<int> sl;
  auto i = l.begin();
  auto j = sl.begin();
  l.emplace(i, 1, 2, 3, 4, 5);
  size_t diff = j.base() - sl.begin().base();
  for (auto m : {1, 2, 3, 4, 5}) sl.insert((sl.begin() + diff++), m);
  ASSERT_EQ(l.size(), sl.size());
  i = l.begin();
  for (auto m = sl.begin(); m != sl.end(); ++m, ++i) {
    ASSERT_EQ(*i, *m);
  }
}

TEST(funcs, emplace_empty_all) {
  s21::vector<int> l;
  std::vector<int> sl;
  auto i = l.begin();
  l.emplace(i);
  comparison(l, sl);
}

TEST(funcs, emplace_minus) {
  s21::vector<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::vector<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  auto i = l.end();
  auto j = sl.end();
  --(--(--(--i)));
  --(--(--(--j)));
  l.emplace(i, 1, 2, 33);
  size_t diff = j.base() - sl.begin().base();
  for (auto m : {1, 2, 33}) sl.insert((sl.begin() + diff++), m);
  ASSERT_EQ(l.size(), sl.size());
  i = l.begin();
  for (auto m = sl.begin(); m != sl.end(); ++m, ++i) {
    ASSERT_EQ(*i, *m);
  }
}

TEST(funcs, emplace_back_normal_value) {
  s21::vector<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::vector<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_back(1, 2, 33);
  auto j = sl.end();
  size_t diff = j.base() - sl.begin().base();
  for (auto m : {1, 2, 33}) sl.insert((sl.begin() + diff++), m);
  ASSERT_EQ(l.size(), sl.size());
  auto i = l.begin();
  for (auto m = sl.begin(); m != sl.end(); ++m, ++i) {
    ASSERT_EQ(*i, *m);
  }
}

TEST(funcs, emplace_back_empty) {
  s21::vector<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::vector<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_back();
  comparison(l, sl);
}

TEST(funcs, emplace_back_empty_list) {
  s21::vector<int> l;
  std::vector<int> sl;
  l.emplace_back(1, 2, 3, 4, 5);
  auto j = sl.end();
  size_t diff = j.base() - sl.begin().base();
  for (auto m : {1, 2, 3, 4, 5}) sl.insert((sl.begin() + diff++), m);
  ASSERT_EQ(l.size(), sl.size());
  auto i = l.begin();
  for (auto m = sl.begin(); m != sl.end(); ++m, ++i) {
    ASSERT_EQ(*i, *m);
  }
}

TEST(funcs, emplace_back_empty_all) {
  s21::vector<int> l;
  std::vector<int> sl;
  l.emplace_back();

  comparison(l, sl);
}
