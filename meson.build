project('Vulkan Tutorial','cpp')
src = 'main.cpp'
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
executable('VulkanApp', sources  : src, override_options : ['c_std=clatest', 'cpp_std=c++latest'], dependencies : dep )