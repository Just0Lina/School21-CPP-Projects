#include <gtest/gtest.h>

#include <map>

#include "s21_map.h"

using s21::map;

template <class Key, class Value,
          class Allocator = std::allocator<std::pair<const Key, Value>>>
using Map = std::map<Key, Value>;

template <typename Key, typename Value>
void comparison(map<Key, Value> &map_a, Map<Key, Value> &map_b);

TEST(Constructor, cons1) {
  map<int, int> map_a;
  ASSERT_EQ(map_a.empty(), true);
}

TEST(Constructor, cons2) {
  map<int, int> map_a{{1, 2}};
  Map<int, int> map_b{{1, 2}};
  comparison(map_a, map_b);
}

TEST(Constructor, cons3) {
  map<int, int> map_a{{1, 2}};
  Map<int, int> map_b{{1, 2}};

  map<int, int> map_c(map_a);
  Map<int, int> map_d(map_b);
  comparison(map_a, map_b);
  comparison(map_c, map_d);
}

TEST(Constructor, cons4) {
  map<int, int> map_a{{1, 2}};
  Map<int, int> map_b{{1, 2}};
  map<int, int> map_c(std::move(map_a));
  Map<int, int> map_d(std::move(map_b));
  ASSERT_EQ(map_b.empty(), true);
  ASSERT_EQ(map_a.empty(), true);
  comparison(map_a, map_b);
  comparison(map_c, map_d);
}

TEST(Constructor, cons5) {
  map<int, int> map_a{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}};
  Map<int, int> map_b{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}};
  comparison(map_a, map_b);
}

TEST(Constructor, cons6) {
  map<int, int> map_a;
  Map<int, int> map_b;
  for (int i = 0; i < 100; ++i) {
    int first = std::rand();
    int second = std::rand();
    auto pair = std::pair<int, int>(first, second);
    map_a.insert(pair);
    map_b.insert(pair);
  }
  comparison(map_a, map_b);
}

TEST(Constructor, cons7) {
  map<int, int> map_a;
  Map<int, int> map_b;
  for (int i = 0; i < 1000; ++i) {
    int first = std::rand();
    int second = std::rand();
    auto pair = std::pair<int, int>(first, second);
    map_a.insert(pair);
    map_b.insert(pair);
  }
  comparison(map_a, map_b);
}

TEST(Constructor, cons8) {
  map<int, int> map_a;
  Map<int, int> map_b;
  for (int i = 0; i < 10000; ++i) {
    int first = std::rand();
    int second = std::rand();
    auto pair = std::pair<int, int>(first, second);
    map_a.insert(pair);
    map_b.insert(pair);
  }
  comparison(map_a, map_b);
}

TEST(Constructor, cons9) {
  map<int, int> map_a;
  Map<int, int> map_b;
  for (int i = 0; i < 10; ++i) {
    int first = std::rand();
    int second = std::rand();
    auto pair = std::pair<int, int>(first, second);
    map_a.insert(pair);
    map_b.insert(pair);
  }
  for (int count = 0; map_a.size() > count && count != 50; ++count) {
    map<int, int>::iterator it1 = map_a.begin();
    Map<int, int>::iterator it2 = map_b.begin();
    map_a.erase(it1);
    map_b.erase(it2);
  }
  comparison(map_a, map_b);
}

TEST(Constructor, cons10) {
  map<int, int> map_a;
  Map<int, int> map_b;
  for (int i = 0; i < 10000; ++i) {
    int first = std::rand() % 100;
    int second = std::rand() % 10;
    auto pair = std::pair<int, int>(first, second);
    map_a.insert(pair);
    map_b.insert(pair);
  }
  for (int count = 0; count < 10; ++count) {
    map<int, int>::iterator it1 = map_a.begin();
    Map<int, int>::iterator it2 = map_b.begin();
    map_a.erase(it1);
    map_b.erase(it2);
  }
  comparison(map_a, map_b);
}

TEST(Erase, erase1) {
  map<int, int> map_a;
  Map<int, int> map_b;
  for (int i = 0; i < 100; ++i) {
    int first = std::rand() % 100;
    int second = std::rand() % 10;
    auto pair = std::pair<int, int>(first, second);
    map_a.insert(pair);
    map_b.insert(pair);
  }
  map<int, int>::iterator it1 = map_a.begin();
  Map<int, int>::iterator it2 = map_b.begin();
  ++(++(++it1));
  ++(++(++it2));

  map_a.erase(it1);
  map_b.erase(it2);
  comparison(map_a, map_b);
}

