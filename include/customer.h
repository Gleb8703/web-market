#pragma once
#include <string>

class Customer {
    std::string _fullName;
    std::string _email;
    std::string _phone;

public:
    Customer() = default;
    Customer(const std::string& name, const std::string& email, const std::string& phone)
        : _fullName(name), _email(email), _phone(phone) {}

    std::string getName()  const { return _fullName; }
    std::string getEmail() const { return _email; }
    std::string getPhone() const { return _phone; }
};