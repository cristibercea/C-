#include "Simulare_mai_2024.h"
#include <QtWidgets/QApplication>
#include "test.h"

int main(int argc, char *argv[])
{
    Tester t;
    t.runAll();
    Repo rep("data.in");
    Service serv(rep);
    QApplication a(argc, argv);
    Simulare_mai_2024 w(serv);
    w.show();
    return a.exec();
}
