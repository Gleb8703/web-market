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
#include "exceptions/exceptions.h"

Catalog& Catalog::operator+=(std::unique_ptr<Product> product) {
    if (!product) return *this;
    for (const auto& p : products) {
        if (*p == product->getItemNo()) {
            throw DuplicateItemException(product->getItemNo());
        }
    }
    products.add(std::move(product));
    return *this;
}

Catalog& Catalog::operator-=(int itemNo) {
    for (std::size_t i = 0; i < products.size(); ++i) {
        if (*products.at(i) == itemNo) {
            products.remove(i);
            return *this;
        }
    }
    std::cout << "Товара с таким артикулом нет\n";
    return *this;
}

void Catalog::printCatalog() const {
    for (std::size_t i = 0; i < products.size(); ++i) {
        std::cout << "----------------------------\n" << i + 1 << ": ";
        products.at(i)->printInfo();
    }
}

void Catalog::printTypes() const {
    products.printWith([](const std::unique_ptr<Product>& p) {
        std::cout << p->getItemNo() << " — " << p->getType() << "\n";
    });
}

void Catalog::printDiscountPrices() const {
    products.printWith([](const std::unique_ptr<Product>& p) {
        std::cout << p->getName()
                  << ": базовая " << p->getPrice()
                  << ", итоговая " << p->printDiscountPrices() << "\n";
    });
}

Product* Catalog::findProduct(int itemNo) const {
    auto found = products.findIf([itemNo](const std::unique_ptr<Product>& p) {
        return *p == itemNo;
    });
    if (found) {
        return found->get();
    }
    throw ProductNotFoundException(itemNo);
}

void Catalog::sortCatalogByPrice() {
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
    if (index >= products.size()) return nullptr;
    return products.at(index).get();
}

void Catalog::checkExpiryDays() const {
    int daysPassed = readInt("Введите кол-во прошедших дней: ");
    for (std::size_t i = 0; i < products.size(); ++i) {
        if (auto food = dynamic_cast<const FoodProduct*>(products.at(i).get())) {
            std::cout << "----------------------------\n";
            products.at(i)->printInfo();
            if (food->isExpired(daysPassed))
                std::cout << "Просрочено!!!\n";
            else
                std::cout << "Годен\n";
        }
    }
}

void Catalog::printReadingTime() const {
    int readingSpeed = readInt("Сколько страниц вы читаете в час: ");
    for (std::size_t i = 0; i < products.size(); ++i) {
        if (auto book = dynamic_cast<const BookProduct*>(products.at(i).get())) {
            std::cout << products.at(i)->getName()
                      << ": ~" << book->calculateReadingTime(readingSpeed) << " ч.\n";
        }
    }
}
// operator[]
void Catalog::printByIndex(std::size_t index) const {
    if (index >= products.size()) {
        std::cout << "Неверный индекс\n";
        return;
    }
    std::cout << "Товар по индексу " << index << ":\n";
    products[index]->printInfo();   // ← operator[]
}

// clear
void Catalog::clearAll() {
    products.clear();
    std::cout << "Каталог очищен\n";
}

// findIf
Product* Catalog::findExpensiveThan(double minPrice) const {
    auto found = products.findIf([minPrice](const std::unique_ptr<Product>& p) {
        return p->getPrice() > minPrice;
    });
    if (found) {
        return found->get();
    }
    return nullptr;
}

void Catalog::printTotalValue() const {
    if (products.empty()) {
        std::cout << "Каталог пуст\n";
        return;
    }

    double total = 0.0;
    forEach(products, [&total](const std::unique_ptr<Product>& p) {
        total += p->getPrice() * p->getQuantity();
    });

    std::cout << "Общая стоимость каталога: " << total << " byn\n";
}