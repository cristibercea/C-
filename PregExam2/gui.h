#pragma once

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include "service.h"
#include "ui_gui.h"
#include "MyModel.h"

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(Service& service) : serv{ service } { init(); connectSlotSocket(); }
    ~GUI() {}
private:
    /// <summary>
    /// initializeaza componente vizuale
    /// </summary>
    void init();

    /// <summary>
    /// conecteaza elementele vizuale la evenimente
    /// </summary>
    void connectSlotSocket();

    Service& serv;
    Ui::GUIClass ui;
    MyModel* m;
    QTableView* tab;
    QSlider* slider; 
    QLineEdit* Id;
    QLineEdit* Nume;
    QLineEdit* Tip;
    QLineEdit* Pret;
    QPushButton* save;
    QWidget* types;
    QLabel* labels;

    /// <summary>
    /// adauga un produs nou
    /// </summary>
    void adauga();

    /// <summary>
    /// filtreaza tabelul dupa pret
    /// </summary>
    void filter(const double& val) const;

    /// <summary>
    /// afiseaza ferestre pe tipuri
    /// </summary>
    void winTipuri();
};