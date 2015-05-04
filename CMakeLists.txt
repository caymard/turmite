cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT("turmite")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# x32 / x64 check
if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    MESSAGE( "64 bits compiler detected" )
    SET( EX_PLATFORM 64 )
    SET( EX_PLATFORM_NAME "x64" )
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    MESSAGE( "32 bits compiler detected" )
    SET( EX_PLATFORM 32 )
    SET( EX_PLATFORM_NAME "x86" )
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

# Windows / Linux check
if(WIN32)
	SET(EX_OS_NAME "windows")
else(WIN32)
	SET(EX_OS_NAME "linux")
endif(WIN32)


 SET(CMAKE_CURRENT_BINARY_DIR ${CMAKE_HOME_DIRECTORY}/bin/${EX_OS_NAME}/${EX_PLATFORM_NAME})

 SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/${EX_OS_NAME}/${EX_PLATFORM_NAME})

find_package(SDL2 REQUIRED)
message(${SDL2_INCLUDE_DIR})
message(${SDL2_LIBRARY})

# Turmite program
SET(SOURCES_TURMITE
	"src/mainturmite.cpp"
	"src/ant.cpp"
	"src/grid.cpp"
	"src/configloader.cpp"
	)

SET(INCLUDES_TURMITE
	"include/ant.h"
	"include/grid.h"
	"include/configloader.h")

INCLUDE_DIRECTORIES("include" ${SDL2_INCLUDE_DIR})

ADD_EXECUTABLE(turmite ${SOURCES_TURMITE} ${INCLUDES_TURMITE})

TARGET_LINK_LIBRARIES(turmite ${SDL2_LIBRARY})
