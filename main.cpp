#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "include/cart.h"
#include "include/product.h"
#include "include/input.h"
#include "include/catalog.h"
#include "include/bookProduct.h"
#include "include/clothingProduct.h"
#include "include/foodProduct.h"
#include "include/customer.h"
#include "include/collection.h"
#include "exceptions/exceptions.h"
#include "file.h"

#ifdef _WIN32
#include <Windows.h>
#endif

void menu() {
    std::cout << "----------------------------\n";
    std::cout << "0.Завершить программу\n";
    std::cout << "1.Добавить товар\n";
    std::cout << "2.Вывести товары\n";
    std::cout << "3.Показать типы товаров\n";
    std::cout << "4.Добавить товар в корзину\n";
    std::cout << "5.Просмотреть корзину\n";
    std::cout << "6.Заказать товар из корзины\n";
    std::cout << "7.Найти товар в каталоге\n";
    std::cout << "8.Отсортировать товары по цене\n";
    std::cout << "9.Удалить товар из каталога\n";
    std::cout << "10.Посмотреть цены со скидкой\n";
    std::cout << "11.Проверить товары на годность\n";
    std::cout << "12.Показать время чтения книг\n";
    std::cout << "13.Товар по индексу (operator[])\n";
    std::cout << "14.Очистить каталог (clear)\n";
    std::cout << "15.Найти товар дороже (findIf)\n";
    std::cout << "16.Общая стоимость каталога (forEach)\n";
    std::cout << "17.Показать покупателей\n";
    std::cout << "---------------Исключения---------------\n";
    std::cout << "18.Уже в корзине\n";
    std::cout << "19.Дубликат в каталоге\n";
    std::cout << "20.Неверные данные\n";
    std::cout << "21.Товаров не достаточно\n";
    std::cout << "22.Товар не найден\n";
    std::cout << "-----------------Файлы------------------\n";
    std::cout << "23.Сохранить данные в файл\n";
    std::cout << "24.Сгенерировать текстовый отчет\n";
}

void printAllProducts(const std::vector<std::unique_ptr<Product>>& products) {
    if (products.empty()) {
        std::cout << "Нет товаров\n";
        return;
    }
    for (size_t i = 0; i < products.size(); ++i) {
        std::cout << "---------------------" << '\n' << i + 1 << ": ";
        std::cout << *products[i] << '\n';
    }
}

void changeProductMenu(const Catalog& catalog) {
    catalog.printCatalog();
    if (catalog.empty()) return;

    int index = readInt("Введите номер товара: ");
    Product* p = catalog.getProduct(index - 1);
    if (p) {
        std::cin >> *p;
    }
}

void addToCartMenu(const Catalog& catalog, Cart& cart) {
    catalog.printCatalog();
    if (catalog.empty()) {
        return;
    }
    int index = readInt("Введите номер товара: ");
    if (index > 0 && index <= static_cast<int>(catalog.size())) {
        cart += catalog.getProduct(index - 1);
    }
}

void printCart(const Cart& cart) {
    if (cart.size() == 0) {
        std::cout << "Корзина пуста\n";
        return;
    } 
    for (std::size_t i = 0; i < cart.size(); ++i) {
        std::cout << "---------------------" << '\n' << i + 1 << ": ";
        std::cout << *cart.getProduct(i) << '\n';
    }
}

void makeOrderMenu(Cart& cart) {
    printCart(cart);
    int index = readInt("Введите номер товара для заказа: ");
    if (index <= 0 || index > static_cast<int>(cart.size())) {
        std::cout << "Неверный индекс\n";
        return;
    }
    int quantity = readInt("Введите кол-во товара для заказа: ");
    Product* cartProduct = cart.getProduct(index - 1);

    if (*cartProduct < quantity) {
        throw NotEnoughStockException(quantity, cartProduct->getQuantity());
    } else {
        cartProduct->setQuantity(cartProduct->getQuantity() - quantity);
        cart -= cartProduct;
        std::cout << "Товар успешно заказан\n";
    }
}

