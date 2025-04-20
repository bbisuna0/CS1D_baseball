#ifndef STADIUM_H
#define STADIUM_H

#include <string>
#include <vector>
#include <map>

class Stadium {
private:
    std::string name;
    int capacity;
    std::string location;
    std::string playingSurface;
    std::string teamName;
    std::string league;
    std::string dateOpened;
    double distanceToCenterField;
    std::string typology;
    std::string roofType;
    double total_spent;
    std::map<std::string, double> souvenirs;
    void addSouvenir(const std::string& name, double price);
    void removeSouvenir(const std::string& name);
    Stadium(const std::string& name,
            int capacity,
            const std::string& location,
            const std::string& playingSurface,
            const std::string& teamName,
            const std::string& league,
            const std::string& dateOpened,
            double distanceToCenterField,
            const std::string& typology,
            const std::string& roofType,
            double total_spent,
            const std::map<std::string, double>& souvenirs);



public:
    Stadium(std::string team_name);
    // Getters
    std::string getName() const;
    int getCapacity() const;
    std::string getLocation() const;
    std::string getLeague() const;
    std::string getRoofType() const;
    std::string getTypology() const;
    std::string getDateOpened() const;
    double getDistanceToCenterField() const;
    std::string getTeamName() const;
    const std::map<std::string, double>& getSouvenirs() const;
    const double money_spent() const;

    // Setters
    void setCapacity(int newCap);
    void setRoofType(const std::string& newRoof);

    //static list to store all objects
    static std::vector<Stadium*>object_list;
};

#endif // STADIUM_H
