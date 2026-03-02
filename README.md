# Lab_9 — Шаблонная функция GroupStats

*[Русский](#ru) | [English](#en)*

---

<a name="ru"></a>

## Описание

Четыре реализации на **C++17**, демонстрирующие передачу вызываемых объектов (callable) в шаблонную функцию `GroupStats`. Каждый вариант решает одну и ту же задачу разным способом.

## Задача

Шаблонная функция `GroupStats(arr, n, key, val)` группирует элементы массива по ключу и для каждой группы вычисляет:

- Количество элементов (`count`)
- Минимальный и максимальный элемент
- Сумму значений (`sum`)
- Среднее значение (`avg`)

## Варианты реализации

| Файл | Подход |
|---|---|
| `function.cpp` | Указатели на функции |
| `functor.cpp` | Функторы (перегрузка `operator()`) |
| `lambda.cpp` | Лямбда-выражения |
| `dop_zadanie.cpp` | Дополнительное задание с классом `Mine` |

## Требования

- Компилятор с поддержкой **C++17**

## Сборка и запуск

```bash
# Пример для варианта с лямбдами
g++ -std=c++17 lambda.cpp -o lab9
./lab9
```

## Пример вывода (`lambda.cpp`)

```
====== INT ======
Key: 1  Count: 3  MinElement: 1  MaxElement: 21  Sum: 33  Average: 11
Key: 1  Count: 2  MinElement: 11  MaxElement: 31  Sum: 42  Average: 21
...
```

---

<a name="en"></a>

## Description

Four **C++17** implementations demonstrating how to pass callable objects to a template function `GroupStats`. Each file solves the same problem using a different approach.

## Task

The template function `GroupStats(arr, n, key, val)` groups array elements by a key and computes for each group:

- Element count (`count`)
- Minimum and maximum element
- Sum of values (`sum`)
- Average value (`avg`)

## Implementations

| File | Approach |
|---|---|
| `function.cpp` | Function pointers |
| `functor.cpp` | Functors (overloaded `operator()`) |
| `lambda.cpp` | Lambda expressions |
| `dop_zadanie.cpp` | Additional task with `Mine` class |

## Requirements

- Compiler with **C++17** support

## Build & Run

```bash
# Example for the lambda variant
g++ -std=c++17 lambda.cpp -o lab9
./lab9
```

## Sample Output (`lambda.cpp`)

```
====== INT ======
Key: 1  Count: 3  MinElement: 1  MaxElement: 21  Sum: 33  Average: 11
Key: 1  Count: 2  MinElement: 11  MaxElement: 31  Sum: 42  Average: 21
...
```
