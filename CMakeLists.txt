

cmake_minimum_required(VERSION 3.0)

set(PROJECTNAME Texter)

set(CMAKE_GENERATOR_PLATFORM Win32)

project(${PROJECTNAME})


# Set the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)




set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Texter)
#set(INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


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


#external items


#-----------------------------------------
#stb image
include_directories(${CMAKE_SOURCE_DIR}Texter/external/stb)









#-----------------------------------------
#glfw
message("Getting glfw")


# Set the download URL for GLFW
set(GLFW_DOWNLOAD_URL "https://github.com/glfw/glfw/releases/download/3.3.5/glfw-3.3.5.bin.WIN64.zip")

# Set the destination directory for the downloaded and unzipped GLFW files
set(GLFW_DOWNLOAD_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glfw_download")

set(GLFW_DIR "${GLFW_DOWNLOAD_DIR}/glfw-3.3.5.bin.WIN64")



# Download and extract the GLFW zip file
file(DOWNLOAD ${GLFW_DOWNLOAD_URL} "${GLFW_DOWNLOAD_DIR}/glfw.zip")
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf "${GLFW_DOWNLOAD_DIR}/glfw.zip"
    WORKING_DIRECTORY ${GLFW_DOWNLOAD_DIR})

# Add the GLFW include directory to the project
include_directories(${GLFW_DIR}/include)










#-----------------------------------------
#glew
message("Getting glew -------------------------------------------")

# Set the download URL for GLEW
set(GLEW_DOWNLOAD_URL "https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download")

# Set the destination directory for the downloaded and unzipped GLEW files
set(GLEW_DOWNLOAD_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glew_download")
set(GLEW_DIR "${GLEW_DOWNLOAD_DIR}/glew-2.1.0")


# Download and extract the GLEW zip file
file(DOWNLOAD ${GLEW_DOWNLOAD_URL} "${GLEW_DOWNLOAD_DIR}/glew.zip")
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf "${GLEW_DOWNLOAD_DIR}/glew.zip"
    WORKING_DIRECTORY ${GLEW_DOWNLOAD_DIR})

# Add the GLEW include directory to the project
include_directories(${GLEW_DIR}/include)















# Add the GLFW library to the project
add_library(glfw3 STATIC IMPORTED)
set_target_properties(glfw3 PROPERTIES IMPORTED_LOCATION "${GLFW_DIR}/lib-vc2019/glfw3.lib")

# Add the GLEW library to the project
add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES IMPORTED_LOCATION "${GLEW_DIR}/lib/Release/x64/glew32s.lib")


# Define the executable target
add_executable(${PROJECTNAME} ${SRC_FILES} ${HEADER_FILES})

# Set the output path for the executable
set_target_properties(${PROJECTNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Link the target against the library
target_link_libraries(${PROJECTNAME} glew glfw3)





# copy dll for glut library because we are statically linking it
#set(GLUT_DLL  "lib/glut64.dll")
#file(COPY ${GLUT_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)





