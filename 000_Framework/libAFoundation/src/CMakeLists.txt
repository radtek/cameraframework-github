project (AFoundation)
add_definitions("-Wl,--no-as-needed  -lpthread -std=c++11")
add_definitions(-DLINUX_OS)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib/linux)

MESSAGE(STATUS "This is lib AFoundation dir" ${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../include/)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} AFOUNDATION_SRC)

add_library(AFoundation SHARED ${AFOUNDATION_SRC})