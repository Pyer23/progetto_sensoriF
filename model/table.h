#ifndef TABLE_H
#define TABLE_H
#include <QAbstractTableModel>
#include <QMessageBox>

class table : public QAbstractTableModel
{
    Q_OBJECT
private:
    QVector<QVector<double>> tableData;

    double minCell;
    double maxCell;

    bool editable;

    QVector<QString> headerRow;
    QVector<QString> headerColumn;

public:

    table(bool editable, int rows, int columns, double minCell, double maxCell, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    bool insertRows(int position, int rowsNumber, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rowsNumber, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int position, int columnsNumber, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columnsNumber, const QModelIndex &parent = QModelIndex()) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    //metodi in più
    void setCellMax(double max);
    void setCellMin(double min);

    int maxValue() const;
    int minValue() const;

    QVector<int> columnSum() const;
    QVector<int> rowSum() const;

    void defaultValue(int value);

};

#endif // TABLE_H
