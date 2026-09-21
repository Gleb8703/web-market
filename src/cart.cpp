#include <iostream>
#include <vector>
#include "cart.h"
#include "product.h"

void Cart::addProductToCart(Product* product) {
    cartProducts.push_back(product);
    totalQuantity++;
    totalPrice += product->getPrice();
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