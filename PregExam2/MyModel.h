#pragma once
#include <QAbstractTableModel>
#include "domain.h"
#include <vector>

class MyModel: public QAbstractTableModel
{
	std::vector<Produs> v;
public:
	MyModel(std::vector<Produs> ve) : v{ ve } {}
	
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override { return (int)v.size(); }

	int columnCount(const QModelIndex& parent = QModelIndex()) const override { return 5; }

	Qt::ItemFlags flags(const QModelIndex& parent = QModelIndex()) const override { return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable; }

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::DisplayRole) override;

	/// <summary>
	/// seteaza modelul cu noile produse
	/// </summary>
	/// <param name="ve"></param>
	void setProduse(std::vector<Produs> ve);

	/// <summary>
	/// coloreaza cu rosu produsele mai ieftine de 50
	/// </summary>
	void schimbaCulori();
};

