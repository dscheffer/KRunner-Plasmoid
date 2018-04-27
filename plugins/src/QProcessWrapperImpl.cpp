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

#include "QProcessWrapperImpl.hpp"

QProcessWrapperImpl::QProcessWrapperImpl(QObject* obj)
    : process(obj)
{ }

QByteArray QProcessWrapperImpl::readAllStandardError()
{
    return process.readAllStandardError();
}

QByteArray QProcessWrapperImpl::readAllStandardOutput()
{
    return process.readAllStandardOutput();
}
void QProcessWrapperImpl::start(const QString &program, const QStringList &arguments)
{
    process.start(program, arguments);
}
bool QProcessWrapperImpl::startDetached(const QString &program)
{
    return process.startDetached(program);
}
bool QProcessWrapperImpl::startDetached(const QString &program, const QStringList &arguments)
{
    return process.startDetached(program, arguments);
}
bool QProcessWrapperImpl::waitForFinished()
{
    return process.waitForFinished();
}

void QProcessWrapperImpl::close()
{
    process.close();
}