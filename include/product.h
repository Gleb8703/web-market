#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <string_view>

class Product {
    unsigned int itemNo = 0;    
    std::string name;
    double prise = 0.0;
    unsigned int quality = 0;
public:
    Product() = default;
    Product(int newItemNo, std::string_view newName, double newPrise, int newQuality);
    
    void setItemNo(unsigned int newItemNo);
    void setName(std::string_view newName); 
    void setPrise(double newPrise);
    void setQuality(int newQuality);
    
    double getPrise() const { return prise; }
    void printProductInfo(size_t index) const;
    void changeProduct();
    
    int getQuality() const { return quality; } 
    std::string getName() const { return name; }
    int getItemNo() const { return itemNo; }
};

Product addProduct();