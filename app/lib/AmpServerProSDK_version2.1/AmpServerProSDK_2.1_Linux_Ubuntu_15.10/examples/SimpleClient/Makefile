#Robert Bell
#Copyright EGI 2006 - All Rights Reserved. CONFIDENTIAL

include make.include/Makefile

INCLUDEDIRS = -I../../include/base \
              -I../../include/sdk \

LIBS = -lAS_Network_Client -lpthread

LIBDIRS = -L../../libs/sdk

CXX = ${LINUX_CXX}

CXXFLAGS = ${LINUX_CXXFLAGS}

LINKOPTS = ${BUILD_LEVEL}

OBJS = 	simpleClient.o DataStreamObserver.o NotificationObserver.o PhysioDetection.o

.SUFFIXES : .o

default : ${OBJS}
	${CXX} ${LINKOPTS} -o simpleClient ${OBJS} ${LIBDIRS} ${LIBS}

.cpp.o : 
	${CXX} ${CXXFLAGS} -c $< ${INCLUDEDIRS}

clean :
	rm -rf *.o
	rm -rf simpleClient

cleanAll:
	rm -rf *.o
	rm -rf simpleClient
	rm -rf *~
