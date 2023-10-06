#include "VkWindow.h"
#include <iostream>
#include <assert.h>
#include <exception>
#include <stdexcept>
#include <vector>
namespace apparatus{

    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    class RDevice{
    public:
        RDevice(GLFWwindow* window);
        ~RDevice();
    private:
        static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
        {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr) {
                func(instance, debugMessenger, pAllocator);
            }
        }
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();
        
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void setupDebugMessenger();
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
        void createLogicalDevice();
        void createSurface();
        GLFWwindow* m_window;
        
        void InitVulkan();
        
        VkInstance instance;
        VkSurfaceKHR surface;
        
        VkDebugUtilsMessengerEXT debugMessenger;
        
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
    };
}