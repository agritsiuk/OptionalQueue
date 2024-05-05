add_library(optional_queue INTERFACE)
add_library(optional_queue::optional_queue ALIAS optional_queue)
target_include_directories(optional_queue INTERFACE ${PROJECT_SOURCE_DIR}/include)
