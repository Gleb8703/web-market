#include <iostream>
#include <vector>
#include "cart.h"
#include "product.h"
#include <algorithm>

void Cart::printCart() const {
    std::cout << "Стоимость корзины: " << totalPrice
              << " Кол-во товаров: " << cartProducts.size() << std::endl;
    cartProducts.printWith([](Product* p) {
        std::cout << *p;
    });
}

void Cart::delProductFromCart(std::size_t index) {
    if (index >= cartProducts.size()) {
        std::cout << "Неверный индекс\n";
        return;
    }
    totalQuantity -= cartProducts.at(index)->getQuantity();
    totalPrice    -= cartProducts.at(index)->getPrice();
    cartProducts.remove(index);
}

void Cart::clearAll() {
    cartProducts.clear();
    totalPrice = 0;
    totalQuantity = 0;
}

Product* Cart::getProduct(std::size_t index) const {
    if (index >= cartProducts.size()) return nullptr;
    return cartProducts.at(index);
}

Cart& Cart::operator+=(Product* product) {
    if (!product) return *this;
    for (std::size_t i = 0; i < cartProducts.size(); ++i) {
        if (*cartProducts.at(i) == *product) {
            std::cout << "Товар уже в корзине\n";
            return *this;
        }
    }
    cartProducts.add(product);
    totalQuantity += product->getQuantity();
    totalPrice += product->getPrice();
    return *this;
}

Cart& Cart::operator-=(Product* product) {
    if (!product) return *this;
    for (std::size_t i = 0; i < cartProducts.size(); ++i) {
        if (cartProducts.at(i) == product) {
            totalQuantity -= cartProducts.at(i)->getQuantity();
            totalPrice    -= cartProducts.at(i)->getPrice();
            cartProducts.remove(i);
            return *this;
        }
    }
    return *this;
}