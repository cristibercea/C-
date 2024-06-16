#include "Gui.h"
#include <QVBoxLayout>
Gui::Gui(Service& s,QWidget *parent) : QMainWindow(parent), serv{s}{
    ui.setupUi(this);
    init();
    connecter();
}

void Gui::init()
{
    QVBoxLayout* vLay = new QVBoxLayout();
    window = new QWidget();
    table = new QTableWidget();
    line = new QLineEdit();
    sort = new QPushButton("Sortare Marime/Pret");

    populateTable(serv.getAll());
    vLay->addWidget(table);
    vLay->addSpacing(15);
    vLay->addWidget(line);
    vLay->addSpacing(15);
    vLay->addWidget(sort);

    window->setLayout(vLay);
    this->setCentralWidget(window);
}

void Gui::connecter()
{
    connect(sort, &QPushButton::clicked, this, [this]() { populateTable(serv.sortAll()); });
    connect(table, &QTableWidget::itemSelectionChanged, this, [this]() {
        for (auto el : table->selectedItems())
            line->setText(el->data(Qt::UserRole).toString());
    });
}

void Gui::populateTable(const vector<Tricou>& vect)
{
    table->setRowCount(0);
    table->setColumnCount(0); 
    table->insertColumn(table->columnCount()); 
    table->insertColumn(table->columnCount()); 

    for (int i = 0; i < vect.size(); i++) {
        table->insertRow(table->rowCount());
    }

    int i = 0;
    for (const Tricou& t : vect) {
        int nr=0;
        if (t.get_marime() == "S") nr = 6;
        else if (t.get_marime() == "M") nr = 9;
        else if (t.get_marime() == "L") nr = 12;
        else nr = 15;

        QFont font("Sheriff", nr);
        QString model, univers, marime, pret;
        pret = QString::number(t.get_pret());
        model = QString::fromStdString(t.get_model());
        univers = QString::fromStdString(t.get_univers());
        marime = QString::fromStdString(t.get_marime());
        QTableWidgetItem* prt = new QTableWidgetItem(pret);
        QTableWidgetItem* mdl = new QTableWidgetItem(model);
        mdl->setData(Qt::UserRole, univers); 
        mdl->setFont(font);
        prt->setFont(font);
        table->setItem(i,0,mdl); 
        table->setItem(i,1,prt); 
        i++;
    }
}

