#include "VkPipeline.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
app::Pipeline::Pipeline(const std::string& vertFilePath, const std::string& fragFilePath)
{
    createGraphicsPipeline(vertFilePath,fragFilePath);
}
std::vector<char> app::Pipeline::readFile(const std::string& filePath)
{
    std::ifstream file{filePath,std::ios::ate | std::ios::binary};
    if(!file.is_open()) {
        throw std::runtime_error("failed to open: " + filePath);
    }
    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

void app::Pipeline::createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath)
{
    auto vertCode = readFile(vertFilePath);
    auto fragCode = readFile(fragFilePath);

    std::cout << "Vertex Shader Code Size: " << vertCode.size() << '\n';
    std::cout << "Fragment Shader Code Size: " << fragCode.size() << '\n';
}
