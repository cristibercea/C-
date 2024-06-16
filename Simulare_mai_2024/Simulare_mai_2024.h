#pragma once

#include <QtWidgets/QMainWindow>
#include <QListWidget>
#include <QProgressBar>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "ui_Simulare_mai_2024.h"
#include "service.h"

class Simulare_mai_2024 : public QMainWindow
{
    Q_OBJECT

public:
    Simulare_mai_2024(Service& s, QWidget *parent = nullptr);
    ~Simulare_mai_2024();
private:
    /// <summary>
    /// initialize widgets
    /// </summary>
    void init();

    /// <summary>
    /// connects widgets with certain events
    /// </summary>
    void eventConnector();

    /// <summary>
    /// loads Stocks from vector to list widget
    /// </summary>
    /// <param name="v"> vector to populate list widget </param>
    void loadWidgetList(vector<Stock> v);

    Service& serv;
    QWidget* central;
    QListWidget* list;
    QProgressBar* progress;
    QLabel* semn;
    QLineEdit* id;
    QLineEdit* nume;
    QLineEdit* pret;
    QPushButton* sterge;

    /// <summary>
    /// functia care se ocupa de functionalitatea de stergere
    /// </summary>
    void dialogStergere();

    Ui::Simulare_mai_2024Class ui;
};
