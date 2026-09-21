#include <iostream>
#include <memory>
#include <vector>

class Product {
    unsigned int itemNo;
    std::string name;
    double prise;
    unsigned int quality;
    public:
    Product();
    Product (int newItemNo, const std::string& newName, double newPrise, int newQuality);
    void setItemNo(unsigned int newItemNo);
    void setName (std::string& newName);
    void setPrise(double newPrise);
    void setQuality(int newQuality);
    double getPrise() const { return prise; }
    void printProductInfo(size_t index) const;
    void printAllProducts(std::vector <std::unique_ptr<Product>> products) const;
    void changeProduct();
    int getQuality() const { return quality; } 
    std::string getName() const { return name; }
    int getItemNo() const { return itemNo; }
};
Product addProduct();
