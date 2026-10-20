#pragma once
#include "baseException.h"
class ProductNotFoundException : public BaseException {
public:
    ProductNotFoundException(int itemNo) : BaseException("Товар c артикулом " + std::to_string(itemNo) + " не найден") {}
};