#pragma once

#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include "ui_gui.h"
#include "MyModel.h"

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(Service& s);
    ~GUI();
private:
    void paintEvent(QPaintEvent* event) override;
    /// <summary>
    /// initializeaza componente vizuale
    /// </summary>
    void init();

    /// <summary>
    /// conecteaza elementale interactive
    /// </summary>
    void connectSlotSocket();

    Service& serv;
    QTableView* tab;
    QPushButton* save;
    QPushButton* destroy;
    QLineEdit* titlu;
    QLineEdit* artist;
    QLineEdit* gen;
    MyModel* model;
    Ui::GUIClass ui;

    /// <summary>
    /// adauga o melodie noua
    /// </summary>
    void adauga();

    /// <summary>
    /// starge o melodie
    /// </summary>
    void starge();
};
