#pragma once
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <string>

namespace apparatus{
class VkWindow {
public:
    VkWindow(int w,int h,std::string name);
    ~VkWindow();

    VkWindow(const VkWindow &) = delete;
    VkWindow &operator=(const VkWindow &) = delete;

    bool shouldClose() {return glfwWindowShouldClose(m_window);}
private:
    void InitWindow();
    const int m_width;
    const int m_height;
    std::string m_windowName;
    GLFWwindow* m_window;
};
} // namespace app
