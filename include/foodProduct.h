#include "product.h"

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