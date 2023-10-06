#include "appDevice.h"

apparatus::InitVulkan::InitVulkan()
{
    CreateInstance();
}

apparatus::InitVulkan::~InitVulkan()
{
    vkDestroyInstance(instance,nullptr);
}

void apparatus::InitVulkan::CreateInstance()
{
    /* Allows tools and drivers to make decisions about
     how to treat your program without needing to guess*/
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "Apparatus";
    appInfo.applicationVersion = VK_MAKE_API_VERSION(0,1,0,0);
    appInfo.pEngineName = nullptr;
    appInfo.engineVersion = NULL;
    appInfo.apiVersion = VK_MAKE_API_VERSION(0,1,0,0);

    VkInstanceCreateInfo createInfo{};
    /* Structure Tag for validation purposes */
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    /* Allows parameters to be extended */
    createInfo.pNext = nullptr;
    createInfo.pApplicationInfo = &appInfo;
    /* Layers are used to intercept the Vulkan API and provide logging, Profiling, Debugging,
     and other additional features*/
    createInfo.ppEnabledLayerNames = nullptr;
    createInfo.ppEnabledExtensionNames = nullptr;
    
    if(vkCreateInstance(&createInfo,nullptr,&instance) != VK_SUCCESS) {
        throw std::runtime_error("Couldn't create an instance.");
    }
}

void apparatus::InitVulkan::CreatePhysicalDevice()
{
    
}
