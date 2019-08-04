delete ampsrv.mexmaci64
setenv(computer,'1')
mex -I../AmpServerProSDK/include -L../AmpServerProSDK/libs -lAS_Network_Client ampsrv.c AmpServerInterface.cpp MexInterface.cpp
