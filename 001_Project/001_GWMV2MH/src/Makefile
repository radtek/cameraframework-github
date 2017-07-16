
CC      = gcc
CPP     = g++
RM      = rm -rf

## debug flag
DBG_ENABLE   = 0

## source file path
SRC_PATH   := .

OBJS_PATH  :=../prj/linux/


## target exec file name
TARGET     := adasmain

## get all source files
SRCS       += $(wildcard $(SRC_PATH)/*.cpp $(SRC_PATH)/Rvc/*.cpp $(SRC_PATH)/Camera/*.cpp)

## all .o based on all .c
OBJS       := $(SRCS:.cpp=.o)

## need libs, add at here
LIBS := AFoundation
LIBS += ABase
LIBS += ACaseSocket
## used headers  file path
INCLUDE_PATH :=  ../include
INCLUDE_PATH += ../../../000_Framework/libAFoundation/include
INCLUDE_PATH += ../../../000_Framework/libABase/include
INCLUDE_PATH += ../../../000_Framework/CaseClient/include
## used include librarys file path
LIBRARY_PATH :=  ../../../000_Framework/libAFoundation/lib/linux
LIBRARY_PATH += ../../../000_Framework/libABase/lib/linux
LIBRARY_PATH += ../../../000_Framework/CaseClient/lib/linux
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

CFLAGS += -D LINUX_OS -fPIC -lm -lrt

#CFLAGS += -D__FILENAME__='"$(subst $(dir $<),,$<)"'

all: build

build:	$(OBJS)
#	$(CPP) -c $(CFLAGS) $(SRCS)
	$(CPP) $(CFLAGS) -lpthread -o $(TARGET) $(addprefix $(OBJS_PATH), $^) $(LDFLAGS)
#	$(RM) $(OBJS)

clean:
	$(RM) $(OBJS_PATH)/$@ $(TARGET)

%.o: %.cpp
	$(CPP) -c -O3 $(CFLAGS) $< -o $(OBJS_PATH)/$@