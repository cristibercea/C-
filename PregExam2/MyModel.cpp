#include "MyModel.h"
#include <QBrush>

QVariant MyModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        Produs p = v[index.row()];
        switch (index.column()) {
            case 0: return QString::number(p.getId());
            case 1: return QString::fromStdString(p.getNume());
            case 2: return QString::fromStdString(p.getTip());
            case 3: return QString::number(p.getPret());
            default: return QString::number(p.nrVocale());
        }
    }
    if (role == Qt::UserRole) {
        QBrush color(Qt::red);
        QBrush color2(Qt::transparent);
        Produs p = v[index.row()];
        if (p.getPret() < 50) return color;
        return color2;
    }
    if (role == Qt::BackgroundRole) {
        QBrush color2(Qt::transparent);
        return color2;
    }
    return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0: return "ID";
            case 1: return "Nume";
            case 2: return "Tip";
            case 3: return "Pret";
            default: return "Nr Vocale";
        }
    }
    return QVariant();
}

bool MyModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::EditRole) {
        int row = index.row();
        int col = index.column();
        if (col == 1) {
            auto i = createIndex(row, col);
            v[row].setNume(value.toString().toStdString());
            emit dataChanged(i, i);
            ///daca ai service ca parametru la acest model poti apela o functie Edit care sa schimbe
            ///datele obiectului pe baza id-ului (deoarece este unic) atat in repo cat si in file
        }
    }
    return true;
}

void MyModel::setProduse(std::vector<Produs> ve)
{
    beginResetModel();
    v = ve;
    endResetModel();
}

void MyModel::schimbaCulori()
{
    for (int i = 0; i < v.size(); i++) {
        data(index(i, 0), Qt::UserRole);
        data(index(i, 1), Qt::UserRole);
        data(index(i, 2), Qt::UserRole);
        data(index(i, 3), Qt::UserRole);
        data(index(i, 4), Qt::UserRole);
    }
}
