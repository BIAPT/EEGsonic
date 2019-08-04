
AmpLab: An example matlab interface to the EGI Net Amps Data Acquisition Systems

Copyright (c) 2015, Electrical Geodesics, Inc.

THIS SOFTWARE IS PROVIDED BY THE ELECTRICAL GEODESICS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE ELECTRICAL GEODESICS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.


Description:

This example application demonstrates the use of Matlab® to interface with
EGI's Net Amps Amplifier products through the AmpServer SDK.  It employs
the Matlab® mexfile development tool to create a Matlab® command line
interface to control and collect data through the amp.

###### IMPORTANT ######

You MUST put the AmpLab root directory in your Matlab® path!

For example, in Matlab®, go to "File" -> "Set Path ..."

This will allow all the commands listed below to function.

####################### 

The mex layer can be built in two ways, the first is from the Makefile in
the AmpLab root directory: 

localhost:~ bertie$ pwd
/Users/bertie
localhost:~ bertie$ cd Desktop/AmpLabRelease/AmpLab/
localhost:AmpLab bertie$ pwd
/Users/bertie/Desktop/AmpLabRelease/AmpLab
localhost:AmpLab bertie$ ls -la
total 168
drwx------  19 bertie  staff    646 Sep 14 08:06 .
drwxr-xr-x   5 bertie  staff    170 Sep 12 11:23 ..
-rwx------   1 bertie  staff  12292 Aug  1  2007 .DS_Store
-rwx------   1 bertie  staff   6618 Sep 14 07:50 AmpServerInterface.cpp
-rwx------   1 bertie  staff   2731 Sep 14 07:43 AmpServerInterface.h
-rw-r--r--   1 bertie  staff    641 Sep 14 07:40 Makefile
-rwx------   1 bertie  staff   1668 Sep 14 07:51 MexInterface.cpp
-rwx------   1 bertie  staff   1311 Sep 14 07:51 MexInterface.h
-rwx------   1 bertie  staff   1053 Jul 31  2007 ampcollect.m
-rwx------   1 bertie  staff   1000 Jul 31  2007 ampinit.m
-rwx------   1 bertie  staff    990 Jul 31  2007 ampoff.m
-rwx------   1 bertie  staff    995 Jul 31  2007 ampon.m
-rwx------   1 bertie  staff   3213 Sep 14 07:50 ampsrv.c
-rwx------   1 bertie  staff   1106 Jun 15  2007 ampsrvinit.m
-rwx------   1 bertie  staff   1005 Jul 31  2007 ampstart.m
-rwx------   1 bertie  staff   1000 Jul 31  2007 ampstop.m
-rwx------   1 bertie  staff    157 Sep 14 07:55 build.m
drwxr-xr-x   2 bertie  staff     68 Sep 14 07:54 old
-rwx------   1 bertie  staff   4673 Sep 14 08:05 readme.txt
localhost:AmpLab bertie$ make
/Applications/MATLAB_R2011b.app/bin/mex -I../AmpServerProSDK/include -L../AmpServerProSDK/libs -lAS_Network_Client ampsrv.c AmpServerInterface.cpp MexInterface.cpp
localhost:AmpLab bertie$ ls -la
total 632
drwx------  20 bertie  staff     680 Sep 14 08:06 .
drwxr-xr-x   5 bertie  staff     170 Sep 12 11:23 ..
-rwx------   1 bertie  staff   12292 Aug  1  2007 .DS_Store
-rwx------   1 bertie  staff    6618 Sep 14 07:50 AmpServerInterface.cpp
-rwx------   1 bertie  staff    2731 Sep 14 07:43 AmpServerInterface.h
-rw-r--r--   1 bertie  staff     641 Sep 14 07:40 Makefile
-rwx------   1 bertie  staff    1668 Sep 14 07:51 MexInterface.cpp
-rwx------   1 bertie  staff    1311 Sep 14 07:51 MexInterface.h
-rwx------   1 bertie  staff    1053 Jul 31  2007 ampcollect.m
-rwx------   1 bertie  staff    1000 Jul 31  2007 ampinit.m
-rwx------   1 bertie  staff     990 Jul 31  2007 ampoff.m
-rwx------   1 bertie  staff     995 Jul 31  2007 ampon.m
-rwx------   1 bertie  staff    3213 Sep 14 07:50 ampsrv.c
-rwxr-xr-x   1 bertie  staff  233900 Sep 14 08:06 ampsrv.mexmaci64
-rwx------   1 bertie  staff    1106 Jun 15  2007 ampsrvinit.m
-rwx------   1 bertie  staff    1005 Jul 31  2007 ampstart.m
-rwx------   1 bertie  staff    1000 Jul 31  2007 ampstop.m
-rwx------   1 bertie  staff     157 Sep 14 07:55 build.m
drwxr-xr-x   2 bertie  staff      68 Sep 14 07:54 old
-rwx------   1 bertie  staff    4673 Sep 14 08:05 readme.txt
localhost:AmpLab bertie$

