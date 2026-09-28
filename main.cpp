#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "include/cart.h"
#include "include/product.h"
#include "include/input.h"

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

void addProductMenu(std::vector<std::unique_ptr<Product>>& products) {
    Product temp;
    do 
    {
        temp = addProduct();
    } while (!checkItemNo(products, temp));
    products.push_back(std::make_unique<Product>(temp));
}

void changeProductMenu(std::vector<std::unique_ptr<Product>>& products) {
    printAllProducts(products);
    if (products.empty()) {
        return;
    }
    int index = readInt("Введите номер товара: ");
    if (index > 0 && index <= static_cast<int>(products.size())) {
        products[index - 1]->changeProduct();
    } else {
        std::cout << "Неверный индекс\n";
    }
}

void addToCartMenu(const std::vector<std::unique_ptr<Product>>& products, Cart& cart) {
    printAllProducts(products);
    if (products.empty()) {
        return;
    }
    int index = readInt("Введите номер товара: ");
    if (index > 0 && index <= static_cast<int>(products.size())) {
        cart.addProductToCart(products[index - 1].get());
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

    if (quantity > cartProduct->getQuantity()) {
        std::cout << "Недостаточно товаров для заказа\n";
    } else {
        orders.push_back(std::make_unique<Product>(
            cartProduct->getItemNo(),
            cartProduct->getName(),
            cartProduct->getPrice(),
            quantity
        ));
        cartProduct->setQuantity(cartProduct->getQuantity() - quantity);
        cart.delProductFromCart(index - 1);
        std::cout << "Товар успешно заказан\n";
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::vector<std::unique_ptr<Product>> products;
    std::vector<std::unique_ptr<Product>> orders;
    Cart cart;

    products.push_back(std::make_unique<Product>(2345, "Копилка", 40.0, 100));
    products.push_back(std::make_unique<Product>(7654, "Подставка", 80.0, 50));
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
            addProductMenu(products);
            break;
        case 2:
            changeProductMenu(products);
            break;
        case 3:
            printAllProducts(products);
            break;
        case 4:
            addToCartMenu(products, cart);
            break;
        case 5:
            printCart(cart);
            break;
        case 6:
            makeOrderMenu(cart, orders);
            break;
        default:
            std::cout << "Неверный пункт меню\n";
            break;
        }
    } while (choise != 0);

    return 0;
}