#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "product.h"
#include "input.h"

class Product;
class Catalog {
    Collection<std::unique_ptr<Product>> products;
public:
    Catalog& operator+=(std::unique_ptr<Product> product);
    Catalog& operator-=(int itemNo);
    void printCatalog() const;
    void printTypes() const;             
    void printDiscountPrices() const; 
    void sortCatalogByPrice();
    Product* findProduct(int itemNo) const;
    std::size_t size() const { return products.size(); }
    bool empty() const { return products.empty(); }
    Product* getProduct(std::size_t index) const;
    void checkExpiryDays() const;
    void printReadingTime() const;

};