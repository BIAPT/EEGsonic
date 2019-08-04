
/*
 *  ampsrv.c
 *  @author Robert Bell
 *  @date 2007/09/01
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 *
 *  ------<br>
 *  Update (001): 2015-09-01: File creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2011-09-14: Fixed bugs. Brought up to date with current release of Amp Server Pro SDK.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (003): 2015-08-03: Fixed bugs. Brought up to date with current release of Amp Server Pro SDK (and NA 400 amplifiers).<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (004): 2015-10-08: Added support for disconnecting and setting whether to apply the scaling factor.<br>
 *  ------<br>
 */

#include "MexInterface.h"
#include <stdio.h>
#include "mex.h"
#include "matrix.h"

void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] )
{
   printf("info: entering mex function\n");

   double *x, *y;
   mwSize mrows, ncols;    
   
   // There must be at least one right hand parameter which
   // indicates which command we are sending to the amp.
   mrows = mxGetM(prhs[0]);
   ncols = mxGetN(prhs[0]);
   
   if( nrhs == 0 )
   {
      mexErrMsgTxt("error: you must at least define amp command");
      return;
   }
   
   // Command is the first right hand parameter.
   x = mxGetPr(prhs[0]);
   int command = (int)(*((double*) x));

   // Output and results.
   double *output = NULL;
   int result = 1;
   
   switch(command)
     {
     
     case amppoweron:

       // Issue the command and check the results.
       plhs[0] = mxCreateDoubleMatrix(1,1, mxREAL);
       output = mxGetPr(plhs[0]);
       *output = 0.0;

       result =  mexTurnOnAmp();
       if( result ) {
	 mexErrMsgTxt("error: unable to turn on the amplifier");
	 *output = 1.0;
       }
       
       break;

     case amppoweroff:

       // Issue the command and check the results.
       plhs[0] = mxCreateDoubleMatrix(1,1, mxREAL);
       output = mxGetPr(plhs[0]);
       *output = 0.0;

       result =  mexTurnOffAmp();
       if( result ) {
	 mexErrMsgTxt("error: unable to turn off the amplifier");
	 *output = 1.0;
       }

       break;

     case ampstart:

       // Issue the command and check the results.
       plhs[0] = mxCreateDoubleMatrix(1,1, mxREAL);
       output = mxGetPr(plhs[0]);
       *output = 0.0;

       result =  mexStartAmp();
       if( result ) {
	 mexErrMsgTxt("error: unable to start the amplifier");
	 *output = 1.0;
       }
       break;

     case ampstop:

       // Issue the command and check the results.
       plhs[0] = mxCreateDoubleMatrix(1,1, mxREAL);
       output = mxGetPr(plhs[0]);
       *output = 0.0;

       result =  mexStopAmp();
       if( result ) {
	 mexErrMsgTxt("error: unable to stop the amplifier");
	 *output = 1.0;
       }
       break;

     case ampconnect:
       {
	 
	 plhs[0] = mxCreateDoubleMatrix(1,1, mxREAL);
	 output = mxGetPr(plhs[0]);
	 *output = 0.0;
	 if( !( nrhs > 1 ) )
	   {
	     mexErrMsgTxt("error: no IP address specified");
	     return;
	   }
	 
	 if( !mxIsChar(prhs[1])  ) 
	   {
	     mexErrMsgTxt("error: input must be a string.");
	     return;
	   }
	 
	 char* ip = (char*)mxArrayToString(prhs[1]);
	 
	 result = mexConnect(ip);
	 if( result )
	   {
	     mexErrMsgTxt("error: unable to connect to server");
	     *output = 1.0;
	   }
	 break;

       }
     
     case ampdisconnect:

       mexDisconnect();
       break;

     case ampacquire:
       {
	 
	 if( nrhs != 2 )
	   {
	     mexErrMsgTxt("error: number of samples not specified");
	     return;
	   }
	 long numsamples = (long)*(double*)mxGetPr(prhs[1]);
	 printf("info: number of samples requested: %d\n", numsamples);
	 
         // Create matrix for the return argument.
         plhs[0] = mxCreateDoubleMatrix(numsamples, 128,mxREAL);
         output = mxGetPr(plhs[0]);
         
	 // Collect the samples.
	 mexAcquire(output, numsamples);
	 
	 // Indicate we are done.
	 printf("info: done collecting samples");
	 
         break;

       }
     case applyscalingfactor:
       {
	 
	 if( nrhs != 2 )
	   {
	     mexErrMsgTxt("error: scaling factor state not specified");
	     return;
	   }

	 bool applyScalingFactor = (bool)*(double*)mxGetPr(prhs[1]);	 
	 mexApplyScalingFactor(applyScalingFactor);
	 
         break;

       }
     case test:
       {

	 // This is just used for testing the layer interation. It does not interact with
	 // the amplifier at all.

	 long test = (long)*(double*)mxGetPr(prhs[1]);
	 printf("test = %d\n", test);
	 break;

       }
     default:

       printf("error: not a command\n");
       break;

     }

}
