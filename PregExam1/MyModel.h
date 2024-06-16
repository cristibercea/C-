#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "service.h"

class MyModel: public QAbstractTableModel
{
	vector<Melodie> v;
	Service& serv;
public:
	MyModel(Service& s) :serv{ s } { v = serv.getAllSorted(); }

	/// <summary>
	/// nr de linii
	/// </summary>
	/// <param name="parent"></param>
	/// <returns></returns>
	int rowCount(const QModelIndex& parent = QModelIndex()) const override { return (int)v.size(); }

	/// <summary>
	/// nr de coloane
	/// </summary>
	/// <param name="parent"></param>
	/// <returns></returns>
	int columnCount(const QModelIndex& parent = QModelIndex()) const override { return 6; }

	/// <summary>
	/// seteaza datele din tabel
	/// </summary>
	/// <param name="index"></param>
	/// <param name="role"></param>
	/// <returns></returns>
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	/// <summary>
	/// header customizat
	/// </summary>
	/// <param name="section"></param>
	/// <param name="orientation"></param>
	/// <param name="role"></param>
	/// <returns></returns>
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	/// <summary>
	/// schimba melodiile din tabel
	/// </summary>
	void setMelodii(vector<Melodie> ve);
};

