#include "GUI.h"
#include "tests.h"
#include "repository.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel>

int main(int argc, char *argv[])
{
    Tests test_app; 
    test_app.run_all(); 
    QApplication a(argc, argv);
    FileRepository repo("data.txt");
    NotificationRepo notifList;
    Validator valid;
    Service serv(notifList, repo, valid);
    MyGUI w(serv);
    w.show();
    return a.exec();
    //return 0;
}
