
/*
 *  MexInterface.cpp
 *  @author Robert Bell
 *  @date 2007/09/01
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br> 
 */

#include "AmpServerInterface.h"
#include "MexInterface.h"

#include <iostream>
#include <fstream>


extern "C" int mexConnect( char* ip_address )
{
  return AmpServerInterface::GetAmpServer()->connect(ip_address);
}

extern "C" int mexDisconnect()
{
  return AmpServerInterface::GetAmpServer()->disconnect();
}

extern "C" int mexStartAmp()
{ 
  return AmpServerInterface::GetAmpServer()->startAmp();
}

extern "C" int mexTurnOnAmp()
{
  return AmpServerInterface::GetAmpServer()->turnOnAmp();
}

extern "C" int mexTurnOffAmp()
{
  return AmpServerInterface::GetAmpServer()->turnOffAmp();
}

extern "C" int mexStopAmp()
{
  return AmpServerInterface::GetAmpServer()->stopAmp();
}

extern "C" int mexAcquire(double* data, long numsamples)
{
  AmpServerInterface::GetAmpServer()->acquire(data, numsamples);
  return 0;
}

extern "C" int mexApplyScalingFactor(bool applyScalingFactor)
{
  AmpServerInterface::GetAmpServer()->setApplyScalingFactor(applyScalingFactor);
  return 0;
}
