#include <iostream>
#include <vector>
#include "cart.h"
#include "product.h"
#include <algorithm>

void Cart::printCart() const {
    std::cout << "Стоимость корзины: " << totalPrice << "Кол-во товаров: " << cartProducts.size() << std::endl;
    for (const auto& p : cartProducts) {
        std::cout << p;
    }
}
void Cart::delProductFromCart(std::size_t index) {
    if (index >= cartProducts.size()) {
        std::cout << "Неверный индекс\n";
        return;
    }
    totalQuantity -= cartProducts[index]->getQuantity();
    totalPrice   -= cartProducts[index]->getPrice();
    cartProducts.erase(cartProducts.begin() + index);
}
void Cart::clearAll() {
    cartProducts.clear();
    totalPrice = 0;
    totalQuantity = 0;
}

Product* Cart::getProduct(std::size_t index) const {
    if (index >= cartProducts.size()) {
        return nullptr;
    }
    return cartProducts[index];
}
Cart& Cart::operator+=(Product* product) {
    if (!product) return *this;
    for (const Product* p : cartProducts) {
        if (*p == *product) {
            std::cout << "Товар уже в корзине\n";
            return *this;
        }
    }

    cartProducts.push_back(product);
    totalQuantity += product->getQuantity();
    totalPrice += product->getPrice();
    return *this;
}
Cart& Cart::operator-=(Product* product) {
    if (!product) return *this;

    auto it = std::find(cartProducts.begin(), cartProducts.end(), product);
    if (it == cartProducts.end()) {
        return *this;
    }

    totalQuantity -= (*it)->getQuantity();
    totalPrice -= (*it)->getPrice();
    cartProducts.erase(it);
    return *this;
}