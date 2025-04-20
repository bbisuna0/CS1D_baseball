#include "Stadium.h"
std::vector<Stadium*> Stadium::object_list;

//constructors
Stadium::Stadium(std::string team_name) {
    souvenirs = {
        {"Baseball cap", 19.99},
        {"Baseball bat", 89.39},
        {"Team pennant", 17.99},
        {"Autographed baseball", 29.99},
        {"Team jersey", 199.99}
    };

    teamName = team_name;
    object_list.push_back(this);

}

#include "stadium.h"

Stadium::Stadium(const std::string& name,
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
                 const std::map<std::string, double>& souvenirs)
    : name(name),
    capacity(capacity),
    location(location),
    playingSurface(playingSurface),
    teamName(teamName),
    league(league),
    dateOpened(dateOpened),
    distanceToCenterField(distanceToCenterField),
    typology(typology),
    roofType(roofType),
    total_spent(total_spent),
    souvenirs(souvenirs)
{}


// Getters
std::string Stadium::getTeamName() const
{
    return teamName;
}

std::string Stadium::getName() const {
    return name;
}

int Stadium::getCapacity() const {
    return capacity;
}

std::string Stadium::getLocation() const {
    return location;
}

std::string Stadium::getLeague() const {
    return league;
}

std::string Stadium::getRoofType() const {
    return roofType;
}

std::string Stadium::getTypology() const {
    return typology;
}

std::string Stadium::getDateOpened() const {
    return dateOpened;
}

double Stadium::getDistanceToCenterField() const {
    return distanceToCenterField;
}

const double Stadium::money_spent() const
{
    return total_spent;
}

// Setters
void Stadium::setCapacity(int newCap) {
    capacity = newCap;
}

void Stadium::setRoofType(const std::string& newRoof) {
    roofType = newRoof;
}

//admin access only
const std::map<std::string, double>& Stadium::getSouvenirs() const {
    return souvenirs;
}

void Stadium::addSouvenir(const std::string& name, double price) {
    souvenirs[name] = price;
}

void Stadium::removeSouvenir(const std::string& name) {
    souvenirs.erase(name);
}


