#include "MyListModel.h"

QVariant MyListModel::data(const QModelIndex& index, int role) const
{
    Tenant t = apartaments[index.row()];
    if (role == Qt::DisplayRole) {
        if (t.get_apartament() == -1) return QString::fromStdString(t.get_name());
        return QString::fromStdString(t.get_name()) + "-" + QString::number(t.get_apartament()) + "-" + QString::fromStdString(t.get_type()) + "-" + QString::number(t.get_area());
    }
    return QVariant();
}

void MyListModel::setTenants(const std::vector<Tenant>& aps) {
    apartaments = aps;
    QModelIndex topLeft = createIndex(0, 0);
    QModelIndex unused = createIndex(0, 0);
    QModelIndex bottomRight = createIndex(rowCount(unused), columnCount(unused));
    emit dataChanged(topLeft, bottomRight);
}
