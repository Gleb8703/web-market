#pragma once
#include "baseException.h"
class AlreadyInCartException : public BaseException{
public:
    AlreadyInCartException() 
        : BaseException("Этот товар уже находится в корзине!") {}
};