TEST(Erase, erase2) {
  map<int, int> map_a;
  Map<int, int> map_b;
  for (int i = 0; i < 100; ++i) {
    int first = std::rand() % 100;
    int second = std::rand() % 10;
    auto pair = std::pair<int, int>(first, second);
    map_a.insert(pair);
    map_b.insert(pair);
  }
  map<int, int>::iterator it1 = map_a.end();
  Map<int, int>::iterator it2 = map_b.end();
  --it1;
  --it2;
  map_a.erase(it1);
  map_b.erase(it2);
  it1 = map_a.end();
  it2 = map_b.end();
  --(--(--it1));
  --(--(--it2));
  map_a.erase(it1);
  map_b.erase(it2);
  comparison(map_a, map_b);
}

TEST(Erase, erase3) {
  map<int, int> map_a;
  Map<int, int> map_b;
  for (int i = 0; i < 1; ++i) {
    int first = std::rand() % 100;
    int second = std::rand() % 10;
    auto pair = std::pair<int, int>(first, second);
    map_a.insert(pair);
    map_b.insert(pair);
  }
  map<int, int>::iterator it1 = map_a.end();
  Map<int, int>::iterator it2 = map_b.end();
  --it1;
  --it2;
  map_a.erase(it1);
  map_b.erase(it2);
  comparison(map_a, map_b);
}

TEST(Empty, empty1) {
  map<int, int> map_a{{1, 2}};
  ASSERT_EQ(map_a.empty(), false);
}

TEST(Contains, cont1) {
  map<int, int> map_a{{1, 2}};
  ASSERT_EQ(map_a.contains(1), true);
}

TEST(Contains, cont2) {
  map<int, int> map_a{{1, 2}};
  ASSERT_EQ(map_a.contains(44), false);
}

TEST(Size, size1) {
  map<int, char> map_a{{1, 2}, {55, 3}, {54, 3}};
  Map<int, char> map_b{{1, 2}, {55, 3}, {54, 3}};
  ASSERT_EQ(map_a.size(), map_b.size());
}

TEST(Insertion, ins1) {
  map<int, char> map_a;
  Map<int, char> map_b{{1, 'd'}};
  map_a.insert(std::pair<int, char>(1, 'd'));

  map_a.insert(std::pair<int, char>(1, 'c'));
  comparison(map_a, map_b);
}

TEST(Insertion, ins5) {
  map<int, char> map_a;
  Map<int, char> map_b{{1, 'd'}, {6, 'f'}};
  map_a.insert(std::pair<int, char>(1, 'd'));

  map_a.insert(std::pair<int, char>(1, 'k'));
  map_a.insert(std::pair<int, char>(6, 'f'));
  comparison(map_a, map_b);
}

TEST(Insertion, ins2) {
  map<int, char> map_a;
  Map<int, char> map_b{{1, 'd'}};
  typename std::pair<typename map<int, char>::iterator, bool> pair1 =
      map_a.insert(1, 'd');

  typename std::pair<typename map<int, char>::iterator, bool> pair2 =
      map_a.insert(1, 'c');

  ASSERT_EQ(pair1.second, true);
  ASSERT_EQ(pair2.second, false);
  ASSERT_EQ(pair2.first, pair1.first);
  comparison(map_a, map_b);
}

TEST(Insertion, ins4) {
  map<int, char> map_a;
  Map<int, char> map_b{{1, 'd'}, {6, 'f'}};
  typename std::pair<typename map<int, char>::iterator, bool> pair1 =
      map_a.insert(1, 'd');

  typename std::pair<typename map<int, char>::iterator, bool> pair2 =
      map_a.insert(1, 'c');

  map_a.insert(6, 'f');
  ASSERT_EQ(pair1.second, true);
  ASSERT_EQ(pair2.second, false);
  ASSERT_EQ(pair2.first, pair1.first);
  comparison(map_a, map_b);
}

TEST(Insertion, ins3) {
  map<int, char> map_a;
  Map<int, char> map_b{{1, 'c'}, {2, 'b'}};
  typename std::pair<typename map<int, char>::iterator, bool> pair1 =
      map_a.insert_or_assign(1, 'd');

  typename std::pair<typename map<int, char>::iterator, bool> pair2 =
      map_a.insert_or_assign(1, 'c');
  map_a.insert_or_assign(2, 'b');
  ASSERT_EQ(pair1.second, true);
  ASSERT_EQ(pair2.second, false);
  ASSERT_EQ(pair2.first, pair1.first);
  comparison(map_a, map_b);
}

