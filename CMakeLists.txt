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
else()
    # set(CMAKE_CXX_FLAGS "/std:c++20 /Ox /Wall /EHsc")
    # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} /DEBUG:FULL")
endif()
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_THREADS_LIBS_INIT Threads::Threads)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
if (WIN32)
    set(BUILD_SHARED_LIBS OFF)
else()
    set(BUILD_SHARED_LIBS ON)
endif()
include(ProcessorCount)
ProcessorCount(CMAKE_BUILD_PARALLEL_LEVEL)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_NETWORK OFF)
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

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

#fetch required deps
find_package(OpenGL REQUIRED)

if (NOT sfml_POPULATED)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_PROGRESS TRUE)
    FetchContent_MakeAvailable(SFML)
endif()

if (NOT boost_POPULATED)
    FetchContent_Declare(
        Boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_PROGRESS TRUE
        GIT_TAG master
        CONFIGURE_COMMAND ""
    )
    FetchContent_MakeAvailable(Boost)
endif()

#set include paths
include_directories(
    ${ImGui_INC}
    ${Boost_INCLUDE_DIR}
    ${PROJECT_NAME}
)

#set source files
add_library(${ImGui} ${ImGui_SRC})

target_link_libraries(${ImGui} PRIVATE ${OPENGL_LIBRARY})
target_link_libraries(${ImGui} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

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
    ${ENGINE_ROOT}/ECS/PreloadEntities/
    ${ENGINE_ROOT}/Graphic/
    ${ENGINE_ROOT}/Network/
    ${ENGINE_ROOT}/Loader/
    ${ENGINE_ROOT}/Level/
)

#fetch source files
set(ENGINE_SRC
    # ECS files
    ${ENGINE_ROOT}/ECS/ECS.cpp
    ${ENGINE_ROOT}/ECS/Entity/EntityManager.cpp
    ${ENGINE_ROOT}/ECS/Component/ComponentManager.cpp
    ${ENGINE_ROOT}/ECS/Component/SparseArray.cpp
    ${ENGINE_ROOT}/ECS/System/SystemManager.cpp
    ${ENGINE_ROOT}/ECS/System/Render/RenderSystem.cpp
    ${ENGINE_ROOT}/ECS/System/Physic/PhysicSystem.cpp
    ${ENGINE_ROOT}/ECS/System/Render/RenderSystem.cpp
    ${ENGINE_ROOT}/ECS/System/GUI/GUISystem.cpp
    ${ENGINE_ROOT}/ECS/System/Input/InputSystem.cpp
    ${ENGINE_ROOT}/ECS/System/Click/ClickSystem.cpp
    ${ENGINE_ROOT}/ECS/System/Animation/AnimationSystem.cpp
    ${ENGINE_ROOT}/ECS/System/Score/ScoreSystem.cpp
    ${ENGINE_ROOT}/ECS/System/Sound/SoundSystem.cpp
    ${ENGINE_ROOT}/ECS/PreloadEntities/MenuPreload.cpp
    ${ENGINE_ROOT}/ECS/PreloadEntities/ParallaxPreload.cpp
    ${ENGINE_ROOT}/ECS/PreloadEntities/VesselPreload.cpp
    ${ENGINE_ROOT}/ECS/PreloadEntities/BossPreload.cpp
    ${ENGINE_ROOT}/ECS/PreloadEntities/EnemyPreload.cpp
    ${ENGINE_ROOT}/ECS/PreloadEntities/BackgroundMusicPreload.cpp
    ${ENGINE_ROOT}/ECS/PreloadEntities/ScoreTextPreload.cpp
    ${ENGINE_ROOT}/ECS/PreloadEntities/DevourerOfGodsPreload.cpp
    ${ENGINE_ROOT}/ECS/PreloadEntities/CthulhuPreload.cpp
    ${ENGINE_ROOT}/ECS/PreloadEntities/ProjectilePreload.cpp
    ${ENGINE_ROOT}/ECS/System/Enemy/EnemySystem.cpp

    # Network files
    ${ENGINE_ROOT}/Network/Connection.cpp
    ${ENGINE_ROOT}/Network/Serializer.cpp
    ${ENGINE_ROOT}/Network/Room.cpp

    # Graphic files
    ${ENGINE_ROOT}/Graphic/Graphic.cpp

    # Loader files
    ${ENGINE_ROOT}/Loader/Loader.cpp

    # Loader files
    ${ENGINE_ROOT}/Level/Level.cpp

    # Engine files
    ${ENGINE_ROOT}/Engine.cpp
)

#set include paths
include_directories(
    ${ENGINE_INC}
    ${BOOST_LIBRARY_INCLUDES}
    ${CMAKE_BINARY_DIR}/_deps/boost-src/libs/numeric/conversion/include
    ${PROJECT_NAME}
)

#set source files (create library/executable)
add_library(${ENGINE} ${ENGINE_SRC})

#link library/executable with deps
target_link_libraries(${ENGINE} PRIVATE ${OPENGL_LIBRARY})
target_link_libraries(${ENGINE} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
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
    ${CLIENT_ROOT}
)

#fetch source files
set(CLIENT_SRC
    ${CLIENT_ROOT}/main.cpp
    ${CLIENT_ROOT}/Client.cpp
    ${CLIENT_ROOT}/ClientNetwork.cpp
    ${CLIENT_ROOT}/MenuSerializer.cpp
    ${CLIENT_ROOT}/GameSerializer.cpp
)

#set include paths
include_directories(
    ${CLIENT_INC}
    ${BOOST_LIBRARY_INCLUDES}
    ${CMAKE_BINARY_DIR}/_deps/boost-src/libs/numeric/conversion/include
    ${PROJECT_NAME}
)

#set source files (create library/executable)
add_executable(${CLIENT} ${CLIENT_SRC})

#link library/executable with deps
target_link_libraries(${CLIENT} PRIVATE ${OPENGL_LIBRARY})
target_link_libraries(${CLIENT} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
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
    ${SERVER_ROOT}
)

#fetch source files
set(SERVER_SRC
    ${SERVER_ROOT}/main.cpp
    ${SERVER_ROOT}/Client.cpp
    ${SERVER_ROOT}/Server.cpp
    ${SERVER_ROOT}/ServerNetwork.cpp
    ${SERVER_ROOT}/MenuSerializer.cpp
    ${SERVER_ROOT}/GameSerializer.cpp
)

#set include paths
include_directories(
    ${SERVER_INC}
    ${BOOST_LIBRARY_INCLUDES}
    ${CMAKE_BINARY_DIR}/_deps/boost-src/libs/numeric/conversion/include
    ${PROJECT_NAME}
)

#set source files (create library/executable)
add_executable(${SERVER} ${SERVER_SRC})

#link library/executable with deps
target_link_libraries(${SERVER} PRIVATE ${OPENGL_LIBRARY})
target_link_libraries(${SERVER} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(${SERVER} PRIVATE ${ImGui})
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
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/_deps/sfml-src/extlibs/bin/x64/openal32.dll ${CMAKE_SOURCE_DIR}
  )
endif()
