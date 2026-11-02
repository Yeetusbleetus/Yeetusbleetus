cmake_minimum_required(VERSION 3.16)
project(omnicept_sdk VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(OMNICEPT_BUILD_TESTS "Build the mock-runtime tests" ON)
option(OMNICEPT_BUILD_EXAMPLES "Build the examples" ON)

find_package(Protobuf REQUIRED)
find_package(Threads REQUIRED)

# ZeroMQ: prefer the CMake package (vcpkg on Windows), fall back to pkg-config.
find_package(ZeroMQ CONFIG QUIET)
if(TARGET libzmq OR TARGET libzmq-static)
    set(OMNICEPT_ZMQ_TARGET $<IF:$<TARGET_EXISTS:libzmq>,libzmq,libzmq-static>)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(ZMQ REQUIRED IMPORTED_TARGET libzmq)
    set(OMNICEPT_ZMQ_TARGET PkgConfig::ZMQ)
endif()
find_path(CPPZMQ_INCLUDE_DIR zmq.hpp REQUIRED)

# Wire schemas recovered from the runtime.
file(GLOB OMNICEPT_PROTOS ${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto)
set(PROTOBUF_IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${OMNICEPT_PROTOS})

add_library(omnicept_sdk
    src/Client.cpp
    src/Codec.cpp
    src/Connection.cpp
    src/DomainTypes.cpp
    src/Glia.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS})
add_library(omnicept::sdk ALIAS omnicept_sdk)

target_include_directories(omnicept_sdk
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CPPZMQ_INCLUDE_DIR})
target_link_libraries(omnicept_sdk PUBLIC Threads::Threads PRIVATE protobuf::libprotobuf ${OMNICEPT_ZMQ_TARGET})

if(MSVC)
    target_compile_options(omnicept_sdk PRIVATE /W4 /wd4100 /wd4244 /wd4267)
else()
    target_compile_options(omnicept_sdk PRIVATE -Wall -Wextra -Wno-unused-parameter)
endif()

install(TARGETS omnicept_sdk ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)

if(OMNICEPT_BUILD_EXAMPLES)
    add_executable(heart_rate_monitor examples/heart_rate_monitor.cpp)
    target_link_libraries(heart_rate_monitor PRIVATE omnicept::sdk)
endif()

if(OMNICEPT_BUILD_TESTS)
    enable_testing()
    # The tests use internal headers (codec + framing) to drive a mock runtime.
    add_executable(omnicept_tests tests/client_test.cpp tests/MockRuntime.cpp)
    target_include_directories(omnicept_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR} ${CPPZMQ_INCLUDE_DIR})
    target_link_libraries(omnicept_tests PRIVATE omnicept::sdk protobuf::libprotobuf ${OMNICEPT_ZMQ_TARGET})
    add_test(NAME omnicept_tests COMMAND omnicept_tests)
endif()
