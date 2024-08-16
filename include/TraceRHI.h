#pragma once
#include "CommandList.h"
#include "Instance.h"
#include "PhysicalDevice.h"
#include "client/TracyProfiler.hpp"
namespace TraceRHI
{
    class Context
    {
        RHI::API api;
        friend class Zone;
    public:
        Context(){}
        Context(RHI::Instance*, RHI::PhysicalDevice*,RHI::Weak<RHI::Device>, RHI::Weak<RHI::CommandQueue>, RHI::Weak<RHI::GraphicsCommandList>);
        ~Context();
        Internal_ID ID = nullptr; //Corresponds to a TracyVkContext or TracyD3D12Context
    };
    #ifdef TRACERHI_ENABLE
    #define TraceRHIContext(inst, phys_dev, dev, queue, list) TraceRHI::Context(inst, phys_dev, dev, list)
    #else
    #define TraceRHIContext(inst, phys_dev, dev, queue, list) TraceRHI::Context()
    #endif
    class Zone
    {
        uintptr_t space[
        #ifdef TRACERHI_ENABLE
            4
        #else
            1
        #endif
        ];
    public:
        Zone(Context& ctx, RHI::Weak<RHI::GraphicsCommandList> list, const tracy::SourceLocationData* loc_d);
        ~Zone();
    };
    #ifdef TRACERHI_ENABLE
    #define TraceRHIZone(name, list, ctx) static constexpr tracy::SourceLocationData TracyConcat(__tracy_gpu_source_location,TracyLine) { name, TracyFunction,  TracyFile, (uint32_t)TracyLine, 0 }; TraceRHI::Zone(ctx, list,&TracyConcat(__tracy_gpu_source_location,TracyLine))
    #else
    #define TraceRHIZone(name, list, ctx)
    #endif
}