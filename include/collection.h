#pragma once
#include <iostream>
#include <vector>
#include <cstddef>
#include <utility>

template<typename T>
class Collection {
    std::vector<T> _items;

public:
    template<typename U>
    void add(U&& item);

    void remove(std::size_t index);

    T& at(std::size_t index);
    const T& at(std::size_t index) const;
    
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    std::size_t size() const;
    bool empty() const;

    void clear();

    auto begin()       { return _items.begin(); }
    auto end()         { return _items.end(); }
    auto begin() const { return _items.begin(); }
    auto end()   const { return _items.end(); }

    template<typename Predicate>
    T* findIf(Predicate pred);

    template<typename Predicate>
    const T* findIf(Predicate pred) const;

    template<typename Printer>
    void printWith(Printer printer) const;
};

template<typename T, typename Func>
void forEach(Collection<T>& c, Func func);          

template<typename T, typename Func>
void forEach(const Collection<T>& c, Func func);   

#include "collection.tpp"