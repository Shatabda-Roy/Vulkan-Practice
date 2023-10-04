#include "VkApp.h"
void apparatus::FirstApp::run()
{
    while(!_window.shouldClose()) {
        glfwPollEvents();
    }
}
