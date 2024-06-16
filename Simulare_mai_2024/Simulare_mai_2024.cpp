#include "Simulare_mai_2024.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

Simulare_mai_2024::Simulare_mai_2024(Service& s, QWidget *parent)
    : QMainWindow(parent), serv{s}
{
    ui.setupUi(this);
    init();
    eventConnector();
}

Simulare_mai_2024::~Simulare_mai_2024()
{}

void Simulare_mai_2024::init()
{
    central = new QWidget();
    list = new QListWidget();
    id = new QLineEdit();
    nume = new QLineEdit();
    pret = new QLineEdit();
    sterge = new QPushButton("Sterge Stock");
    progress = new QProgressBar();
    progress->setRange(0,100);
    id->setReadOnly(true);
    nume->setReadOnly(true);
    pret->setReadOnly(true);
    QVBoxLayout* vLay = new QVBoxLayout();

    loadWidgetList(serv.getAll());

    vLay->addWidget(list);
    vLay->addWidget(id);
    vLay->addWidget(nume);
    vLay->addWidget(pret);
    vLay->addWidget(progress);
    vLay->addWidget(sterge);

    central->setLayout(vLay);
    this->setCentralWidget(central);
}

void Simulare_mai_2024::eventConnector()
{
    connect(list, &QListWidget::itemSelectionChanged, this, [this]() {
        for (auto el : list->selectedItems()) {
            QVector<QVariant> data = el->data(Qt::UserRole).toList();
            QString str = el->text();
            QVector<QString> text = str.split(" - ");
            nume->setText(data[0].toString());
            id->setText(text[0]);
            pret->setText(text[1]);
            progress->reset();
            progress->setValue(abs(data[1].toInt()));
        }
    });
    connect(sterge, &QPushButton::clicked, this, [this]() { dialogStergere(); });
}

void Simulare_mai_2024::loadWidgetList(vector<Stock> v)
{
    for (Stock& s : v) {
        QString id = QString::fromStdString(s.get_id());
        QString nume = QString::fromStdString(s.get_name());
        QString pret = QString::number(s.get_price());
        QString rata = QString::number(s.get_rate());
        QListWidgetItem* i = new QListWidgetItem(id+" - "+pret);
        if (s.get_rate() < 0) i->setBackground(Qt::red);
        else i->setBackground(Qt::green); 
        QVector<QString> data;
        data.push_back(nume);
        data.push_back(rata);
        i->setData(Qt::UserRole, data);
        list->addItem(i); 
    }
}

void Simulare_mai_2024::dialogStergere()
{
    if(list->selectedItems().size() == 0) return;
    
    string ID = id->text().toStdString();
    QMessageBox* mess = new QMessageBox();
    QPushButton* y = new QPushButton("Yes");
    QPushButton* n = new QPushButton("No");
    mess->setWindowTitle("Stergere");
    mess->setText("Sunteti sigur ca vreti sa stergeti Stock-ul selectat?");
    mess->addButton(y, QMessageBox::YesRole); 
    mess->addButton(n, QMessageBox::NoRole);

    connect(y, &QPushButton::clicked, this, [this, mess,ID]() { serv.sterge(ID); mess->close(); });
    connect(n, &QPushButton::clicked, this, [mess]() { mess->close(); });
    
    mess->show();
}
