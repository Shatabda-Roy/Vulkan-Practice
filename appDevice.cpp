#include "appDevice.h"

apparatus::InitVulkan::InitVulkan(HWND hWnd,HINSTANCE hInstance) : m_hWnd{hWnd}, m_hInstance{hInstance}
{
    try {
        CreateInstance();
    }
    catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        abort();
    }
    try {
        CreatePhysicalDevice();
    }
    catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        abort();
    }
    try {
        DeviceQueues();
    }
    catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        abort();
    }
    try {
        CreateLogicalDevice();
    }
    catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        abort();
    }
    try {
        CreateSurface();
    }
    catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        abort();
    }
    try {
        CreateSwapChain();
    }
    catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        abort();
    }

    try
    {
        CreateCommandBuffer();        
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        abort();
    }
    try
    {
        CreateFramebuffer();        
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        abort();
    }
    
}

apparatus::InitVulkan::~InitVulkan()
{
    vkDestroyInstance(m_instance,nullptr);
}



VkResult apparatus::InitVulkan::CreateInstance()
{
    VkResult result = VK_SUCCESS;
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
    
    uint32_t instLayerCount = NULL;
    result = vkEnumerateInstanceLayerProperties(&instLayerCount,nullptr);
    std::vector<VkLayerProperties> instLayerList(instLayerCount);
    result = vkEnumerateInstanceLayerProperties(&instLayerCount,&instLayerList[0]);
    const char* layers[] = {instLayerList[0].layerName};

    uint32_t instExtCount = NULL;
    result = vkEnumerateInstanceExtensionProperties(nullptr,&instExtCount,nullptr);
    std::vector<VkExtensionProperties> instExtList(instExtCount);
    result = vkEnumerateInstanceExtensionProperties(nullptr,&instExtCount,&instExtList[0]);
    const char* extensions[] = {instExtList[8].extensionName,instExtList[10].extensionName};

    VkInstanceCreateInfo createInfo{};
    /* Structure Tag for validation purposes */
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    /* Allows parameters to be extended */
    createInfo.pNext = nullptr;
    createInfo.pApplicationInfo = &appInfo;
    /* Layers are used to intercept the Vulkan API and provide logging, Profiling, Debugging,
     and other additional features*/
    createInfo.enabledLayerCount = 1;
    createInfo.ppEnabledLayerNames = layers;
    createInfo.enabledExtensionCount = 2;
    createInfo.ppEnabledExtensionNames = extensions;
    result = vkCreateInstance(&createInfo,nullptr,&m_instance);
    if( result != VK_SUCCESS) {
        throw std::runtime_error("Couldn't create an instance.");
    }
    return result;
}

VkResult apparatus::InitVulkan::CreatePhysicalDevice()
{
    VkResult result = VK_SUCCESS;
    
    result = vkEnumeratePhysicalDevices(m_instance,&m_physicalDeviceCount,nullptr);
    std::vector<VkPhysicalDevice> allPhysicalDevices(m_physicalDeviceCount);
    result = vkEnumeratePhysicalDevices(m_instance,&m_physicalDeviceCount,&allPhysicalDevices[0]);

    if(result != VK_SUCCESS) {
        throw std::runtime_error("Couldn't Create a Physical Device");
    }
    m_physicalDevice = allPhysicalDevices[0];

    return result;
}

VkResult apparatus::InitVulkan::CreateLogicalDevice()
{
    VkResult result = VK_SUCCESS;

    /* Mandatory for VkDeviceCreateInfo */
    VkDeviceQueueCreateInfo queueInfo{};

    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.queueFamilyIndex = 0;
    queueInfo.queueCount = 1;
    float queuePriorities[] = {1};
    queueInfo.pQueuePriorities = queuePriorities;

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(m_physicalDevice,&deviceFeatures);

    uint32_t deviceExtCount = NULL;
    vkEnumerateDeviceExtensionProperties(m_physicalDevice,nullptr,&deviceExtCount,nullptr);
    std::vector<VkExtensionProperties> deviceExtList(deviceExtCount);
    vkEnumerateDeviceExtensionProperties(m_physicalDevice,nullptr,&deviceExtCount,&deviceExtList[0]);
    const char* deviceExtensions[] = {deviceExtList[48].extensionName};
    
    VkDeviceCreateInfo deviceInfo{};
    deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.pNext = nullptr;
    deviceInfo.queueCreateInfoCount = 1;
    deviceInfo.pQueueCreateInfos = &queueInfo;
    
    const char* layers[] = {"VK_LAYER_NV_optimus"};
    
    deviceInfo.enabledExtensionCount = 1;
    deviceInfo.ppEnabledExtensionNames = deviceExtensions;
    deviceInfo.enabledLayerCount = 1;
    deviceInfo.ppEnabledLayerNames = layers;

    deviceFeatures.shaderClipDistance = VK_TRUE;
    deviceInfo.pEnabledFeatures = &deviceFeatures;

    result = vkCreateDevice(m_physicalDevice,&deviceInfo,nullptr,&g_device);
    if(result != VK_SUCCESS) {
        throw std::runtime_error("Couldn't create a Logical Device");
    }

    return result;
}

