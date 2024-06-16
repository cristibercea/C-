#include "MyModel.h"

QVariant MyModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        Task t = v[index.row()];
        int j = index.column();
        switch (j) {
            case 0: return QString::number(t.getId());
            case 1: return QString::fromStdString(t.getDescriere());
            case 2: return QString::fromStdString(t.getStare()); 
            case 3: return QString::number(t.getProgramatori().size()); 
        }
    }
    return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole&&orientation==Qt::Horizontal) {
        switch (section) {
        case 0: return "Id";
        case 1: return "Descriere";
        case 2: return "Stare";
        case 3: return "Programatori";
        }
    }
    return QVariant();
}

void MyModel::setTasks()
{
    beginResetModel();
    v = serv.getAllSorted();
    endResetModel();
}

void MyModel::setTasksFiltered(vector<Task> ve)
{
    beginResetModel(); 
    v = ve; 
    endResetModel(); 
}
