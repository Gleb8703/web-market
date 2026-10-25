#pragma once
#include "baseException.h"
class InvalidProductDataException : public BaseException {
public:
    explicit InvalidProductDataException(const std::string& msg) 
    : BaseException("Неверно введены данные: " + msg) {}
};