TEST(Max_size, max_size1) {
  map<int, int> map_a{{1, 2}, {55, 3}, {54, 3}};
  Map<int, int> map_b{{1, 2}, {55, 3}, {54, 3}};
  ASSERT_EQ(map_a.max_size(), map_b.max_size());
}

TEST(Brackets, brac1) {
  Map<int, int> map_b{{1, 2}, {55, 3}, {54, 3}};
  map<int, int> map_a{{1, 2}, {55, 3}, {54, 3}};
  ASSERT_EQ(map_a[55], map_b[55]);
}

TEST(Iterator, iter2) {
  Map<int, int> map_b{{1, 2}, {55, 5}, {54, 4}};
  map<int, int> map_a{{1, 2}, {55, 5}, {54, 4}};
  map<int, int>::iterator it1 = map_a.begin();
  Map<int, int>::iterator it2 = map_b.begin();
  ++it1;
  ++it2;
  ++it1;
  ++it2;
  ASSERT_EQ(it1->first, it2->first);
  ASSERT_EQ(it1->second, it2->second);
}

TEST(Iterator, iter2_2) {
  Map<int, int> map_b{{7, 2}, {1, 5}};
  map<int, int> map_a{{7, 2}, {1, 5}};
  map<int, int>::iterator it1 = map_a.begin();
  Map<int, int>::iterator it2 = map_b.begin();
  ++it1;
  ++it2;
  map_a.erase(it1);
  map_b.erase(it2);
  comparison(map_a, map_b);
}

TEST(Iterator, iter4) {
  Map<int, int> map_b{{1, 2}, {55, 5}, {54, 4}, {45, 2}, {6, 5}, {64, 4}};
  map<int, int> map_a{{1, 2}, {55, 5}, {54, 4}, {45, 2}, {6, 5}, {64, 4}};
  map<int, int>::iterator it1 = map_a.begin();
  Map<int, int>::iterator it2 = map_b.begin();
  ++it1;
  ++it2;
  ASSERT_EQ(it1->first, it2->first);
  ASSERT_EQ(it1->second, it2->second);
}

TEST(Iterator, iter8) {
  Map<int, int> map_b{{1, 2}, {55, 5}};
  map<int, int> map_a{{1, 2}, {55, 5}};
  map<int, int>::iterator it1 = map_a.begin();
  Map<int, int>::iterator it2 = map_b.begin();
  ++it1;
  ++it2;
  ASSERT_EQ(it1->first, it2->first);
  ASSERT_EQ(it1->second, it2->second);
}

TEST(Iterator, iter3) {
  Map<int, int> map_b{{1, 2}, {55, 5}, {54, 4}};
  map<int, int> map_a{{1, 2}, {55, 5}, {54, 4}};
  map<int, int>::iterator it1 = map_a.begin();
  Map<int, int>::iterator it2 = map_b.begin();
  it1++;
  it2++;
  it1++;
  it2++;
  ASSERT_EQ(it1->first, it2->first);
  ASSERT_EQ(it1->second, it2->second);
}

TEST(Iterator, iter5) {
  Map<int, int> map_b{{1, 2}, {55, 5}, {54, 4}, {45, 2}, {6, 5}, {64, 4}};
  map<int, int> map_a{{1, 2}, {55, 5}, {54, 4}, {45, 2}, {6, 5}, {64, 4}};
  map<int, int>::iterator it1 = map_a.begin();
  Map<int, int>::iterator it2 = map_b.begin();
  it1++;
  it2++;
  it1--;
  it2--;
  ASSERT_EQ(it1->first, it2->first);
  ASSERT_EQ(it1->second, it2->second);
}

TEST(Iterator, iter1) {
  Map<int, int> map_b{{1, 2}, {55, 5}, {54, 4}};
  map<int, int> map_a{{1, 2}, {55, 5}, {54, 4}};
  map<int, int>::iterator it1 = map_a.end();
  Map<int, int>::iterator it2 = map_b.end();
  --it1;
  --it2;
  ASSERT_EQ(it1->first, it2->first);
  ASSERT_EQ(it1->second, it2->second);
}

TEST(Iterator, iter1_1) {
  Map<int, int> map_b{{1, 2}, {55, 5}, {54, 4}};
  map<int, int> map_a{{1, 2}, {55, 5}, {54, 4}};
  map<int, int>::iterator it1 = map_a.end();
  Map<int, int>::iterator it2 = map_b.end();
  it1--;
  it2--;
  ASSERT_EQ(it1->first, it2->first);
  ASSERT_EQ(it1->second, it2->second);
}

