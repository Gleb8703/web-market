#pragma once
#include "baseException.h"
#include <format>
class ProductNotFoundException : public BaseException {
public:
    explicit ProductNotFoundException(int itemNo) : BaseException("Товар c артикулом " + std::to_string(itemNo) + " не найден") {}
};