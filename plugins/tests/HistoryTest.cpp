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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <QString>
#include <memory>

#include "History.hpp"

using namespace testing;

namespace
{

    TEST(HistoryTest, AddToHistoryTest) {
        History history;
        history.clearHistory();
        history.setPersistent(false);
        history.addToHistory(QString("abcd"), QString("efgh"), QString("ijkl"), 1);

        QQmlListProperty<HistoryEntry> resultList = history.getHistory();
        HistoryEntry *result = resultList.at(&resultList, 0);

        EXPECT_EQ(result->getQueryString(), QString("abcd"));
        EXPECT_EQ(result->getDisplayText(), QString("efgh"));
        EXPECT_EQ(result->getIcon(), QString("ijkl"));
        EXPECT_EQ(result->getResultIndex(), 1);
    }

    TEST(HistoryTest, AddToHistoryTwice) {
        History history;
        history.clearHistory();
        history.setPersistent(false);
        history.addToHistory(QString("abcd"), QString("efgh"), QString("ijkl"), 1);
        history.addToHistory(QString("mnop"), QString("qrst"), QString("uvwx"), 2);
        history.addToHistory(QString("mnop"), QString("qrst"), QString("uvwx"), 2);

        QQmlListProperty<HistoryEntry> resultList = history.getHistory();
        HistoryEntry *result = resultList.at(&resultList, 0);

        EXPECT_EQ(result->getQueryString(), QString("mnop"));
        EXPECT_EQ(result->getDisplayText(), QString("qrst"));
        EXPECT_EQ(result->getIcon(), QString("uvwx"));
        EXPECT_EQ(result->getResultIndex(), 2);
    }

    TEST(HistoryTest, RemoveFromHistory) {
        History history;
        history.clearHistory();
        history.setPersistent(false);
        history.addToHistory(QString("abcd"), QString("efgh"), QString("ijkl"), 1);
        history.addToHistory(QString("mnop"), QString("qrst"), QString("uvwx"), 2);
        history.removeFromHistory(QString("qrst"));

        QQmlListProperty<HistoryEntry> resultList = history.getHistory();
        HistoryEntry *result = resultList.at(&resultList, 0);

        EXPECT_EQ(result->getQueryString(), QString("abcd"));
        EXPECT_EQ(result->getDisplayText(), QString("efgh"));
        EXPECT_EQ(result->getIcon(), QString("ijkl"));
        EXPECT_EQ(result->getResultIndex(), 1);
    }

    TEST(HistoryTest, RemoveFromEmpty) {
        History history;
        history.clearHistory();
        history.setPersistent(false);
        history.removeFromHistory(QString("abcd"));

        QQmlListProperty<HistoryEntry> resultList = history.getHistory();
        int count = resultList.count(&resultList);

        EXPECT_EQ(count, 0);
    }
}