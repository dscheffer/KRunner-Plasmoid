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

#include <QtCore/QMap>
#include <QVariant>
#include "HistoryEntry.hpp"


HistoryEntry::HistoryEntry(QObject * parent)
        : QObject(parent),
          queryString(),
          displayText(),
          icon(),
          resultIndex(-1)
{

}

HistoryEntry::HistoryEntry(const QString &queryString,
                           const QString &displayText,
                           const QString &icon,
                           int resultIndex,
                           QObject *parent)
        : QObject(parent),
          queryString(queryString),
          displayText(displayText),
          icon(icon),
          resultIndex(resultIndex)
{

}

HistoryEntry::HistoryEntry(const QJsonObject json) {
    QVariantMap map = json.toVariantMap();
    displayText = map.find("displayText").value().toString();
    queryString = map.find("queryString").value().toString();
    icon = map.find("icon").value().toString();
    resultIndex = map.find("resultIndex").value().toInt();
}

const QString &HistoryEntry::getQueryString() const
{
    return queryString;
}

void HistoryEntry::setQueryString(const QString &queryString)
{
    HistoryEntry::queryString = queryString;
}

const QString &HistoryEntry::getDisplayText() const
{
    return displayText;
}

void HistoryEntry::setDisplayText(const QString &displayText)
{
    HistoryEntry::displayText = displayText;
}

const QString &HistoryEntry::getIcon() const
{
    return icon;
}

void HistoryEntry::setIcon(const QString &icon)
{
    HistoryEntry::icon = icon;
}

int HistoryEntry::getResultIndex() const
{
    return resultIndex;
}

void HistoryEntry::setResultIndex(int resultIndex)
{
    HistoryEntry::resultIndex = resultIndex;
}

QJsonObject HistoryEntry::toJson() const
{
    return {{"displayText", displayText},
            {"queryString", queryString},
            {"icon", icon},
            {"resultIndex", resultIndex}};
}