VkResult apparatus::InitVulkan::CreateSurface()
{
    VkResult result = VK_SUCCESS;
    
    VkWin32SurfaceCreateInfoKHR surfaceInfo{};
    surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surfaceInfo.hwnd = m_hWnd;
    surfaceInfo.hinstance = m_hInstance;
    surfaceInfo.pNext = nullptr;

    result = vkCreateWin32SurfaceKHR(m_instance,&surfaceInfo,nullptr,&g_surface);
    if(result != VK_SUCCESS) {
        throw std::runtime_error("Couldn't create a Surface");
    }
    return VkResult();
}

VkResult apparatus::InitVulkan::CreateSwapChain()
{
    VkResult result = VK_SUCCESS;

    VkSurfaceCapabilitiesKHR surfCapabilities{};
    result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice,g_surface,&surfCapabilities);

    VkExtent2D surfaceResolution = surfCapabilities.currentExtent;
    g_width = surfaceResolution.width;
    g_height = surfaceResolution.height;

    VkSwapchainCreateInfoKHR swapChainInfo{};
    swapChainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapChainInfo.surface = g_surface;
    swapChainInfo.minImageCount = surfCapabilities.minImageCount;
    swapChainInfo.imageFormat = VK_FORMAT_R8G8B8A8_UNORM;
    swapChainInfo.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    swapChainInfo.imageExtent = surfCapabilities.currentExtent;
    swapChainInfo.imageArrayLayers = 1;
    swapChainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapChainInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    swapChainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapChainInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
    swapChainInfo.clipped = true;
    swapChainInfo.oldSwapchain = NULL;

    result = vkCreateSwapchainKHR(g_device,&swapChainInfo,nullptr,&g_swapChain);
    if(result != VK_SUCCESS) {
        throw std::runtime_error("Couldn't create Swapchain");
    }

    uint32_t imageCount = 0;
    result = vkGetSwapchainImagesKHR(g_device,g_swapChain,&imageCount,NULL);
    assert(imageCount == 2);
    m_presentImages = new VkImage[2];
    result = vkGetSwapchainImagesKHR(g_device,g_swapChain,&imageCount,m_presentImages);
    
    // handle for our images.
    m_presentImageViews = new VkImageView[2];

    for(uint32_t i = 0; i < 2; i++) {
        // create image view for our swapchain.
        VkImageViewCreateInfo viewCreateInfo{};
        viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewCreateInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_R;
        viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_G;
        viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_B;
        viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_A;
        viewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewCreateInfo.subresourceRange.baseMipLevel = 0;
        viewCreateInfo.subresourceRange.levelCount = 1;
        viewCreateInfo.subresourceRange.baseArrayLayer = 0;
        viewCreateInfo.subresourceRange.layerCount = 1;
        viewCreateInfo.image = m_presentImages[i];

        result = vkCreateImageView(g_device,&viewCreateInfo,nullptr,&m_presentImageViews[i]);
    }
    return result;
}

void apparatus::InitVulkan::DeviceQueues()
{
    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice,&m_queueFamilyCount,nullptr);
    m_familyProperties.resize(m_queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice,&m_queueFamilyCount,&m_familyProperties[0]);

    // for(uint32_t i = 0; i < m_physicalDeviceCount; i++) {
    //     for(uint32_t j = 0; j < m_queueFamilyCount; j++) {
    //         std::cout << "Count of Queues : " << m_familyProperties[j].queueCount << '\n';
    //         std::cout << "Supported opertation on this queue" << '\n';
    //         if(m_familyProperties[j].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
    //             std::cout << "Graphics" << '\n';
    //         }
    //         if(m_familyProperties[j].queueFlags & VK_QUEUE_COMPUTE_BIT) {
    //             std::cout << "Compute" << '\n';
    //         }
    //         if(m_familyProperties[j].queueFlags & VK_QUEUE_TRANSFER_BIT) {
    //             std::cout << "Transfer" << '\n';
    //         }
    //         if(m_familyProperties[j].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) {
    //             std::cout << "Sparse Binding" << '\n';
    //         }
    //         std::cout << '\n';
    //     }
    // }
}

