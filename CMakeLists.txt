cmake_minimum_required(VERSION 3.10)
project(MathH)

add_library(MathH src/MathH.cpp)

target_include_directories(MathH PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS MathH
        EXPORT MathHConfig
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT MathHConfig DESTINATION lib/cmake/MathH)
