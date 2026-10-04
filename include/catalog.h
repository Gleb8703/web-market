#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
//#include "include/cart.h"
#include "product.h"
#include "input.h"

class Product;
class Catalog {
    std::vector<std::unique_ptr<Product>> products;
public:
    Catalog& operator+=(const Product& product); // добавление товара в каталог
    Catalog& operator-=(int itemNo); // 
    void printCatalog() const;
    const Product& findProduct(int itemNo) const;
    void sortCatalogByPrice(); 
    std::size_t size() const { return products.size(); }
    Product* getProduct(std::size_t index) const;
};