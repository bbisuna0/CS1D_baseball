#include "loginwindow.h"
#include "stadium.h"
#include "user.h"
#include "admin.h"
#include "tripplanner.h"
#include "plantour.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/logos/baseball.ico")); // From qrc

    User user("Robin Hood"); //user

    Admin admin; //admin

    plantour obj;

    // Create Stadium objects with team names (stack objects)
    Stadium obj1("Arizona Diamondbacks");
    Stadium obj2("Atlanta Braves");
    Stadium obj3("Baltimore Orioles");
    Stadium obj4("Boston Red Sox");
    Stadium obj5("Chicago Cubs");
    Stadium obj6("Chicago White Sox");
    Stadium obj7("Cincinnati Reds");
    Stadium obj8("Cleveland Indians");
    Stadium obj9("Colorado Rockies");
    Stadium obj10("Detroit Tigers");
    Stadium obj11("Houston Astros");
    Stadium obj12("Kansas City Royals");
    Stadium obj13("Los Angeles Angels");
    Stadium obj14("Los Angeles Dodgers");
    Stadium obj15("Miami Marlins");
    Stadium obj16("Milwaukee Brewers");
    Stadium obj17("Minnesota Twins");
    Stadium obj18("New York Mets");
    Stadium obj19("New York Yankees");
    Stadium obj20("Oakland Athletics");
    Stadium obj21("Philadelphia Phillies");
    Stadium obj22("Pittsburgh Pirates");
    Stadium obj23("San Diego Padres");
    Stadium obj24("San Francisco Giants");
    Stadium obj25("Seattle Mariners");
    Stadium obj26("St. Louis Cardinals");
    Stadium obj27("Tampa Bay Rays");
    Stadium obj28("Texas Rangers");
    Stadium obj29("Toronto Blue Jays");
    Stadium obj30("Washington Nationals");

    LoginWindow w;
    w.show();
    return a.exec();
}
