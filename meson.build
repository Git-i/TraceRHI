project('TraceRHI', 'cpp', default_options: ['cpp_std=c++20'])
tracy_dep = dependency('tracy')
rhi = dependency('pistachio_rhi')
deps = [tracy_dep, rhi]
trace_rhi_lib = library('TraceRHI', 'src/TraceRHI.cpp', dependencies: deps)
trace_rhi_dep = declare_dependency(link_with: trace_rhi_lib)
