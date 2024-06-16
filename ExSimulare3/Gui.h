#pragma once

#include <QtWidgets/QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "ui_Gui.h"
#include "service.h"

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(Service serv,QWidget *parent = nullptr);
    ~Gui() {}

private:
    Service service;
    QListWidget* proc;
    QListWidget* plc;
    QLineEdit* nume;
    QLineEdit* soclu;
    QLineEdit* pret;
    QPushButton* add;
    QLineEdit* pretTotal;
    void init();
    void connectElements();
    void genereazalistaPlaci(const vector<PlacaDeBaza> v);
    void genereazalistaProc(const vector<Procesor> v); 
    Ui::GuiClass ui;
};
