add_library(perf perf_counter.cpp)
add_dependencies(perf prebuild_targets)
target_compile_options(perf PRIVATE ${MAX_CUSTOM_OPT_LEVEL})
