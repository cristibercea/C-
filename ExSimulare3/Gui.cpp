#include "Gui.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QVector>

Gui::Gui(Service serv, QWidget *parent)
    : QMainWindow(parent), service{serv}
{
    ui.setupUi(this);
    init();
    connectElements();
}

void Gui::init()
{
    QWidget* window = new QWidget;
    plc = new QListWidget;
    proc = new QListWidget;
    add = new QPushButton("Adauga");
    nume = new QLineEdit;
    soclu = new QLineEdit;
    pret = new QLineEdit;
    pretTotal = new QLineEdit;
    pretTotal->setReadOnly(true);

    genereazalistaPlaci(service.getPlaciDeBaza());
    genereazalistaProc(service.getProcesoare());

    QHBoxLayout* hLay = new QHBoxLayout;
    QVBoxLayout* vLay = new QVBoxLayout;

    QLabel *l1 = new QLabel("Nume:");
    QLabel *l2 = new QLabel("Soclu:");
    QLabel *l3 = new QLabel("Pret:");
    QLabel *l4 = new QLabel("Pret total (procesor+placa de baza):");

    vLay->addWidget(l1);
    vLay->addWidget(nume);
    vLay->addWidget(l3);
    vLay->addWidget(soclu);
    vLay->addWidget(l2);
    vLay->addWidget(pret);
    vLay->addWidget(add);
    vLay->addSpacing(10);
    vLay->addWidget(l4);
    vLay->addWidget(pretTotal);
    hLay->addWidget(plc); 
    hLay->addWidget(proc);
    hLay->addLayout(vLay);
    window->setLayout(hLay);

    this->setCentralWidget(window);
}

void Gui::connectElements()
{
    connect(add, &QPushButton::clicked, this, [this]() {
        string num = nume->text().toStdString();
        string soc = soclu->text().toStdString();
        int prt = pret->text().toInt();
        if(num=="" || soc == "") QMessageBox::warning(this, "Addition error", "Date invalide!", QMessageBox::Ok);
        nume->setText("");
        soclu->setText("");
        pret->setText("");
        try { service.addPlaci(num, soc, prt); ;plc->clear(); genereazalistaPlaci(service.getPlaciDeBaza()); }
        catch (std::exception& e) { QMessageBox::warning(this, "Addition error", "Aceasta placa exista deja!", QMessageBox::Ok); }
        });
    connect(proc, &QListWidget::itemSelectionChanged, this, [this]() {
        for (auto el : proc->selectedItems()) {
            QVector<QVariant> v = el->data(Qt::UserRole).toList();
            QString s = v[0].toString();
            int p = v[1].toInt();
            string st = s.toStdString();
            plc->clear();
            genereazalistaPlaci(service.filtruSoclu(st));
            disconnect(plc);
            connect(plc, &QListWidget::itemSelectionChanged, this, [this, p]() {
                for (auto e : plc->selectedItems()) {
                    QVector<QVariant> v = e->data(Qt::UserRole).toList();
                    int pr = v[1].toInt();
                    pretTotal->setText(QString::number(p+pr));
                }
            });
        }
    });
}

void Gui::genereazalistaPlaci(const vector<PlacaDeBaza> v)
{
    for (PlacaDeBaza e : v) {
        QString num = num.fromStdString(e.get_nume());
        QListWidgetItem* i = new QListWidgetItem(num);
        QVector<QString> v;
        v.push_back(QString::fromStdString(e.get_soclu()));
        v.push_back(QString::number(e.get_pret()));
        i->setData(Qt::UserRole, v);
        plc->addItem(i);
    }
}

void Gui::genereazalistaProc(const vector<Procesor> v)
{
    for (Procesor e : v) { 
        QString num = num.fromStdString(e.get_nume()); 
        QString thread = thread.number(e.get_threads());
        QListWidgetItem* i = new QListWidgetItem(num+" - "+thread);
        QVector<QString> v; 
        v.push_back(QString::fromStdString(e.get_soclu())); 
        v.push_back(QString::number(e.get_pret())); 
        i->setData(Qt::UserRole, v); 
        proc->addItem(i);  
    } 
}
