#include <iostream>
#include <vector>

class Product;
class Cart {
    double totalPrise;
    int totalQuality;
    std::vector<Product> cartProducts;
    public:
    void delProductFromCart(Product product);
    void addProductToCart(Product product);
    void setTotalQuality();
    void setTotalPrise();
};
