#include <iostream>
#include <vector>
#include <string>
#include "product.h"




void menu(){
    using namespace std;
    cout << "1.Добавить товар\n";
    cout << "2.Изменить товар\n";
    cout << "3.Вывести товары на экран\n";
    cout << "4.Сделать заказ\n";
}
int main() {
    

    menu;
    int choise(0);
    std::vector <Product> products;
    switch (choise) {
    case 1:
        products.push_back(addProduct());
        break;
    case 2:
        int num;
        std::cin >> num;
        changeProduct(products[num]);
        break;
    case 3:
    if (products.size())
        for (int i = 0; i < products.size(); i++)
            products[i].printProductInfo();
    else
    std::cout << "Нет товаров" << std::endl;
    break;
    }
    
}