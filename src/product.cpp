#include <iostream>
#include "product.h"
#include <string>
#include <string_view>
#include "input.h"
#include "bookProduct.h"
#include "clothingProduct.h"
#include "foodProduct.h"

Product::Product(int newItemNo, std::string_view newName, double newPrice, int newQuantity)
    : itemNo(newItemNo), name(newName), price(newPrice), quantity(newQuantity) {}

void Product::setItemNo(unsigned int newItemNo) {
    itemNo = newItemNo;
}

void Product::setName(std::string_view newName) {
    name = newName;
}
void Product::setPrice(double newPrice) {
    price = newPrice;
}

void Product::setQuantity(int newQuantity) {
    quantity = newQuantity;
}

void Product::printInfo() const {
    std::cout << name << ' ' << price << " byn" << '\n' << "Артикул: " << itemNo << std::endl;
    if (quantity) {
        std::cout << "В наличии: " << quantity << std::endl;
    } else {
        std::cout << "Нет в наличии: " << std::endl;
    }
}

void Product::changeProduct() {
    setItemNo(readInt("Введите артикул: "));
    setName(readString("Введите имя: "));
    setPrice(readDouble("Введите стоимость: "));
    setQuantity(readInt("Введите кол-во: "));
}

double Product::printDiscountPrices() const {
    return price;
}

bool Product::operator==(const Product& other) const {
    return itemNo == other.itemNo;
}

bool Product::operator<(const Product& other) const {
    return price < other.price;
}

bool Product::operator>(const Product& other) const {
    return other < *this;
}

bool Product::operator<=(const Product& other) const {
    return !(other < *this);
}

bool Product::operator>=(const Product& other) const {
    return !(*this < other);
}
bool Product::operator==(int otherItemNo) const {
    return this->itemNo == otherItemNo;
}
bool Product::operator!=(int otherItemNo) const {
    return !(*this == otherItemNo);
}
bool checkItemNo(const std::vector<std::unique_ptr<Product>>& products, const Product& product) {
    for (const auto& productTemp : products) {
        if (*productTemp == product) {
            std::cout << "Товар с таким артикулом уже есть" << std::endl;
            return false; 
        }
    }
    return true;
}
Product* checkItemNo(const std::vector<std::unique_ptr<Product>>& products, int itemNo) {
    for (const auto& product : products) {
        if (*product == itemNo) {
            std::cout << "Товар с таким артикулом уже есть" << std::endl;
            return product.get(); 
        }
    }
    return nullptr;
}

bool Product::operator<(int otherQuantity) const {
    return this->quantity < otherQuantity;
}

bool Product::operator>(int otherQuantity) const {
    return !(this->quantity < otherQuantity);
}