VkResult apparatus::InitVulkan::CreateCommandBuffer()
{
    VkResult result = VK_SUCCESS;
    // Get the device queue on which we will be submitting our work.
    vkGetDeviceQueue(g_device,0,0,&g_presentQueue);

    VkCommandPoolCreateInfo cmdPoolInfo{};
    cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    cmdPoolInfo.queueFamilyIndex = 0;
    
    // store query result.
    VkCommandPool commandPool;
    result = vkCreateCommandPool(g_device,&cmdPoolInfo,nullptr,&commandPool);

    VkCommandBufferAllocateInfo cmdBufferAllocInfo{};
    cmdBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmdBufferAllocInfo.commandPool = commandPool;
    cmdBufferAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmdBufferAllocInfo.commandBufferCount = 1;
    result = vkAllocateCommandBuffers(g_device,&cmdBufferAllocInfo,&g_drawCmdBuffer);
    if(result != VK_SUCCESS) {
        throw std::runtime_error("Couldn't create a Command Buffer");
    }
    return result;
}

VkResult apparatus::InitVulkan::CreateFramebuffer()
{
    VkResult result = VK_SUCCESS;
    VkAttachmentDescription pass[1] = {};
    pass[0].format = VK_FORMAT_R8G8B8A8_UNORM;
    pass[0].samples = VK_SAMPLE_COUNT_1_BIT;
    pass[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    pass[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    pass[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    pass[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    pass[0].initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    pass[0].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference attachmentRef{};
    attachmentRef.attachment = 0;
    attachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    
    // Create the main subpass of our renderpass.
    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &attachmentRef;
    subpass.pDepthStencilAttachment = nullptr;
    // create our main renderpass.
    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = pass;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    result = vkCreateRenderPass(g_device,&renderPassInfo,nullptr,&g_renderPass);

    // Create our framebuffer.
    VkImageView frameBufferAttachments[1] = {0};
    VkFramebufferCreateInfo frameBufferInfo{};
    frameBufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO;
    frameBufferInfo.renderPass = g_renderPass;
    frameBufferInfo.attachmentCount = 1;
    frameBufferInfo.pAttachments = frameBufferAttachments;
    frameBufferInfo.width = g_width;
    frameBufferInfo.height = g_height;
    frameBufferInfo.layers = 1;

    // Create a framebuffer per swap chain imageView.
    g_frameBuffers = new VkFramebuffer[2];
    for(uint32_t i = 0; i < 2; i++) {
        frameBufferAttachments[0] = m_presentImageViews[ i ];
        result = vkCreateFramebuffer(g_device,&frameBufferInfo,nullptr,&g_frameBuffers[i]);

    }
    if(result != VK_SUCCESS) {
        throw std::runtime_error("Couldn't create a framebuffer");
    }
    return result;
}

VkResult apparatus::InitVulkan::render() {
    VkResult result;
    uint32_t nextImageIdx;

    result = vkAcquireNextImageKHR(g_device,g_swapChain,UINT64_MAX,VK_NULL_HANDLE,VK_NULL_HANDLE,&nextImageIdx);
    
    // buffer commands.
    VkCommandBufferBeginInfo cmdBeginInfo={};
    cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    // start recoding.
    result = vkBeginCommandBuffer(g_drawCmdBuffer,&cmdBeginInfo);
    {
        /* Temporary float that oscilates between 0 and 1, to gradually change color on the screen*/
        static float aa = 0;
        // slowly incrememnt.
        aa += 0.001f;
        // when value reaches 1 reset to 0.
        if ( aa >= 1) {
            aa = 0;
        }
        // activate render pass.
        VkClearValue clearValue[] = {
            {1,aa,1,1}, {1,1}
        };
        // define render pass structure
        VkRenderPassBeginInfo rendPassBeginInfo{};
        rendPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        rendPassBeginInfo.renderPass = g_renderPass;
        /* Which image to draw upon ( use the ID from the swap-chain look up we did at the start)*/
        rendPassBeginInfo.framebuffer = g_frameBuffers[nextImageIdx];
        VkOffset2D a = {0,0};
        VkExtent2D b = {g_width,g_height};
        VkRect2D _rect = {a,b};
        rendPassBeginInfo.renderArea = _rect;
        rendPassBeginInfo.clearValueCount = 2;
        rendPassBeginInfo.pClearValues = clearValue;
        // command to start a render pass
        vkCmdBeginRenderPass(g_drawCmdBuffer,&rendPassBeginInfo,VK_SUBPASS_CONTENTS_INLINE);
        
        /* call draw commands, to present geometry data/triangles.*/
        {
            struct vertex {
                float x,y,z,w; // position.
                float r,g,b;   // color.
            };
            VkBufferCreateInfo vertexInputBufferInfo{};
            vertexInputBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            vertexInputBufferInfo.size = sizeof(vertex) * 3;
            // what the buffer will hold.
            vertexInputBufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
            // sharing/access level.
            vertexInputBufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

            // create the buffer.
            VkResult result = vkCreateBuffer(g_device,&vertexInputBufferInfo,nullptr,&m_vertexInputBuffer);
            if(result != VK_SUCCESS) {
                throw std::runtime_error("Couldn't Create a vertex buffer.");
            }
            /* allocate memory for buffers :
                Get the memory information - type of memory required.
                for our vertex buffer (we can't put the data just anywere)*/

            VkMemoryRequirements vertBufferMemReq{};
            vkGetBufferMemoryRequirements(g_device,m_vertexInputBuffer,&vertBufferMemReq);
            VkMemoryAllocateInfo bufferAllocateInfo{};
            bufferAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            bufferAllocateInfo.allocationSize = vertBufferMemReq.size;
            bufferAllocateInfo.pNext = nullptr;
            // the memory our vertex needs.
            uint32_t vertexmemoryTypeBits = vertBufferMemReq.memoryTypeBits;
            VkMemoryPropertyFlags vertexDesiredMemoryFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
            VkPhysicalDeviceMemoryProperties memoryProperties;
            vkGetPhysicalDeviceMemoryProperties(m_physicalDevice,&memoryProperties);
            /* Check each of the memory types and store the one we want. */
            for (uint32_t i = 0; i < VK_MAX_MEMORY_TYPES; i++)
            {
                VkMemoryType memoryType = memoryProperties.memoryTypes[i];
                // is this the memroy type we are looking for?
                if(memoryType.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT){
                    // Save location
                    bufferAllocateInfo.memoryTypeIndex = i;
                    // exit loop.
                }
            }
            VkDeviceMemory vertexBufferMemory;
            result = vkAllocateMemory(g_device,&bufferAllocateInfo,nullptr,&vertexBufferMemory);
            if(result != VK_SUCCESS) {
                throw std::runtime_error("Failed to allocate buffer mmeory");
            }
            // temporary pointer
            void *mapped;
            /* lock memor and set the temp pointer to point to the memory we want to write to*/
            result = vkMapMemory(g_device,vertexBufferMemory,0,VK_WHOLE_SIZE,0,&mapped);
            if(result != VK_SUCCESS) {
                throw std::runtime_error("Failed to map buffer memory.");
            }
            // cast our temp pointer to a vertex type.
            vertex *triangle = (vertex*) mapped;
            /* Define our triangle vertices facing down the z-axis.*/
            vertex v1 =
            {
                 -1.0f, -1.0f, 0.0f, 1.0f, // position
                0.0f, 1.0f, 0.0f           // color
            };
            vertex v2 =
            {
                 1.0f, -1.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f
            };
            vertex v3 =
            {
                 0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f
            };
            /* set triangle vertices on our locked allocated buffer. */
            triangle[0] = v1;
            triangle[1] = v2;
            triangle[2] = v3;
            vkUnmapMemory(g_device,vertexBufferMemory);
            result = vkBindBufferMemory(g_device,m_vertexInputBuffer,vertexBufferMemory,0);
        }
        vkCmdEndRenderPass(g_drawCmdBuffer);
    }
    // end recoding commands.
    result = vkEndCommandBuffer(g_drawCmdBuffer);
    /*prsent: 
        create a fence to inform us when the gpu has finished
        processing our commands.                             */
    
    // setup the type of fence.
    VkFence renderFence;
    VkFenceCreateInfo fenceCreateInfo{};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    result = vkCreateFence(g_device,&fenceCreateInfo,nullptr,&renderFence);
    
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount = 0;
    submitInfo.pWaitSemaphores = VK_NULL_HANDLE;
    submitInfo.pWaitDstStageMask = NULL;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &g_drawCmdBuffer;
    submitInfo.signalSemaphoreCount = 0;
    submitInfo.pSignalSemaphores = VK_NULL_HANDLE;

    // submit the command queue (notice, we also pass the fence, to let us know the gpu has finished)
    result = vkQueueSubmit(g_presentQueue,1,&submitInfo,renderFence);
    
    // wait until the gpu has finished processing the commands.
    result = vkWaitForFences(g_device,1,&renderFence,VK_TRUE,UINT64_MAX);
    vkDestroyFence(g_device,renderFence,NULL);

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext = NULL;
    presentInfo.waitSemaphoreCount = 0;
    presentInfo.pWaitSemaphores = VK_NULL_HANDLE;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &g_swapChain;
    presentInfo.pImageIndices = &nextImageIdx;
    presentInfo.pResults = NULL;
    result = vkQueuePresentKHR(g_presentQueue,&presentInfo);
    return result;
}