#include "ExSimulare1.h"
#include <QtWidgets/QApplication>
#include "tests.h"

int main(int argc, char *argv[])
{
    tests t;
    t.startTests();
    string file = "data.txt";
    repo rep(file);
    service serv(rep);
    QApplication a(argc, argv);
    ExSimulare1 w(serv, nullptr);
    w.show();
    return a.exec();
}
