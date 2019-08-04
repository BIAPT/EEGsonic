
# Global Stuff.

#######
# Build level.
#######

DEBUG = -g
RELEASE = -Os

BUILD_LEVEL = $(RELEASE)

#######
# End - Build level.
#######

#######
# General.
#######
#######
# End - General.
#######


#######
# Objs.
#######

OBJS = 	client.o

#######
# End - Objs.
#######

#######
# Mach.
#######

MACH_CXX = g++

MACH_ARCHS = intel_64
MACH_BASE_OS_VERSION = -mmacosx-version-min=10.10

MACH_INTEL_64_ARCH = -arch x86_64
MACH_INTEL_64_CXXFLAGS = $(MACH_INTEL_64_ARCH) $(BUILD_LEVEL) $(MACH_BASE_OS_VERSION)

#######
# End - Mach.
#######

#######
# Linux.
#######

LINUX_CXX = g++
LINUX_CXXFLAGS = $(BUILD_LEVEL) -Wno-multichar

#######
# End - Linux.
#######
