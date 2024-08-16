#include <vulkan/vulkan_core.h>
#define VK_NO_PROTOTYPES
#define TRACY_VK_USE_SYMBOL_TABLE
#include "TraceRHI.h"
#include <vulkan/vulkan.h>
#include "Instance.h"
#include "tracy/TracyVulkan.hpp"
#if _WIN32

#endif
TraceRHI::Context::Context
    (RHI::Instance* instance,
    RHI::PhysicalDevice* physicalDev, 
    RHI::Weak<RHI::Device> device, 
    RHI::Weak<RHI::CommandQueue> queue, 
    RHI::Weak<RHI::GraphicsCommandList> list)
{
    api = instance->GetInstanceAPI();
    if(api == RHI::API::Vulkan)
    {
        ID = TracyVkContext(
            (VkInstance)instance->ID,
            (VkPhysicalDevice)physicalDev->ID,
            (VkDevice)device->ID,
            (VkQueue)queue->ID,
            (VkCommandBuffer)list->ID,
            vkGetInstanceProcAddr, vkGetDeviceProcAddr);
    }
    else {
    }
}
TraceRHI::Context::~Context()
{
    if(ID) TracyVkDestroy((tracy::VkCtx*)ID);
}

TraceRHI::Zone::Zone(
    Context& ctx, 
    RHI::Weak<RHI::GraphicsCommandList> list, 
    const tracy::SourceLocationData* loc_d
)
{
    if(ctx.api == RHI::API::Vulkan)
    {
        new(space) tracy::VkCtxScope((tracy::VkCtx*)ctx.ID,loc_d, (VkCommandBuffer)list->ID, true); 
    }
    else {
    }
}
TraceRHI::Zone::~Zone()
{
    tracy::VkCtxScope* sc = (tracy::VkCtxScope*)space;
    sc->~VkCtxScope();
}