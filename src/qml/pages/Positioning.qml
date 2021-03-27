/***************************************************************************
 *   Copyright (C) 2019-2021 by Stefan Kebekus                             *
 *   stefan.kebekus@gmail.com                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

import QtQml 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import enroute 1.0
import "../dialogs"
import "../items"

Page {
    id: trafficReceiverPage
    title: qsTr("Positioning")

    header: StandardHeader {}

    ScrollView {
        id: view
        clip: true
        anchors.fill: parent

        // The visibility behavior of the vertical scroll bar is a little complex.
        // The following code guarantees that the scroll bar is shown initially. If it is not used, it is faded out after half a second or so.
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: (height < contentHeight) ? ScrollBar.AlwaysOn : ScrollBar.AsNeeded

        GridLayout {
            id: gl
            columnSpacing: 30
            columns: 2

            Label { text: qsTr("Satellite Status") }
            Label {
                font.weight: Font.Bold
                text: satNav.statusAsString
                color: (satNav.status === SatNav.OK) ? "green" : "red"
                wrapMode: Text.Wrap
            }

            Label { text: qsTr("Last Fix") }
            Label { text: satNav.timestampAsString }

            Label { text: qsTr("Mode") }
            Label { text: satNav.isInFlight ? qsTr("Flight") : qsTr("Ground") }

            Label {
                font.pixelSize: Qt.application.font.pixelSize*0.5
                Layout.columnSpan: 2
            }

            Label {
                text: qsTr("Horizontal")
                font.weight: Font.Bold
                Layout.columnSpan: 2
            }

            Label { text: qsTr("Latitude") }
            Label { text: satNav.latitudeAsString }

            Label { text: qsTr("Longitude") }
            Label { text: satNav.longitudeAsString }

            Label { text: qsTr("Error") }
            Label { text: satNav.positionErrorEstimate.isFinite() ? "±" + Math.round(satNav.positionErrorEstimate.toFeet()) + " ft" : "-" }

            Label { text: "VAR" }
            Label { text: satNav.VAR.isFinite() ? Math.round(satNav.VAR.toDEG()) + "°" : "-" }

            Label { text: "GS" }
            Label {
                text: {
                    if (!satNav.GS.isFinite())
                        return "-"
                    return globalSettings.useMetricUnits ? Math.round(satNav.GS.toKMH()) + " km/h" : Math.round(satNav.GS.toKN()) + " kn"
                }
            }

            Label { text: "TT" }
            Label { text: satNav.TT.isFinite() ? satNav.TT.toDEG() + "°" : "-" }

            Label {
                font.pixelSize: Qt.application.font.pixelSize*0.5
                Layout.columnSpan: 2
            }

            Label {
                text: qsTr("Vertical")
                font.weight: Font.Bold
                Layout.columnSpan: 2
            }

            Label { text: "T.ALT" }
            Label { text: satNav.trueAltitude.isFinite() ? Math.round(satNav.trueAltitude.toFeet()) + " ft" : "-" }

            Label { text: "T.ALT Error" }
            Label { text: satNav.trueAltitudeErrorEstimate.isFinite() ? "±" + Math.round(satNav.trueAltitudeErrorEstimate.toFeet()) + " ft" : "-" }

            Label { text: "Pressure ALT" }
            Label { text: satNav.pressureAltitude.isFinite() ? Math.round(satNav.pressureAltitude.toFeet()) + " ft" : "-" }

            Label { text: "Vert. Speed" }
            Label { text: satNav.verticalSpeed.isFinite() ? Math.round(satNav.verticalSpeed.toMPS()) + " m/s" : "-" }

        } // GridLayout

    } // Scrollview

    LongTextDialog {
        id: trafficHelp
        standardButtons: Dialog.Ok
        anchors.centerIn: parent

        title: qsTr("Connect your traffic receiver")
        text: librarian.getStringFromRessource(":text/flarmSetup.md")
    }

}
