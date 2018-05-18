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
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import org.kde.plasma.components 2.0 as PlasmaComponents                                                                    
import org.kde.plasma.core 2.0 as PlasmaCore

import dscheffer.krunnerplasmoidplugin 0.1

Item {
    id: runnerWindow
    visible: true
    property real currentHeight: units.gridUnit * 31
    property var history: []

    Layout.minimumWidth: units.gridUnit * 28
    Layout.minimumHeight: currentHeight
    Layout.maximumHeight: currentHeight

    RunCommand { 
        id: krunner
        showHistory: true
        toggleHistory: false  

        anchors.fill: parent
    }

    function addToHistory(entry) {
        runnerWindow.history.push(entry);
    }

    function removeFromHistory(index) {
        if (index > -1) {
            runnerWindow.history.splice(index, 1);
        }
    }

    function displayConfiguration() {
        ApplicationLauncher.launchPlasmasearchSettings();
    }

    onVisibleChanged: {
        if (runnerWindow.visible == false) {
            runnerWindow.visible = true;
            krunner.showHistory = true;
        }
    }

    /*MouseArea {
        id: resize
        cursorShape: Qt.SizeVerCursor
        anchors.bottom: runnerWindow.bottom
        anchors.left: runnerWindow.left
        anchors.right: runnerWindow.right
        height: 2

        onPositionChanged: function(event) {
            var point = resize.mapToItem(runnerWindow, event.x, event.y);
            runnerWindow.currentHeight = point.y;
        }
    }*/
}