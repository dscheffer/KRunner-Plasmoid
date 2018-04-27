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

#include "ApplicationLauncher.hpp"
#include "QProcessWrapperImpl.hpp"

#include <pwd.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include <memory>

ApplicationLauncher::ApplicationLauncher(QObject *parent)
    : QObject(parent), process(new QProcessWrapperImpl(this))
{ }

void ApplicationLauncher::setProcess(std::shared_ptr<QProcessWrapper> p)
{
    process = p;
}

void ApplicationLauncher::launchPlasmasearchSettings()
{
    QStringList params;
    params << "plasmasearch";
    process->startDetached("kcmshell5", params);
    process->close();
}