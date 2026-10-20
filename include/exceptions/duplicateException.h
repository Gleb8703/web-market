#pragma once
#include "baseException.h"
class DuplicateItemException : public BaseException {
public:
    DuplicateItemException(int itemNo) 
        : BaseException("Товар с артикулом " + std::to_string(itemNo) + " уже существует!") {}
};