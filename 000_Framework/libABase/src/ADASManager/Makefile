#子目录的Makefile直接读取其子目录就行
#SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 == "Camera") print $$9}')
SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 == "Camera" || $$9 == "CameraDisplay" || $$9 == "RVC") print $$9}')
#以下同根目录下的makefile的相同代码的解释
CUR_SOURCE=${wildcard *.cpp}
CUR_OBJS=${patsubst %.cpp, %.o, $(CUR_SOURCE)}
all:$(SUBDIRS) $(CUR_OBJS)
$(SUBDIRS):ECHO
	make -C $@
$(CUR_OBJS):%.o:%.cpp
	$(CXX) -c $(CFLAGS) $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@
ECHO:
	@echo $(SUBDIRS)