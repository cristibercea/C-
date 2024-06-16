#include "gui.h"
#include <QBoxLayout>
#include <QMessageBox>
#include <QLabel>

void GUI::init()
{
	this->setWindowTitle("Programming Tasks");
	id = new QLineEdit;
	descr = new QLineEdit;
	status = new QLineEdit;
	names = new QLineEdit;
	tab = new QTableView;
	save = new QPushButton("Adauga");
	filter = new QPushButton("Filtreaza");
	model = new MyModel(serv);
	tab->setModel(model);
	QVBoxLayout* v = new QVBoxLayout;
	QHBoxLayout* h = new QHBoxLayout;
	QLabel* idL = new QLabel("Id:");
	QLabel* namesL = new QLabel("Nume programatori (cu virgula intre ele; minim 1, maxim 4):");
	QLabel* statusL = new QLabel("Stare:");
	QLabel* descrL = new QLabel("Descriere:");
	v->addWidget(tab);
	v->addWidget(idL);
	v->addWidget(id);
	v->addWidget(descrL);
	v->addWidget(descr);
	v->addWidget(statusL);
	v->addWidget(status);
	v->addWidget(namesL);
	v->addWidget(names);
	h->addWidget(save);
	h->addWidget(filter);
	v->addLayout(h);
	this->setLayout(v);
}

void GUI::connectSlotSocket()
{
	QObject::connect(save, &QPushButton::clicked, this, [this]() { adauga(); id->setText(""); names->setText(""); status->setText(""); descr->setText(""); });
	QObject::connect(filter, &QPushButton::clicked, this, [this]() { filtru(); names->setText(""); });
}

void GUI::adauga()
{
	if (descr->text() == "") {
		QMessageBox::warning(this, "Adaugare Esuata!", "Descriere invalida!", QMessageBox::Ok);
		return;
	}
	try { 
		vector<string> v;
		auto tmp = names->text().split(",");
		for (const auto& t : tmp) v.push_back(t.toStdString());
		serv.adauga(id->text().toInt(),descr->text().toStdString(),status->text().toStdString(), v); 
		model->setTasks();
	}
	catch (std::exception& e) {QMessageBox::warning(this,"Adaugare Esuata!",QString::fromStdString(e.what()),QMessageBox::Ok);}
}

void GUI::filtru()
{
	if (names->text() == "") {
		QMessageBox::warning(this, "Filtru Esuat!", "Nume invalid!", QMessageBox::Ok);
		return;
	}
	model->setTasksFiltered(serv.filtruProgramator(names->text().toStdString()));
}




void Ferestre::init(const string& title)
{
	tab = new QTableView;
	model = new MyModel(s);
	tab->setModel(model);
	model->setTasksFiltered(s.filtruStatus(title));
	open = new QPushButton("Open");
	close = new QPushButton("Close");
	inprog = new QPushButton("In Progress");
	QVBoxLayout* v = new QVBoxLayout;
	QHBoxLayout* h = new QHBoxLayout;
	v->addWidget(tab);
	h->addWidget(open);
	h->addWidget(inprog);
	h->addWidget(close);
	v->addLayout(h);
	this->setLayout(v);
}

void Ferestre::connectSlotSocket()
{
	QObject::connect(open, &QPushButton::clicked, this, [this]() { editStat("open"); });
	QObject::connect(close, &QPushButton::clicked, this, [this]() { editStat("closed"); });
	QObject::connect(inprog, &QPushButton::clicked, this, [this]() { editStat("inprogress"); });
}

void Ferestre::editStat(const string& status)
{
	if (tab->selectionModel()->selectedIndexes().isEmpty()) return;
	auto ind = tab->selectionModel()->selectedIndexes().at(0);
	if (ind.column() != 0) return;
	s.editStat(status, model->data(ind, Qt::DisplayRole).toInt());
	qDebug()<<model->data(ind, Qt::DisplayRole).toString();
}
