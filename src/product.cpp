#include <iostream>
#include "product.h"
#include <string>
#include <string_view>
#include "input.h"

Product::Product(int newItemNo, std::string_view newName, double newPrise, int newQuality)
    : itemNo(newItemNo), name(newName), prise(newPrise), quality(newQuality) {}

void Product::setItemNo(unsigned int newItemNo) {
    itemNo = newItemNo;
}

void Product::setName(std::string_view newName) {
    name = newName;
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
    // Добавлены фигурные скобки
    if (quality) {
        std::cout << "В наличии: " << quality << std::endl;
    } else {
        std::cout << "Нет в наличии: " << std::endl;
    }
}

Product addProduct() {
    int itemNo       = readInt("Введите артикул: ");
    std::string name = readString("Введите имя: ");
    double prise     = readDouble("Введите стоимость: ");
    int quality      = readInt("Введите кол-во: ");

    return Product(itemNo, name, prise, quality);
}

void Product::changeProduct() {
    // Убрано затенение полей. Сразу передаём значения в сеттеры.
    setItemNo(readInt("Введите артикул: "));
    setName(readString("Введите имя: "));
    setPrise(readDouble("Введите стоимость: "));
    setQuality(readInt("Введите кол-во: "));
}