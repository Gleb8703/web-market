#include "file.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <foodProduct.h>
#include <bookProduct.h>
#include <clothingProduct.h>
#include <stdexcept>
#include <sstream>

// ==================== СОХРАНЕНИЕ ====================

void FileManager::saveState(const std::string& filename, const Catalog& catalog, const Cart& cart) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для сохранения: " + filename);
    }

    // Вызываем специализированные методы
    saveFoods(out, catalog);
    saveBooks(out, catalog);
    saveClothes(out, catalog);
    saveCart(out, cart);
}

void FileManager::saveFoods(std::ofstream& out, const Catalog& catalog) {
    for (std::size_t i = 0; i < catalog.size(); ++i) {
        if (auto food = dynamic_cast<FoodProduct*>(catalog.getProduct(i))) {
            out << "FOOD " << food->getItemNo() << " " 
                << std::quoted(food->getName()) << " " 
                << food->getPrice() << " " << food->getQuantity() << " " 
                << food->getExpiryDays() << " " << food->getRefrigerated() << "\n";
        }
    }
}

void FileManager::saveBooks(std::ofstream& out, const Catalog& catalog) {
    for (std::size_t i = 0; i < catalog.size(); ++i) {
        if (auto book = dynamic_cast<BookProduct*>(catalog.getProduct(i))) {
            out << "BOOK " << book->getItemNo() << " " 
                << std::quoted(book->getName()) << " " 
                << book->getPrice() << " " << book->getQuantity() << " " 
                << book->getPages() << " " << std::quoted(book->getAuthor()) << "\n";
        }
    }
}

void FileManager::saveClothes(std::ofstream& out, const Catalog& catalog) {
    for (std::size_t i = 0; i < catalog.size(); ++i) {
        if (auto cloth = dynamic_cast<ClothingProduct*>(catalog.getProduct(i))) {
            out << "CLOTH " << cloth->getItemNo() << " " 
                << std::quoted(cloth->getName()) << " " 
                << cloth->getPrice() << " " << cloth->getQuantity() << " " 
                << std::quoted(cloth->getSize()) << " " << std::quoted(cloth->getMaterial()) << "\n";
        }
    }
}

void FileManager::saveCart(std::ofstream& out, const Cart& cart) {
    for (std::size_t i = 0; i < cart.size(); ++i) {
        out << "CART " << cart.getProduct(i)->getItemNo() << "\n";
    }
}

// ==================== ЗАГРУЗКА ====================

bool FileManager::loadState(const std::string& filename, Catalog& catalog, Cart& cart) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        return false; // Файла нет — начинаем с чистого листа
    }

    std::string type;
    try {
        while (in >> type) {
            if (type == "FOOD")       loadFood(in, catalog);
            else if (type == "BOOK")  loadBook(in, catalog);
            else if (type == "CLOTH") loadCloth(in, catalog);
            else if (type == "CART")  loadCartItem(in, catalog, cart);
            else {
                // Пропускаем неизвестную строку, чтобы не сломать чтение
                std::string dummy;
                std::getline(in, dummy);
            }
        }
    } 
    catch (const std::exception& e) {
        std::cerr << "Ошибка при загрузке данных: " << e.what() << "\n";
        return false;
    }
    
    return true;
}

void FileManager::loadFood(std::ifstream& in, Catalog& catalog) {
    int id, qty, exp, refr; 
    std::string name; 
    double price;
    
    if (!(in >> id >> std::quoted(name) >> price >> qty >> exp >> refr)) {
        throw std::runtime_error("Ошибка чтения данных FOOD (файл поврежден)");
    }
    catalog += std::make_unique<FoodProduct>(id, name, price, qty, exp, refr);
}

void FileManager::loadBook(std::ifstream& in, Catalog& catalog) {
    int id, qty, pages; 
    std::string name, author; 
    double price;
    
    if (!(in >> id >> std::quoted(name) >> price >> qty >> pages >> std::quoted(author))) {
        throw std::runtime_error("Ошибка чтения данных BOOK (файл поврежден)");
    }
    catalog += std::make_unique<BookProduct>(id, name, price, qty, pages, author);
}

void FileManager::loadCloth(std::ifstream& in, Catalog& catalog) {
    int id, qty; 
    std::string name, size, material; 
    double price;
    
    if (!(in >> id >> std::quoted(name) >> price >> qty >> std::quoted(size) >> std::quoted(material))) {
        throw std::runtime_error("Ошибка чтения данных CLOTH (файл поврежден)");
    }
    catalog += std::make_unique<ClothingProduct>(id, name, price, qty, size, material);
}

void FileManager::loadCartItem(std::ifstream& in, Catalog& catalog, Cart& cart) {
    int id;
    if (!(in >> id)) {
        throw std::runtime_error("Ошибка чтения данных CART");
    }
    
    // Проверка связей: товар из корзины должен существовать в каталоге!
    Product* p = catalog.findProduct(id);
    if (p) {
        cart += p;
    } else {
        throw std::runtime_error("Нарушение связей: товар из корзины (ID=" + std::to_string(id) + ") не найден в каталоге!");
    }
}

// ==================== ЛОГИРОВАНИЕ И ОТЧЕТ ====================

void FileManager::logAction(const std::string& logFilename, const std::string& action) {
    std::ofstream log(logFilename, std::ios::app); // Режим добавления
    if (!log.is_open()) {
        std::cerr << "Предупреждение: не удалось открыть лог-файл " << logFilename << "\n";
        return;
    }

    std::time_t now = std::time(nullptr);
    std::tm timeInfo;
    
    // Безопасный способ получить локальное время (работает и в Windows, и в Linux)
#ifdef _WIN32
    localtime_s(&timeInfo, &now);
#else
    localtime_r(&now, &timeInfo);
#endif

    log << "[" << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << "] " << action << "\n";
}

void FileManager::generateReport(const std::string& reportFilename, const Catalog& catalog, const Cart& cart) {
    std::ofstream report(reportFilename);
    if (!report.is_open()) {
        throw std::runtime_error("Не удалось создать файл отчета: " + reportFilename);
    }

    report << "========================================\n";
    report << "         ОТЧЕТ ПО СИСТЕМЕ МАГАЗИНА       \n";
    report << "========================================\n\n";

    report << "--- КАТАЛОГ ТОВАРОВ (" << catalog.size() << " шт.) ---\n";
    for (std::size_t i = 0; i < catalog.size(); ++i) {
        Product* p = catalog.getProduct(i);
        report << p->getItemNo() << " | " << p->getName() << " | " 
               << p->getPrice() << " byn | Остаток: " << p->getQuantity() << "\n";
    }

    report << "\n--- КОРЗИНА (" << cart.size() << " шт.) ---\n";
    if (cart.size() == 0) report << "Корзина пуста.\n";
    for (std::size_t i = 0; i < cart.size(); ++i) {
        Product* p = cart.getProduct(i);
        report << "В корзине: " << p->getName() << " (" << p->getPrice() << " byn)\n";
    }
}