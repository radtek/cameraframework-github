
RM      = rm -rf

## debug flag
DBG_ENABLE   = 0

## source file path
SRC_PATH   := .

OBJS_PATH  :=../../obj/

## target exec file name
TARGET     := nanotest

## get all source files
SRCS1       = $(wildcard $(SRC_PATH)/*.cpp)
OBJS1       = $(patsubst %.cpp,%.o,$(SRCS1))

OBJS = $(OBJS1)

## need libs, add at here
LIBS := AFoundation
LIBS += ABase
LIBS += ACaseSocket

LIBS += dlt
LIBS += nanomsg

## used headers  file path
INCLUDE_PATH := ../../include
INCLUDE_PATH += ../../include/Client
INCLUDE_PATH += ../../../../000_Framework/libAFoundation/include
INCLUDE_PATH += ../../../../000_Framework/libABase/include
INCLUDE_PATH += ../../../../000_Framework/libABase/include/external
INCLUDE_PATH += ../../../../000_Framework/libABase/include/ADASManager

## used include librarys file path
LIBRARY_PATH := ../../../../000_Framework/libAFoundation/lib/linux
LIBRARY_PATH += ../../../../000_Framework/libABase/lib/linux
LIBRARY_PATH += ../../../../000_Framework/CaseClient/lib/linux
LIBRARY_PATH += .
#LIBRARY_PATH += ~/install/lib

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
CFLAGS += -Wl,--no-as-needed  -lpthread

CFLAGS += -D LINUX_OS -fPIC -lm -lrt

all: build

build:	$(OBJS)
	$(CXX) $(CFLAGS) -lpthread -std=c++11 -o $(TARGET) $(addprefix $(OBJS_PATH), $(notdir $^)) $(LDFLAGS)

clean:
	$(RM) $(addprefix $(OBJS_PATH), $(notdir $(OBJS))) $(TARGET)

%.o: %.cpp
	$(CXX) -c -O3 $(CFLAGS) -std=c++11 $< -o $(OBJS_PATH)/$(notdir $@)

#%.o: %.c
#	$(CC) -c -O3 $(CFLAGS) $< -o $(OBJS_PATH)/$@
