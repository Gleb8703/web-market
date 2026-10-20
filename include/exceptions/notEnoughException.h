#pragma once
#include "baseException.h"
class NotEnoughStockException : public BaseException {
public:
    NotEnoughStockException(int requested, int available) 
        : BaseException("Недостаточно товара! Запрошено: " + std::to_string(requested) + ", в наличии: " + std::to_string(available)) {}
};