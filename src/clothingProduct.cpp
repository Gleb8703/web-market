#include "clothingProduct.h"
#define DISCOUNT_COEFF 0.9

ClothingProduct::ClothingProduct(int newItemNo, std::string_view newName, double newPrice, int newQuantity, std::string_view newSize, std::string_view newMaterial) 
    : Product(newItemNo, newName, newPrice, newQuantity),
    size(newSize),
    material(newMaterial) {}

std::string ClothingProduct::getType() const {
    return "Одежда";
}

void ClothingProduct::printInfo() const {
    Product::printInfo();
    std::cout << "Размер: " << size << "\n" << "Материал: " << material << "\n";
}

double ClothingProduct::calculateFinalPrice() const {
    return getPrice() * DISCOUNT_COEFF;
}
std::string ClothingProduct::getSizeInfo() const {
    return "Размер " + size + ", материал: " + material;
}