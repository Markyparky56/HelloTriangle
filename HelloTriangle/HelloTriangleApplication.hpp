#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>

#include "VDeleter.hpp"

VkResult CreateDebugReportCallbackEXT(
    VkInstance instance,
    const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugReportCallbackEXT *pCallBack);

void DestroyDebugReportCallbackEXT(
    VkInstance instance,
    VkDebugReportCallbackEXT callback,
    const VkAllocationCallbacks *pAllocator);

struct QueueFamilyIndices
{
    int graphicsFamily = -1;

    bool isComplete()
    {
        return graphicsFamily >= 0;
    }
};

class HelloTriangleApplication
{
public:
    void Run();

private:
    void initWindow();
    void initVulkan();
    void createInstance();
    void setupDebugCallback();
    void pickPhysicalDevice();
    bool checkValidationLayerSupport();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);
    std::vector<const char*> getRequiredExtensions();
    void mainLoop();

    static VkBool32 debugCallback(
        VkDebugReportFlagsEXT flags,
        VkDebugReportObjectTypeEXT objType,
        uint64_t obj,
        size_t location,
        int32_t code,
        const char *layerPrefix,
        const char *msg,
        void *userData)
    {
        std::cerr << "Validation layer: " << msg << std::endl;

        return VK_FALSE;
    }

    VDeleter<VkInstance> instance{ vkDestroyInstance };
    VDeleter<VkDebugReportCallbackEXT> callback { instance, DestroyDebugReportCallbackEXT };
    VkPhysicalDevice physicalDevice;

    const std::vector<const char*> validationLayers =
    {
        "VK_LAYER_LUNARG_standard_validation"
    };

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    const int Width = 800;
    const int Height = 600;
    GLFWwindow *window;
};


