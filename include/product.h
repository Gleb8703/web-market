#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <string_view>

class Product {
    unsigned int itemNo = 0;    
    std::string name;
    double price = 0.0;
    unsigned int quantity = 0;
public:
    Product() = default;
    Product(int newItemNo, std::string_view newName, double newPrise, int newQuantity);
    
    void setItemNo(unsigned int newItemNo);
    void setName(std::string_view newName); 
    void setPrice(double newPrise);
    void setQuantity(int newQuantity);
    
    double getPrice() const { return price; }
    void printProductInfo(size_t index) const;
    void changeProduct();
    
    int getQuantity() const { return quantity; } 
    std::string getName() const { return name; }
    int getItemNo() const { return itemNo; }
    friend std::ostream& operator<<(std::ostream& cout, const Product& product);
};

Product addProduct();