#include "Window.h"

int main() {

    Window winMain;

    while (winMain.Is_Open()) {

        winMain.Poll_Events();

        if (winMain.Mouse_Moved()) {
            winMain.Update();
        }
    }

    return 0;
}