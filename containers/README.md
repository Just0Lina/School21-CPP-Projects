# Containers

- Программа разработана на языке C++ стандарта C++17 с использованием компилятора gcc
- Подготовлено полное покрытие unit-тестами методов контейнерных классов c помощью библиотеки GTest

###  Реализация основные методы контейнеров:
    Array, List, Vector, Queue, Stack, Set, Map, Multiset

- Map, Set, Multiset созданы на базе красно-черного дерева.
- Тесты для каждого из контейнеров представлены в соответствующей директрории
- Более подробно об особенностях запуска можно ознакомиться в Makefile

### Реализованы модифицированные методы `emplace`

| Modifiers      | Definition                                      | Containers |
|----------------|-------------------------------------------------| -------------------------------------------|
| `iterator emplace(const_iterator pos, Args&&... args)`          | inserts new elements into the container directly before `pos`  | List, Vector |
| `void emplace_back(Args&&... args)`          | appends new elements to the end of the container  | List, Vector, Queue |
| `void emplace_front(Args&&... args)`          | appends new elements to the top of the container  | List, Stack |
| `std::pair<iterator,bool> emplace(Args&&... args)`          | inserts new elements into the container  | Map, Set, Multiset |
