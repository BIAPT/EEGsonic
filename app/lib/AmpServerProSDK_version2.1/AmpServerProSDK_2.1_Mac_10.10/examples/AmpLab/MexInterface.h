
/**@file
 *  MexInterface Header File
 *  @author Robert Bell
 *  @date 2007/09/01
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 */

enum{
  amppoweron         = 1,
  amppoweroff        = 2,
  ampstart           = 3,
  ampstop            = 4,
  ampconnect         = 5,
  ampdisconnect      = 6,
  ampacquire         = 7,
  applyscalingfactor = 8,
  test               = 9
};
    
#ifdef __cplusplus
extern "C"
{
#endif
  
  int mexConnect( char* ip_address );
  int mexDisconnect();
  int mexStartAmp();
  int mexTurnOnAmp();
  int mexTurnOffAmp();
  int mexStopAmp();
  int mexAcquire( double* data, long numsamples );
  int mexApplyScalingFactor(bool applyScalingFactor);
    
#ifdef __cplusplus
}
#endif
        
