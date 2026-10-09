#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "cart.h"
#include "product.h"
#include "input.h"
#include "catalog.h"
#include "foodProduct.h"
#include "bookProduct.h"

Catalog& Catalog::operator+=(std::unique_ptr<Product> product) {
    if (!product) return *this;
    for (const auto& p : products) {
        if (*p == product->getItemNo()) {
            std::cout << "Товар с таким артикулом уже есть\n";
            return *this;
        }
    }
    products.push_back(std::move(product));
    return *this;
}
Catalog& Catalog::operator-=(int itemNo) {
    auto it = std::find_if(products.begin(), products.end(),
        [itemNo](const std::unique_ptr<Product>& p) { return *p == itemNo; });
    if (it == products.end()) {
        std::cout << "Товара с таким артикулом нет\n";
        return *this;
    }
    products.erase(it);
    return *this;
}

void Catalog::printCatalog() const {
    int i = 0;
    for (const auto& p : products) {
        std::cout << "----------------------------\n" << i + 1 << ": ";
        p->printInfo(); 
        i++;
    }
}

void Catalog::printTypes() const {
    for (const auto& p : products) {
        std::cout << p->getItemNo() << " — " << p->getType() << "\n"; 
    }
}

void Catalog::printDiscountPrices() const {
    for (const auto& p : products) {
        std::cout << p->getName()
                  << ": базовая " << p->getPrice()
                  << ", итоговая " << p->printDiscountPrices() << "\n";  
    }
}
Product* Catalog::findProduct(int itemNo) const {
    for (const auto& p : products) {
        if (*p == itemNo) {
            return p.get();
        }
    }
    return nullptr;
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
void Catalog::checkExpiryDays() const {
    int daysPassed = readInt("Введите кол-во прошедших дней: ");
    for (const auto& p : products) {
        if (auto food = dynamic_cast<const FoodProduct*>(p.get())) {
            std::cout << "----------------------------\n";
            p->printInfo();
            if (food->isExpired(daysPassed)) {
                std::cout << "Просрочено!!!" << std::endl;
            } else {
                std::cout << "Годен" << std::endl;
            }
        }
    }
}
void Catalog::printReadingTime() const {
    int readingSpeed = readInt("Сколько страниц вы читаете в час: ");
    for (const auto& p : products) {
        if (auto book = dynamic_cast<const BookProduct*>(p.get())) {
            std::cout << p->getName() << ": ~" << book->calculateReadingTime(readingSpeed) << " ч.\n";
        }
    }
}