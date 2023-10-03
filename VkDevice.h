#include "VkWindow.h"

namespace app{
    class AppDevice{
    public:
        AppDevice();
        ~AppDevice();
    private:
        void InitVulkan();
        VkInstance instance;
    };
}