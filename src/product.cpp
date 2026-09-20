#include <iostream>
#include "product.h"
#include <string>
#include "input.h"

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
void Product::printProductInfo() const {
    std::cout << "---------------------------" << std::endl;
    std::cout << name << ' ' << prise << " byn" << '\n' << "Артикул: " << itemNo << std::endl;
    if (quality)
    std::cout << "В наличии: " << quality << std::endl;
    else
    std::cout << "Нет в наличии: " << std::endl;
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
