#include "vulkan/vulkan.h"
#include <iostream>
#include <stdexcept>
#include <vector>
namespace apparatus
{
    class InitVulkan {
    public:
        InitVulkan();
        ~InitVulkan();
        /* As an input, it should be preinitialized with the maximum number
         of devices your application can handle*/
        uint32_t physicalDeviceCount = 2;
    private:
        void CreateInstance();
        VkResult CreatePhysicalDevice();
        void CreateQueue();
        VkInstance instance;
        
        VkPhysicalDevice physicalDevice;
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
    };
} // namespace apparatus
