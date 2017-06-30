# This is an automatically generated record.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)
ifndef LOCAL_P4_SRC_PATH_ADAS
LOCAL_P4_SRC_PATH_ADAS=D:/localToVm/00_code/08_MAN_Scania/p4_Unicore_ADAS/Unicorn
endif

ifndef LOCAL_SVN_SRC_PATH_ADAS
LOCAL_SVN_SRC_PATH_ADAS=../../../../../../00_zchCode
endif

#===== USEFILE - the file containing the usage message for the application. 
USEFILE=

# Next lines are for C++ projects only

EXTRA_SUFFIXES+=cxx cpp

#===== LDFLAGS - add the flags to the linker command line.
LDFLAGS+=-lang-c++

VFLAG_g=-gstabs+

#===== EXTRA_INCVPATH - a space-separated list of directories to search for include files.
EXTRA_INCVPATH+=$(PROJECT_ROOT)/../../include/screen/usr/include  \
	$(PROJECT_ROOT)/../../include  \
	$(PROJECT_ROOT)/../../src/videoCapture  \
	$(PROJECT_ROOT)/../../src/videoCapture/adv7182  \
	$(PROJECT_ROOT)/../../src/graphics/pipeline  \
	$(PROJECT_ROOT)/../../src/graphics/resource  \
	$(PROJECT_ROOT)/../../src  \
	$(PROJECT_ROOT)/../../src/graphics  \
	$(LOCAL_SVN_SRC_PATH_ADAS)/Foundation/src  \
	$(LOCAL_P4_SRC_PATH_ADAS)/Target/qnx6/armle-v7/usr/include  \
	$(LOCAL_P4_SRC_PATH_ADAS)/Target/qnx6/armle-v7/usr/include/api/sys/tracesrv/pf/trace/src

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH+=$(PROJECT_ROOT)/../../src/videoCapture  \
	$(PROJECT_ROOT)/../../src/videoCapture/adv7182  \
	$(PROJECT_ROOT)/../../src/graphics/pipeline  \
	$(PROJECT_ROOT)/../../src/graphics/resource  \
	$(PROJECT_ROOT)/../../src  \
	$(PROJECT_ROOT)/../../src/graphics  \
	$(PROJECT_ROOT)/../../src/simple
	
#===== CCFLAGS - add the flags to the C compiler command line. 
CCFLAGS+=-DPLATFORM_QNX -DCAPTURE_ADV

#===== POST_BUILD - extra steps to do after building the image.
define POST_BUILD
cp -f $(PROJECT_ROOT)/arm/so-le-v7/libGraphics.so $(PROJECT_ROOT)/../../lib/libGraphics.so
cp -f $(PROJECT_ROOT)/arm/so-le-v7/libGraphics.so $(PROJECT_ROOT)/arm/so-le-v7/libGraphics.so.1
cp -f $(PROJECT_ROOT)/arm/so-le-v7/libGraphics.so D:/mnttest/libGraphics.so.1
#cp -f $(PROJECT_ROOT)/arm/so-le-v7/libGraphics.so D:/localToVm/00000000/MS/local/libGraphics.so.1
endef

include $(MKFILES_ROOT)/qmacros.mk

#===== BUILDNAME - exact name (before appending suffixes like .a, .so) of build goal.
BUILDNAME=libGraphics

ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

postbuild:
	$(POST_BUILD)
OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

