#include "foodProduct.h"

FoodProduct::FoodProduct(int newItemNo, std::string_view newName, double newPrice, int newQuantity,
                         int newExpiryDays, bool newIsRefrigerated)
    : Product(newItemNo, newName, newPrice, newQuantity),
      expiryDays(newExpiryDays),
      isRefrigerated(newIsRefrigerated) {}

std::string FoodProduct::getType() const {
    return "Продукт питания";
}

void FoodProduct::printInfo() const {
    Product::printInfo(); 
    std::cout << "Срок годности: " << expiryDays << " дней\n"
              << "Хранение: " << getStorageInfo() << "\n";
}

double FoodProduct::calculateFinalPrice() const {
    if (expiryDays < 3) {
        return price * 0.8;
    }
    return price;
}

bool FoodProduct::isExpired(int daysPassed) const {
    return daysPassed > expiryDays;
}

std::string FoodProduct::getStorageInfo() const {
    return isRefrigerated ? "В холодильнике" : "При комнатной температуре";
}