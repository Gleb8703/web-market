#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "include/cart.h"
#include "include/product.h"
#include "include/input.h"
#include "include/catalog.h"

#ifdef _WIN32
#include <Windows.h>
#endif

void menu() {
    std::cout << "----------------------------\n";
    std::cout << "0.Завершить программу\n";
    std::cout << "1.Добавить товар\n";
    std::cout << "2.Изменить товар\n";
    std::cout << "3.Вывести товары на экран\n";
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

void addProductMenu(Catalog& catalog) {
    Product temp;
    std::cin >> temp;
    catalog += temp;
}

void changeProductMenu(std::vector<std::unique_ptr<Product>>& products) {
    printAllProducts(products);
    if (products.empty()) {
        return;
    }
    int index = readInt("Введите номер товара: ");
    if (index > 0 && index <= static_cast<int>(products.size())) {
            std::cin >> *products[index - 1];
    } else {
        std::cout << "Неверный индекс\n";
    }
}

void addToCartMenu(Catalog catalog, Cart& cart) {
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

void makeOrderMenu(Cart& cart, std::vector<std::unique_ptr<Product>>& orders) {
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
        orders.push_back(std::make_unique<Product>(
            cartProduct->getItemNo(),
            cartProduct->getName(),
            cartProduct->getPrice(),
            quantity
        ));
        cartProduct->setQuantity(cartProduct->getQuantity() - quantity);
        cart -= cartProduct;
        std::cout << "Товар успешно заказан\n";
    }
}
void removeProductMenu(Catalog catalog, Cart& cart) {
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

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    Catalog catalog;
    std::vector<std::unique_ptr<Product>> products;
    std::vector<std::unique_ptr<Product>> orders;
    Cart cart;

    products.push_back(std::make_unique<Product>(2345, "Копилка", 40.0, 100));
    products.push_back(std::make_unique<Product>(7654, "Подставка", 32.0, 50));
    products.push_back(std::make_unique<Product>(9876, "Куртка", 200.0, 20));

    int choise = 0;

    do {
        menu();
        choise = readInt("Ваш выбор: ");

        switch (choise) {
        case 0:
            std::cout << "Выход...\n";
            break;
        case 1:
            addProductMenu(catalog);
            break;
        case 2:
            changeProductMenu(products);
            break;
        case 3:
            catalog.printCatalog();
            break;
        case 4:
            addToCartMenu(catalog, cart);
            break;
        case 5:
            printCart(cart);
            break;
        case 6:
            makeOrderMenu(cart, orders);
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