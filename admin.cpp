#include "admin.h"
#include <iostream>

void Admin::addStadium(Stadium* stadium) {
    if (stadium) {
        Stadium::object_list.push_back(stadium);
        std::cout << "Stadium added: " << stadium->getName() << std::endl;
    }
}

void Admin::editSouvenir(Stadium* stadium, const std::string& name, double newPrice) {
    if (!stadium) return;

    auto& souvenirs = const_cast<std::map<std::string, double>&>(stadium->getSouvenirs());
    auto it = souvenirs.find(name);
    if (it != souvenirs.end()) {
        it->second = newPrice;
        std::cout << "Updated souvenir price: " << name << " to $" << newPrice << std::endl;
    } else {
        std::cout << "Souvenir not found: " << name << std::endl;
    }
}

void Admin::editStadiumInfo(Stadium* stadium, const std::string& name) {
    if (stadium) {
        // Replace only the name for now; could be extended
        stadium->setRoofType(name); // Example: treat name as roof type update for now
        std::cout << "Updated stadium info (example): new roof type = " << name << std::endl;
    }
}
