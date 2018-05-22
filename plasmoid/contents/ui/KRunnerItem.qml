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
    property real currentHeight: units.gridUnit * 31

    Layout.minimumWidth: units.gridUnit * 28
    Layout.minimumHeight: currentHeight
    Layout.maximumHeight: currentHeight

    RunCommand { 
        id: krunner
        showHistory: true
        toggleHistory: false

        anchors.fill: parent

        Component.onCompleted: {
            krunner.activateFocus();
        }

        onClosed: {
            krunner.query = "";
            krunner.runner = "";
            krunner.showHistory = false; // toggle show history so milou result delegate updates model??
            krunner.showHistory = true;
            krunner.activateListViewFocus();
        }

        onQueryFieldFocused: History.loadHistory()
    }

    function displayConfiguration() {
        ApplicationLauncher.launchPlasmasearchSettings();
    }
}