#include <iostream>
#include <vector>
#include "cart.h"
#include "product.h"

void Cart::addProductToCart(Product product) {
    cartProducts.push_back(product);
    totalQuality++;
    totalPrise += product.getPrise();
}
void Cart::delProductFromCart(Product product) {
    cartProducts.
}
