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

#ifndef __GTestWidget_HPP_INCLUDED__
#define __GTestWidget_HPP_INCLUDED__

#include <QWidget>

class GTestWidget : public QWidget {
    Q_OBJECT

public:
    GTestWidget(int argc, char** argv, QWidget* widget = 0);
    void showEvent(QShowEvent* event) override;
};

#endif //_GTestWidget_HPP_INCLUDED__
