#pragma once
#include "product.h"
#include "collection.h"

class Product;

class Cart {
    double totalPrice = 0;
    int totalQuantity = 0;
    Collection<Product*> cartProducts;
public:
    void delProductFromCart(std::size_t index);
    void printCart() const;
    void clearAll();
    Product* getProduct(std::size_t index) const;
    std::size_t size() const { return cartProducts.size(); }
    Cart& operator+=(Product* product);
    Cart& operator-=(Product* product);
};