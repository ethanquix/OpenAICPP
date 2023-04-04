cmake_minimum_required(VERSION 3.24)

# https://github.com/aminya/project_options/
include(FetchContent)
FetchContent_Declare(_project_options URL
        https://github.com/aminya/project_options/archive/refs/tags/v0.27.1.zip
        )
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

# install vcpkg dependencies: - should be called before defining project()
run_vcpkg()

project(OpenAI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

# Library
add_library(OpenAI INTERFACE)

# Find dependencies:
target_find_dependencies(OpenAI daw::daw-json-link)

target_link_libraries(OpenAI INTERFACE daw::daw-json-link)

# Includes:
# Includes
set(INCLUDE_DIR "include") # must be relative paths
target_include_directories(OpenAI INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<INSTALL_INTERFACE:./${CMAKE_INSTALL_INCLUDEDIR}>")
target_include_interface_directories(OpenAI "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_features(OpenAI INTERFACE cxx_std_17)

# Package the project
package_project(TARGETS OpenAI PUBLIC_INCLUDES ${INCLUDE_DIR})

# Examples
set(COMPILE_EXAMPLES "TRUE")

IF((DEFINED $ENV{COMPILE_EXAMPLES}) OR (${COMPILE_EXAMPLES}))
    set(OPENSSL_SUPPORT "-DCPPHTTPLIB_OPENSSL_SUPPORT -I/opt/homebrew/opt/openssl@1.1/include -L/opt/homebrew/opt/openssl@1.1/lib -lssl -lcrypto -framework CoreFoundation -framework Security")
    set(CMAKE_CXX_FLAGS ${OPENSSL_SUPPORT})

    find_package(daw-json-link)

    ## chat
    add_executable(example_chat examples/example_chat.cpp)
    target_link_libraries(example_chat OpenAI daw::daw-json-link)

    ## images
    add_executable(example_image examples/example_image.cpp)
    target_link_libraries(example_image OpenAI daw::daw-json-link)

    ## all
    add_executable(example examples/examples.cpp)
    target_link_libraries(example OpenAI daw::daw-json-link)
ENDIF ()

##--------- INSTALL ---------#
#
## 'make install' to the correct locations (provided by GNUInstallDirs).
#install(TARGETS OpenAI EXPORT OpenAIConfig
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
#
#install(DIRECTORY include/openai DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
#
## This makes the project importable from the install directory
## Put config file in per-project dir (name MUST match), can also
## just go into 'cmake'.
#install(EXPORT OpenAIConfig DESTINATION share/OpenAI/cmake)
#
## This makes the project importable from the build directory
#export(TARGETS OpenAI FILE OpenAI.cmake)