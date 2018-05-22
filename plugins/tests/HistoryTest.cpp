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

#include "History.hpp"

using namespace testing;

namespace
{

    TEST(HistoryTest, AddToHistoryTest) {
        History history;
        history.setPersistent(false);
        history.addToHistory(QString("abcd"));

        QString result = history.getHistory()[0];

        EXPECT_EQ(result, QString("abcd"));
    }

    TEST(HistoryTest, AddToHistoryTwice) {
        History history;
        history.setPersistent(false);
        history.addToHistory(QString("abcd"));
        history.addToHistory(QString("efgh"));
        history.addToHistory(QString("efgh"));

        QString result = history.getHistory()[0];

        EXPECT_EQ(result, QString("efgh"));
    }

    TEST(HistoryTest, RemoveFromHistory) {
        History history;
        history.setPersistent(false);
        history.addToHistory(QString("abcd"));
        history.addToHistory(QString("efgh"));
        history.removeFromHistory(QString("abcd"));

        QString result = history.getHistory()[0];

        EXPECT_EQ(result, QString("efgh"));
    }

    TEST(HistoryTest, RemoveFromEmpty) {
        History history;
        history.setPersistent(false);
        history.removeFromHistory(QString("abcd"));

        int count = history.getHistory().length();

        EXPECT_EQ(count, 0);
    }
}