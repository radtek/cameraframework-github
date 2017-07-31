project (ACaseSocket)
add_definitions(-DLINUX_OS)
include_directories(${PROJECT_SOURCE_DIR}/../../../libAFoundation/include)
add_definitions("-Wl,--no-as-needed  -lpthread -std=c++11")
link_directories(${PROJECT_SOURCE_DIR}/../../../libAFoundation/lib/linux)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib/linux)

MESSAGE(STATUS "This is lib ASocket dir " ${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../../include/)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} ASOCKET_SRC)
target_link_libraries(AFoundation)
add_library(ACaseSocket SHARED ${ASOCKET_SRC})