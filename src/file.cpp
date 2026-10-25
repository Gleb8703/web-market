#include "file.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <foodProduct.h>
#include <bookProduct.h>
#include <clothingProduct.h>

void FileManager::saveState(const std::string& filename, const Catalog& catalog, const Cart& cart) {
    std::ofstream out(filename);
    if (!out.is_open()) throw std::runtime_error("Не удалось открыть файл для сохранения!");

    for (std::size_t i = 0; i < catalog.size(); ++i) {
        Product* p = catalog.getProduct(i);
        
        if (auto food = dynamic_cast<FoodProduct*>(p)) {
            out << "FOOD " << food->getItemNo() << " " 
                << std::quoted(food->getName()) << " " // <-- Оборачиваем имя
                << food->getPrice() << " " << food->getQuantity() << " " 
                << food->getExpiryDays() << " " << food->getRefrigerated() << "\n";
        } 
        else if (auto book = dynamic_cast<BookProduct*>(p)) {
            out << "BOOK " << book->getItemNo() << " " 
                << std::quoted(book->getName()) << " " // <-- Имя
                << book->getPrice() << " " << book->getQuantity() << " " 
                << book->getPages() << " " 
                << std::quoted(book->getAuthor()) << "\n"; // <-- Автор
        } 
        else if (auto cloth = dynamic_cast<ClothingProduct*>(p)) {
            out << "CLOTH " << cloth->getItemNo() << " " 
                << std::quoted(cloth->getName()) << " " // <-- Имя
                << cloth->getPrice() << " " << cloth->getQuantity() << " " 
                << std::quoted(cloth->getSize()) << " " // <-- Размер (на случай "XL и больше")
                << std::quoted(cloth->getMaterial()) << "\n"; // <-- Материал
        }
    }

    // Сохранение корзины (там только ID, пробелов нет)
    for (std::size_t i = 0; i < cart.size(); ++i) {
        out << "CART " << cart.getProduct(i)->getItemNo() << "\n";
    }
    
    out.close();
}

bool FileManager::loadState(const std::string& filename, Catalog& catalog, Cart& cart) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    std::string type;

    try {
        while (in >> type) {
            if (type == "FOOD") {
                int id, qty, exp, refr; 
                std::string name; 
                double price;
                
                // Читаем с std::quoted для имени
                if (!(in >> id >> std::quoted(name) >> price >> qty >> exp >> refr)) 
                    throw std::runtime_error("Ошибка чтения FOOD");
                
                catalog += std::make_unique<FoodProduct>(id, name, price, qty, exp, refr);
            }
            else if (type == "BOOK") {
                int id, qty, pages; 
                std::string name, author; 
                double price;
                
                // Читаем с std::quoted для имени и автора
                if (!(in >> id >> std::quoted(name) >> price >> qty >> pages >> std::quoted(author))) 
                    throw std::runtime_error("Ошибка чтения BOOK");
                
                catalog += std::make_unique<BookProduct>(id, name, price, qty, pages, author);
            }
            else if (type == "CLOTH") {
                int id, qty; 
                std::string name, size, material; 
                double price;
                
                // Читаем с std::quoted для имени, размера и материала
                if (!(in >> id >> std::quoted(name) >> price >> qty >> std::quoted(size) >> std::quoted(material))) 
                    throw std::runtime_error("Ошибка чтения CLOTH");
                
                catalog += std::make_unique<ClothingProduct>(id, name, price, qty, size, material);
            }
            else if (type == "CART") {
                int id;
                if (!(in >> id)) throw std::runtime_error("Ошибка чтения CART");
                
                Product* p = catalog.findProduct(id);
                if (p) cart += p;
            }
        }
    } 
    catch (const std::exception& e) {
        std::cerr << "Ошибка при загрузке: " << e.what() << "\n";
        return false;
    }

    return true;
}

void FileManager::logAction(const std::string& action) {
    // Открываем в режиме app (добавление в конец)
    std::ofstream log("log.txt", std::ios::app);
    if (!log.is_open()) return;

    // Получаем текущее время
    std::time_t now = std::time(nullptr);
    log << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "] " << action << "\n";
}

void FileManager::generateReport(const std::string& filename, const Catalog& catalog, const Cart& cart) {
    std::ofstream report(filename);
    if (!report.is_open()) throw std::runtime_error("Не удалось создать отчет!");

    report << "========================================\n";
    report << "         ОТЧЕТ ПО СИСТЕМЕ МАГАЗИНА       \n";
    report << "========================================\n\n";

    report << "--- КАТАЛОГ ТОВАРОВ (" << catalog.size() << " шт.) ---\n";
    for (std::size_t i = 0; i < catalog.size(); ++i) {
        Product* p = catalog.getProduct(i);
        report << p->getItemNo() << " | " << p->getName() << " | " << p->getPrice() << " byn | Остаток: " << p->getQuantity() << "\n";
    }

    report << "\n--- КОРЗИНА (" << cart.size() << " шт.) ---\n";
    if (cart.size() == 0) report << "Корзина пуста.\n";
    for (std::size_t i = 0; i < cart.size(); ++i) {
        Product* p = cart.getProduct(i);
        report << "Товар в корзине: " << p->getName() << " (" << p->getPrice() << " byn)\n";
    }

    report << "\nОтчет сгенерирован автоматически.\n";
}