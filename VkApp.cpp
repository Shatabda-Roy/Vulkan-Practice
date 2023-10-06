#include "VkApp.h"
void apparatus::RApp::run()
{
    while(!_window.shouldClose()) {
        glfwPollEvents();
    }
}
