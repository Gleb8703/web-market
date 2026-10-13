#pragma once
#include <string>
#include "product.h"
#include "collection.h"

class Customer {
    std::string fullName;
    std::string email;
    std::string phone;
    Collection<Product*> viewedProducts;

public:
    Customer() = default;
    Customer(const std::string& name, const std::string& email, const std::string& phone)
        : fullName(name), email(email), phone(phone) {}

    std::string getName()  const { return fullName; }
    std::string getEmail() const { return email; }
    std::string getPhone() const { return phone; }

    void viewProduct(Product* p) { if (p) viewedProducts.add(p); }
    std::size_t viewedCount() const { return viewedProducts.size(); }
};