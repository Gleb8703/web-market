#include "bookProduct.h"
constexpr double DISCOUNT_COEFF = 0.9;
constexpr int DISCOUNT_PAGES = 500;

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
double BookProduct::printDiscountPrices() const {
    if (pages > DISOUNT_PAGES) {
        return getPrice() * DISCOUNT_COEFF;
    }
    return getPrice();
}
int BookProduct::calculateReadingTime(int readingSpeed) const {
    return pages/readingSpeed;
}