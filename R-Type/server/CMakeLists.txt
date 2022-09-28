#init Cmake
cmake_minimum_required(VERSION 3.16)

project(R-Type LANGUAGES C CXX VERSION 1.0)

#set standard flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-std=c++20 -pedantic")
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

#set binary/executable name
set(EXEC_NAME r-type_client)

#fetch include paths
set(INC
    ${PROJECT_NAME}/
    ${PROJECT_NAME}/Entity/
    ${PROJECT_NAME}/Component/
    ${PROJECT_NAME}/System/
)

#fetch source files
set(SRC
    ${PROJECT_NAME}/Game.cpp
    ${PROJECT_NAME}/Entity/EntityManager.cpp
    ${PROJECT_NAME}/Component/ComponentManager.cpp
    ${PROJECT_NAME}/Component/Component.cpp
    ${PROJECT_NAME}/System/SystemManager.cpp
    ${PROJECT_NAME}/System/Render/RenderSystem.cpp
    ${PROJECT_NAME}/System/Physic/PhysicSystem.cpp
)

#set source files
add_executable(${EXEC_NAME}
    ${SRC}
    ${PROJECT_NAME}/main.cpp
)

target_compile_options(${EXEC_NAME} PRIVATE -Wall -Wextra -g)

if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(${EXEC_NAME} PRIVATE -Werror)
endif()

#set include paths
include_directories(${INC}
)

target_link_libraries(${EXEC_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_THREAD_LIBS_REQUIRED}
)

if(WIN32)
    add_custom_command(
        TARGET ${EXEC_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}.exe ${CMAKE_CURRENT_SOURCE_DIR}
    )
else()
    add_custom_command(
        TARGET ${EXEC_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME} ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()