The second method is to use the build command from within Matlab®, as shown below.

Usage:

Here is an example usage in Matlab®:

>> ampinit('127.0.0.1')
entering mex function
AmpServerProSDK: spawning notification connnection ...
AmpServerProSDK: spawned notification connnection
AmpServerProSDK: spawning stream connnection ...
AmpServerProSDK: spawned stream connnection

ans =

     0

>> ampon
entering mex function

ans =

     0

>> ampstart
entering mex function

ans =

     0

>> data = ampcollect(10);
entering mex function
numsamples = 0AmpServerProSDK: listening to amplifier: 0
AmpServerProSDK: stopped listening to amplifier: 0
>> ampstop
entering mex function

ans =

     0

>> ampoff
entering mex function

ans =

     0

>>

The following commands are supported:

***************************************************************************

build.m:

This command builds the mex-file from source and binary files.  Once in the root directory of the AmpLab project within matlab¨, type build in the command prompt.

For example, from within Matlab®:

>> pwd

ans =

/Users/bertie/Documents/MATLAB

>> cd /Users/bertie
>> pwd

ans =

/Users/bertie

>> cd Desktop/
>> cd AmpLabRelease
>> cd AmpLab/
>> ls -la
total 624
drwx------  20 bertie  staff     680 Sep 14 08:00 .
drwxr-xr-x   5 bertie  staff     170 Sep 12 11:23 ..
-rwx------   1 bertie  staff   12292 Aug  1  2007 .DS_Store
-rwx------   1 bertie  staff    6618 Sep 14 07:50 AmpServerInterface.cpp
-rwx------   1 bertie  staff    2731 Sep 14 07:43 AmpServerInterface.h
-rw-r--r--   1 bertie  staff     641 Sep 14 07:40 Makefile
-rwx------   1 bertie  staff    1668 Sep 14 07:51 MexInterface.cpp
-rwx------   1 bertie  staff    1311 Sep 14 07:51 MexInterface.h
-rwx------   1 bertie  staff    1053 Jul 31  2007 ampcollect.m
-rwx------   1 bertie  staff    1000 Jul 31  2007 ampinit.m
-rwx------   1 bertie  staff     990 Jul 31  2007 ampoff.m
-rwx------   1 bertie  staff     995 Jul 31  2007 ampon.m
-rwx------   1 bertie  staff    3213 Sep 14 07:50 ampsrv.c
-rwxr-xr-x   1 bertie  staff  233900 Sep 14 08:00 ampsrv.mexmaci64
-rwx------   1 bertie  staff    1106 Jun 15  2007 ampsrvinit.m
-rwx------   1 bertie  staff    1005 Jul 31  2007 ampstart.m
-rwx------   1 bertie  staff    1000 Jul 31  2007 ampstop.m
-rwx------   1 bertie  staff     157 Sep 14 07:55 build.m
drwxr-xr-x   2 bertie  staff      68 Sep 14 07:54 old
-rwx------   1 bertie  staff    3142 Sep 14 07:54 readme.txt

>> build
>>

***************************************************************************

ampinit.m:

This command allows the user to initialize the connection to the Amp Server
through TCP/IP to the Net Amps host computer.  

Usage:

ampinit('<IP Adress>')

e.g.

ampinit('10.0.0.95') ' initializes the connection to the amp server
                     ' at the specified IP address

***************************************************************************
ampon.m:

This command allows the user to power up the amp to which it has been prev-
iously connected.  

Usage:

ampon ' turns on the selected Net Amp

***************************************************************************
ampoff.m:

This command allows the user to power down the amp.  

Usage:

ampoff

***************************************************************************
ampstart.m:

This command allows the user to start acquisition from the amp.  Data is 
not collected or returned until the ampcollect command is issued.

***************************************************************************
ampstop.m:

This command stops acquisition from the selected amp.  

***************************************************************************
ampcollect.m:

This command returns data collected from the selected amp.  It returns a 
Matlab® matrix containing N columns, where N is the number of channels of
data from the amp and M columns, where M is the number of samples specified.

Usage:

ampcollect(<number of samples>)

***************************************************************************
