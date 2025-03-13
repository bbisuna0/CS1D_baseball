#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/logos/baseball.ico")); // From qrc
    LoginWindow w;
    w.show();
    return a.exec();
}
