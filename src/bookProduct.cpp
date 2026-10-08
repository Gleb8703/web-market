#include "bookProduct.h"
#define DISCOUNT_COEFF 0.9
#define DISOUNT_PAGES 500

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
    if (pages > DISOUNT_PAGES) {
        return getPrice() * DISCOUNT_COEFF;
    }
    return getPrice();
}