#include "user.h"
#include "stadium.h"  // Only if you need full Stadium definition

User::User(const std::string& name)
    : username(name), souvenirCart(0.0) {}

double User::viewTotalSpent() const {
    return souvenirCart;
}

std::string User::getUsername() const {
    return username;
}

std::vector<Stadium*>* User::get_stadium_list() {
    return &stadiums_visited;
}

// Optional helper to add a visited stadium
void User::addStadium(Stadium* stadium) {
    stadiums_visited.push_back(stadium);
}

// Optional helper to add to total spent
void User::addToCart(double amount) {
    souvenirCart += amount;
}
