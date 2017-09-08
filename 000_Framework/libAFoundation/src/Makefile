
RM      = rm -rf
CP      = cp

DIR_OBJ := ../proj/linux

## debug flag
DBG_ENABLE   = 0

## source file path
SRC_PATH   := .

## target exec file name
TARGET     := libAFoundation.so

TARGET_PATH  := ../lib/linux

## get all source files
SRCS       := $(wildcard $(SRC_PATH)/*.cpp)

## all .o based on all .c
#OBJS       := $(notdir $(SRCS:.cpp=.o))
OBJS    := $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRCS}))


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

## get all librarys
#LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))

## c++11 support
CFLAGS += -Wl,--no-as-needed  -lpthread -std=c++11

CFLAGS += -D LINUX_OS -fPIC

#CFLAGS += -D__FILENAME__='"$(subst $(dir $<),,$<)"'

all:$(OBJS)
	$(CXX) -shared -fPIC $(CFLAGS) $(LDFLAGS) -o $(TARGET_PATH)/$(TARGET) $(OBJS)

${DIR_OBJ}/%.o : $(SRC_PATH)/%.cpp
	@echo Compiling $< ...
	$(CXX) -c $(CFLAGS) $< -o ${DIR_OBJ}/$*.o

clean:
	$(RM) $(OBJS) $(TARGET_PATH)/$(TARGET)

cp:
	$(CP) $(TARGET_PATH)/$(TARGET) /usr/lib
