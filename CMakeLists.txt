cmake_minimum_required(VERSION 3.0)
set(PROJECTNAME Texter)
project(${PROJECTNAME})

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Texter)
set(EXTERNALS ${SRC_DIR}/external)

set(SRC_FILES 
    ${SRC_DIR}/Main.cpp
    ${SRC_DIR}/Renderer.cpp
    ${SRC_DIR}/IndexBufferHelpers.cpp
    ${SRC_DIR}/VertexBuffer.cpp
    ${SRC_DIR}/VertexArray.cpp
    ${SRC_DIR}/TextureBase.cpp
    ${SRC_DIR}/TextureHelpers.cpp
    ${SRC_DIR}/ShaderBase.cpp
    ${SRC_DIR}/ShaderCore.cpp
)

#make filter
source_group("source" FILES ${SRC_FILES})


set(HEADER_FILES 
${SRC_DIR}/Debug.h
${SRC_DIR}/VertexArray.h
${SRC_DIR}/IndexBufferHelpers.h
${SRC_DIR}/VertexBuffer.h
${SRC_DIR}/VertexBufferLayout.h
${SRC_DIR}/ShaderBase.h
${SRC_DIR}/TextureHelpers.h
${SRC_DIR}/Main.h
${SRC_DIR}/Renderer.h
)


#make filter
source_group("headers" FILES ${HEADER_FILES})

# Set the directory where the build files should be placed
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# Create the build directory if it does not exist
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

#required to link with glew static library
add_definitions(-DGLEW_STATIC)

set(CMAKE_PREFIX_PATH "${EXTERNALS}/glew-2.1.0" )
find_package(GLEW REQUIRED)
set(GLFW_DIR "${EXTERNALS}/glfw-3.3.8.bin.WIN64")

# Include directories for GLFW
include_directories("${GLFW_DIR}/include")

#stb image
include_directories(${EXTERNALS}/stb/)

# Link directories for GLFW
link_directories("${GLFW_DIR}/lib-vc2022")
link_directories("${EXTERNALS}/glew-2.1.0/lib/Release/x64/")

#exe
add_executable(${PROJECTNAME} ${SRC_FILES})


target_link_libraries(${PROJECTNAME} PRIVATE ${GLFW_DIR}/lib-vc2022/glfw3.lib)
target_include_directories(${PROJECTNAME} PRIVATE ${GLEW_INCLUDE_DIRS})
#add OpenGL32.lib to included libs
target_link_libraries(${PROJECTNAME} PRIVATE OpenGL32.lib)
target_link_libraries(${PROJECTNAME} PRIVATE ${EXTERNALS}/glew-2.1.0/lib/Release/x64/glew32s.lib)

# Install 
install(TARGETS ${PROJECTNAME} DESTINATION bin)
