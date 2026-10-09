#include "product.h"

class BookProduct : public Product {
    int pages = 0;
    std::string author;
public:
    BookProduct(int newItemNo, std::string_view newName, double newPrise, int newQuantity, int newPages, std::string_view newAuthor);
    int getPages() const { return pages; } 
    std::string getAuthor() const { return author; }
    void setPages(int newPages); 
    void setAuthor(std::string_view newAuthor);
    void printInfo() const override;
    std::string getType() const override;
    double printDiscountPrices() const override;
    int calculateReadingTime(int readingSpeed) const;      
};