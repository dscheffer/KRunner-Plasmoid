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

import QtQuick 2.7
import org.kde.plasma.components 2.0 as PlasmaComponents                                                                    
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.plasmoid 2.0

import dscheffer.krunnerplasmoidplugin 0.1

Item {
    anchors.fill: parent
    MouseArea {
        id: menu
        anchors.fill: parent
        PlasmaCore.IconItem {
            id: buttonIcon

            anchors.fill: parent
            source: "search"
            active: parent.containsMouse
            smooth: true
            roundToIconSize: true
        }

        KRunnerDialog { 
            id: runnerWindow 
            hide: !menu.containsMouse
        }
    
        onClicked: open();

        Connections {
            target: ShortcutHandler
            onCtrlSpaceTriggered: menu.open()
        }

        function open() {
            var pos = menu.mapToGlobal(0, 0);
            runnerWindow.x = pos.x + buttonIcon.width - runnerWindow.mainItem.width - 12;
            runnerWindow.y = pos.y + buttonIcon.height;
            runnerWindow.visible = !runnerWindow.visible;
        }
    }
}