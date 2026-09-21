#pragma once
#include <iostream>
#include <vector>

class Product;

class Cart {
    double totalPrise = 0;
    int totalQuality = 0;
    std::vector<Product*> cartProducts;
public:
    void delProductFromCart(std::size_t index);
    void addProductToCart(Product* product);
    void clearAll();
    Product* getProduct(std::size_t index) const;
    std::size_t size() const { return cartProducts.size(); }
};