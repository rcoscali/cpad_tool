cmake_minimum_required(VERSION 2.6)
 
Project(CreateGraph)
 
set(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE(Boost 1.38 COMPONENTS required)
 
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})
 
ADD_EXECUTABLE(CreateGraph CreateGraph.cc)
target_link_libraries(CreateGraph)
