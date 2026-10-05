#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <string_view>
#include "input.h"

class Product {
protected:
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

    virtual ~Product() = default;

    virtual std::string getType() const = 0;               
    virtual void printInfo() const;                      
    virtual double calculateFinalPrice() const;

    friend std::ostream& operator<<(std::ostream& cout, const Product& product) {
        cout << product.name << ' ' << product.price << " byn" << '\n' << "Артикул: " << product.itemNo << '\n';
        if (product.quantity) {
            cout << "В наличии: " << product.quantity;
        } else {
            cout << "Нет в наличии: " << '\n';
        }
        return cout;
    };
    friend std::istream& operator>>(std::istream& is, Product& product) {
        product.itemNo  = readInt("Введите артикул: ");
        product.name    = readString("Введите имя: ");
        product.price   = readDouble("Введите стоимость: ");
        product.quantity = readInt("Введите кол-во: ");
        return is;
    };

    bool operator==(const Product& product) const;

    bool operator==(int itemNo) const;
    bool operator!=(int itemNo) const;
    bool operator<(const Product& product) const; //NOSONAR
    bool operator>(const Product& product) const;
    bool operator<=(const Product& product) const;
    bool operator>=(const Product& product) const;
    bool operator<(int quantity) const;
    bool operator>(int quantity) const;
};

bool checkItemNo(const std::vector<std::unique_ptr<Product>>& products, const Product& product);
Product* checkItemNo(const std::vector<std::unique_ptr<Product>>& products, int itemNo);

class BookProduct : public Product {
    int pages = 0;
    std::string author;
public:
    BookProduct(int newItemNo, std::string_view newName, double newPrise, int newQuantity, int newPages, std::string_view newAuthor);
    int getPages() { return pages; } 
    std::string getAuthor() { return author; }
    void setPages(int newPages);
    void setAuthor(std::string_view newAuthor);
    void printInfo() const override;
    std::string getType() const override;
    double calculateFinalPrice() const override;
};
class FoodProduct : public Product {
    int expiryDays = 0;
    bool isRefrigerated = false;

public:
    FoodProduct() = default;
    FoodProduct(int newItemNo, std::string_view newName, double newPrice, int newQuantity,
                int newExpiryDays, bool newIsRefrigerated);

    std::string getType() const override;                 
    void printInfo() const override;                      
    double calculateFinalPrice() const override;          

    bool isExpired(int daysPassed) const;
    std::string getStorageInfo() const;
};

class ClothingProduct : public Product {
    std::string size;
    std::string material;

public:
    ClothingProduct() = default;
    ClothingProduct(int newItemNo, std::string_view newName, double newPrice, int newQuantity, std::string_view newSize, std::string_view newMaterial);
    std::string getType() const override;
    void printInfo() const override;
    double calculateFinalPrice() const override;  
    std::string getSizeInfo() const;
};