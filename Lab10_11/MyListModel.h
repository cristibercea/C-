#pragma once
#include <QAbstractListModel>
#include <vector>
#include "domain.h"

class MyListModel : public QAbstractListModel {
private:
	std::vector<Tenant> apartaments;
public:
	MyListModel(std::vector<Tenant>& a) : apartaments(a) {  }

    int rowCount(const QModelIndex& /*parent*/) const override {return apartaments.size();}

	int columnCount(const QModelIndex& /*parent*/) const override { return 4; }

	QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const override;

	void setTenants(const std::vector<Tenant>& aps);
};

