################# CONFIG ##################

#init Cmake
cmake_minimum_required(VERSION 3.24)

project(R-Type LANGUAGES CXX VERSION 1.0)

#set standard flags
set(CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/../../")
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

################## BUILD ##################

#set binary/executable name
set(EXEC_NAME r-type_client)

#fetch include paths
set(INC
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/ECS/
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/ECS/Entity/
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/ECS/Component/
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/ECS/System/
)

#fetch source files
set(SRC
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/ECS/Engine.cpp
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/ECS/Entity/EntityManager.cpp
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/ECS/Component/ComponentManager.cpp
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/ECS/Component/Component.cpp
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/ECS/System/SystemManager.cpp
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/ECS/System/Render/RenderSystem.cpp
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/ECS/System/Physic/PhysicSystem.cpp
)

find_package(SFML REQUIRED)

#set include paths
include_directories(${INC} ${SFML_INCLUDE_DIRS})

#set source files
add_executable(${EXEC_NAME}
    ${SRC}
    main.cpp
)

target_link_libraries(${EXEC_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${EXEC_NAME} PUBLIC ${CMAKE_THREAD_LIBS_REQUIRED})
target_link_libraries(${EXEC_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_compile_features(${EXEC_NAME} PRIVATE cxx_std_20)
if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(${EXEC_NAME} PRIVATE -Werror)
endif()

install(TARGETS ${EXEC_NAME})

################## POST BUILD ##################

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
