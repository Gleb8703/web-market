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

void Product::printInfo() const {
    std::cout << "---------------------------" << std::endl;
    //std::cout << index + 1 << ": " << name << ' ' << price << " byn" << '\n' << "Артикул: " << itemNo << std::endl;
    std::cout << ": " << name << ' ' << price << " byn" << '\n' << "Артикул: " << itemNo << std::endl;
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

BookProduct::BookProduct(int newItemNo, std::string_view newName, double newPrise, int newQuantity, int newPages, std::string_view newAuthor) :
Product(newItemNo, newName, newPrise, newQuantity), pages(newPages), author(newAuthor) {}
void BookProduct::setPages(int newPages) {
    pages = newPages;
}
void BookProduct::setAuthor(std::string_view newAuthor) {
    author = newAuthor;
}
std::string BookProduct::getType() const {
    return "Книга";
}
void BookProduct::printInfo() const {
    Product::printInfo();  
    std::cout << "Автор: " << author << "\n"
              << "Страниц: " << pages << "\n";
}
double BookProduct::calculateFinalPrice() const {
    if (pages > 500) {
        return price * 0.9;
    }
    return price;
}

FoodProduct::FoodProduct(int newItemNo, std::string_view newName, double newPrice, int newQuantity,
                         int newExpiryDays, bool newIsRefrigerated)
    : Product(newItemNo, newName, newPrice, newQuantity),
      expiryDays(newExpiryDays),
      isRefrigerated(newIsRefrigerated) {}

std::string FoodProduct::getType() const {
    return "Продукт питания";
}

void FoodProduct::printInfo() const {
    Product::printInfo();   // общая часть
    std::cout << "Срок годности: " << expiryDays << " дней\n"
              << "Хранение: " << getStorageInfo() << "\n";
}

double FoodProduct::calculateFinalPrice() const {
    // Скидка 20% если срок годности меньше 3 дней
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
ClothingProduct::ClothingProduct(int newItemNo, std::string_view newName, double newPrice, int newQuantity, std::string_view newSize, std::string_view newMaterial) 
    : Product(newItemNo, newName, newPrice, newQuantity),
    size(newSize),
    material(newMaterial) {}

std::string ClothingProduct::getType() const {
    return "Одежда";
}

void ClothingProduct::printInfo() const {
    Product::printInfo();
    std::cout << "Размер: " << size << "\n"
              << "Материал: " << material << "\n";
}

double ClothingProduct::calculateFinalPrice() const {
    return price * 0.9;
}
std::string ClothingProduct::getSizeInfo() const {
    return "Размер " + size + ", материал: " + material;
}