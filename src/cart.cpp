#include <iostream>
#include <vector>
#include "cart.h"
#include "product.h"

Cart::Cart() : totalQuality(0), totalPrise(0) {}
void Cart::addProductToCart(Product* product) {
    cartProducts.push_back(product);
    totalQuality++;
    totalPrise += product->getPrise();
}
void Cart::delProductFromCart(std::size_t index) {
    cartProducts.erase(cartProducts.begin() + index);
}
void Cart::clearAll() {
        cartProducts.clear();
}
Product* Cart::getProduct(std::size_t index) const {
    if (index >= cartProducts.size()) return nullptr;
    return cartProducts[index];
}
