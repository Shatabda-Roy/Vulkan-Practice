project('Vulkan Tutorial','cpp')
#src = ['VkWindow.cpp','VkDevice.cpp','VkPipeline.cpp','VkApp.cpp','main.cpp']
src = ['appWnd.cpp','appDevice.cpp','appMain.cpp']

libdir1 = 'A:\Work\DEVELOPMENT\Vulkan-Practice\lib'
libdir2 = 'A:\Work\DEVELOPMENT\VulkanSDK\Lib'
inclib1 = 'glfw3'
inclib2 = 'vulkan-1'
dep = declare_dependency(
    include_directories : include_directories('include'),
    version : '1.0',
    link_args : [
    '-L' + libdir1, '-l' + inclib1,
    '-L' + libdir2, '-l' + inclib2
    ]
)
executable('app', sources  : src, dependencies : dep, override_options : ['cpp_std=c++20'], gui_app: true)