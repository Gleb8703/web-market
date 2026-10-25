#pragma once
#include "baseException.h"
class FileException : public BaseException {
public:
explicit FileException(const std::string& fileName) : BaseException("Ошибка файла:" + fileName) {}
}; 