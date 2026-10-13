#pragma once
#include <iostream>
#include <vector>
#include <cstddef>
#include <utility>

template<typename T>
class Collection {
    std::vector<T> _items;

public:
    // Добавление (универсальная ссылка — для копируемых и move-only)
    template<typename U>
    void add(U&& item);

    // Удаление по индексу
    void remove(std::size_t index);

    // Доступ по индексу
    T& at(std::size_t index);
    const T& at(std::size_t index) const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    // Размер
    std::size_t size() const;
    bool empty() const;

    // Очистка
    void clear();

    // Итераторы
    auto begin()       { return _items.begin(); }
    auto end()         { return _items.end(); }
    auto begin() const { return _items.begin(); }
    auto end()   const { return _items.end(); }

    // Поиск по критерию
    template<typename Predicate>
    T* findIf(Predicate pred);

    template<typename Predicate>
    const T* findIf(Predicate pred) const;

    // Вывод через лямбду
    template<typename Printer>
    void printWith(Printer printer) const;
};

template<typename T, typename Func>
void forEach(Collection<T>& c, Func func);          

template<typename T, typename Func>
void forEach(const Collection<T>& c, Func func);   

#include "collection.tpp"