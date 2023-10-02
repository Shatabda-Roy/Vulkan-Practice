#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "VkApp.h"

int main() {
    app::FirstApp _app{};

    try {
        _app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}