#pragma once
#include "ui_lab10_11.h"
#include "service.h"
#include <vector>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QToolbar>
#include <QListView>
#include "MyListModel.h"


class NotificationListUI : public QWidget, public Observer {
public:
    NotificationListUI(Service& s) : serv{ s } {
        init();
        addEventListeners();
        //updateWidgetList();
    }
    ~NotificationListUI() {
        serv.removeObserver(this);  
    }
private:
    Service& serv;
    QPushButton* exit;
    QPushButton* add;
    QPushButton* clear;
    QPushButton* random;
    QPushButton* exprt;
    QPushButton* cancel;
    QPushButton* enter;
    QLabel* textL;
    QLabel* spaceL;
    QListView* notif;
    MyListModel* notifModel;
    QLineEdit* reader;
    QLabel* context;
    QString text;

    /// <summary>
    /// initialize window and elements
    /// </summary>
    void init();

    /// <summary>
    /// add events to widgets
    /// </summary>
    void addEventListeners();

    /// <summary>
    /// this menu's functionalities
    /// </summary>
    void addTenant();
    void addSomeTenants();
    void exportNotificationList();
    void doAddTenant();
    void doAddSomeTenants();
    void doExport();
    void clearNotificationList();

    /// <summary>
    /// cancel an action (linked to "Cancel" button)
    /// </summary>
    void cancelUtil();

    /// <summary>
    /// do an action (linked to "Enter" button)
    /// </summary>
    void actionUtil();

    /// <summary>
    /// updates widget list with a vector's elements
    /// </summary>
    /// <param name="vect"> vector containing tenants </param>
    //void updateWidgetList();

    void update() override;
};



class NotificationListDrawingUI : public QWidget, public Observer {
public:
    NotificationListDrawingUI(Service& s) : serv{ s } {
        Seed = time(NULL);
        this->setWindowTitle("Apartaments Notificated");
        this->setMinimumHeight(80); 
        this->setMinimumWidth(60); 
    }
    ~NotificationListDrawingUI() {
        serv.removeObserver(this);
    }
private:
    int Seed;
    Service& serv;

    /// <summary>
    /// initialize window and draw elements
    /// </summary>
    void paintEvent(QPaintEvent* ev) override;

    void update() override;
};



class MyGUI : public QMainWindow
{
    /// <summary>
    /// main app window
    /// </summary>
    Q_OBJECT

public:
    MyGUI(Service& s, QWidget* parent = nullptr);
    ~MyGUI() {}
private:
    Service& service;
    
    /// <summary>
    /// initialize components
    /// </summary>
    void initUI();
    
    /// <summary>
    /// adds events to qt widgets
    /// </summary>
    void addEventListeners();

    /// <summary>
    /// notfication list menu manager
    /// </summary>
    void notificationListWindow();

    /// <summary>
    /// notfication list drawing window
    /// </summary>
    void notificationListRdOnlWindow();

    /// <summary>
    /// report menu manager
    /// </summary>
    void typeReportWindow();

    /// <summary>
    /// initialize widget list with the elements in repo
    /// </summary>
    /// <param name="l"> widget list to be initialized </param>
    void initWidgetList(QListWidget* l);

    /// <summary>
    /// help window generation and initialization
    /// </summary>
    void helpWindow();

    QMenu* helpMenu;
    QAction* help;
    //QListWidget* l;
    QPushButton* undoB;
    QPushButton* add;
    QPushButton* modif;
    QPushButton* del;
    QPushButton* find;
    QPushButton* filter1;
    QPushButton* filter2;
    QPushButton* sort1;
    QPushButton* sort2;
    QPushButton* sort3;
    QPushButton* sort4;
    QPushButton* sort5;
    QPushButton* sort6;
    QPushButton* report;
    QPushButton* notif;
    QPushButton* AddToNotif;
    QPushButton* AddRandToNotif;
    QPushButton* ClearNotif;
    QPushButton* notifRdOnly;
    QLineEdit* name;
    QLineEdit* apartament;
    QLineEdit* type;
    QLineEdit* area;
    QLineEdit* NotifEditLine;
    Ui::Lab10_11Class ui;
    QListWidgetItem* last;

    QListView* mainList;
    MyListModel* mainListModel;

    NotificationListUI* NotifUi;
    NotificationListDrawingUI* DrawUi;

    QVBoxLayout* butoaneaux;
    QHBoxLayout* butoaneaux2;
    vector<QPushButton*> butoane;

    /// <summary>
    /// app main functionalities
    /// </summary>
    void undo();
    void addTenant();
    void editTenant();
    void deleteTenant();
    void findApartament() const;
    void filterByType();
    void filterByArea();
    void sort(const int& sortType);
    void addToNotifFunc();
    void addRandToNotifFunc();

    /// <summary>
    /// clears all LineEdits
    /// </summary>
    void clearInputLines() const noexcept;
    
    /// <summary>
    /// updates widget list with current state of the repo
    /// </summary>
    /// <param name="vect"></param>
    //void updateWidgetList(const vector<Tenant>& vect);

    /// <summary>
    /// puts tenant data from a QWidgetListItem to corresponding LineEdit
    /// </summary>
    /// <param name="elem"> the tenant to be dumped in LineEdits </param>
    void dumpDataFromListItem(QListWidgetItem* elem) const;

    /// <summary>
    /// generates buttons on main window with apartament types in the list
    /// </summary>
    void generateButtons();
};
