
#ADD_SUBDIRECTORY(ADASManager)
add_definitions(-DLINUX_OS)

AUX_SOURCE_DIRECTORY(./ADASManager ABASE_SRC)
AUX_SOURCE_DIRECTORY(./ADASManager/APA ABASE_SRC)
AUX_SOURCE_DIRECTORY(./ADASManager/AVM ABASE_SRC)
AUX_SOURCE_DIRECTORY(./ADASManager/Camera ABASE_SRC)
AUX_SOURCE_DIRECTORY(./ADASManager/Camera/Display ABASE_SRC)
AUX_SOURCE_DIRECTORY(./ADASManager/PAS ABASE_SRC)
AUX_SOURCE_DIRECTORY(./ADASManager/PAS/GraphicCore ABASE_SRC)
AUX_SOURCE_DIRECTORY(./ADASManager/RVC ABASE_SRC)

MESSAGE(STATUS "HW Platform is " ${HW_PLATFORM})

INCLUDE_DIRECTORIES(../../libAFoundation/include)
INCLUDE_DIRECTORIES(../../libAGraphic/include)
INCLUDE_DIRECTORIES(../../libAGraphic/include/GuideLine)
INCLUDE_DIRECTORIES(../include)
INCLUDE_DIRECTORIES(../include/ADASManager)

if("${HW_PLATFORM}" STREQUAL "UBUNTU_OS")  
	INCLUDE_DIRECTORIES(/root/install/include)
	LINK_DIRECTORIES(/root/install/lib)
endif()

MESSAGE(STATUS "This is lib ABase dir: " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "The src are: " ${ABASE_SRC})

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
MESSAGE(STATUS "This is lib out dir " ${LIBRARY_OUTPUT_PATH})

#add_library(AFoundation SHARED ${AFOUNDATION_SRC})
#ADD_EXECUTABLE(testAGraphic ${AGRAPHIC_SRC})
ADD_LIBRARY(ABase SHARED ${ABASE_SRC})
ADD_LIBRARY(ABase_static STATIC ${ABASE_SRC})
SET_TARGET_PROPERTIES(ABase_static PROPERTIES OUTPUT_NAME "ABase")

#TARGET_LINK_LIBRARIES(testAGraphic libEGL.so)
#TARGET_LINK_LIBRARIES(testAGraphic libGLESv2.so)
#TARGET_LINK_LIBRARIES(testAGraphic libwayland-client.so)
#TARGET_LINK_LIBRARIES(testAGraphic libwayland-egl.so)
#TARGET_LINK_LIBRARIES(testAGraphic libpthread.so)
#TARGET_LINK_LIBRARIES(testAGraphic libwayland-cursor.so)
#TARGET_LINK_LIBRARIES(testAGraphic libilmControl.so)

IF("${HW_PLATFORM}" STREQUAL "UBUNTU_OS")  
	#SET(DESTINATION lib)
	INSTALL(TARGETS ABase ABase_static
		#RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
	)
ELSEIF("${HW_PLATFORM}" STREQUAL "LINUX_OS") 
	#SET(DESTINATION elina/2.0.2015143A/sysroots/corei7-64-elina-linux/usr)	
	INSTALL(TARGETS ABase ABase_static
		#RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib/adas
		ARCHIVE DESTINATION lib/adas
	)
ENDIF()
