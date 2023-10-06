#include "vulkan/vulkan.h"
#include <iostream>
#include <stdexcept>
namespace apparatus
{
    class InitVulkan {
    public:
        InitVulkan();
        ~InitVulkan();
    private:
        void CreateInstance();
        void CreatePhysicalDevice();
        VkInstance instance;
    };
} // namespace apparatus
