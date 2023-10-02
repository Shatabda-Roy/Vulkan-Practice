#include "VkApp.h"

void app::FirstApp::run()
{
        while(!_window.shouldClose()) {
        glfwPollEvents();
    }
}
