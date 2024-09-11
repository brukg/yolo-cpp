cmake_minimum_required(VERSION 3.10)
project(yolo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(yaml-cpp REQUIRED)
option(WITH_OPENVINO "Build with OpenVINO support" OFF)
option(WITH_OPENGL "Build with OpenVINO support" OFF)
option(WITH_TENSORRT "Build with TensorRT support" OFF)

if(WITH_OPENVINO)
    find_package(OpenVINO REQUIRED)
    message(STATUS "OpenVINO found" ${OpenVINO_VERSION})
    add_definitions(-DWITH_OPENVINO)

endif()

if(WITH_TENSORRT)
    # Find TensorRT
    find_path(TENSORRT_INCLUDE_DIR NvInfer.h HINTS ${TENSORRT_ROOT}/include)
    find_library(TENSORRT_LIB nvinfer HINTS ${TENSORRT_ROOT}/lib)
    find_library(NVINFER_PLUGIN_LIB nvinfer_plugin HINTS ${TENSORRT_ROOT}/lib)
    find_library(NVPARSERS_LIB nvparsers HINTS ${TENSORRT_ROOT}/lib)
    find_library(NVONNXPARSER_LIB nvonnxparser HINTS ${TENSORRT_ROOT}/lib)
    set(TENSORRT_LIBS nvinfer nvinfer_plugin nvparsers nvonnxparser cudnn cublas cudart)

    add_definitions(-DWITH_TENSORRT)
    include_directories(
      ${TENSORRT_INCLUDE_DIRS}
    )
endif()

if(WITH_OPENGL)
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    find_package(GLEW REQUIRED) 
    add_definitions(-DWITH_OPENGL)
    include_directories(
      ${OPENGL_INCLUDE_DIRS}
      ${GLUT_INCLUDE_DIRS}
      ${GLEW_INCLUDE_DIRS}
    )
endif()
include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
)

# find src files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} 
  ${SRC_FILES}
)
target_link_libraries(${PROJECT_NAME} 
  ${OpenCV_LIBS}
  yaml-cpp
)

if(WITH_OPENVINO)
    target_link_libraries(${PROJECT_NAME} 
        openvino::runtime
)
endif()

if(WITH_TENSORRT)
    target_link_libraries(${PROJECT_NAME} 
        ${TENSORRT_LIBS}
)
endif()

if(WITH_OPENGL)
    target_link_libraries(${PROJECT_NAME} 
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        ${GLEW_LIBRARIES}
        glfw
)
endif()

install(TARGETS 
        ${PROJECT_NAME} 
    DESTINATION 
        bin/
)

