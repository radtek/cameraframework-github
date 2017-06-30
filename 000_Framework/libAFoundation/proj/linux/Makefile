
CC      = gcc
CPP     = g++
RM      = rm -rf

DIR_OBJ := .

## debug flag
DBG_ENABLE   = 0

## source file path
SRC_PATH   := ../../src

## target exec file name
TARGET     := libAFoundation.so

## get all source files
SRCS       := $(wildcard $(SRC_PATH)/*.cpp)

## all .o based on all .c
OBJS       := $(notdir $(SRCS:.cpp=.o))


## need libs, add at here
#LIBS := MyApi

## used headers  file path
INCLUDE_PATH := ../../include

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

## get all librarys
#LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))

## c++11 support
CFLAGS += -Wl,--no-as-needed  -lpthread -std=c++11

CFLAGS += -D LINUX_OS -fPIC

all:$(OBJS)
	$(CPP) -shared -fPIC $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS)
#$(RM) $(OBJS)
	cp $(TARGET) ../../lib/linux/
#cp $(TARGET) /usr/lib/

${DIR_OBJ}/%.o : $(SRC_PATH)/%.cpp
	@echo Compiling $< ...
	$(CPP) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)

#../../lib/linux/$(TARGET)