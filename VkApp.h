#include "VkWindow.h"
#include "VkPipeline.h"
#include "VkDevice.h"
namespace apparatus {
class RApp
{
public:
    static constexpr int _WIDTH = 640;
    static constexpr int _HEIGHT = 480;
    void run();
private:
    RWindow _window{_WIDTH,_HEIGHT,"Vulkan"};
    RDevice _device{_window.m_window};
    RPipeline _pipeline{"shaders/shade.vert.spv","shaders/shade.frag.spv"};
};
} // namespace app
