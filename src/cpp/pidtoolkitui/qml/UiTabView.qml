import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2

TabView {
  id: uiDialogTabView
  width: parent.width
  height: parent.height

  //function prepare() {
  //  uiTabMaximum.prepare()
  //  return uiTabPrecision.prepare();
  //}

  //function resetSignalling() {
  //  uiTabMaximum.setEnableSignalling(false);
  //  uiTabPrecision.setEnableSignalling(false);
  //}


  UiTab {
    id: uiTabMaximum 
  }
}
