#include "foodProduct.h"
#define DISCOUNT_COEFF 0.8
#define DISCOUNT_EXPIRY_DAYS 3

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
    if (expiryDays < DISCOUNT_EXPIRY_DAYS) {
        return getPrice() * DISCOUNT_COEFF;
    }
    return getPrice();
}

bool FoodProduct::isExpired(int daysPassed) const {
    return daysPassed > expiryDays;
}

std::string FoodProduct::getStorageInfo() const {
    return isRefrigerated ? "В холодильнике" : "При комнатной температуре";
}