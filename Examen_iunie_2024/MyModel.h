#pragma once
#include "service.h"
#include <QAbstractTableModel>

class MyModel : public QAbstractTableModel
{
	Service& serv;
	vector<Task> v;
public:
	MyModel(Service& service) : serv{ service } { v = serv.getAllSorted(); }

	int rowCount(const QModelIndex& parent = QModelIndex()) const override { return (int)v.size(); }

	int columnCount(const QModelIndex& parent = QModelIndex()) const override { return 4; }

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	/// <summary>
	/// afiseaza task-urile sortate dupa stare
	/// </summary>
	void setTasks();

	/// <summary>
	/// afiseaza task-urile filtrate
	/// </summary>
	/// <param name="ve"></param>
	void setTasksFiltered(vector<Task> ve);
};

