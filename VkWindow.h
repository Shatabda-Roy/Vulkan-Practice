#pragma once
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <string>

namespace app{
class Window {
public:
    Window(int w,int h,std::string name);
    ~Window();

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    bool shouldClose() {return glfwWindowShouldClose(m_window);}
private:
    void InitWindow();
    const int m_width;
    const int m_height;
    std::string m_windowName;
    GLFWwindow* m_window;
};
} // namespace app
