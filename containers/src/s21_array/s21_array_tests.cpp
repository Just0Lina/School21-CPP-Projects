#include <gtest/gtest.h>

#include <array>

#include "s21_array.h"
using s21::array;
template <class T, size_t N, class Allocator = std::allocator<T>>
using Array = std::array<T, N>;
template <typename T, size_t N>
void comparison(array<T, N> &arr_a, Array<T, N> &arr_b);

TEST(Constructor, cons1) {
  array<int, 2> arr_a;
  Array<int, 2> arr_b;
  ASSERT_EQ(arr_a.size(), arr_b.size());
}

TEST(Constructor, cons2) {
  array<double, 3> arr_a{1, 2, 3};
  Array<double, 3> arr_b{1, 2, 3};
  comparison(arr_a, arr_b);
}

TEST(Constructor, cons3) {
  array<double, 3> arr_a{1, 2, 3};
  Array<double, 3> arr_b{1, 2, 3};
  Array<double, 3> arr_d(arr_b);
  array<double, 3> arr_c(arr_a);
  comparison(arr_c, arr_d);
}

TEST(Constructor, cons4) {
  array<double, 3> arr_a{1, 2, 3};
  Array<double, 3> arr_b{1, 2, 3};
  Array<double, 3> arr_d(std::move(arr_b));
  array<double, 3> arr_c(std::move(arr_a));
  comparison(arr_a, arr_b);
  comparison(arr_c, arr_d);
}

TEST(Constructor, cons5) {
  array<double, 5> arr_a{1, 2, 3, 4, 5};
  Array<double, 5> arr_b{1, 2, 3, 4, 5};
  Array<double, 5> arr_d = arr_b;
  array<double, 5> arr_c = arr_a;
  comparison(arr_a, arr_b);
  comparison(arr_c, arr_d);
}

TEST(Brackets, brac1) {
  const array<double, 3> arr_a{1, 2, 3};
  const Array<double, 3> arr_b{1, 2, 3};
  for (size_t i = 0; i < 3; ++i) {
    ASSERT_EQ(arr_a[i], arr_b[i]);
  }
}

TEST(At, at1) {
  array<char, 3> arr_a{1, 2, 3};
  Array<char, 3> arr_b{1, 2, 3};
  for (size_t i = 0; i < 3; ++i) {
    ASSERT_EQ(arr_a.at(i), arr_b.at(i));
  }
}

TEST(At, at2) {
  const array<char, 3> arr_a{'a', 'b', '3'};
  const Array<char, 3> arr_b{'a', 'b', '3'};
  for (size_t i = 0; i < 3; ++i) {
    ASSERT_EQ(arr_a.at(i), arr_b.at(i));
  }
}

TEST(Front, front1) {
  const array<char, 3> arr_a{'a', 'b', '3'};
  const Array<char, 3> arr_b{'a', 'b', '3'};
  ASSERT_EQ(arr_a.front(), arr_b.front());
}

TEST(Front, front2) {
  array<char, 3> arr_a{'a', 'b', '3'};
  Array<char, 3> arr_b{'a', 'b', '3'};
  ASSERT_EQ(arr_a.front(), arr_b.front());
}

TEST(Back, back1) {
  const array<char, 3> arr_a{'a', 'b', '3'};
  const Array<char, 3> arr_b{'a', 'b', '3'};
  ASSERT_EQ(arr_a.back(), arr_b.back());
}
TEST(Back, back2) {
  array<char, 3> arr_a{'a', 'b', '3'};
  Array<char, 3> arr_b{'a', 'b', '3'};
  ASSERT_EQ(arr_a.back(), arr_b.back());
}

TEST(Empty, empty1) {
  const array<char, 3> arr_a{'a', 'b', '3'};
  const Array<char, 3> arr_b{'a', 'b', '3'};
  ASSERT_EQ(arr_a.empty(), arr_b.empty());
}

