
RM      = rm -rf
CP      = cp

DIR_OBJ := ../proj/linux

ROOT_DIR=$(shell pwd)

## debug flag
DBG_ENABLE   = 0

## source file path
SRC_PATH   := .

## target exec file name
TARGET     := libAFoundation.so

TARGET_PATH  := ../lib/linux

## get all source files
#SRCS       := $(wildcard $(SRC_PATH)/*.cpp)

SRCS += CCRef.cpp
SRCS += CMessageHandler.cpp
SRCS += CRunableBase.cpp
SRCS += CMessageQueue.cpp
SRCS += CTimer.cpp
SRCS += State.cpp
SRCS += CMessage.cpp
SRCS += CMQRunnableService.cpp
SRCS += Epoller.cpp
SRCS += MessageForQueue.cpp
SRCS += StateMachine.cpp
ifeq ($(PLATFORM), board)
SRCS += EpollGPIO.cpp
SRCS += NanoIPC.cpp
endif

## all .o based on all .c
#OBJS       := $(notdir $(SRCS:.cpp=.o))
OBJS    := $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRCS}))

ifneq ($(PLATFORM), board)
CFLAGS += -D _UBUNTU_
endif


## need libs, add at here
#LIBS := MyApi

## used headers  file path
INCLUDE_PATH := ../include

## used include librarys file path
LIBRARY_PATH := lib

## debug for debug info, when use gdb to debug
ifeq (1, ${DBG_ENABLE})
CFLAGS += -D_DEBUG -O0 -g -DDEBUG=1
endif

## get all include path
CFLAGS  += $(foreach dir, $(INCLUDE_PATH), -I$(dir))

## get all library path
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))

LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))

## get all librarys
#LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))

## c++11 support
CFLAGS += -Wl,--no-as-needed  -lpthread -std=c++11

CFLAGS += -D LINUX_OS -fPIC

#echo -n "snow" | sudo -S $(CP) -fv ../lib/linux/libAFoundation.so /opt/elina/2.0.2015143A/sysroots/corei7-64-elina-linux/lib/

#CFLAGS += -D__FILENAME__='"$(subst $(dir $<),,$<)"'

all:$(OBJS)
	$(CXX) -shared -fPIC $(CFLAGS) $(LDFLAGS) -o $(TARGET_PATH)/$(TARGET) $(OBJS)
ifeq ($(PLATFORM), board)
	sudo $(RM) -rf $(CMAKE_SYSROOT)/usr/include/adas/libAFoundation
	sudo $(CP) -rf ../include $(CMAKE_SYSROOT)/usr/include/adas/libAFoundation
	sudo $(RM) $(CMAKE_SYSROOT)/usr/lib/adas/libAFoundation*
	sudo $(CP) -rf ../lib/linux/libAFoundation* $(CMAKE_SYSROOT)/usr/lib/adas
else
	sudo $(RM) /usr/lib/libAFoundation*
	sudo $(CP) -rf ../lib/linux/libAFoundation* /usr/lib/
endif


${DIR_OBJ}/%.o : $(SRC_PATH)/%.cpp
	@echo Compiling $< ...
	$(CXX) -c $(CFLAGS) $< -o ${DIR_OBJ}/$*.o

clean:
	$(RM) $(DIR_OBJ)/*.o $(TARGET_PATH)/$(TARGET)

cp:
	$(CP) $(TARGET_PATH)/$(TARGET) /usr/lib
