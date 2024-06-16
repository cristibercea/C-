#include "Gui.h"
#include <QtWidgets/QApplication>
#include "test.h"
#include "service.h"

int main(int argc, char *argv[])
{
    tester t;
    t.runAllTests();
    repoPB repoPlaci("placi.txt");
    repoPR repoProc("proc.txt");
    Service serv(repoPlaci, repoProc);
    QApplication a(argc, argv);
    Gui w(serv);
    w.show();
    return a.exec();
}
