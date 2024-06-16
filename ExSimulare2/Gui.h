#pragma once

#include <QtWidgets/QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include "ui_Gui.h"
#include "service.h"

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(Service& s, QWidget *parent = nullptr);
    ~Gui() {}

private:
    QWidget* window;
    Service& serv;
    QTableWidget* table;
    QLineEdit* line;
    QPushButton* sort;
    
    /// <summary>
    /// initializes widgets
    /// </summary>
    void init();

    /// <summary>
    /// connects widgets
    /// </summary>
    void connecter();

    /// <summary>
    /// populates table widget with data from a vector
    /// </summary>
    /// <param name="vect">data vector</param>
    void populateTable(const vector<Tricou>& vect);
    Ui::GuiClass ui;
};
