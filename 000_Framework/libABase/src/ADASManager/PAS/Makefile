#子目录的Makefile直接读取其子目录就行
SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 == "Res" || $$9 == "GraphicCore") print $$9}')
#以下同根目录下的makefile的相同代码的解释
CUR_SOURCE=${wildcard *.cpp}
CUR_OBJS=${patsubst %.cpp, %.o, $(CUR_SOURCE)}

all:$(SUBDIRS) $(CUR_OBJS)
$(SUBDIRS):ECHO
	perl Png2PngRes.pl Png.list
	perl PngRes2Cpp.pl Png.list
	make -C $@
$(CUR_OBJS):%.o:%.cpp
	$(CXX) -c $(CFLAGS) $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@
ECHO:
	@echo $(SUBDIRS)
