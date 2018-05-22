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

class History : public QObject {
    Q_OBJECT

    Q_PROPERTY(QStringList history READ getHistory NOTIFY historyChanged);

    QStringList history;
    bool persistent = true;
public:
    History(QObject* parent = 0);
    ~History();

    void setPersistent(bool persistent);

    QStringList getHistory();

    Q_INVOKABLE void addToHistory(QString entry);
    Q_INVOKABLE void removeFromHistory(QString entry);

signals:
    void historyChanged(bool checked = 0);

private:
    void writeHistoryToFile();
};


#endif //PROJECT_HISTORY_HPP
