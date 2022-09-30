################# CONFIG ##################

#init Cmake
cmake_minimum_required(VERSION 3.24)

project(R-Type LANGUAGES CXX VERSION 1.0)

#set standard flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")

#set thread flags
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY ON)
set(CMAKE_USE_WIN32F_THREADS_INIT OFF)
set(CMAKE_USE_PTHREADS_INIT ON)

if(UNIX)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /Ox")
endif()

################## BUILD ECS ##################

#set library name
set(ECS ECS)

#set root path
set(ECS_ROOT ${PROJECT_NAME}/ECS)

#fetch include paths
set(ECS_INC
    ${ECS_ROOT}/
    ${ECS_ROOT}/Entity/
    ${ECS_ROOT}/Component/
    ${ECS_ROOT}/System/
)

#fetch source files
set(ECS_SRC
    ${ECS_ROOT}/Game.cpp
    ${ECS_ROOT}/Entity/EntityManager.cpp
    ${ECS_ROOT}/Component/ComponentManager.cpp
    ${ECS_ROOT}/Component/Component.cpp
    ${ECS_ROOT}/System/SystemManager.cpp
    ${ECS_ROOT}/System/Render/RenderSystem.cpp
    ${ECS_ROOT}/System/Physic/PhysicSystem.cpp
    ${ECS_ROOT}/System/Render/RenderSystem.cpp
    ${ECS_ROOT}/System/Input/InputSystem.cpp
)

find_package(SFML REQUIRED)
find_package(Asio REQUIRED)

#set include paths
include_directories(
    ${ECS_INC}
    ${SFML_INCLUDE_DIRS}
    ${ASIO_INCLUDE_DIRS}
    ${PROJECT_NAME}
)

#set source files
add_library(${ECS} SHARED ${ECS_SRC})

target_link_libraries(${ECS} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${ECS} PRIVATE ${CMAKE_THREAD_LIBS_REQUIRED})
target_link_libraries(${ECS} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_compile_features(${ECS} PRIVATE cxx_std_20)
target_link_libraries(${ECS} PRIVATE asio)
if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(${ECS} PRIVATE -Werror)
endif()

install(TARGETS ${ECS})

################## BUILD GRAPHIC ##################

#set library name
set(GRAPH GRAPH)

#set root path
set(GRAPH_ROOT ${PROJECT_NAME}/Graphic)

#fetch include paths
set(GRAPH_INC
    ${GRAPH_ROOT}/
)

#fetch source files
set(GRAPH_SRC
    ${GRAPH_ROOT}/Graphic.cpp
)

#set include paths
include_directories(
    ${GRAPH_INC}
    ${SFML_INCLUDE_DIRS}
    ${ASIO_INCLUDE_DIRS}
    ${PROJECT_NAME}
)

#set source files
add_library(${GRAPH} SHARED ${GRAPH_SRC})

target_link_libraries(${GRAPH} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${GRAPH} PRIVATE ${CMAKE_THREAD_LIBS_REQUIRED})
target_link_libraries(${GRAPH} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_compile_features(${GRAPH} PRIVATE cxx_std_20)
target_link_libraries(${GRAPH} PRIVATE asio)
if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(${GRAPH} PRIVATE -Werror)
endif()

install(TARGETS ${GRAPH})

################## BUILD CLIENT ##################

#set library/executable name
set(CLIENT r-type_client)

#set usefull paths
set(CLIENT_ROOT ${PROJECT_NAME}/client)

#fetch include paths
set(CLIENT_INC
)

#fetch source files
set(CLIENT_SRC
    ${CLIENT_ROOT}/main.cpp
)

#set include paths
include_directories(
    ${CLIENT_INC}
    ${SFML_INCLUDE_DIRS}
    ${ASIO_INCLUDE_DIRS}
    ${PROJECT_NAME}
)

#set source files
add_executable(${CLIENT} ${CLIENT_SRC})

target_link_libraries(${CLIENT} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${CLIENT} PRIVATE ${CMAKE_THREAD_LIBS_REQUIRED})
target_link_libraries(${CLIENT} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_compile_features(${CLIENT} PRIVATE cxx_std_20)
target_link_libraries(${CLIENT} PRIVATE asio)
target_link_libraries(${CLIENT} PRIVATE ${ECS})
target_link_libraries(${CLIENT} PRIVATE ${GRAPH})
if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(${CLIENT} PRIVATE -Werror)
endif()
set_target_properties(${CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

install(TARGETS ${CLIENT})

################## BUILD SERVER ##################

#set library/executable name
set(SERVER r-type_server)

#set usefull paths
set(SERVER_ROOT ${PROJECT_NAME}/server)

#fetch include paths
set(SERVER_INC
)

#fetch source files
set(SERVER_SRC
    ${SERVER_ROOT}/main.cpp
)

#set include paths
include_directories(
    ${SERVER_INC}
    ${SFML_INCLUDE_DIRS}
    ${ASIO_INCLUDE_DIRS}
    ${PROJECT_NAME}
)

#set source files
add_executable(${SERVER} ${SERVER_SRC})

target_link_libraries(${SERVER} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${SERVER} PRIVATE ${CMAKE_THREAD_LIBS_REQUIRED})
target_link_libraries(${SERVER} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_compile_features(${SERVER} PRIVATE cxx_std_20)
target_link_libraries(${SERVER} PRIVATE asio)
target_link_libraries(${SERVER} PRIVATE ${ECS})
target_link_libraries(${CLIENT} PRIVATE ${GRAPH})
if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(${SERVER} PRIVATE -Werror)
endif()
set_target_properties(${SERVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

install(TARGETS ${SERVER})
