#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "cart.h"
#include "product.h"
#include "input.h"
#include "catalog.h"

Catalog& Catalog::operator+=(const Product& newProduct) {
    for (const auto& p : products) {
        if (*p == newProduct) {
            std::cout << "Товар с таким артикулом уже есть\n";
            return *this;
        }
        products.push_back(std::make_unique<Product>(newProduct));
        return *this; 
    }
}
Catalog& Catalog::operator-=(int itemNo) {
    auto it = std::find_if(products.begin(), products.end(),
        [itemNo](const std::unique_ptr<Product>& p) {
            return *p == itemNo;
        });
    if (it == products.end()) {
        std::cout << "Товара с таким артикулом нет в каталоге\n";
        return *this;
    }
    products.erase(it);
    return *this;
}
void Catalog::printCatalog() const {
    for (const auto& p : products) {
        std::cout << *p;
    }
}
const Product& Catalog::findProduct(int itemNo) const {
    for (const auto& p : products) { //NOSONAR
        if (*p == itemNo) {
            return *p;
            break;
        }
    }
}
void Catalog:: sortCatalogByPrice() {
    if (products.empty()) {
        std::cout << "Нет товаров\n";
        return;
    }
    std::sort(products.begin(), products.end(),
        [](const std::unique_ptr<Product>& a, const std::unique_ptr<Product>& b) {
            return *a < *b;
        });
    std::cout << "Товары отсортированы по цене:\n";
}
Product* Catalog::getProduct(std::size_t index) const {
    if (index >= products.size()) {
        return nullptr; 
    }
    return products[index].get();
}