TEST(Merge, merge1) {
  map<int, int> map_a;
  map<int, int> map_b{{1, 3}, {55, 5}, {54, 4}};
  Map<int, int> Map_a;
  Map<int, int> Map_b{{1, 3}, {55, 5}, {54, 4}};
  map_a.merge(map_b);
  Map_a.merge(Map_b);
  comparison(map_a, Map_a);
  comparison(map_b, Map_b);
}

TEST(Merge, merge2) {
  map<int, int> map_a{{1, 2}, {54, 22}, {17, 25}};
  map<int, int> map_b{{1, 3}, {55, 5}, {54, 4}};
  Map<int, int> Map_a{{1, 2}, {54, 22}, {17, 25}};
  Map<int, int> Map_b{{1, 3}, {55, 5}, {54, 4}};
  map_a.merge(map_b);
  Map_a.merge(Map_b);
  comparison(map_a, Map_a);
  comparison(map_b, Map_b);
}

TEST(Search, search1) {
  map<int, int> map_a{{1, 3}, {55, 5}, {54, 4}};
  ASSERT_EQ(map_a.contains(1), true);
}

TEST(Search, search2) {
  map<int, int> map_a{{1, 3}, {55, 5}, {54, 4}};
  ASSERT_EQ(map_a.contains(4435), false);
}

TEST(funcs, emplace_normal_value) {
  map<int, int> l{{1, 5}, {6, 2}, {3, 4}, {5, 22}, {11, 5}};
  Map<int, int> sl{{1, 5}, {6, 2}, {3, 4}, {5, 22}, {11, 5}};
  l.emplace(std::pair<int, int>{1, -2}, std::pair<int, int>{5, 2});
  std::vector<std::pair<int, int>> v{{1, -2}, {5, 2}};
  for (auto k : v) sl.insert(k);
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  comparison(l, sl);
}

TEST(Clear, clear1) {
  map<int, int> l{{1, 5}, {6, 2}, {3, 4}, {5, 22}, {11, 5}};
  Map<int, int> sl{{1, 5}, {6, 2}, {3, 4}, {5, 22}, {11, 5}};
  l.clear();
  sl.clear();
  ASSERT_EQ(l.empty(), sl.empty());
}

TEST(Swap, swap1) {
  map<int, int> map_a{{1, 2}};
  Map<int, int> map_b{{1, 2}};

  map<int, int> map_c{{1, 2}, {55, 5}, {54, 4}};
  Map<int, int> map_d{{1, 2}, {55, 5}, {54, 4}};
  map_a.swap(map_c);
  map_b.swap(map_d);

  comparison(map_a, map_b);
  comparison(map_c, map_d);
}

TEST(funcs, emplace_empty) {
  map<int, int> l({});
  Map<int, int> sl({});
  l.emplace(std::pair<int, int>{1, -2}, std::pair<int, int>{5, 2});
  std::vector<std::pair<int, int>> v{{1, -2}, {5, 2}};
  for (auto k : v) sl.insert(k);
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  comparison(l, sl);
}

TEST(funcs, emplace_empty_insert) {
  map<int, int> l{{1, 5}, {6, 2}, {3, 4}, {5, 22}, {11, 5}};
  Map<int, int> sl{{1, 5}, {6, 2}, {3, 4}, {5, 22}, {11, 5}};
  l.emplace(std::pair<int, int>{}, std::pair<int, int>{});
  std::vector<std::pair<int, int>> v{{}, {}};
  for (auto k : v) sl.insert(k);
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  comparison(l, sl);
}

TEST(funcs, emplace_empty_all) {
  map<int, int> l({});
  Map<int, int> sl({});
  l.emplace(std::pair<int, int>{}, std::pair<int, int>{});
  std::vector<std::pair<int, int>> v{{}, {}};
  for (auto k : v) sl.insert(k);
  ASSERT_EQ(l.empty(), sl.empty());
  ASSERT_EQ(l.size(), sl.size());
  comparison(l, sl);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template <typename Key, typename Value>
void comparison(map<Key, Value> &map_a, Map<Key, Value> &map_b) {
  ASSERT_EQ(map_a.size(), map_b.size());
  typename map<Key, Value>::iterator it1 = map_a.begin();
  typename Map<Key, Value>::iterator it2 = map_b.begin();
  for (; it1 != map_a.end(); ++it1, ++it2) {
    ASSERT_EQ(it1->first, it2->first);
    ASSERT_EQ(it1->second, it2->second);
  }
}
