#include <iostream>

class Product {
    unsigned int itemNo;
    std::string name;
    double prise;
    unsigned int quality;
    public:
    Product();
    Product (unsigned int newItemNo, std::string& newName, double newPrise, unsigned int newQuality);
    void setItemNo(unsigned int newItemNo);
    void setName (std::string& newName);
    void setPrise(double newPrise);
    void setQuality(int newQuality);
    void printProductInfo();
};
Product addProduct();
void changeProduct(Product product);