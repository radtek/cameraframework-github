
CP = cp
#debug文件夹里的makefile文件需要最后执行，所以这里需要执行的子目录要排除debug文件夹，这里使用awk排除了debug文件夹，读取剩下的文件夹
SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 == "src") print $$9}')
#无需下一行的注释代码，因为我们已经知道debug里的makefile是最后执行的，所以最后直接去debug目录下执行指定的makefile文件就行，具体下面有注释
#DEBUG=$(shell ls -l | grep ^d | awk '{if($$9 == "debug") print $$9}')
#记住当前工程的根目录路径
ROOT_DIR=$(shell pwd)
#最终bin文件的名字，可以更改为自己需要的
BIN=libABase.so
#目标文件所在的目录
#OBJS_DIR=debug/obj
OBJS_DIR=proj/linux/obj
#bin文件所在的目录
#BIN_DIR=debug/bin
BIN_DIR=lib/linux
#获取当前目录下的c文件集，放在变量CUR_SOURCE中
CUR_SOURCE=${wildcard *.cpp}
#将对应的c文件名转为o文件后放在下面的CUR_OBJS变量中
CUR_OBJS=${patsubst %.cpp, %.o, $(CUR_SOURCE)}

INCLUDE_PATH := $(ROOT_DIR)/include
INCLUDE_PATH += $(ROOT_DIR)/include/ADASManager
INCLUDE_PATH += $(ROOT_DIR)/include/external
INCLUDE_PATH += $(ROOT_DIR)/../libAFoundation/include
INCLUDE_PATH += $(ROOT_DIR)/../CaseClient/include

LIBS := dlt


CFLAGS= -Wl,--no-as-needed  -lpthread -std=c++11 -D LINUX_OS -D ENABLE_EGL -fPIC
CFLAGS+= $(foreach dir, $(INCLUDE_PATH), -I$(dir))

LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))
#CFLAGS += -D__FILENAME__='"$(subst $(dir $<),,$<)"'
#将以下变量导出到子shell中，本次相当于导出到子目录下的makefile中
export CXX BIN OBJS_DIR BIN_DIR ROOT_DIR CFLAGS LDFLAGS
#注意这里的顺序，需要先执行SUBDIRS最后才能是DEBUG
all:$(SUBDIRS) $(CUR_OBJS) DEBUG
#递归执行子目录下的makefile文件，这是递归执行的关键
$(SUBDIRS):ECHO
	make -C $@
DEBUG:ECHO
    #直接去debug目录下执行makefile文件
	#make -C debug
	make -C proj
ECHO:
	@echo $(SUBDIRS)
#将c文件编译为o文件，并放在指定放置目标文件的目录中即OBJS_DIR
$(CUR_OBJS):%.o:%.cpp
	$(CXX) -c  $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@
clean:
	@rm $(OBJS_DIR)/*.o
	@rm -rf $(BIN_DIR)/*.so

cp:
	$(CP) $(ROOT_DIR)/$(BIN_DIR)/$(BIN) /usr/lib
