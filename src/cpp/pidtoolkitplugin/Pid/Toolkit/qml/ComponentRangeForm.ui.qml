import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

RowLayout {
    DoubleValidator {
        id: doubleValidator
    }

    RowLayout {
        Label {
            color: Style.labelTextColor
            font.pointSize: Style.labelFontPointSize
            text: qsTr("From: ")
        }
        TextField {
            id: maximumTextField
            validator: doubleValidator
            Layout.preferredWidth: Style.rangeMaximumWidth
            font.pointSize: Style.inputFontPointSize
        }
    }

    RangeSlider {
        id: rangeSlider
    }

    RowLayout {
        Label {
            id: firstIndicator
            horizontalAlignment: Text.AlignRight
            Layout.preferredWidth: Style.rangeIndicatorWidth
            Layout.alignment: Qt.AlignRight
            color: Style.indicatorsTextColor
        }
        Label {
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            color: Style.labelTextColor
            text: qsTr(" - ")
        }
        Label {
            id: secondIndicator
            horizontalAlignment: Text.AlignLeft
            Layout.preferredWidth: Style.rangeIndicatorWidth
            Layout.alignment: Qt.AlignLeft
            color: Style.indicatorsTextColor
        }
    }
}
