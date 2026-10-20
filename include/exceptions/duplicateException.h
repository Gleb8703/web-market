#pragma once
#include "baseException.h"
class DuplicateItemException : public BaseException {
public:
    explicit DuplicateItemException(int itemNo) 
        : BaseException("Товар с артикулом " + std::to_string(itemNo) + " уже существует!") {}
};