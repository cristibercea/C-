#include "gui.h"
#include "test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Tester t;
    t.runAll();
    QApplication a(argc, argv);
    Repository repo("data.txt");
    Service serv(repo);
    GUI w(serv);
    w.show();
    return a.exec();
}
