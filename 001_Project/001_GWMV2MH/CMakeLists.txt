project (adas)

#add_definitions(-DLINUX_OS)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX_OS -lpthread -std=c++11")
add_definitions(-DLINUX_OS)
add_definitions("-Wl,--no-as-needed  -lpthread -std=c++11")

include_directories(${PROJECT_SOURCE_DIR}/../../000_Framework/libAFoundation/include)
include_directories(${PROJECT_SOURCE_DIR}/../../000_Framework/libABase/include)
include_directories(${PROJECT_SOURCE_DIR}/../../000_Framework/CaseClient/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/Rvc)
include_directories(${PROJECT_SOURCE_DIR}/include/Camera)


link_directories(${PROJECT_SOURCE_DIR}/../../000_Framework/libAFoundation/lib/linux)
link_directories(${PROJECT_SOURCE_DIR}/../../000_Framework/libABase/lib/linux)
link_directories(${PROJECT_SOURCE_DIR}/../../000_Framework/CaseClient/lib/linux)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/linux)

MESSAGE(STATUS "This is binary ADAS dir " ${PROJECT_SOURCE_DIR})

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src MAIN_SRC)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src/Camera CAM_SRC)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src/Rvc RVC_SRC)

ADD_EXECUTABLE(adas ${MAIN_SRC} ${CAM_SRC} ${RVC_SRC})

target_link_libraries(adas AFoundation ABase ACaseSocket rt)