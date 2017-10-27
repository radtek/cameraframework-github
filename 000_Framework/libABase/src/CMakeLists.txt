project (ABase)
add_definitions(-DLINUX_OS)
add_definitions("-Wl,--no-as-needed  -lpthread -std=c++11")
include_directories(${PROJECT_SOURCE_DIR}/../../libAFoundation/include)
include_directories(${PROJECT_SOURCE_DIR}/../../CaseClient/include)
include_directories(${PROJECT_SOURCE_DIR}/../include/ADASManager)
include_directories(${PROJECT_SOURCE_DIR}/../include/ADASManager/RVC)
include_directories(${PROJECT_SOURCE_DIR}/../include/ADASManager/Camera)
include_directories(${PROJECT_SOURCE_DIR}/../include/ADASManager/Camera/Display)
include_directories(${PROJECT_SOURCE_DIR}/../include/)


link_directories(${PROJECT_SOURCE_DIR}/../../libAFoundation/lib/linux)
link_directories(${PROJECT_SOURCE_DIR}/../../CaseClient/lib/linux)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib/linux)

MESSAGE(STATUS "This is lib ABase dir " ${PROJECT_SOURCE_DIR})
aux_source_directory(./ADASManager SRC_MANAGER)
aux_source_directory(./ADASManager/Camera SRC_MGR_CAM)
aux_source_directory(./ADASManager/Camera/Display SRC_MGR_DIS)
#aux_source_directory(./ADASManager/PAS SRC_MGR_PAS)
#aux_source_directory(./ADASManager/PAS/GraphicCore SRC_MGR_GRAPHICCORE)
aux_source_directory(./ADASManager/RVC SRC_MGR_RVC)
aux_source_directory(./ADASManager/AVM SRC_MGR_AVM)

target_link_libraries(AFoundation)
add_library(ABase SHARED ${SRC_MANAGER} ${SRC_MGR_CAM} ${SRC_MGR_DIS} ${SRC_MGR_RVC} ${SRC_MGR_AVM}
#add_library(ABase SHARED ${SRC_MANAGER} ${SRC_MGR_CAM} ${SRC_MGR_DIS} ${SRC_MGR_RVC} ${SRC_MGR_AVM} ${SRC_MGR_PAS} ${SRC_MGR_GRAPHICCORE})