#include "gui.h"
#include <QVBoxLayout>
#include <QMessageBox>

void GUI::init()
{
	this->setWindowTitle("Produse");
	QVBoxLayout* vLay = new QVBoxLayout;
	tab = new QTableView;
	slider = new QSlider(this);
	slider->setTickPosition(QSlider::TicksRight);
	slider->setTickInterval(1);
	Id = new QLineEdit;
	Nume = new QLineEdit;
	Tip = new QLineEdit;
	Pret = new QLineEdit;
	QLabel* id = new QLabel("Id:");
	QLabel* nume = new QLabel("Nume:");
	QLabel* tip = new QLabel("Tip:");
	QLabel* pret = new QLabel("Pret:");
	save = new QPushButton("Salveaza Produs");
	m = new MyModel(serv.getAllSorted());
	tab->setModel(m);
	slider->setOrientation(Qt::Horizontal);
	vLay->addWidget(tab);
	vLay->addWidget(slider);
	vLay->addWidget(id);
	vLay->addWidget(Id);
	vLay->addWidget(nume);
	vLay->addWidget(Nume);
	vLay->addWidget(tip);
	vLay->addWidget(Tip);
	vLay->addWidget(pret);
	vLay->addWidget(Pret);
	vLay->addWidget(save);
	this->setLayout(vLay);
	winTipuri();
}

void GUI::connectSlotSocket()
{
	QObject::connect(save, &QPushButton::clicked, this, [this]() { adauga(); Id->setText(""); Nume->setText(""); Tip->setText(""); Pret->setText(""); });
	QObject::connect(slider, &QSlider::valueChanged, this, [this]() { filter(slider->value()+1); });
}

void GUI::adauga() {
	if (Nume->text() == "") { 
		QMessageBox::warning(this, "Adaugare Esuata", "Nume invalid", QMessageBox::Ok);
		return;
	}
	if (Tip->text() == "") {
		QMessageBox::warning(this, "Adaugare Esuata", "Tip invalid", QMessageBox::Ok);
		return;
	}
	try { serv.adaugare(Id->text().toInt(), Nume->text().toStdString(), Tip->text().toStdString(), Pret->text().toDouble()); m->setProduse(serv.getAllSorted()); }
	catch (std::exception& e) {
		QMessageBox::warning(this, "Adaugare Esuata", e.what(), QMessageBox::Ok);
	}
}

void GUI::filter(const double& val) const
{
	vector<Produs> v = serv.filter(val);
	m->setProduse(v);
	if (val == 50) m->schimbaCulori();
}

void GUI::winTipuri()
{
	auto p = serv.tipuri();
	vector<string> v = p.first; 
	vector<int> f = p.second;
	qDebug() << v.size();
	types = new QWidget[v.size()];
	labels = new QLabel[v.size()];
	for (int i = 0; i < v.size();i++) {
		QVBoxLayout* lay = new QVBoxLayout;
		labels[i].setText("Numarul de produse de acest tip: "+QString::number(f[i]));
		lay->addWidget(&labels[i]);
		types[i].setLayout(lay);
		types[i].setWindowTitle(QString::fromStdString(v[i]));
		types[i].show();
	}
}
