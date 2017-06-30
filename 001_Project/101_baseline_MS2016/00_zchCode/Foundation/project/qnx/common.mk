# This is an automatically generated record.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#===== USEFILE - the file containing the usage message for the application. 
USEFILE=

# Next lines are for C++ projects only

EXTRA_SUFFIXES+=cxx cpp

#===== LDFLAGS - add the flags to the linker command line.
LDFLAGS+=-lang-c++

VFLAG_g=-gstabs+

#===== EXTRA_INCVPATH - a space-separated list of directories to search for include files.
EXTRA_INCVPATH+=$(PROJECT_ROOT)/../../src/common  \
	$(PROJECT_ROOT)/../../src/thread  \
	$(PROJECT_ROOT)/../../src/math  \
	$(PROJECT_ROOT)/../../src/config  \
	$(PROJECT_ROOT)/../../src/log  \
	$(PROJECT_ROOT)/../../src/timer  \
	$(PROJECT_ROOT)/../../src/message  \
	$(PROJECT_ROOT)/../../src/memory $(PROJECT_ROOT)/../../src  \
	#D:/localToVm/00_code/08_MAN_Scania/p4_10.80.98.243530_Unicore_ADAS/Unicorn/Target/qnx6/armle-v7/usr/include

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH+=$(PROJECT_ROOT)/../../src/common  \
	$(PROJECT_ROOT)/../../src/thread  \
	$(PROJECT_ROOT)/../../src/thread/qnx  \
	$(PROJECT_ROOT)/../../src/config  \
	$(PROJECT_ROOT)/../../src/math  \
	$(PROJECT_ROOT)/../../src/log  \
	$(PROJECT_ROOT)/../../src/timer  \
	$(PROJECT_ROOT)/../../src/message  \
	$(PROJECT_ROOT)/../../src/memory $(PROJECT_ROOT)/../../src

#===== CCFLAGS - add the flags to the C compiler command line. 
CCFLAGS+=-DPLATFORM_QNX

include $(MKFILES_ROOT)/qmacros.mk

#===== BUILDNAME - exact name (before appending suffixes like .a, .so) of build goal.
BUILDNAME=libAbase

#===== POST_BUILD - extra steps to do after building the image.
define POST_BUILD
cp -f $(PROJECT_ROOT)/arm/so-le-v7/libAbase.so D:/mnttest/libAbase.so.1
#cp -f $(PROJECT_ROOT)/arm/so-le-v7/libAbase.so D:/localToVm/00000000/MS/local/libAbase.so.1

endef


ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk
postbuild:
	$(POST_BUILD)
OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

