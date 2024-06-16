#include "MyModel.h"

QVariant MyModel::data(const QModelIndex& index, int role) const
{
	int r = index.row();
	int c = index.column();
	Melodie m = v[r];
	if (role == Qt::DisplayRole) {
		switch (c) {
		case 0:
			return QString::number(m.getId());
		case 1:
			return QString::fromStdString(m.getTitlu());
		case 2:
			return QString::fromStdString(m.getArtist());
		case 3:
			return QString::fromStdString(m.getGen());
		case 4:
			return QString::number(serv.nrMelodiiArtist(m.getArtist()));
		default:
			return QString::number(serv.nrMelodiiGen(m.getGen()));
		}
	}
	return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		switch (section) {
		case 0:
			return "Id";
		case 1:
			return "Titlu";
		case 2:
			return "Autor";
		case 3:
			return "Gen";
		case 4:
			return "Similare-Autor";
		default:
			return "Similare-Gen";
		}
	}
	return QVariant();
}

void MyModel::setMelodii(vector<Melodie> ve)
{
	beginResetModel();
	v = ve;
	endResetModel(); 
}
