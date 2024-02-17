#include "table.h"

table::table(bool editable, int rows, int columns, double minCell, double maxCell, QObject *parent)
    : QAbstractTableModel(parent),
    minCell(minCell),
    maxCell(maxCell),
    editable(editable)
{
    for (int i = headerRow.size(); i <= rows; ++i) {
        headerRow.append(QString::number(i));
    }
    for (int i = headerColumn.size(); i <= columns; ++i) {
        headerColumn.append(QString::number(i));
    }

    QList<double> newTable;
    for (int column = 0; column < qMax(1, columns); ++column) {
        if(minCell<0){
        newTable.append(0);
        }else{
        newTable.append(minCell);
        }
    }
    for (int row = 0; row < qMax(1, rows); ++row) {
        tableData.append(newTable);
    }
}



int table::rowCount(const QModelIndex & /*parent*/) const
{
    return tableData.size();
    //restituisce ROWS
}

int table::columnCount(const QModelIndex & /*parent*/) const
{
    return tableData[0].size();
    //restituisce COLS;
}

bool table::insertRows(int position, int rowsNumber, const QModelIndex &parent/*parent*/)
{
    int columnsNumber = columnCount();
    beginInsertRows(parent, position, position + rowsNumber - 1);
    for (int row = 0; row < rowsNumber; ++row) {
        QList<double> cells;
        for (int column = 0; column < columnsNumber; ++column) {
            cells.append(0);
            tableData.insert(position, cells);
        }
    }
    endInsertRows();
    return true;
}

bool table::removeRows(int position, int rowsNumber, const QModelIndex &parent/*parent*/)
{
    beginRemoveRows(parent, position, position + rowsNumber -1);
    for (int row = 0; row < rowsNumber; ++row) {
        tableData.removeAt(0);
    }
    endRemoveRows();
    return true;
}

bool table::insertColumns(int position, int columnsNumber, const QModelIndex &parent/*parent*/)
{
    int rowsNumber = rowCount();
    int headerCNumber = columnCount();
    beginInsertColumns(parent, position, position + columnsNumber - 1);
    for (int row = 0; row < rowsNumber; ++row) {
        for (int column = 0; column < columnsNumber; ++column) {
            tableData[row].insert(position, 0);
            headerCNumber++;
            headerColumn.append(QString::number(headerCNumber));
        }
    }
    endInsertColumns();
    return true;
}

bool table::removeColumns(int position, int columnsNumber, const QModelIndex &parent/*parent*/)
{
    int rowsNumber = rowCount();
    beginRemoveColumns(parent, position, position + columnsNumber -1);
    for (int row = 0; row < rowsNumber; ++row) {
        for (int column = 0; column < columnsNumber; ++column) {
            tableData[row].removeAt(position);
            headerColumn.removeAt(position+1);
        }
    }
    endRemoveColumns();
    return true;
}


QVariant table::data(const QModelIndex &index, int role) const
{

    int row = index.row();
    int col = index.column();

    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return (tableData[row][col] < minCell) ? minCell : (tableData[row][col] > maxCell) ? maxCell : tableData[row][col];    }

    return QVariant();
}

bool table::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if (!index.isValid())
            return false;

        double newValue = (value.toDouble() < minCell) ? minCell : (value.toDouble() > maxCell) ? maxCell : value.toDouble();
        tableData[index.row()][index.column()] = newValue;
        emit dataChanged(index, index);
        return true;

    }
    return false;
}

QVariant table::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal){
        return headerColumn.at(section+1);
    }else{
        return headerRow.at(section);
    }

    return QVariant();
}

bool table::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        if(section < headerColumn.size() && orientation == Qt::Horizontal){
            headerColumn.replace(section, value.toString());
            emit headerDataChanged(orientation,section,section);
            return true;
        }

        if(section < headerRow.size() && orientation == Qt::Vertical){
            headerRow.replace(section, value.toString());
            emit headerDataChanged(orientation,section,section);
            return true;
        }
    }
    return false;
}


Qt::ItemFlags table::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags;
    flags = QAbstractItemModel::flags(index);
    {
        if((editable)==true)  //tabella editable
        {
            flags |=  Qt::ItemIsEditable;
            return flags;
        }
    }
    return  QAbstractItemModel::flags(index);
}

void table::setCellMin(double min) {
    if (min < maxCell) {
        minCell = min;
    } else {
        if(editable==true){
        //QMessageBox::critical(nullptr, "Errore", "Il valore minimo deve essere inferiore al valore massimo");
        }
    }
}

void table::setCellMax(double max) {
    if (max > minCell) {
        maxCell = max;
    } else {
        if(editable==true){ //il messaggio appare solo per le tabelle editable per evitare ripetizioni
        //QMessageBox::critical(nullptr, "Errore", "Il valore massimo deve essere superiore al valore minimo");
        }
    }
}

int table::maxValue() const{
    int max = 0;
    for (int i = 0; i < tableData.size(); i++) {
        for (int j = 0; j < tableData[i].size(); j++) {
            if (tableData[i][j] > max) {
                max = tableData[i][j];
            }
        }
    }
    return max;
}
int table::minValue() const{
    int min = 0;
    for (int i = 0; i < tableData.size(); i++) {
        for (int j = 0; j < tableData[i].size(); j++) {
            if (tableData[i][j] < min) {
                min = tableData[i][j];
            }
        }
    }
    return min;
}

QVector<int> table::columnSum() const {
    QVector<int> vector;
    for(int i = 0; i < columnCount(); ++i){
        int sum = 0;
        for(int j = 0; j < rowCount(); ++j)
            sum = sum + tableData[j][i];
        vector.push_back(sum);
    }
    return vector;
}

QVector<int> table::rowSum() const {
    QVector<int> vector;
    for(int i = 0; i < rowCount(); ++i){
        int sum = 0;
        for(int j = 0; j < columnCount(); ++j)
            sum = sum + tableData[i][j];
        vector.push_back(sum);
    }
    return vector;
}

void table::defaultValue(int value){
    const QModelIndex index;
    for (int i = 0; i < tableData.size(); ++i) {
        for (int j = 0; j < tableData[i].size(); ++j) {
            tableData[i][j]= value;
            emit dataChanged(index, index);
        }
    }
}

