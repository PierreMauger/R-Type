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
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Cmake-Modules/")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_THREADS_LIBS_INIT Threads::Threads)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(DBUILD_SHARED_LIBS TRUE)

################## BUILD ImGui ##################

#set library name
set(ImGui ImGui)

#set root path
set(ImGui_ROOT ${PROJECT_NAME}/ImGui)

#fetch include paths
set(ImGui_INC
    ${ImGui_ROOT}/
)

#fetch source files
set(ImGui_SRC
    ${ImGui_ROOT}/imgui_draw.cpp
    ${ImGui_ROOT}/imgui_tables.cpp
    ${ImGui_ROOT}/imgui_widgets.cpp
    ${ImGui_ROOT}/imgui.cpp
    ${ImGui_ROOT}/imgui-SFML.cpp
)

#set include paths
include_directories(
    ${ImGui_INC}
    ${SFML_INCLUDE_DIRS}
    ${BOOST_INCLUDE_DIRS}
    ${PROJECT_NAME}
)

#fetch required deps
find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED)
find_package(Boost REQUIRED)

#set source files
add_library(${ImGui} ${ImGui_SRC})

target_link_libraries(${ImGui} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${ImGui} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${ImGui} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

#install target
install(TARGETS ${ImGui})

################## BUILD ENGINE ##################

#set library name
set(ENGINE Engine)

#set root path
set(ENGINE_ROOT ${PROJECT_NAME}/Engine)

#fetch include paths
set(ENGINE_INC
    ${ENGINE_ROOT}/
    ${ENGINE_ROOT}/ECS
    ${ENGINE_ROOT}/ECS/Entity/
    ${ENGINE_ROOT}/ECS/Component/
    ${ENGINE_ROOT}/ECS/System/
    ${ENGINE_ROOT}/Graphic/
)

#fetch source files
set(ENGINE_SRC
    # ECS files
    ${ENGINE_ROOT}/ECS/ECS.cpp
    ${ENGINE_ROOT}/ECS/Entity/EntityManager.cpp
    ${ENGINE_ROOT}/ECS/Component/ComponentManager.cpp
    ${ENGINE_ROOT}/ECS/Component/Component.cpp
    ${ENGINE_ROOT}/ECS/System/SystemManager.cpp
    ${ENGINE_ROOT}/ECS/System/Render/RenderSystem.cpp
    ${ENGINE_ROOT}/ECS/System/Physic/PhysicSystem.cpp
    ${ENGINE_ROOT}/ECS/System/Render/RenderSystem.cpp
    ${ENGINE_ROOT}/ECS/System/Render/GUI.cpp
    ${ENGINE_ROOT}/ECS/System/Input/InputSystem.cpp

    # Graphic files
    ${ENGINE_ROOT}/Graphic/Graphic.cpp

    # Engine files
    ${ENGINE_ROOT}/Engine.cpp
)

#set include paths
include_directories(
    ${ENGINE_INC}
    ${SFML_INCLUDE_DIRS}
    ${BOOST_INCLUDE_DIRS}
    ${PROJECT_NAME}
)

#set source files (create library/executable)
add_library(${ENGINE} ${ENGINE_SRC})

#link library/executable with deps
target_link_libraries(${ENGINE} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${ENGINE} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${ENGINE} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(${ENGINE} PRIVATE ${BOOST_LIBRARIES})
target_link_libraries(${ENGINE} PRIVATE ${ImGui})

#install target
install(TARGETS ${ENGINE})

################## BUILD CLIENT ##################

#set executable name
set(CLIENT r-type_client)

#set root path
set(CLIENT_ROOT ${PROJECT_NAME}/Client)

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
    ${BOOST_INCLUDE_DIRS}
    ${PROJECT_NAME}
)

#set source files (create library/executable)
add_executable(${CLIENT} ${CLIENT_SRC})

#link library/executable with deps
target_link_libraries(${CLIENT} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${CLIENT} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${CLIENT} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(${CLIENT} PRIVATE ${BOOST_LIBRARIES})
target_link_libraries(${CLIENT} PRIVATE ${ImGui})
target_link_libraries(${CLIENT} PRIVATE ${ENGINE})
set_target_properties(${CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set_target_properties(${CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

#install target
install(TARGETS ${CLIENT})

################## BUILD SERVER ##################

#set executable name
set(SERVER r-type_server)

#set root paths
set(SERVER_ROOT ${PROJECT_NAME}/Server)

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
    ${BOOST_INCLUDE_DIRS}
    ${PROJECT_NAME}
)

#set source files (create library/executable)
add_executable(${SERVER} ${SERVER_SRC})

#link library/executable with deps
target_link_libraries(${SERVER} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${SERVER} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${SERVER} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(${SERVER} PRIVATE ${BOOST_LIBRARIES})
target_link_libraries(${CLIENT} PRIVATE ${ImGui})
target_link_libraries(${SERVER} PRIVATE ${ENGINE})
set_target_properties(${SERVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set_target_properties(${SERVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

#install target
install(TARGETS ${SERVER})

################## POST BUILD ##################

#copy dlls to root for resources (only on windows)
if(WIN32)
  add_custom_command(
    TARGET ${ENGINE} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/_deps/sfml-build/lib/${CMAKE_BUILD_TYPE}/sfml-window-d-2.dll ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/_deps/sfml-build/lib/${CMAKE_BUILD_TYPE}/sfml-graphics-d-2.dll ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/_deps/sfml-build/lib/${CMAKE_BUILD_TYPE}/sfml-system-d-2.dll ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Engine.dll ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ImGui.dll ${CMAKE_SOURCE_DIR}
  )
endif()
