import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2

TabView {
  width: parent.width
  height: parent.height

  function prepare() {
    blackBoxTabTimersOther.prepare()
    return blackBoxTabStartRange.prepare();
  }

  function resetSignalling() {
    blackBoxTabStartRange.setEnableSignalling(false);
    blackBoxTabTimersOther.setEnableSignalling(false);
  }


  BlackBoxTabStartRange {
    id: blackBoxTabStartRange 
  }

  BlackBoxTabTimersOther {
    id: blackBoxTabTimersOther 
  }
}
