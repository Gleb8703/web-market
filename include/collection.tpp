#pragma once
template<typename T>
template<typename U>
void Collection<T>::add(U&& item) {
    _items.push_back(std::forward<U>(item));
}

template<typename T>
void Collection<T>::remove(std::size_t index) {
    if (index < _items.size())
        _items.erase(_items.begin() + index);
}

template<typename T>
T& Collection<T>::at(std::size_t index) {
    return _items[index];
}

template<typename T>
const T& Collection<T>::at(std::size_t index) const {
    return _items[index];
}

template<typename T>
T& Collection<T>::operator[](std::size_t index) {
    return _items[index];
}

template<typename T>
const T& Collection<T>::operator[](std::size_t index) const {
    return _items[index];
}

template<typename T>
std::size_t Collection<T>::size() const {
    return _items.size();
}

template<typename T>
bool Collection<T>::empty() const {
    return _items.empty();
}

template<typename T>
void Collection<T>::clear() {
    _items.clear();
}

template<typename T>
template<typename Predicate>
T* Collection<T>::findIf(Predicate pred) {
    for (auto& item : _items)
        if (pred(item)) return &item;
    return nullptr;
}

template<typename T>
template<typename Predicate>
const T* Collection<T>::findIf(Predicate pred) const {
    for (const auto& item : _items)
        if (pred(item)) return &item;
    return nullptr;
}

template<typename T>
template<typename Printer>
void Collection<T>::printWith(Printer printer) const {
    for (const auto& item : _items)
        printer(item);
}

template<typename T, typename Func>
void forEach(Collection<T>& c, Func func) {
    for (std::size_t i = 0; i < c.size(); ++i)
        func(c.at(i));
}

template<typename T, typename Func>
void forEach(const Collection<T>& c, Func func) {
    for (std::size_t i = 0; i < c.size(); ++i)
        func(c.at(i));
}