#include <iostream>
#include "product.h"
#include <string>
#include <string_view>
#include "input.h"

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

void Product::printProductInfo(size_t index) const {
    std::cout << "---------------------------" << std::endl;
    std::cout << index + 1 << ": " << name << ' ' << price << " byn" << '\n' << "Артикул: " << itemNo << std::endl;
    if (quantity) {
        std::cout << "В наличии: " << quantity << std::endl;
    } else {
        std::cout << "Нет в наличии: " << std::endl;
    }
}

Product addProduct() {
    int itemNo       = readInt("Введите артикул: ");
    std::string name = readString("Введите имя: ");
    double price     = readDouble("Введите стоимость: ");
    int quantity      = readInt("Введите кол-во: ");

    return Product(itemNo, name, price, quantity);
}

void Product::changeProduct() {
    setItemNo(readInt("Введите артикул: "));
    setName(readString("Введите имя: "));
    setPrice(readDouble("Введите стоимость: "));
    setQuantity(readInt("Введите кол-во: "));
}