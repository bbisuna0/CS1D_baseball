#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class Stadium;  // Forward declaration

class User {
private:
    std::string username;
    double souvenirCart;
    std::vector<Stadium*> stadiums_visited;

public:
    // Constructor
    User(const std::string& name);

    // Accessors
    double viewTotalSpent() const;
    std::string getUsername() const;
    std::vector<Stadium*>* get_stadium_list();

    // Mutators (optional)
    void addStadium(Stadium* stadium);
    void addToCart(double amount);
};

#endif // USER_H
