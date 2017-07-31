project (CaseClientDeamon)

#add_definitions(-DLINUX_OS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX_OS -lpthread -std=c++11")

include_directories(${PROJECT_SOURCE_DIR}/../../../../libAFoundation/include)
include_directories(${PROJECT_SOURCE_DIR}/../../../include)
include_directories(${PROJECT_SOURCE_DIR}/../../../include/)
include_directories(${PROJECT_SOURCE_DIR})

link_directories(${PROJECT_SOURCE_DIR}/../../../../libAFoundation/lib/linux)
link_directories(${PROJECT_SOURCE_DIR}/../../../lib/linux)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../../bin/linux)

MESSAGE(STATUS "This is binary CaseClientDeamon dir " ${PROJECT_SOURCE_DIR})

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} CASECLIENTDEAMON_SRC)
ADD_EXECUTABLE(CaseClientDeamon ${CASECLIENTDEAMON_SRC})

target_link_libraries(CaseClientDeamon AFoundation ACaseSocket rt)