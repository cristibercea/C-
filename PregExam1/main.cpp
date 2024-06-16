#include "gui.h"
#include <QtWidgets/QApplication>
#include "tests.h"

int main(int argc, char *argv[])
{
    Tester t;
    t.runAll();
    Repo r("data.txt");
    Service s(r); 

    QApplication a(argc, argv); 
    GUI w(s);
    w.show();
    return a.exec();
}
