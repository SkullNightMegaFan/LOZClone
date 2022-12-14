import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
​
​
ApplicationWindow {
    visible: true
    width: 800
    height: 500
    title: "Converter"
​
    property QtObject converter
    property string inputFile
​
​
    AddComp { id: addcomp }
​
    StackView {
        id: stack
        anchors.fill: parent
        initialItem: addcomp
    }
​
​
}