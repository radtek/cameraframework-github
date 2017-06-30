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
LDFLAGS+=-lang-c++ -ljsoncpp -ldbus-1 -lPocoFoundation  \
	-lGraphics -lAbase -lsvcipc -lsys_trace_clienttrace  \
	-lsys_colibry -lsys_colibry_net

VFLAG_g=-gstabs+

#===== LIBS - a space-separated list of library items to be included in the link.
LIBS+=screen EGL GLESv2 m img pps capture

#===== EXTRA_LIBVPATH - a space-separated list of directories to search for library files.
EXTRA_LIBVPATH+=$(PROJECT_ROOT)/lib  \
	$(LOCAL_SVN_SRC_PATH_ADAS)/Application/Adas/Core/Graphics/lib  \
	$(LOCAL_SVN_SRC_PATH_ADAS)/Foundation/lib  \
	$(LOCAL_P4_SRC_PATH_ADAS)/Target/qnx6\armle-v7\usr\lib  
	#$(LOCAL_P4_SRC_PATH_ADAS)/Target/qnx6\armle-v7\lib

#===== EXTRA_INCVPATH - a space-separated list of directories to search for include files.
EXTRA_INCVPATH+=$(PROJECT_ROOT)/../../src  \
	$(LOCAL_SVN_SRC_PATH_ADAS)/Foundation/src  \
	$(LOCAL_P4_SRC_PATH_ADAS)/Target/qnx6/armle-v7/usr/include/api/sys/tracesrv/pf/trace/src  \
	$(LOCAL_SVN_SRC_PATH_ADAS)/Application/Adas/Core/Graphics/src  \
	D:/localToVm/00_code/08_MAN_Scania/00_zchCode/Application/Adas/Customer/Scania/src/logic  \
    $(LOCAL_P4_SRC_PATH_ADAS)/Target/qnx6/armle-v7/usr/include  
#$(LOCAL_P4_SRC_PATH_ADAS)/Drivers/Qnx6  

PROJECT_SRC=$(PROJECT_ROOT)/../../src

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH+=$(PROJECT_SRC) $(PROJECT_SRC)/svcIpc  \
	$(PROJECT_SRC)/logic $(PROJECT_SRC)/graphics  \
	$(PROJECT_SRC)/framework $(PROJECT_SRC)/framework/common  \
	$(PROJECT_SRC)/pps $(PROJECT_SRC)/framework/config  \
	$(PROJECT_SRC)/framework/svcIpc  \
	$(PROJECT_SRC)/framework/pps  \
	#$(LOCAL_P4_SRC_PATH_ADAS)/Drivers/Qnx6

#===== CCFLAGS - add the flags to the C compiler command line. 
CCFLAGS+=-DPLATFORM_QNX -DCAPTURE_ADV

#===== POST_BUILD - extra steps to do after building the image.
define POST_BUILD
cp -f $(PROJECT_ROOT)/arm/o-le-v7/adas D:/mnttest/adas
#cp -f $(PROJECT_ROOT)/arm/o-le-v7/adas D:/localToVm/00000000/MS/local/adas
endef

include $(MKFILES_ROOT)/qmacros.mk

#===== BUILDNAME - exact name (before appending suffixes like .a, .so) of build goal.
BUILDNAME=adas

ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

postbuild:
	$(POST_BUILD)
OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

