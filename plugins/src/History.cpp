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

#include <QFile>
#include <QDataStream>
#include <QtConcurrent/QtConcurrent>
#include "config.hpp"
#include "History.hpp"

History::History(QObject *parent)
    : QAbstractListModel(parent), history()
{
    loadHistory();
}

History::~History()
{
    clearHistory();
}

QQmlListProperty<HistoryEntry> History::getHistory()
{
    return QQmlListProperty<HistoryEntry>(this, history);
}

void History::addToHistory(QString queryString, QString displayText, QString icon, int resultIndex)
{
    removeFromHistory(displayText);

    HistoryEntry* entry = new HistoryEntry(queryString, displayText, icon, resultIndex, this);
    history.push_front(entry);

    if (persistent) {
        QtConcurrent::run(this, &History::writeHistoryToFile);
    }
}

void History::removeFromHistory(QString displayName)
{
    HistoryEntry* toRemove = nullptr;
    for (auto entry : history) {
        if (entry->getDisplayText() == displayName) {
            toRemove = entry;
        }
    }

    if (toRemove != nullptr) {
        history.removeAll(toRemove);
        delete toRemove;
    }
}

void History::writeHistoryToFile() {
    QFile file(CONFIG_LOCATION);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    file.write(QJsonDocument(toJson()).toJson());
}

void History::setPersistent(bool persistent) {
    this->persistent = persistent;
}

void History::loadHistory() {
    QFile file(CONFIG_LOCATION);

    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isArray()) {
        clearHistory();

        for (auto entry : doc.array()) {
            history.push_back(new HistoryEntry(entry.toObject()));
        }
    }
}

QVariant History::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= history.size())
        return QVariant();

    auto m = history[index.row()];

    switch(role) {
        case Qt::DisplayRole:
            return m->getDisplayText();
        case Qt::DecorationRole:
            if (!m->getIcon().isEmpty()) {
                return m->getIcon();
            }
            break;
    }

    return QVariant();
}

int History::rowCount(const QModelIndex &parent) const {
    return history.size();
}

QJsonArray History::toJson() {
    QJsonArray json;
    for (auto entry : history) {
        json.append(entry->toJson());
    }

    return json;
}

void History::clearHistory() {
    qDeleteAll(history);
    history.clear();
}
