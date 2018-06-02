/*
 *   Copyright (c) 2018 Dennis Scheffer.
 *
 *   This file is part of KRunner Plasmoid.
 *
 *   KRunner Plasmoid is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   KRunner Plasmoid is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with KRunner Plasmoid.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PROJECT_HISTORY_HPP
#define PROJECT_HISTORY_HPP

#include <QObject>
#include <QQmlListProperty>
#include <QAction>
#include <QAbstractListModel>
#include "HistoryEntry.hpp"

class History : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<HistoryEntry> history READ getHistory NOTIFY historyChanged);

    QList<HistoryEntry *> history;
    bool persistent = true;
public:
    History(QObject* parent = 0);
    ~History();

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

    bool hasChildren(const QModelIndex&) const Q_DECL_OVERRIDE {
        return false;
    }

    void setPersistent(bool persistent);
    void clearHistory();

    QQmlListProperty<HistoryEntry> getHistory();

    Q_INVOKABLE void addToHistory(QString queryString, QString displayText, QString icon, int resultIndex);
    Q_INVOKABLE void removeFromHistory(QString displayName);

    Q_INVOKABLE void loadHistory();

signals:
    void historyChanged(bool checked = 0);

private:
    void writeHistoryToFile();
    QJsonArray toJson();
};


#endif //PROJECT_HISTORY_HPP
