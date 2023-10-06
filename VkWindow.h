#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <string>

namespace apparatus{
class RWindow {
public:
    RWindow(int w,int h,std::string name);
    ~RWindow();

    RWindow(const RWindow &) = delete;
    RWindow &operator=(const RWindow &) = delete;
    GLFWwindow* m_window;

    bool shouldClose() {return glfwWindowShouldClose(m_window);}
private:
    void InitWindow();
    const int m_width;
    const int m_height;
    std::string m_windowName;
};
} // namespace app
