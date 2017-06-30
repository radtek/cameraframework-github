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
LDFLAGS+=-lang-c++ -ljsoncpp -lsvcipc -ldbus-1  \
	-lPocoFoundation -lsys_trace_clienttrace -lsys_colibry  \
	-lsys_colibry_net
VFLAG_g=-gstabs+

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

EXTRA_INCVPATH+= \
	${PATH_BASE} \
	${PATH_TARGET}/usr/include  \
	${PATH_BSP}/Qnx/bsp-nto650-hbas/trunk/src/prebuilt/usr/include

#===== EXTRA_LIBVPATH - a space-separated list of directories to search for library files.
EXTRA_LIBVPATH+=${PATH_TARGET}/usr/lib

#===== NAME - name of the project (default - name of project directory).
NAME=Adas

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

release: all
	@cp -fr ${NAME} ${PATH_TARGET}/usr/bin ";"

