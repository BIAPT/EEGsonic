
#Robert Bell                                                                                                         
#Copyright EGI 2011 - All Rights Reserved. CONFIDENTIAL

ROOT=$(shell pwd)

MATLAB=/Applications/MATLAB_R2017a.app

MEX=${MATLAB}/bin/mex

INCLUDEDIRS = -I../../include/base \
              -I../../include/sdk \

LIBS = -lAS_Network_Client -lpthread

LIBDIRS = -L../../libs/sdk

INSTALLDIR=${MATLAB}/extern/examples/mex

.SUFFIXES :

default:
	${MEX} ${INCLUDEDIRS} ${LIBDIRS} ${LIBS} ampsrv.c NotificationObserver.cpp DataStreamObserver.cpp AmpServerInterface.cpp MexInterface.cpp

install:
	cp ampsrv.mexmaci64 ${INSTALLDIR}

clean:
	rm -rf ampsrv.mexmaci64

cleanAll:
	rm -rf ampsrv.mexmaci64
	rm -rf *~
