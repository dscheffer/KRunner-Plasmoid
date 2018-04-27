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

#ifndef __QProcessWrapperImpl_HPP_INCLUDED__  
#define __QProcessWrapperImpl_HPP_INCLUDED__

#include "QProcessWrapper.hpp"

#include <QProcess>

class QProcessWrapperImpl : public QProcessWrapper {
    QProcess process;

public:
    QProcessWrapperImpl(QObject* obj = 0);

    QByteArray readAllStandardError() override;
    QByteArray readAllStandardOutput() override;
    void start(const QString &program, const QStringList &arguments) override;
    bool startDetached(const QString &program) override;
    bool startDetached(const QString &program, const QStringList &arguments) override;
    bool waitForFinished() override;
    void close() override;
};

#endif //__QProcessWrapperImpl_HPP_INCLUDED__