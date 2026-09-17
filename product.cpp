#include <iostream>
#include "product.h"
#include <string>

    Product::Product(): itemNo(0), name(0), prise(0), quality(0) {}
    Product::Product (unsigned int newItemNo, std::string& newName, double newPrise, unsigned int newQuality) : 
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
    void Product::printProductInfo() {
        std::cout << name << prise << "byn" << '\n' << "Артикул: " << itemNo << std::endl;
        // if (quality)
        // std::cout << "В наличии: " << quality << std::endl;
        // else
        // std::cout << "Нет в наличии: " << std::endl;
    }
    Product addProduct() {
    unsigned int itemNo;
    std::string name;
    double prise;
    unsigned int quality;
    std::cout << "Введите артикул: ";
    std::cin >> itemNo;
    std::cout << "Введите имя: ";
    std::getline(std::cin, name);
    std::cout << "Введите стоимость: ";
    std::cin >> prise;
    std::cout << "Введите кол-во: ";
    std::cin >> quality;
    Product product(itemNo, name, prise, quality);
    return product;
}
void changeProduct(Product product) {
    unsigned int itemNo;
    std::string name;
    double prise;
    unsigned int quality;
    std::cout << "Введите артикул: ";
    std::cin >> itemNo;
    std::cout << "Введите имя: ";
    std::getline(std::cin, name);
    std::cout << "Введите стоимость: ";
    std::cin >> prise;
    std::cout << "Введите кол-во: ";
    std::cin >> quality;
    product.setItemNo(itemNo);
    product.setName (name);
    product.setPrise(prise);
    product.setQuality(quality);
}
