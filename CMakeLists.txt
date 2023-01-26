cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)
#create Project
project(BlockBuildingGame)

#add source files
add_executable(
        BlockBuildingGame
        dependencies/glad/src/glad.c
        src/main.cpp
        src/Engine/Render/Camera/Camera.h
        src/Engine/Render/Camera/Camera.cpp
        src/Engine/Render/Camera/CameraController.cpp
        src/Engine/Render/Camera/CameraController.h
        src/Engine/Render/VertexBuffer.cpp
        src/Engine/Render/VertexBuffer.h
        src/Engine/Render/IndexBuffer.cpp
        src/Engine/Render/IndexBuffer.h
        src/Engine/Render/VertexArrayObject.cpp
        src/Engine/Render/VertexArrayObject.h
        src/Engine/Render/ShaderProgram.cpp
        src/Engine/Render/ShaderProgram.h
        src/Engine/Util/FileIO.cpp
        src/Engine/Util/FileIO.h
        src/Engine/Render/Texture2D.cpp
        src/Engine/Render/Texture2D.h
        src/Engine/OS/WindowProcessing.cpp
        src/Engine/OS/WindowProcessing.h
        src/Engine/Render/Objects/Primitives.h
        src/Game/World/Objects/BlockAtlas.h
        src/Game/World/Objects/BlockManager.cpp
        src/Game/World/Objects/BlockManager.h
        src/Game/World/Objects/BlockAtlas.cpp
        src/Engine/Render/Objects/Primitives.cpp
        src/Game/World/WorldGen/Chunk.cpp src/Game/World/WorldGen/Chunk.h)

#add custom target for copying resource files to binary folder
add_custom_target(
        copy-files ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_BINARY_DIR}/res
)
add_dependencies(${PROJECT_NAME} copy-files)

#find and add libraries
find_package(OpenGL REQUIRED)
include_directories(
        ${OPENGL_INCLUDE_DIRS}
        "${CMAKE_SOURCE_DIR}/dependencies/glfw/include"
        "${CMAKE_SOURCE_DIR}/dependencies/glad/include"
        "${CMAKE_SOURCE_DIR}/dependencies/stb"
        "${CMAKE_SOURCE_DIR}/dependencies/glm"
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/src/Engine"


)
target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        ${OPENGL_LIBRARIES}

        "${CMAKE_SOURCE_DIR}/dependencies/glfw/lib/libglfw3.a"
)

#add mac specific libraries
if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    target_link_libraries(
            ${CMAKE_PROJECT_NAME}
            ${COCOA_LIBRARY}
            ${IOKIT_LIBRARY}
    )
endif()
