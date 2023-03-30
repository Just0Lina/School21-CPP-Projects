#include <gtest/gtest.h>

#include <iostream>
#include <stack>

#include "s21_stack.h"
template <typename T> bool check_stacks(s21::stack<T> &s, std::stack<T> &ss) {
  for (int i = s.size(); i > 0; --i) {
    if (s.top() != ss.top())
      return false;
    s.pop();
    ss.pop();
  }
  return true;
}

template <typename T> bool check_stacks(s21::stack<T> &s, s21::stack<T> &ss) {
  for (int i = s.size(); i > 0; --i) {
    if (s.top() != ss.top())
      return false;
    s.pop();
    ss.pop();
  }
  return true;
}

TEST(push, once) {
  s21::stack<int> s;
  s.push(5);
  ASSERT_EQ(5, s.top());
  ASSERT_EQ(1, s.size());
}

TEST(pop, once) {
  s21::stack<int> s;
  s.push(5);
  s.pop();
  std::stack<int> ss;
  ss.push(5);
  ss.pop();
  ASSERT_EQ(s.empty(), ss.empty());
  ASSERT_EQ(s.size(), ss.size());
}

TEST(push_pop, in_for) {
  s21::stack<int> s;
  for (int i = 0; i < 10; ++i) {
    s.push(i);
  }
  ASSERT_EQ(s.size(), 10);
  for (int i = 9; i > 0; --i) {
    ASSERT_EQ(i, s.top());
    s.pop();
  }
}

TEST(constr, init_list) {
  s21::stack<int> s{1, 2, 3, 4, 5, 6};
  std::stack<int> ss({1, 2, 3, 4, 5, 6});
  for (int i = s.size(); i > 0; --i) {
    ASSERT_EQ(s.top(), ss.top());
    s.pop();
    ss.pop();
  }
}

TEST(constr, copy) {
  s21::stack<int> s{1, 2, 3, 3, 2};
  s21::stack<int> s_copy(s);
  std::stack<int> ss({1, 2, 3, 3, 2});
  std::stack<int> ss_copy(ss);
  ASSERT_TRUE(check_stacks(s_copy, ss_copy));
}

TEST(constr, move) {
  s21::stack<int> s{1, 11, 111, 1111};
  s21::stack<int> s_moved(std::move(s));
  ASSERT_EQ(0, s.size());
  std::stack<int> ss({1, 11, 111, 1111});
  std::stack<int> ss_moved(std::move(ss));
  ASSERT_EQ(s.size(), ss.size());
  ASSERT_TRUE(check_stacks(s_moved, ss_moved));
}

TEST(operators, move) {
  s21::stack<int> s{1, 11, 111, 1111};
  s21::stack<int> s_moved;
  s_moved = std::move(s);
  ASSERT_EQ(0, s.size());
  std::stack<int> ss({1, 11, 111, 1111});
  std::stack<int> ss_moved;
  ss_moved = std::move(ss);
  ASSERT_EQ(s.size(), ss.size());
  ASSERT_TRUE(check_stacks(s_moved, ss_moved));
}

TEST(operators, copy_same_size) {
  s21::stack<int> s{1, 2, 3, 4, 5};
  s21::stack<int> s_copy{5, 5, 5, 5, 5};
  s_copy = s;
  ASSERT_EQ(s.size(), s_copy.size());
  ASSERT_TRUE(check_stacks(s, s_copy));
}

TEST(operators, copy_less_size) {
  s21::stack<int> s{1, 2, 3, 4, 5};
  s21::stack<int> s_copy{5, 5, 5, 5, 5, 5};
  s_copy = s;
  std::stack<int> ss({1, 2, 3, 4, 5});
  std::stack<int> ss_copy({5, 5, 5, 5, 5, 5});
  ss_copy = ss;
  ASSERT_EQ(ss.size(), ss_copy.size());
  ASSERT_TRUE(check_stacks(s, s_copy));
  ASSERT_TRUE(check_stacks(s, ss_copy));
  ASSERT_TRUE(check_stacks(s_copy, s));
}

TEST(operators, copy_more_size) {
  s21::stack<int> s{1, 2, 3, 4, 5};
  s21::stack<int> s_copy{
      5,
      5,
      5,
      5,
  };
  s_copy = s;
  std::stack<int> ss({1, 2, 3, 4, 5});
  std::stack<int> ss_copy({
      5,
      5,
      5,
      5,
  });
  ss_copy = ss;
  ASSERT_EQ(ss.size(), ss_copy.size());
  ASSERT_TRUE(check_stacks(s, s_copy));
  ASSERT_TRUE(check_stacks(s, ss_copy));
  ASSERT_TRUE(check_stacks(s_copy, s));
}

TEST(swap, not_zero) {
  s21::stack<std::string> s{"abc", "ggg", "eee"};
  s21::stack<std::string> s_swap{"dead inside", "zxcvzxcvg", "asdasda"};
  std::stack<std::string> ss({"abc", "ggg", "eee"});
  std::stack<std::string> ss_swap({"dead inside", "zxcvzxcvg", "asdasda"});
  s.swap(s_swap);
  ss.swap(ss_swap);
  ASSERT_TRUE(check_stacks(s, ss));
  ASSERT_TRUE(check_stacks(s_swap, ss_swap));
}

TEST(funcs, emplace_front_normal_value) {
  s21::stack<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::stack<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_front(-1, 2, 33);

  for (auto k : {-1, 2, 33})
    sl.push(k);

  ASSERT_TRUE(check_stacks(l, sl));
}

TEST(funcs, emplace_front_empty) {
  s21::stack<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::stack<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_front();
  ASSERT_TRUE(check_stacks(l, sl));
}

TEST(funcs, emplace_front_empty_list) {
  s21::stack<int> l;
  std::stack<int> sl;
  l.emplace_front(1, 2, 3, 4, 5);

  for (auto k : {1, 2, 3, 4, 5})
    sl.push(k);

  ASSERT_TRUE(check_stacks(l, sl));
}

TEST(funcs, emplace_front_empty_all) {
  s21::stack<int> l;
  std::stack<int> sl;
  l.emplace_front();

  ASSERT_TRUE(check_stacks(l, sl));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}