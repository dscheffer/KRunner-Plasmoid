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

import QtQuick 2.0
import org.kde.plasma.plasmoid 2.0                                                                                                                      

Item {
    id: application
    width: childrenRect.implicitWidth
    height: childrenRect.implicitHeight

    Plasmoid.switchHeight: 555
    Plasmoid.compactRepresentation: MainMenu { }
    Plasmoid.fullRepresentation: KRunnerItem { }

    //Plasmoid.preferredRepresentation: compactRepresentation
}