#include "VkWindow.h"
#include "VkPipeline.h"
#include "VkDevice.h"
namespace apparatus {
class FirstApp
{
public:
    static constexpr int _WIDTH = 640;
    static constexpr int _HEIGHT = 480;
    void run();
private:
    VkWindow _window{_WIDTH,_HEIGHT,"Vulkan"};
    VkDevice _device{};
    VkPipeline _pipeline{"shaders/shade.vert.spv","shaders/shade.frag.spv"};
};
} // namespace app
