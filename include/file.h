#pragma once
#include <string>
#include "catalog.h"
#include "cart.h"

class FileManager {
public:
    // Сохранение состояния
    static void saveState(const std::string& filename, const Catalog& catalog, const Cart& cart);
    
    // Загрузка состояния (возвращает true, если успешно)
    static bool loadState(const std::string& filename, Catalog& catalog, Cart& cart);
    
    // Добавление записи в лог
    static void logAction(const std::string& action);
    
    // Формирование текстового отчета
    static void generateReport(const std::string& filename, const Catalog& catalog, const Cart& cart);
};