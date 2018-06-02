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

#ifndef PROJECT_HISTORYENTRY_HPP
#define PROJECT_HISTORYENTRY_HPP


#include <QObject>
#include <QtCore/QJsonObject>

class HistoryEntry : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString queryString READ getQueryString WRITE setQueryString);

    Q_PROPERTY(QString displayText READ getDisplayText WRITE setDisplayText);

    Q_PROPERTY(QString icon READ getIcon WRITE setIcon);

    Q_PROPERTY(int reultIndex READ getResultIndex WRITE setResultIndex);

    QString queryString;
    QString displayText;
    QString icon;
    int resultIndex;

public:
    HistoryEntry(QObject *parent = 0);

    HistoryEntry(const QString &queryString,
                 const QString &displayText,
                 const QString &icon,
                 int resultIndex,
                 QObject *parent = 0);

    HistoryEntry(const QJsonObject json);

    const QString &getQueryString() const;

    void setQueryString(const QString &queryString);

    const QString &getDisplayText() const;

    void setDisplayText(const QString &displayText);

    const QString &getIcon() const;

    void setIcon(const QString &icon);

    int getResultIndex() const;

    void setResultIndex(int resultIndex);

    QJsonObject toJson() const;
};


#endif //PROJECT_HISTORYENTRY_HPP
