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
import QtQuick.Layouts 1.1
import org.kde.plasma.components 2.0 as PlasmaComponents                                                                    
import org.kde.plasma.core 2.0 as PlasmaCore

import dscheffer.krunnerplasmoidplugin 0.1

PlasmaCore.Dialog {
    property var hide

    id: runnerWindow
    hideOnWindowDeactivate: hide
    visible: false
    property bool canConfigure: true

    location: PlasmaCore.Types.Floating
    
    mainItem: Item {
        width: childrenRect.width
        height: childrenRect.height - 5
        RunCommand { 
            id: krunner
            width: units.gridUnit * 28

            onClosed: {
                runnerWindow.visible = false;
                krunner.query = "";
                krunner.runner = "";
                krunner.showHistory = false;
            }

            onQueryFieldFocused: {
                krunner.showHistory = false;
            }
        }
    }

    onVisibleChanged: {
        if (runnerWindow.visible) {
            krunner.showHistory = false;
            krunner.activateFocus();
        }
    }

    function displayConfiguration() {
        ApplicationLauncher.launchPlasmasearchSettings();
    }
}
