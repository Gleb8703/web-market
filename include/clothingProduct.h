#include "product.h"

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