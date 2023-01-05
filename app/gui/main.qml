import QtQuick
import QtQuick.Controls 6.3

Window {
    id: root
    visible: true

    Column {
        id: column
        x: 90
        y: 52
        width: 200
        height: 400

        Text {
            text: "Hello, world!"
        }

        Grid {
            id: grid
            width: 400
            height: 400
            rows: 4
            columns: 3

            Button {
                id: btn7
                text: qsTr("7")
            }

            Button {
                id: btn8
                text: qsTr("8")
            }

            Button {
                id: btn9
                text: qsTr("9")
            }

            Button {
                id: btn4
                text: qsTr("4")
            }

            Button {
                id: btn5
                text: qsTr("5")
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
