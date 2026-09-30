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

// std::ostream& operator<<(std::ostream& cout, const Product& product) {
//     cout << product.name << ' ' << product.price << " byn" << '\n' << "Артикул: " << product.itemNo << '\n';
//     if (product.quantity) {
//         cout << "В наличии: " << product.quantity;
//     } else {
//         cout << "Нет в наличии: " << '\n';
//     }
//     return cout;
// }
// std::istream& operator>>(std::istream& is, Product& product) {
//     product.itemNo  = readInt("Введите артикул: ");
//     product.name    = readString("Введите имя: ");
//     product.price   = readDouble("Введите стоимость: ");
//     product.quantity = readInt("Введите кол-во: ");
//     return is;
// }

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
bool checkItemNo(std::vector<std::unique_ptr<Product>>& products, const Product& product) {
    for (const auto& productTemp : products) {
        if (*productTemp == product) {
            std::cout << "Товар с таким артикулом уже есть" << std::endl;
            return false; 
        }
    }
    return true;
}
Product* checkItemNo(std::vector<std::unique_ptr<Product>>& products, int itemNo) {
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

