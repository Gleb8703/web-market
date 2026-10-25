#pragma once
#include <string>
#include <fstream>
#include "catalog.h"
#include "cart.h"

class FileManager {
public:
    static void saveState(const std::string& filename, const Catalog& catalog, const Cart& cart);
    static bool loadState(const std::string& filename, Catalog& catalog, Cart& cart);
    static void logAction(const std::string& logFilename, const std::string& action);
    static void generateReport(const std::string& reportFilename, const Catalog& catalog, const Cart& cart);

private:
    static void saveFoods(std::ofstream& out, const Catalog& catalog);
    static void saveBooks(std::ofstream& out, const Catalog& catalog);
    static void saveClothes(std::ofstream& out, const Catalog& catalog);
    static void saveCart(std::ofstream& out, const Cart& cart);

    static void loadFood(std::ifstream& in, Catalog& catalog);
    static void loadBook(std::ifstream& in, Catalog& catalog);
    static void loadCloth(std::ifstream& in, Catalog& catalog);
    static void loadCartItem(std::ifstream& in, const Catalog& catalog, Cart& cart);
};