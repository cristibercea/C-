#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QLineEdit>
#include <QPushButton>
#include "ui_ExSimulare1.h"
#include "service.h"

class ExSimulare1 : public QMainWindow
{
    Q_OBJECT

public:
    ExSimulare1(service& serv, QWidget *parent = nullptr);
    ~ExSimulare1();

private:
    service& srv;
    QListWidget* list;
    QLineEdit* cnp;
    QLineEdit* date;
    QPushButton* filtru1;
    QPushButton* filtru2;
    QPushButton* reset;
    void init();
    void linkWidgets();
    void updateList(vector<doctor> v);
    void filtruSectie(string sectie);
    void filtruNume(string nume);
    Ui::ExSimulare1Class ui;
};
