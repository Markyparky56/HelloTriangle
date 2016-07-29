#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <set>

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
    int presentFamily = -1;

    bool isComplete()
    {
        return graphicsFamily >= 0 && presentFamily >= 0;
    }
};

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
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
    void createLogicalDevice();
    void createSurface();
    bool checkValidationLayerSupport();
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
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
        void *userData);


    VDeleter<VkInstance> instance { vkDestroyInstance };
    VDeleter<VkDebugReportCallbackEXT> callback { instance, DestroyDebugReportCallbackEXT };
    VkPhysicalDevice physicalDevice;
    VDeleter<VkDevice> device { vkDestroyDevice };
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VDeleter<VkSurfaceKHR> surface { instance, vkDestroySurfaceKHR };

    const std::vector<const char*> validationLayers =
    {
        "VK_LAYER_LUNARG_standard_validation"
    };

    const std::vector<const char*> deviceExtensions = 
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
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