void removeProductMenu(Catalog& catalog, Cart& cart) {
    catalog.printCatalog();
    if (catalog.empty()) {
        return;
    }
    int index = readInt("Введите номер товара для удаления: ");
    Product* target = catalog.getProduct(index - 1); 
    catalog -= target->getItemNo();
    cart -= target;
    std::cout << "Товар удалён из каталога\n";
}
std::unique_ptr<Product> createProductFromInput() {

    int itemNo        = readInt("Артикул: ");
    std::string name  = readString("Имя: ");
    double price      = readDouble("Цена: ");
    int quantity      = readInt("Кол-во: ");

    std::cout << "1. Продукт\n"
              << "2. Книга\n"
              << "3. Одежда\n";
    switch (int type = readInt("Тип товара: "); type) {
    case 1: {
        int expiryDays = readInt("Срок годности (дней): ");
        int refr       = readInt("Нужен холодильник (0/1): ");
        return std::make_unique<FoodProduct>(itemNo, name, price, quantity, expiryDays, refr);
    }
    case 2: {
        int pages          = readInt("Страниц: ");
        std::string author = readString("Автор: ");
        return std::make_unique<BookProduct>(itemNo, name, price, quantity, pages, author);
    }
    case 3: {
        std::string size     = readString("Размер: ");
        std::string material = readString("Материал: ");
        return std::make_unique<ClothingProduct>(itemNo, name, price, quantity, size, material);
    }
    default:
        std::cout << "Неверный пункт меню\n";
        break;
    }
    return nullptr;
}
void demonstrateCustomer(const Catalog& catalog) {

    Customer ivan("Иванов Иван", "ivanov@mail.ru", "+375291112233");

    if (catalog.size() >= 1) ivan.viewProduct(catalog.getProduct(0));
    if (catalog.size() >= 2) ivan.viewProduct(catalog.getProduct(1));
    if (catalog.size() >= 3) ivan.viewProduct(catalog.getProduct(2));

    std::cout << "Покупатель: " << ivan.getName() << "\n";
    std::cout << "Email:      " << ivan.getEmail() << "\n";
    std::cout << "Просмотрено товаров: " << ivan.viewedCount() << "\n";

    std::cout << "==============================\n\n";
}
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    Catalog catalog;
    std::vector<std::unique_ptr<Product>> orders;
    Cart cart;
    if (!FileManager::loadState("state.txt", catalog, cart)) {
        std::cout << "Загрузка не удалась. Создаем базовый каталог.\n";
        catalog += std::make_unique<FoodProduct>(1001, "Молоко", 2.5, 50, 7, true);
        catalog += std::make_unique<FoodProduct>(1002, "Хлеб", 1.8, 30, 2, false);
        catalog += std::make_unique<BookProduct>(2001, "Война и мир", 50.0, 10, 1300, "Л. Толстой");
        catalog += std::make_unique<BookProduct>(2002, "Преступление и наказание", 40.0, 15, 670, "Ф. Достоевский");
        catalog += std::make_unique<ClothingProduct>(3001, "Футболка", 30.0, 100, "L", "хлопок");
        catalog += std::make_unique<ClothingProduct>(3002, "Куртка", 200.0, 20, "M", "кожа");
    }

    int choise = 0;

    do {
        try {
            menu();
            choise = readInt("Ваш выбор: ");

            switch (choise) {
            case 0:
                try {
                    FileManager::saveState("state.txt", catalog, cart);
                    std::cout << "Автосохранение выполнено. Выход...\n";
                } catch (const std::exception& e) {
                    std::cout << "Ошибка автосохранения: " << e.what() << "\n";
                }
                break;
            case 1:
                catalog += createProductFromInput();
                break;
            case 2:
                catalog.printCatalog();
                break;
            case 3:
                catalog.printTypes(); 
                break;
            case 4:
                addToCartMenu(catalog, cart);
                break;
            case 5:
                printCart(cart);
                break;
            case 6:
                makeOrderMenu(cart);
                break;
            case 7:
                std::cout << catalog.findProduct(readInt("Введите артикул"));
                break;
            case 8:
                catalog.sortCatalogByPrice();
                catalog.printCatalog();
                break;
            case 9:
                removeProductMenu(catalog, cart);
                break;
            case 10:
                catalog.printDiscountPrices();
                break;
            case 11:
                catalog.checkExpiryDays();
                break;
            case 12:
                catalog.printReadingTime();
                break;
            case 13: {
                int index = readInt("Индекс товара: ");
                catalog.printByIndex(index);
                break;
            }
            case 14:
                catalog.clearAll();
                break;
            case 15: {
                double minPrice = readDouble("Минимальная цена: ");
                if (const Product* p = catalog.findExpensiveThan(minPrice)) {
                    std::cout << "Найден:\n";
                    p->printInfo();
                } else {
                    std::cout << "Не найдено\n";
                }
                break;
            }
            case 16:
                catalog.printTotalValue();
                break;
            case 17:
                demonstrateCustomer(catalog);
                break;
            case 18:
                cart += catalog.getProduct(1);
                cart += catalog.getProduct(1);
                break;
            case 19:
                catalog += std::make_unique<FoodProduct>(1001, "Молоко", 2.5, 50, 7, true);
                break;
            case 20:
                catalog += std::make_unique<FoodProduct>(1001, "Молоко", -2.5, 50, 7, true);
                break;
            case 21:
                cart += catalog.getProduct(1);
                makeOrderMenu(cart);
                break;
            case 22:
                std::cout << catalog.findProduct(9999);
                break;
            case 23:
                try {
                    FileManager::saveState("state.txt", catalog, cart);
                    std::cout << "Данные успешно сохранены в state.txt!\n";
                } catch (const std::exception& e) {
                    std::cout << "Ошибка сохранения: " << e.what() << "\n";
                }
                break;
            case 24:
                try {
                    FileManager::generateReport("report.txt", catalog, cart);
                    std::cout << "Отчет успешно создан в файле report.txt!\n";
                } catch (const std::exception& e) {
                    std::cout << "Ошибка создания отчета: " << e.what() << "\n";
                }
                break;
            default:
                std::cout << "Неверный пункт меню\n";
                break;
            }
             
        }
        catch (const AlreadyInCartException& e) { std::cout <<"ОШИБКА " << e.what() << std::endl; }
        catch (const DuplicateItemException& e) { std::cout <<"ОШИБКА " << e.what() << std::endl; } 
        catch (const InvalidProductDataException& e) { std::cout <<"ОШИБКА " << e.what() << std::endl; } 
        catch (const NotEnoughStockException& e) { std::cout <<"ОШИБКА " << e.what() << std::endl; } 
        catch (const ProductNotFoundException& e) { std::cout <<"ОШИБКА " << e.what() << std::endl; }  
    } while (choise != 0);

    return 0;
}