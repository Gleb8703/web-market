#pragma once
#include "baseException.h"
class AlreadyInCartException : public BaseException{
public:
    explicit AlreadyInCartException() 
        : BaseException("Этот товар уже находится в корзине!") {}
};