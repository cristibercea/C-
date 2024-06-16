#pragma once

#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include "ui_gui.h"
#include "MyModel.h"

class GUI : public QWidget{
    Q_OBJECT

public:
    GUI(Service& service) : serv{service} {
        init();
        connectSlotSocket();
    }
    ~GUI() {}

private:
    Ui::GUIClass ui;
    Service& serv;
    QTableView* tab;
    MyModel* model;
    QPushButton* save; 
    QPushButton* filter;
    QLineEdit* id;
    QLineEdit* descr;
    QLineEdit* status;
    QLineEdit* names;

    /// <summary>
    /// initializeaza componentele vizuale 
    /// </summary>
    void init();

    /// <summary>
    /// conecteaza elem vizuale cu evenimente coresp
    /// </summary>
    void connectSlotSocket();

    /// <summary>
    /// adauga un nou task in app
    /// </summary>
    void adauga();

    /// <summary>
    /// filtreaza task-uri
    /// </summary>
    void filtru();
};


class Ferestre : public QWidget//,public Observer
{
    Service& s;
    QTableView* tab;
    MyModel* model;
    QPushButton* open;
    QPushButton* close;
    QPushButton* inprog;

    /// <summary>
    /// initializeaza componentele vizuale 
    /// </summary>
    void init(const string& title);

    /// <summary>
    /// conecteaza elem vizuale cu evenimente coresp
    /// </summary>
    void connectSlotSocket();

    /// <summary>
    /// edits a task's ststus
    /// </summary>
    void editStat(const string& status);
public:
    Ferestre(Service& service, string& title) :s{service}{
        this->setWindowTitle(QString::fromStdString(title));
        if (title == "Open") title = "open";
        else if (title == "Closed") title = "closed";
        else if (title == "In Progress") title = "inprogress";
        init(title);
        connectSlotSocket();
    }
    //void update(vector<Task> ve) { setTasksFiltered(s.filtruStatus(title)); }
};