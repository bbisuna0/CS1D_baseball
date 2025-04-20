#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "stadium.h"

class Admin {
public:
    Admin() = default;

    void addStadium(Stadium* stadium);
    void editSouvenir(Stadium* stadium, const std::string& name, double newPrice);
    void editStadiumInfo(Stadium* stadium, const std::string& name);
};

#endif // ADMIN_H
