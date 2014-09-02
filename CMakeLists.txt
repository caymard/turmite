cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT("turmite")

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

LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.0.3/lib/${EX_PLATFORM_NAME}")
EXECUTE_PROCESS(COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.0.3/lib/${EX_PLATFORM_NAME}/SDL2.dll ${CMAKE_CURRENT_BINARY_DIR}/Release/SDL2.dll)
EXECUTE_PROCESS(COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.0.3/lib/${EX_PLATFORM_NAME}/SDL2.dll ${CMAKE_CURRENT_BINARY_DIR}/Debug/SDL2.dll)
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.0.3/include")

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

INCLUDE_DIRECTORIES("include")

ADD_EXECUTABLE(turmite ${SOURCES_TURMITE} ${INCLUDES_TURMITE})

TARGET_LINK_LIBRARIES(turmite SDL2)