#include <iostream>
#include "product.h"
#include <string>
#include "input.h"
#include <memory>
#include <vector>

Product::Product(): itemNo(0), name(""), prise(0), quality(0) {}
Product::Product (int newItemNo, const std::string& newName, double newPrise, int newQuality) : 
itemNo(newItemNo), name(newName), prise(newPrise), quality(newQuality) {}

void Product::setItemNo(unsigned int newItemNo) {
    Product::itemNo = newItemNo;
}
void Product::setName (std::string& newName) {
    Product::name = newName;
}
void Product::setPrise(double newPrise) {
    prise = newPrise;
}
void Product::setQuality(int newQuality) {
    quality = newQuality;
}
void Product::printProductInfo(size_t index) const {
    std::cout << "---------------------------" << std::endl;
    std::cout << index + 1 << ": " << name << ' ' << prise << " byn" << '\n' << "Артикул: " << itemNo << std::endl;
    if (quality)
    std::cout << "В наличии: " << quality << std::endl;
    else
    std::cout << "Нет в наличии: " << std::endl;
}
void Product::printAllProducts(std::vector <std::unique_ptr<Product>> products) const {
    if (products.empty()) {
        std::cout << "Нет товаров" << std::endl;
        exit;
    }
    else
    for (size_t i = 0; i < products.size(); i++)
        products[i]->printProductInfo(i);
}
Product addProduct() {
    int itemNo       = readInt("Введите артикул: ");
    std::string name = readString("Введите имя: ");
    double prise     = readDouble("Введите стоимость: ");
    int quality      = readInt("Введите кол-во: ");

    return Product(itemNo, name, prise, quality);
}

void Product::changeProduct() {
    int itemNo       = readInt("Введите артикул: ");
    std::string name = readString("Введите имя: ");
    double prise     = readDouble("Введите стоимость: ");
    int quality      = readInt("Введите кол-во: ");

    setItemNo(itemNo);
    setName(name);
    setPrise(prise);
    setQuality(quality);
}
