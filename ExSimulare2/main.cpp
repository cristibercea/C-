#include "Gui.h"
#include "test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    test Tester;
    Tester.runTests();

    Repo rep("data.txt");
    Service serv(rep);

    QApplication a(argc, argv);
    Gui w(serv);
    w.show();
    return a.exec();
}
