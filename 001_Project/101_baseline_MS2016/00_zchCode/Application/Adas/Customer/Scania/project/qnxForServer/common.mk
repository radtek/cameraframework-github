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
LDFLAGS+=-lang-c++ -lAbase -ljsoncpp -lsvcipc -ldbus-1  \
	-lPocoFoundation -lsys_trace_clienttrace -lsys_colibry  \
	-lsys_colibry_net -lGraphics -lpps

VFLAG_g=-gstabs+



#===== LIBS - a space-separated list of library items to be included in the link.
LIBS+=screen EGL GLESv2 m img pps capture

#===== EXTRA_INCVPATH - a space-separated list of directories to search for include files.
PATH_PACKAGE:= $(shell eval ' \
	topdir() { \
		currdir="`(cd "$$1" && pwd)`"; \
	        count=`ls -1d "$$1/Base" "$$1/Make" 2>/dev/null | wc -l`; \
		if [ $$count -eq 2 ] ; then echo "$$currdir"; \
		elif [ x"$$currdir" = x"/" ] ; then return 1; \
		else topdir "../$$1"; \
		fi \
		}; \
	topdir .')

export PATH_PACKAGE

PATH_TARGET=${PATH_PACKAGE}/Target/qnx6/armle-v7
PATH_BSP=${PATH_PACKAGE}/Bsp
PATH_BASE=${PATH_PACKAGE}/Base
PATH_ADASFW=${PATH_PACKAGE}/Application/Adas/Core/Graphics

EXTRA_INCVPATH+= \
	${PATH_BASE} \
	${PATH_TARGET}/usr/include  \
	${PATH_BSP}/Qnx/bsp-nto650-hbas/trunk/src/prebuilt/usr/include  \
	${PATH_ADASFW}
	
#===== EXTRA_LIBVPATH - a space-separated list of directories to search for library files.
EXTRA_LIBVPATH+=${PATH_TARGET}/usr/lib  \
		${PATH_TARGET}/lib  \
		${PATH_ADASFW}/lib


#===== EXTRA_INCVPATH - a space-separated list of directories to search for include files.
EXTRA_INCVPATH+= \
        $(PROJECT_ROOT)/../../src  \
	${PATH_BASE} \
	${PATH_TARGET}/usr/include  \
	${PATH_TARGET}/usr/include/api/sys/tracesrv/pf/trace/src  \
	$(PATH_ADASFW)/src  \
	$(PATH_ADASFW)/src/foundation\common  \
	$(PATH_ADASFW)/src/foundation

PROJECT_SRC=$(PROJECT_ROOT)/../../src

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH+= \
        $(PROJECT_SRC) $(PROJECT_SRC)/svcIpc  \
	$(PROJECT_SRC)/logic \
	$(PROJECT_SRC)/graphics  \
	$(PROJECT_SRC)/framework $(PROJECT_SRC)/framework/common  \
	$(PROJECT_SRC)/framework/config  \
	$(PROJECT_SRC)/framework/logic  \
	$(PROJECT_SRC)/framework/svcIpc

#===== CCFLAGS - add the flags to the C compiler command line. 
CCFLAGS+=-DCAPTURE_ADV CAPTURE_J5

include $(MKFILES_ROOT)/qmacros.mk

#===== BUILDNAME - exact name (before appending suffixes like .a, .so) of build goal.
BUILDNAME=adas

ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)



include $(MKFILES_ROOT)/qtargets.mk

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

