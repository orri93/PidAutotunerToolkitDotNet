pragma Singleton
import QtQuick 2.12

Item {

  readonly property string titleText: qsTr("PID Toolkit")

  readonly property int mainWindowWidth: 1600
  readonly property int mainWindowHeight: 900

  readonly property color mainWindowColor: "#404040"

  readonly property color dialogColor: "#404040"
  readonly property color titleTextColor: "floralwhite"
  readonly property color labelTextColor: "white"
  readonly property color inputTextColor: "beige"
  readonly property color informationTextColor: "burlywood"
  readonly property color errorTextColor: "red"
  readonly property color groupTextColor: "gray"
  readonly property color unitTextColor: "cornsilk"
  readonly property color indicatorsTextColor: "indigo"

  readonly property color dialogGroupTextColor: "navy"
  readonly property color dialogLabelTextColor: "midnightblue"
  readonly property color dialogInputTextColor: "darkslateblue"
  readonly property color dialogIndicatorsTextColor: "indigo"

  readonly property color statusConnectionIndicator: "green"
  readonly property color statusActivityIndicator: "blue"

  readonly property int titleFontPointSize: 18
  readonly property int labelFontPointSize:  8
  readonly property int inputFontPointSize: 10
  readonly property int informationFontPointSize: 10
  readonly property int unitFontPointSize:  8

  readonly property int fileDialogHeight: 600
  readonly property int fileDialogWidth: 800

  readonly property double panelMargin: 10.0
  readonly property double panelItemMargin: 4.0
  readonly property double labelLeftMargin: 2.0
  readonly property double inputTextLeftMargin: 5.0
  readonly property double informationTextLeftMargin: 5.0

  readonly property real groupTitleLocation: 10.0

  readonly property real rangeIndicatorWidth: 40.0
  readonly property real rangeMaximumWidth: 20.0

  readonly property real preferredWidth: 80.0

  readonly property real panelWidth: 390.0
  readonly property real preferredPanelItemWidth: 170.0
  readonly property real preferredPanelDoubleItemWidth: 353.0
  readonly property real groupWidth: 380.0

  readonly property real gaugeWidth: 93.0

  readonly property real preferredButtonSize: 52.0

  readonly property real preferredNumberInputWidth: 60.0
  readonly property real preferredRangeInputWidth: 60.0

  readonly property real preferredSeparatorInputWidth: 40.0

  readonly property real fileTextFieldWidth: 320.0

  readonly property int quitDelay: 1000
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
