################# CONFIG ##################

#init Cmake
cmake_minimum_required(VERSION 3.24)
project(R-Type LANGUAGES CXX VERSION 1.0)

#set flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(UNIX)
    set(CMAKE_CXX_FLAGS "-std=c++20 -O3 -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Werror")
else()
    set(CMAKE_CXX_FLAGS "/std:c++20 /Ox /Wall /EHsc")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} /DEBUG:FULL")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /WX")
endif()
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_THREADS_LIBS_INIT Threads::Threads)

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
    ${ECS_ROOT}/Engine.cpp
    ${ECS_ROOT}/Entity/EntityManager.cpp
    ${ECS_ROOT}/Component/ComponentManager.cpp
    ${ECS_ROOT}/Component/Component.cpp
    ${ECS_ROOT}/System/SystemManager.cpp
    ${ECS_ROOT}/System/Render/RenderSystem.cpp
    ${ECS_ROOT}/System/Physic/PhysicSystem.cpp
)

#fetch required deps
find_package(SFML REQUIRED)
find_package(Asio REQUIRED)

#set include paths
include_directories(
    ${ECS_INC}
    ${SFML_INCLUDE_DIRS}
    ${ASIO_INCLUDE_DIRS}
    ${PROJECT_NAME}
)

#set source files (create library/executable)
if(UNIX)
    add_library(${ECS} SHARED ${ECS_SRC})
else()
    add_library(${ECS} STATIC ${ECS_SRC})
endif()

#link library/executable with deps
target_link_libraries(${ECS} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${ECS} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(${ECS} PRIVATE asio)

#install target
install(TARGETS ${ECS})

################## BUILD CLIENT ##################

#set executable name
set(CLIENT r-type_client)

#set root path
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

#set source files (create library/executable)
add_executable(${CLIENT} ${CLIENT_SRC})

#link library/executable with deps
target_link_libraries(${CLIENT} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${CLIENT} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(${CLIENT} PRIVATE asio)
target_link_libraries(${CLIENT} PRIVATE ${ECS})
set_target_properties(${CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

#install target
install(TARGETS ${CLIENT})

################## BUILD SERVER ##################

#set executable name
set(SERVER r-type_server)

#set root paths
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

#set source files (create library/executable)
add_executable(${SERVER} ${SERVER_SRC})

#link library/executable with deps
target_link_libraries(${SERVER} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${SERVER} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(${SERVER} PRIVATE asio)
target_link_libraries(${SERVER} PRIVATE ${ECS})
set_target_properties(${SERVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

#install target
install(TARGETS ${SERVER})