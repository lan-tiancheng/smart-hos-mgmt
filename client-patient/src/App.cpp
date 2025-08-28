#include "App.h"
#include "ui/LoginWindow.h"

void App::start() {
    auto* w = new LoginWindow();
    w->show();
}