project('Vulkan Tutorial','cpp')
src = ['VkWindow.cpp','VkPipeline.cpp','VkApp.cpp','main.cpp']
libdir1 = 'A:\Work\DEVELOPMENT\Vulkan-Practice\lib'
libdir2 = 'A:\Work\DEVELOPMENT\VulkanSDK\Lib'
inclib1 = 'glfw3'
inclib2 = 'vulkan-1'
dep = declare_dependency(
    include_directories : include_directories('include'),
    version : '1.0'
)
executable('VulkanApp', sources  : src, dependencies : dep )