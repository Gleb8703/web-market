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

void changeProductMenu(Catalog& catalog) {
    catalog.printCatalog();
    if (catalog.size() == 0) return;

    int index = readInt("Введите номер товара: ");
    Product* p = catalog.getProduct(index - 1);
    if (p) {
        std::cin >> *p;
    }
}

void addToCartMenu(Catalog& catalog, Cart& cart) {
    catalog.printCatalog();
    if (catalog.size() == 0) {
        return;
    }
    int index = readInt("Введите номер товара: ");
    if (index > 0 && index <= static_cast<int>(catalog.size())) {
        cart += catalog.getProduct(index - 1);
        std::cout << "Выбранный товар успешно добавлен" << std::endl; 
    } else {
        std::cout << "Неверный индекс\n";
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
        std::cout << "Недостаточно товаров для заказа\n";
    } else {
        cartProduct->setQuantity(cartProduct->getQuantity() - quantity);
        cart -= cartProduct;
        std::cout << "Товар успешно заказан\n";
    }
}
void removeProductMenu(Catalog& catalog, Cart& cart) {
    catalog.printCatalog();
    if (catalog.size() == 0) {
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
    int type = readInt("Тип товара: ");

    switch (type) {
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
    }
    return nullptr;
}
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    Catalog catalog;
    std::vector<std::unique_ptr<Product>> orders;
    Cart cart;

    catalog += std::make_unique<FoodProduct>(1001, "Молоко", 2.5, 50, 7, true);
    catalog += std::make_unique<FoodProduct>(1002, "Хлеб", 1.8, 30, 2, false);
    catalog += std::make_unique<BookProduct>(2001, "Война и мир", 50.0, 10, 1300, "Л. Толстой");
    catalog += std::make_unique<BookProduct>(2002, "Преступление и наказание", 40.0, 15, 670, "Ф. Достоевский");
    catalog += std::make_unique<ClothingProduct>(3001, "Футболка", 30.0, 100, "L", "хлопок");
    catalog += std::make_unique<ClothingProduct>(3002, "Куртка", 200.0, 20, "M", "кожа");

    int choise = 0;

    do {
        menu();
        choise = readInt("Ваш выбор: ");

        switch (choise) {
        case 0:
            std::cout << "Выход...\n";
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
        default:
            std::cout << "Неверный пункт меню\n";
            break;
        }
    } while (choise != 0);

    return 0;
}