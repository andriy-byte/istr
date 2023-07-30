cmake_minimum_required(VERSION 3.25)
project(istr CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} include/istr.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX PUBLIC_HEADER "include/istr.hpp")
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
        )

if (BUILD_EXAMPLES)
    file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
    foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
        get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
        add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
        target_link_libraries(${EXAMPLE_NAME} PRIVATE istr)
    endforeach()
endif()


install(TARGETS istr)
