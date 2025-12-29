#pragma once

#include <QAbstractListModel>
#include "TelemetryItem.h"

class TelemetryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles
    {
        IdRole = Qt::UserRole + 1,
        TimestampRole,
        TypeRole,
        ValueRole,
        StatusRole,
    };

    explicit TelemetryModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addTelemetry(const TelemetryItem& item);
    void clear();

private:
    QList<TelemetryItem> m_items;
};
