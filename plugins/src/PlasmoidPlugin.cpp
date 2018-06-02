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

#include "PlasmoidPlugin.hpp"

#include "ApplicationLauncher.hpp"
#include "config.hpp"
#include "ShortcutHandler.hpp"
#include "History.hpp"

#include <KConfigGroup>
#include <KSharedConfig>

#include <QtQml/QtQml>

void PlasmoidPlugin::registerTypes(const char *uri)
{
    qmlRegisterSingletonType<ApplicationLauncher>(uri, MAJOR_VERSION, MINOR_VERSION, "ApplicationLauncher", [](QQmlEngine * engine, QJSEngine * scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        ApplicationLauncher *launcher = new ApplicationLauncher();
        return launcher;
    });

    qmlRegisterSingletonType<ShortcutHandler>(uri, MAJOR_VERSION, MINOR_VERSION, "ShortcutHandler", [](QQmlEngine * engine, QJSEngine * scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        ShortcutHandler *handler = new ShortcutHandler();
        return handler;
    });

    qmlRegisterSingletonType<ShortcutHandler>(uri, MAJOR_VERSION, MINOR_VERSION, "History", [](QQmlEngine * engine, QJSEngine * scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        History *history = new History();
        return history;
    });

    qmlRegisterType<HistoryEntry>(uri, MAJOR_VERSION, MINOR_VERSION, "HistoryEntry");
}