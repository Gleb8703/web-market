#include <iostream>
#include <vector>
#include <string>
#include "product.h"



void menu() {
    using namespace std;
    cout << "1.Добавить товар\n";
    cout << "2.Изменить товар\n";
    cout << "3.Вывести товары на экран\n";
    cout << "4.Добавить товар в корзину\n";
    cout << "5.Просмотреть корзину\n";
    cout << "6.Завершить программу\n";
}
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);   
#endif  

    menu();
    int choise(0);
    do
    {
    std::cin >> choise;
    std::vector <std::unique_ptr<Product>> products;
    switch (choise) {
    case 1:
        products.push_back(std::make_unique<Product>(addProduct()));
        break;
    case 2:
        int num;
        std::cin >> num;
        changeProduct(products[num]);
        break;
    case 3:
    if (products.empty())
    std::cout << "Нет товаров" << std::endl;
    else
    for (int i = 0; i < products.size(); i++)
            products[i].printProductInfo();
    break;
    case 4:
    
    case 5:
    return 0;
    }
    } while (choise != 5);
    
}