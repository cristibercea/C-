#include "ExSimulare1.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <algorithm>

ExSimulare1::ExSimulare1(service& serv, QWidget *parent )
    : QMainWindow(parent), srv{serv}
{
    ui.setupUi(this);
    init();
    linkWidgets();
}

ExSimulare1::~ExSimulare1() {}

void ExSimulare1::init()
{
    QWidget *win = new QWidget(); 
    QVBoxLayout* vLay = new QVBoxLayout();
    QHBoxLayout* hLay = new QHBoxLayout();
    QLabel* l = new QLabel("CNP: ");
    QLabel* f = new QLabel("\nFiltru: ");

    list = new QListWidget();
    cnp = new QLineEdit();
    date = new QLineEdit(); 
    reset = new QPushButton("Toate");
    filtru1 = new QPushButton("Filtreaza dupa sectie");
    filtru2 = new QPushButton("Filtreaza dupa nume");
    cnp->setReadOnly(true);

    updateList(srv.get_all());
    vLay->addWidget(list);

    hLay->addWidget(l);
    hLay->addWidget(cnp); 
    vLay->addLayout(hLay);
    vLay->addWidget(f);
    vLay->addWidget(date);
    vLay->addWidget(reset);
    vLay->addWidget(filtru1);
    vLay->addWidget(filtru2);
    win->setLayout(vLay);
    this->setCentralWidget(win);
}

void ExSimulare1::linkWidgets() {
    QObject::connect(reset, &QPushButton::clicked, this, [this]() { updateList(srv.get_all()); });
    QObject::connect(filtru2, &QPushButton::clicked, this, [this]() { filtruNume(date->text().toStdString()); });
    QObject::connect(filtru1, &QPushButton::clicked, this, [this]() { filtruSectie(date->text().toStdString()); });
    QObject::connect(list, &QListWidget::itemSelectionChanged, this, [this]() {
        for (auto& el : list->selectedItems()) {
            cnp->setText(el->data(Qt::UserRole).toString()); 
        }
    });   
}

void ExSimulare1::updateList(vector<doctor> v) {
    list->clear();
    for (const doctor& el : v) {
        QString data = "";
        data += el.get_nume() + " " + el.get_prenume() + " - " + el.get_sectie();
        QListWidgetItem* i = new QListWidgetItem(data);
        i->setData(Qt::UserRole, QString::fromStdString(el.get_cnp()));
        if (el.get_status()) i->setBackground(Qt::red);
        else i->setBackground(Qt::green);
        list->addItem(i);
    }
}

void ExSimulare1::filtruSectie(string sectie){//se face in service si se testeaza
    vector<doctor> filtered;
    vector<doctor> src = srv.get_all();
    std::copy_if(src.begin(), src.end(), std::back_inserter(filtered), [sectie](const doctor& d) {return sectie == d.get_sectie(); });
    updateList(filtered);
}

void ExSimulare1::filtruNume(string nume) {//se face in service si se testeaza
    vector<doctor> filtered;
    vector<doctor> src = srv.get_all();
    std::copy_if(src.begin(), src.end(), std::back_inserter(filtered), [nume](const doctor& d) {return nume == d.get_nume(); });
    updateList(filtered);
}
