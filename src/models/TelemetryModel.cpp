#include "TelemetryModel.h"
#include <QDebug>

TelemetryModel::TelemetryModel(QObject *parent)
    : QAbstractListModel(parent)
{
    
}

int TelemetryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_items.size();
}

QVariant TelemetryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_items.size())
        return {};

    const auto& item = m_items[index.row()];

    switch (role)
    {
    case IdRole:
        return item.id;
    case TimestampRole:
        return item.timestamp.toString(Qt::ISODate);
    case TypeRole:
        return item.type;
    case ValueRole:
        return item.value;
    case StatusRole:
        return item.status;
    default:
        return {};
    }
}

QHash<int, QByteArray> TelemetryModel::roleNames() const
{
    return
    {
        {IdRole, "id"},
        {TimestampRole, "timestamp"},
        {TypeRole, "type"},
        {ValueRole, "value"},
        {StatusRole, "status"}
    };
}

void TelemetryModel::addTelemetry(const TelemetryItem &item)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.append(item);
    endInsertRows();
}

void TelemetryModel::clear()
{
    beginResetModel();
    m_items.clear();
    endResetModel();
}
