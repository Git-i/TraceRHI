#define VK_NO_PROTOTYPES
#include "include/TraceRHI.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include "CommandList.h"
#include "FormatsAndTypes.h"
#include "Instance.h"
#include "Ptr.h"
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
            (VkPhysicalDevice)physicalDev->ID,
            (VkDevice)device->ID,
            (VkQueue)queue->ID,
            (VkCommandBuffer)list->ID);
    }
    else {
    }
}

TraceRHI::Zone::Zone(
    Context& ctx, 
    RHI::Weak<RHI::GraphicsCommandList> list, 
    tracy::SourceLocationData* loc_d
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