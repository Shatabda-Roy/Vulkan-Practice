#define VK_USE_PLATFORM_WIN32_KHR
#include "vulkan/vulkan.h"
#include "appWnd.h"
#include <stdexcept>
#include <vector>
#include <string>

#ifndef _DEBUG
#define _DEBUG
#endif

namespace apparatus
{
    class InitVulkan {
    public:
        InitVulkan(HWND hWnd,HINSTANCE hInstance);
        ~InitVulkan();
        VkDevice g_device;
        VkSurfaceKHR g_surface;
        VkFormat g_imageFormat;
        VkSwapchainKHR g_swapChain;
        VkCommandBuffer g_drawCmdBuffer;
        VkRenderPass g_renderPass;
        VkFramebuffer* g_frameBuffers;
        uint32_t g_width;
        uint32_t g_height;
        VkQueue g_presentQueue;
        VkResult render();
    private:
        VkResult CreateInstance();
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
         const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
         const VkAllocationCallbacks* pAllocator);
        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        VkResult SetupDebugMessenger();
        VkResult CreatePhysicalDevice();
        VkResult CreateLogicalDevice();
        VkResult CreateSurface();
        VkResult CreateSwapChain();
        void DeviceQueues();
        VkResult CreateCommandBuffer();
        VkResult CreateFramebuffer();
        
        VkInstance m_instance;
        VkDebugUtilsMessengerEXT m_debugMessenger; 
        uint32_t m_queueFamilyCount;
        uint32_t m_extensionCount;
        std::vector<VkExtensionProperties> m_allExtensions;
        std::vector<VkQueueFamilyProperties> m_familyProperties;
        VkPhysicalDevice m_physicalDevice;
        VkPhysicalDeviceMemoryProperties m_PDMemoryProperties;
        
        HWND m_hWnd;
        HINSTANCE m_hInstance;


        // Store a pointer to the created image.
        VkImage* m_presentImages;
        VkImageView* m_presentImageViews;
        VkBuffer m_vertexInputBuffer;
        
    };
} // namespace apparatus
