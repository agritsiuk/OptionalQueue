find_package(GTest REQUIRED)

add_executable(OptionalQueueTest OptionalQueueTest.cpp)
target_compile_options(OptionalQueueTest PRIVATE -Wall -Werror -Wpedantic -fsanitize=address -fsanitize=undefined -fsanitize=leak)
target_link_libraries(OptionalQueueTest PRIVATE asan ubsan optional_queue::optional_queue GTest::gtest_main)
add_test(NAME OptionalQueueTest COMMAND OptionalQueueTest)
