cmake_minimum_required(VERSION 2.8.3)
project(hear_architecture)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

find_package(Boost REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS
    roscpp
)

include_directories(
  include libs
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

FILE(GLOB SOURCE_FILES
        src/*.cpp
        )

add_library(${PROJECT_NAME}
${SOURCE_FILES}
)
