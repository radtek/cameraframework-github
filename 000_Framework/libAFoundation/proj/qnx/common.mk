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
EXTRA_INCVPATH+=$(PROJECT_ROOT)/../../include  \
	$(PROJECT_ROOT)/../../src

PROJECT_SRC=$(PROJECT_ROOT)/../../src

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH+=$(PROJECT_SRC)

#===== CCFLAGS - add the flags to the C compiler command line. 
CCFLAGS+=-DQNX_OS

#===== POST_BUILD - extra steps to do after building the image.
define POST_BUILD
#cp -f $(PROJECT_ROOT)/x86/so/libAFoundation.so $(PROJECT_ROOT)/../../lib/x86/
cp -f $(PROJECT_ROOT)/arm/so-le-v7/libAFoundation.so $(PROJECT_ROOT)/../../lib/arm/
endef

include $(MKFILES_ROOT)/qmacros.mk
#===== BUILDNAME - exact name (before appending suffixes like .a, .so) of build goal.
BUILDNAME=libAFoundation

ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)
postbuild:
	$(POST_BUILD)

include $(MKFILES_ROOT)/qtargets.mk

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

