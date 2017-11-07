
RM      = rm -rf
CP      = cp

DIR_OBJ := ../proj/linux

## debug flag
DBG_ENABLE   = 0

## source file path
SRC_PATH   := .

## target exec file name
TARGET     := libAGraphic.so

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

LIBS := dlt nanomsg

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

#CFLAGS += -D__FILENAME__='"$(subst $(dir $<),,$<)"'

all:$(OBJS)
	$(CXX) -shared -fPIC $(CFLAGS) $(LDFLAGS) -o $(TARGET_PATH)/$(TARGET) $(OBJS)
	$(RM) ../../../001_Project/001_GWMV2MH/libAGraphic/include/*
	$(CP) -rf ../include/* ../../../001_Project/001_GWMV2MH/libAGraphic/include
	$(RM) ../../../001_Project/001_GWMV2MH/libAGraphic/lib/linux/*
	$(CP) -rf ../lib/linux/* ../../../001_Project/001_GWMV2MH/libAGraphic/lib/linux
	sudo $(CP) -fv ../lib/linux/libAGraphic.so /opt/elina/2.0.2015143A/sysroots/corei7-64-elina-linux/lib/

${DIR_OBJ}/%.o : $(SRC_PATH)/%.cpp
	@echo Compiling $< ...
	$(CXX) -c $(CFLAGS) $< -o ${DIR_OBJ}/$*.o

clean:
	$(RM) $(OBJS) $(TARGET_PATH)/$(TARGET)

cp:
	$(CP) $(TARGET_PATH)/$(TARGET) /usr/lib
