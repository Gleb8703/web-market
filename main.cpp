#include <iostream>
#include <vector>
#include <string>
#include "cart.h"
#include "product.h"
#include <memory>
#include "input.h"



void menu() {
    using namespace std;
    cout << "----------------------------\n";
    cout << "0.Завершить программу\n";
    cout << "1.Добавить товар\n";
    cout << "2.Изменить товар\n";
    cout << "3.Вывести товары на экран\n";
    cout << "4.Добавить товар в корзину\n";
    cout << "5.Просмотреть корзину\n";
    cout << "6.Заказать товар из корзины\n";
}

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);   
#endif 

    int choise(0);
    int index;
    std::vector <std::unique_ptr<Product>> products;
    std::vector <std::unique_ptr<Product>> orders;
    Cart cart;
    do
    {
        menu();
        choise = readInt("Ваш выбор: ");
        switch (choise) {
        case 1:
            products.push_back(std::make_unique<Product>(addProduct()));
            break;
        case 2:
            for (size_t i = 0; i < products.size(); i++)
                products[i]->printProductInfo(i);
            index = readInt("Введите номер товара: ");
            products[index - 1]->changeProduct();
            break;
        case 3:
            if (products.empty())
            std::cout << "Нет товаров" << std::endl;
            else
            for (size_t i = 0; i < products.size(); i++)
                products[i]->printProductInfo(i);
            break;
        case 4:
            if (products.empty()) { std::cout << "Нет товаров\n"; break; }
            else
            for (size_t i = 0; i < products.size(); i++)
                products[i]->printProductInfo(i);
            index = readInt("Введите номер товара: ");
            if (index - 1 < products.size())
                cart.addProductToCart(products[index - 1].get());
            else
                std::cout << "Неверный индекс\n";
            break;
        case 5:
            for (std::size_t i = 0; i < cart.size(); i++)
                cart.getProduct(i)->printProductInfo(i);  
            break;
        case 6:
            int quality;
            index = readInt("Введите номер товара для заказа: ");
            quality = readInt("Введите кол-во товара для заказа: ");
            if (quality > cart.getProduct(index - 1)->getQuality()) {
                std::cout << "Недостаточно товаров для заказа" << std::endl;
            }
            else {
                Product order {cart.getProduct(index - 1)->getItemNo(), cart.getProduct(index - 1)->getName(), cart.getProduct(index - 1)->getPrise(), quality};
                orders.push_back(std::make_unique<Product>(order));
                cart.getProduct(index - 1)->setQuality(cart.getProduct(index - 1)->getQuality() - quality);
                std::cout << "Товар успешно заказан" << std::endl;
            }
            break;
        case 0:
        return 0;
        }
    } while (choise);
    
}