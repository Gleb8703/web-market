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
    std::cout << "15.Найти товар дороже N (findIf)\n";
    std::cout << "16.Общая стоимость каталога (forEach)\n";
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
// ==================== Демонстрация шаблона Collection ====================
void demonstrateCollection() {
    std::cout << "\n========== Демонстрация шаблона Collection<T> ==========\n";
    std::cout << "Один шаблон — два разных пользовательских типа:\n\n";

    // ===== Тип 1: Product* =====
    std::cout << "--- Collection<Product*> ---\n";

    FoodProduct milk(1001, "Молоко", 2.5, 50, 7, true);
    BookProduct book(2001, "Война и мир", 50.0, 10, 1300, "Л. Толстой");
    ClothingProduct shirt(3001, "Футболка", 30.0, 100, "L", "хлопок");

    Collection<Product*> productPtrs;
    productPtrs.add(&milk);
    productPtrs.add(&book);
    productPtrs.add(&shirt);

    std::cout << "Товаров в коллекции: " << productPtrs.size() << "\n";
    productPtrs.printWith([](Product* p) {
        std::cout << "  " << p->getName() << " (" << p->getType()
                  << ") — " << p->getPrice() << " byn\n";
    });

    // Поиск через findIf
    Product** expensive = productPtrs.findIf([](Product* p) {
        return p->getPrice() > 40;
    });
    if (expensive)
        std::cout << "Первый дорогой товар: " << (*expensive)->getName() << "\n";

    // Удаление и размер
    productPtrs.remove(0);
    std::cout << "После удаления первого — размер: " << productPtrs.size() << "\n";

    // ===== Тип 2: Customer (покупатель) =====
    std::cout << "\n--- Collection<Customer> ---\n";

    Collection<Customer> customers;
    customers.add(Customer("Иванов Иван",   "ivanov@mail.ru",  "+375291112233"));
    customers.add(Customer("Петров Пётр",   "petrov@mail.ru",  "+375292223344"));
    customers.add(Customer("Сидоров Сидор", "sidorov@mail.ru", "+375293334455"));

    std::cout << "Всего покупателей: " << customers.size() << "\n";
    customers.printWith([](const Customer& c) {
        std::cout << "  " << c.getName() << " — " << c.getEmail() << "\n";
    });

    // Поиск по email
    Customer* found = customers.findIf([](const Customer& c) {
        return c.getEmail() == "petrov@mail.ru";
    });
    if (found)
        std::cout << "Найден по email: " << found->getName()
                  << " (" << found->getPhone() << ")\n";

    // ===== Шаблонная функция forEach =====
    std::cout << "\n--- Шаблонная функция forEach ---\n";
    forEach(customers, [](const Customer& c) {
        std::cout << "  " << c.getName() << ": " << c.getPhone() << "\n";
    });

    // ===== Очистка =====
    customers.clear();
    productPtrs.clear();
    std::cout << "\nПосле clear() — покупателей: " << customers.size()
              << ", товаров: " << productPtrs.size() << "\n";

    std::cout << "=======================================================\n\n";
}
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    Catalog catalog;
    std::vector<std::unique_ptr<Product>> orders;
    Cart cart;
    demonstrateCollection();
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
            Product* p = catalog.findExpensiveThan(minPrice);
            if (p) {
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
        default:
            std::cout << "Неверный пункт меню\n";
            break;
        }
    } while (choise != 0);

    return 0;
}