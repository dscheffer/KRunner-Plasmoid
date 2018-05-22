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
#include <QtConcurrent>
#include "config.hpp"
#include "History.hpp"

History::History(QObject *parent)
    : QObject(parent),  history()
{
    QFile file(CONFIG_LOCATION);

    if (!file.open(QIODevice::ReadWrite)) {
        return;
    }

    QDataStream in(&file);
    while (!in.atEnd()) {
        QString entry;
        in >> entry;
        history.push_back(entry);
    }

    file.close();
}

History::~History()
{ }

QStringList History::getHistory()
{
    return history;
}

void History::addToHistory(QString entry)
{
    history.removeAll(entry);
    history.push_front(entry);

    if (persistent) {
        QtConcurrent::run(this, &History::writeHistoryToFile);
    }
}

void History::removeFromHistory(QString entry)
{
    history.removeAll(entry);

    if (persistent) {
        QtConcurrent::run(this, &History::writeHistoryToFile);
    }
}

void History::writeHistoryToFile() {
    QFile file(CONFIG_LOCATION);
    if (!file.open(QIODevice::ReadWrite)) {
        return;
    }

    file.copy(QString(CONFIG_LOCATION) + QString(".backup"));

    QDataStream out(&file);
    for (QString entry : history) {
        out << entry;
    }

    file.close();
}

void History::setPersistent(bool persistent) {
    this->persistent = persistent;
}
