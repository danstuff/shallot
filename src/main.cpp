#include "global.h"
#include "controller.h"

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.yostlabs.shallot");

    Gtk::Window window;

    Controller controller;

    window.add(controller);

    return app->run(window);
}

