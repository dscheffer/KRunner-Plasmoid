/*
 *   Original work Copyright 2014 Marco Martin <mart@kde.org>
 *   Modified work Copyright 2018 Dennis Scheffer.
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

import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Window 2.1
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.milou 0.1 as Milou

import dscheffer.krunnerplasmoidplugin 0.1

ColumnLayout {
    id: root
    property string query
    property string runner
    property bool showHistory: false
    property bool toggleHistory: true

    signal closed()

    LayoutMirroring.enabled: Qt.application.layoutDirection === Qt.RightToLeft
    LayoutMirroring.childrenInherit: true
    
    onQueryChanged: {
        queryField.text = query;
    }

    function activateFocus() {
        queryField.forceActiveFocus();
    }

    function activateListViewFocus() {
        listView.forceActiveFocus();
        listView.currentIndex = -1
    }

    RowLayout {
        id: searchRow
        Layout.alignment: Qt.AlignTop

        PlasmaComponents.Label {
            text: "KRunner"
            horizontalAlignment: Text.AlignRight

            Layout.minimumWidth: units.gridUnit * 9
        }
        PlasmaComponents.TextField {
            id: queryField
            property bool allowCompletion: false

            clearButtonShown: true
            //Layout.minimumWidth: units.gridUnit * 21
            Layout.fillWidth: true
            

            activeFocusOnPress: true
            placeholderText: results.runnerName ? i18ndc("plasma_lookandfeel_org.kde.lookandfeel",
                                                         "Textfield placeholder text, query specific KRunner",
                                                         "Search '%1'...", results.runnerName)
                                                : i18ndc("plasma_lookandfeel_org.kde.lookandfeel",
                                                         "Textfield placeholder text", "Search...")

            onTextChanged: {
                root.query = queryField.text
                if (allowCompletion && length > 0) {
                    var history = History.history

                    // search the first item in the history rather than the shortest matching one
                    // this way more recently used entries take precedence over older ones (Bug 358985)
                    for (var i = 0, j = history.length; i < j; ++i) {
                        var item = history[i]

                        if (item.toLowerCase().indexOf(text.toLowerCase()) === 0) {
                            var oldText = text
                            text = text + item.substr(oldText.length)
                            select(text.length, oldText.length)
                            break
                        }
                    }
                }
            }
            Keys.onPressed: allowCompletion = (event.key !== Qt.Key_Backspace && event.key !== Qt.Key_Delete)
            Keys.onUpPressed: {
                if (length === 0) {
                    root.showHistory = true;
                    listView.forceActiveFocus();
                } else if (results.count > 0) {
                    results.forceActiveFocus();
                    results.decrementCurrentIndex();
                }
            }
            Keys.onDownPressed: {
                if (length === 0) {
                    root.showHistory = true;
                    listView.forceActiveFocus();
                } else if (results.count > 0) {
                    results.forceActiveFocus();
                    results.incrementCurrentIndex();
                }
            }
            Keys.onEnterPressed: results.runCurrentIndex(event)

            Keys.onReturnPressed: results.runCurrentIndex(event)

            Keys.onEscapePressed: root.closed()

            PlasmaCore.SvgItem {
                anchors {
                    right: parent.right
                    rightMargin: 6 // from PlasmaStyle TextFieldStyle
                    verticalCenter: parent.verticalCenter
                }
                // match clear button
                width: Math.max(parent.height * 0.8, units.iconSizes.small)
                height: width
                svg: PlasmaCore.Svg {
                    imagePath: "widgets/arrows"
                    colorGroup: PlasmaCore.Theme.ButtonColorGroup
                }
                elementId: "down-arrow"
                visible: toggleHistory ? queryField.length === 0 : false

                MouseArea {
                    anchors.fill: parent
                    onPressed: {
                        root.showHistory = !root.showHistory
                        console.log(History.history[0]);
                        console.log(root.query.length === 0 && History.history.length > 0);
                        if (root.showHistory) {
                            listView.forceActiveFocus(); // is the history list
                        } else {
                            queryField.forceActiveFocus();
                        }
                    }
                }
            }
        }
    }

    PlasmaExtras.ScrollArea {
        Layout.alignment: Qt.AlignTop
        visible: results.count > 0
        enabled: visible
        Layout.fillWidth: true
        Layout.preferredHeight: Math.min(Screen.height, results.contentHeight + 5)

        anchors.top: searchRow.bottom

        Milou.ResultsView {
            id: results
            queryString: root.query
            runner: root.runner

            anchors.topMargin: 5

            Keys.onPressed: {
                if (event.text != "") {
                    queryField.text += event.text;
                    queryField.focus = true;
                }
            }

            onActivated: {
                History.addToHistory(results.currentItem.theModel.display);
                root.closed();
                root.query = "";
                queryField.forceActiveFocus();
            }

            onUpdateQueryString: {
                queryField.text = text
                queryField.cursorPosition = cursorPosition
            }
        }
    }

    PlasmaExtras.ScrollArea {
        Layout.alignment: Qt.AlignTop
        Layout.fillWidth: true
        visible: root.query.length === 0 && History.history.length > 0
        // don't accept keyboard input when not visible so the keys propagate to the other list
        enabled: visible
        Layout.preferredHeight: Math.min(Screen.height, listView.contentHeight + 5)

        anchors.top: searchRow.bottom

        ListView {
            id: listView // needs this id so the delegate can access it
            keyNavigationWraps: true
            highlight: PlasmaComponents.Highlight {}
            highlightMoveDuration: 0
            activeFocusOnTab: true

            anchors.topMargin: 5

            model: root.showHistory ? History.history : []
            delegate: Milou.ResultDelegate {
                id: resultDelegate
                width: listView.width
                typeText: index === 0 ? i18nd("plasma_lookandfeel_org.kde.lookandfeel", "Recent Results") : ""
                /*additionalActions: [{
                    icon: "list-remove",
                    text: i18nd("plasma_lookandfeel_org.kde.lookandfeel", "Remove"),
                    onTriggered: History.removeFromHistory(index)
                }]*/
                Accessible.description: i18n("in category recent queries")
            }

            onActiveFocusChanged: {
                if (!activeFocus && currentIndex == listView.count-1) {
                    currentIndex = 0;
                }
            }
            Keys.onReturnPressed: runCurrentIndex()
            Keys.onEnterPressed: runCurrentIndex()
            
            Keys.onTabPressed: {
                if (currentIndex == listView.count-1) {
                    listView.nextItemInFocusChain(true).forceActiveFocus();
                } else {
                    incrementCurrentIndex()
                }
            }
            Keys.onBacktabPressed: {
                if (currentIndex == 0) {
                    listView.nextItemInFocusChain(false).forceActiveFocus();
                } else {
                    decrementCurrentIndex()
                }
            }
            Keys.onPressed: {
                if (event.text != "") {
                    queryField.text += event.text;
                    queryField.focus = true;
                }
            }
  
            Keys.onUpPressed: decrementCurrentIndex()
            Keys.onDownPressed: incrementCurrentIndex()

            function runCurrentIndex() {
                var entry = History.history[currentIndex]
                if (entry) {
                    queryField.text = entry
                    queryField.forceActiveFocus();
                }
            }
        }

    }
}