TEST(Empty, empty2) {
  const array<char, 0> arr_a;
  const Array<char, 0> arr_b;
  ASSERT_EQ(arr_a.empty(), arr_b.empty());
}

TEST(Size, size1) {
  const array<int, 4> arr_a{1, 2, 3, 4};
  const Array<int, 4> arr_b{1, 2, 3, 4};
  ASSERT_EQ(arr_a.size(), arr_b.size());
}

TEST(Size, size2) {
  const array<int, 0> arr_a;
  const Array<int, 0> arr_b;
  ASSERT_EQ(arr_a.size(), arr_b.size());
}

TEST(Max_size, max_size1) {
  array<int, 1> arr_a;
  Array<int, 1> arr_b;
  ASSERT_EQ(arr_a.max_size(), arr_b.max_size());
}

TEST(Swap, swap1) {
  array<int, 4> arr_a{1, 2, 3, 4};
  array<int, 4> arr_c{1, 2, 2, 1};

  Array<int, 4> arr_b{1, 2, 3, 4};
  Array<int, 4> arr_d{1, 2, 2, 1};

  arr_a.swap(arr_c);
  arr_b.swap(arr_d);
  comparison(arr_a, arr_b);
  comparison(arr_c, arr_d);
}

TEST(Assignment, assig1) {
  array<int, 4> arr_a{1, 2, 3, 4};
  array<int, 4> arr_c = arr_a;

  Array<int, 4> arr_b{1, 2, 3, 4};
  Array<int, 4> arr_d = arr_b;

  comparison(arr_a, arr_b);
  comparison(arr_c, arr_d);
}

TEST(Fill, fill1) {
  array<int, 4> arr_a;
  Array<int, 4> arr_b;

  arr_a.fill(5);
  arr_b.fill(5);
  comparison(arr_a, arr_b);
}

TEST(Fill, fill2) {
  array<int, 4> arr_a{1, 2, 3, 4};
  Array<int, 4> arr_b{1, 2, 3, 4};

  arr_a.fill(5);
  arr_b.fill(5);
  comparison(arr_a, arr_b);
}

TEST(Data, data1) {
  array<int, 4> arr_a{1, 2, 3, 4};
  Array<int, 4> arr_b{1, 2, 3, 4};
  int *data1 = arr_a.data();
  int *data2 = arr_b.data();
  ASSERT_EQ(*data1, *data2);
  ASSERT_EQ(*++data1, *++data2);
}

TEST(begin, begin) {
  array<int, 4> arr_a{1, 2, 3, 4};
  Array<int, 4> arr_b{1, 2, 3, 4};
  auto a_iter = arr_a.begin();
  auto b_iter = arr_b.begin();
  while (a_iter != arr_a.end()) ASSERT_EQ(*a_iter++, *b_iter++);
}

TEST(begin, const_begin) {
  array<int, 4> arr_a{1, 2, 3, 4};
  Array<int, 4> arr_b{1, 2, 3, 4};
  auto a_iter = arr_a.begin();
  auto b_iter = arr_b.begin();
  while (a_iter != arr_a.end()) ASSERT_EQ(*a_iter++, *b_iter++);
}

TEST(move, operator_eq) {
  array<int, 4> arr_a{1, 2, 3, 4};
  array<int, 4> arr_b;
  Array<int, 4> arr_c{1, 2, 3, 4};
  Array<int, 4> arr_d;
  arr_b = std::move(arr_a);
  arr_d = std::move(arr_c);
  comparison(arr_b, arr_d);
}

TEST(move, operator_eq_same) {
  array<int, 4> arr_a{1, 2, 3, 4};
  Array<int, 4> arr_c{1, 2, 3, 4};
  arr_a = std::move(arr_a);
  arr_c = std::move(arr_c);
  comparison(arr_a, arr_c);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template <typename T, size_t N>
void comparison(array<T, N> &arr_a, Array<T, N> &arr_b) {
  for (size_t i = 0; i < N; ++i) {
    ASSERT_EQ(arr_a[i], arr_b[i]);
  }
}
