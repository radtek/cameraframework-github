
CC      = gcc
CPP     = g++
RM      = rm -rf

DIR_OBJ := ../../../proj/linux/Deamon

## debug flag
DBG_ENABLE   = 1

## source file path
SRC_PATH   := ./

## target exec file name
TARGET     := CaseClientDeamon

TARGET_PATH  := ../../../bin/linux

## get all source files
SRCS       := $(wildcard $(SRC_PATH)/*.cpp)

## all .o based on all .c
#OBJS       := $(notdir $(SRCS:.cpp=.o))
OBJS    := $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRCS}))


## need libs, add at here
LIBS := AFoundation
LIBS += ACaseSocket
#LIBS := MyApi

## used headers  file path
INCLUDE_PATH := .
INCLUDE_PATH += ../../../../libAFoundation/include/
## used include librarys file path
LIBRARY_PATH := ../../../../libAFoundation/lib/linux
LIBRARY_PATH += ../../../lib/linux
LIBRARY_PATH += lib
#LIBRARY_PATH += ../../../../000_Framework/libABase/lib/linux

## debug for debug info, when use gdb to debug
ifeq (1, ${DBG_ENABLE})
CFLAGS += -D_DEBUG -O0 -g -DDEBUG=1
endif

## get all include path
CFLAGS  += $(foreach dir, $(INCLUDE_PATH), -I$(dir))

## get all library path
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))

## get all librarys
LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))

## c++11 support
CFLAGS += -Wl,--no-as-needed  -lpthread -std=c++11

CFLAGS += -D LINUX_OS

CFLAGS += -D__FILENAME__='"$(subst $(dir $<),,$<)"'

all:$(OBJS)
	$(CPP) $(CFLAGS) $(LDFLAGS) -o $(TARGET_PATH)/$(TARGET) $(OBJS)
	#kill -n 9 $(pidof CaseClientDeamon)
	cp $(TARGET_PATH)/$(TARGET) /usr/bin

${DIR_OBJ}/%.o : $(SRC_PATH)/%.cpp
	@echo Compiling $< ...
	$(CPP) -c $(CFLAGS) $< -o ${DIR_OBJ}/$*.o

clean:
	$(RM) $(OBJS) $(TARGET_PATH)/$(TARGET)