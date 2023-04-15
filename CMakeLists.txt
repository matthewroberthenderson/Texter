
cmake_minimum_required(VERSION 3.0)

set(PROJECTNAME Texter)

# set(CMAKE_GENERATOR_PLATFORM Win32)

project(${PROJECTNAME})



set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Texter)



# Set up the main source files
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

# Set up the header files
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
# source_group("headers/otherfolder" FILES ${HEADER_FILES})




# Set the directory where the build files should be placed
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# Create the build directory if it does not exist
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

#required to link with glew static library
add_definitions(-DGLEW_STATIC)

set(GLEW_LIBRARIES "${CMAKE_SOURCE_DIR}/Texter/external/glew-2.1.0/lib/Release/x64/glew32s.lib")

set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/Texter/external/glew-2.1.0" )


find_package(GLEW REQUIRED)

# Set the path to the GLFW library
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Texter/external/glfw-3.3.8.bin.WIN64")

# Include directories for GLFW
include_directories("${GLFW_DIR}/include")

#stb image
include_directories(${CMAKE_SOURCE_DIR}/Texter/external/stb/)



# Link directories for GLFW
link_directories("${GLFW_DIR}/lib-vc2022")

link_directories("${CMAKE_SOURCE_DIR}/Texter/external/glew-2.1.0/lib/Release/x64/")



# Add the Mello executable
add_executable(${PROJECTNAME} ${SRC_FILES})


target_link_libraries(${PROJECTNAME} PRIVATE "${GLFW_DIR}/lib-vc2022/glfw3.lib")


# Set the include directories for your project
target_include_directories(${PROJECTNAME} PRIVATE ${GLEW_INCLUDE_DIRS})


#add OpenGL32.lib to included libs
target_link_libraries(${PROJECTNAME} PRIVATE OpenGL32.lib)

# Add the Jup header directory to the include directories for Mello
target_include_directories(${PROJECTNAME} PRIVATE Jup)

target_link_libraries(${PROJECTNAME} PRIVATE ${CMAKE_SOURCE_DIR}/Texter/external/glew-2.1.0/lib/Release/x64/glew32s.lib)




# Install the executable
install(TARGETS ${PROJECTNAME} DESTINATION bin)
