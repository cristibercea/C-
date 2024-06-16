#include "gui.h"
#include <QLabel>
#include <QBoxLayout>
#include <QMessageBox>
#include <QPainter>

GUI::GUI(Service& s) : serv{s}
{
    init();
    connectSlotSocket();
}

GUI::~GUI(){}

void GUI::paintEvent(QPaintEvent* event)
{
    QPainter paint{ this };
    int r = 10;
    QPoint c1(70,70);
    QPoint c2(70, height()-70);
    QPoint c3(width()-70, 70);
    QPoint c4(width()-70, height()-70);
    int pop = serv.nrMelodiiGen("pop");
    int folk = serv.nrMelodiiGen("folk");
    int rock = serv.nrMelodiiGen("rock");
    int disco = serv.nrMelodiiGen("disco");
    for (int i = 0; i < pop; i++){
        paint.drawEllipse(c1, r, r);
        r += 10;
    }
    r = 10;
    for (int i = 0; i < folk; i++) {
        paint.drawEllipse(c2, r, r);
        r += 10;
    }
    r = 10;
    for (int i = 0; i < rock; i++) {
        paint.drawEllipse(c3, r, r);
        r += 10;
    }
    r = 10;
    for (int i = 0; i < disco; i++) {
        paint.drawEllipse(c4, r, r);
        r += 10;
    }
}

void GUI::init()
{
    tab = new QTableView;
    titlu = new QLineEdit;
    artist = new QLineEdit;
    gen = new QLineEdit;
    QLabel* t = new QLabel("Titlu");
    QLabel* a = new QLabel("Artist");
    QLabel* g = new QLabel("Gen");
    save = new QPushButton("Salveaza Melodie");
    destroy = new QPushButton("Sterge Melodie");
    t->setBuddy(titlu);
    a->setBuddy(artist);
    g->setBuddy(gen);
    QVBoxLayout* vLay = new QVBoxLayout;
    QHBoxLayout* hLay = new QHBoxLayout;
    model = new MyModel(serv);
    tab->setModel(model);

    vLay->addSpacing(100);
    vLay->addWidget(tab);
    vLay->addWidget(t);
    vLay->addWidget(titlu);
    vLay->addWidget(a);
    vLay->addWidget(artist);
    vLay->addWidget(g);
    vLay->addWidget(gen);
    vLay->addWidget(save);
    vLay->addWidget(destroy);
    vLay->addSpacing(100);
    hLay->addSpacing(100);
    hLay->addLayout(vLay);
    hLay->addSpacing(100);
    this->setLayout(hLay);
}

void GUI::connectSlotSocket()
{
    QObject::connect(save, &QPushButton::clicked, this, [this]() { adauga(); });
    QObject::connect(destroy, &QPushButton::clicked, this, [this]() { 
        starge();
        });
}

void GUI::adauga()
{
    int ok = 0;
    const QVector<QString> v = { "pop", "rock", "folk", "disco" };
    for (const QString& e : v)
        if (gen->text() == e) {
            ok = 1;
            break;
        }
    if (titlu->text() != "" && artist->text() != "" && ok) {
        string t = titlu->text().toStdString();
        string a = artist->text().toStdString();
        string g = gen->text().toStdString();
        serv.adauga(t,a,g);

        model->setMelodii(serv.getAllSorted());

        titlu->setText("");
        artist->setText("");
        gen->setText("");
        update();
        return;
    }
    QMessageBox::warning(this,"Add Error","Invalid input!", QMessageBox::Ok);
    titlu->setText("");
    artist->setText("");
    gen->setText("");
}

void GUI::starge()
{
    if (tab->selectionModel()->selectedIndexes().isEmpty()) return;
    auto r = tab->selectionModel()->selectedIndexes().at(0).row();
    vector<Melodie> v = serv.getAllSorted();
    serv.sterge(v[r].getId());
    model->setMelodii(serv.getAllSorted());
    update();
}
