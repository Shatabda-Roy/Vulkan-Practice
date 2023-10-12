#define VK_USE_PLATFORM_WIN32_KHR
#include "vulkan/vulkan.h"
#include "appWnd.h"
#include <stdexcept>
#include <vector>
#include <string>
namespace apparatus
{
    class InitVulkan {
    public:
        InitVulkan(HWND hWnd,HINSTANCE hInstance);
        ~InitVulkan();

    private:
        VkResult CreateInstance();
        VkResult CreatePhysicalDevice();
        VkResult CreateLogicalDevice();
        VkResult CreateSurface();
        VkResult CreateSwapChain();
        void DeviceQueues();
        VkResult CreateCommands();
        VkResult CreateFramebuffer();
        
        VkInstance m_instance;        
        uint32_t m_queueFamilyCount;
        uint32_t m_extensionCount;
        uint32_t m_physicalDeviceCount;
        std::vector<VkExtensionProperties> m_allExtensions;
        std::vector<VkQueueFamilyProperties> m_familyProperties;
        VkPhysicalDevice m_physicalDevice;
        VkPhysicalDeviceMemoryProperties m_PDMemoryProperties;
        
        VkDevice m_device;
        VkSurfaceKHR m_surface;
        HWND m_hWnd;
        HINSTANCE m_hInstance;
        VkSwapchainKHR m_swapChain;
        uint32_t m_width;
        uint32_t m_height;
        // Store a pointer to the created image.
        VkImage* m_presentImages;
        VkImageView* m_presentImageViews;

        VkCommandBuffer m_drawCmdBuffer;
        VkQueue m_presentQueue;

        VkFramebuffer* m_frameBuffers = NULL;
        VkRenderPass m_renderPass = NULL;
        
    };
} // namespace apparatus
