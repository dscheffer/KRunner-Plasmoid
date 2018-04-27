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

#include "ShortcutHandler.hpp"

#include <KGlobalAccel>
#include <KLocalizedString>

ShortcutHandler::ShortcutHandler(QObject *parent)
    : QObject(parent), ctrlSpace(new QAction(nullptr))
{
    ctrlSpace->setText(i18n("Run Command Plasmoid"));
    ctrlSpace->setObjectName(QStringLiteral("run command"));
    ctrlSpace->setProperty("componentDisplayName", i18nc("Name for krunner plasmoid shortcuts category", "Run Command Plasmoid"));
    QObject::connect(ctrlSpace, SIGNAL(triggered()), this, SIGNAL(ctrlSpaceTriggered()));
    KGlobalAccel::self()->setDefaultShortcut(ctrlSpace, QList<QKeySequence>() << QKeySequence(Qt::CTRL + Qt::Key_Space) << QKeySequence(Qt::CTRL + Qt::Key_F2), KGlobalAccel::NoAutoloading);
    KGlobalAccel::self()->setShortcut(ctrlSpace, QList<QKeySequence>() << QKeySequence(Qt::CTRL + Qt::Key_Space) << QKeySequence(Qt::CTRL + Qt::Key_F2), KGlobalAccel::NoAutoloading);
}

ShortcutHandler::~ShortcutHandler() 
{
    delete ctrlSpace;
}