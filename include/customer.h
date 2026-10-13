#pragma once
#include <string>

class Customer {
    std::string fullName;
    std::string email;
    std::string phone;

public:
    Customer() = default;
    Customer(const std::string& name, const std::string& email, const std::string& phone)
        : fullName(name), email(email), phone(phone) {}

    std::string getName()  const { return fullName; }
    std::string getEmail() const { return email; }
    std::string getPhone() const { return phone; }
};