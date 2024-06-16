#include "gui.h"
#include "test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    Tester t;
    t.runAll();
    QApplication a(argc, argv);
    Repository r("data.txt");
    Service s(r);
    string s1, s2, s3;
    s1 = "Open";
    s2 = "In Progress";
    s3 = "Closed";
    Ferestre f1(s, s1);
    Ferestre f2(s, s2);
    Ferestre f3(s, s3);
    GUI w(s);
    //r.AddObserver(&f1);
    //r.AddObserver(&f2);
    //r.AddObserver(&f3);
    w.show();
    f1.show();
    f2.show();
    f3.show();
    
    return a.exec();
}
