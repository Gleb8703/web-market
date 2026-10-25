#pragma once
#include "baseException.h"
class FileException : public BaseException {
public:
FileException(std::string fileName) : BaseException("Ошибка файла:" + fileName) {}
}; 