cmake_minimum_required(VERSION 3.0)

set(PROJECTNAME Texter)
project(${PROJECTNAME})


if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/glfw")
    message("-----------------------------------------------------------------------------------------------------------------")
    message("GLFW is included in this project as a submodule, so if you did not clone with '--recurse-submodules' you will need to do that")
    message("clone --recurse-submodules https://url.of.repo")
    message("-----------------------------------------------------------------------------------------------------------------")    
    message(FATAL_ERROR "The 'glfw' directory does not exist.") #fail early.
endif()



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


#---------------------------
# GLFW - SETUP
#---------------------------
# Add GLFW as a subdirectory
add_subdirectory(glfw)

#---------------------------
# GLEW - SETUP
#---------------------------
#required to link with glew static library
add_definitions(-DGLEW_STATIC)

set(CMAKE_PREFIX_PATH "${EXTERNALS}/glew-2.1.0" )
find_package(GLEW REQUIRED)
link_directories("${EXTERNALS}/glew-2.1.0/lib/Release/x64/")

#---------------------------
# STB - SETUP
#---------------------------
include_directories(${EXTERNALS}/stb/)



#---------------------------
# PROJECT - EXE
#---------------------------
add_executable(${PROJECTNAME} ${SRC_FILES})



#---------------------------
# GLFW - TARGET
#---------------------------
# Set the include directories for GLFW
target_include_directories(${PROJECTNAME} PUBLIC glfw/include)

# Link GLFW to your project
target_link_libraries(${PROJECTNAME} PUBLIC glfw)



#---------------------------
# OPENGL - TARGET
#---------------------------
#add OpenGL32.lib to included libs
target_link_libraries(${PROJECTNAME} PRIVATE OpenGL32.lib)

#---------------------------
# GLEW - TARGET
#---------------------------
target_include_directories(${PROJECTNAME} PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECTNAME} PRIVATE ${EXTERNALS}/glew-2.1.0/lib/Release/x64/glew32s.lib)



# Install 
install(TARGETS ${PROJECTNAME} DESTINATION bin)
