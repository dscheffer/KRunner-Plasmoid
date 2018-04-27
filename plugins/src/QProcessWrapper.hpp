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

#ifndef __QProcessWrapper_HPP_INCLUDED__  
#define __QProcessWrapper_HPP_INCLUDED__

#include <QtCore>

class QProcessWrapper {    
public:
    QProcessWrapper() { };
    virtual ~QProcessWrapper() { };
    virtual QByteArray readAllStandardError() = 0;
    virtual QByteArray readAllStandardOutput() = 0;
    virtual void start(const QString &program, const QStringList &arguments) = 0;
    virtual bool startDetached(const QString &program) = 0;
    virtual bool startDetached(const QString &program,  const QStringList &arguments) = 0;
    virtual bool waitForFinished() = 0;
    virtual void close() = 0;
};

#endif //__QProcessWrapper_HPP_INCLUDED__