
/**@file
 *  MFFUtils header.
 *  @author Robert Bell
 *  @date 10/02/2012
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

@class MFFResourceType;

/**
 *  MFFUtils Class.
 *  @author Robert Bell.
 *  @remarks
 *  Conceptual wrapper of an MFF file.
 *
 *  ------<br>
 *  Update: 2012-02-10: Class creation.<br>
 *  ------<br>
 */
@interface MFFUtils : NSObject {
    
}

+ (BOOL) isResourceURLOfValidMFFType:(NSURL *)resourceURL;

+ (BOOL) isResourceURIOfValidMFFType:(NSString *)resourceURI;

+ (NSArray *)arrayByFilteringResourceURIsByValidMFFType:(NSArray *) resourceURIs;

/**
 *  Attempts to detect when non-valid characters are present in the text uri given.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) MFF supports UTF-8. This method tries to detect when invalid character sequences
 *  are present in at the given uri.<br>
 *  ------<br>
 *  <b>Arguments:</b><br>
 *  &nbsp; 1) uri: The uri to test.<br>
 *  ------<br>
 *  <b>Return:</b><br>
 *  &nbsp; 1) true: uri passes the verify test; false: uri fails the verify test.<br>
 *  ------<br>
 *  <b>Throws</b><br>
 *  &nbsp; N/A<br>
 */
+ (BOOL) isValidUTF8Resource: (const char *)uri;

+ (BOOL) fixUTF8Resource: (const char *)resourceURI
                        : (MFFResourceType *)resourceType
                        : (bool)saveOldFile
                        : (char)replaceWith;

/**
 *  Converts an MFF date time string to microseconds since epoch.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Examples of an MFF date time string are:<br>
 *  &nbsp; &nbsp; i) 2011-09-12T10:53:36.140373-07:00<br>
 *  &nbsp; &nbsp; ii) 2012-01-10T14:23:45.140373+01:00<br>
 *  &nbsp; 2) The time zone will be extracted during the parsing of the
 *  string, and returned in the argument "timeZone". This will be the time zone offset
 *  in seconds. Thus, in (i) above, the value would be: (-7 * 3600) = -25200.<br>
 *  ------<br>
 *  <b>Arguments:</b><br>
 *  &nbsp; 1): dateTime: An MFF date time string.<br>
 *  &nbsp; 2): timeZone: An int expressing the timezone (will be filled in by
 *  this function whilst parsing of the data time string given in argument 1 (dateTime).<br>
 *  ------<br>
 *  <b>Return:</b><br>
 *  &nbsp; 1); uint64_t: Microseconds since epoch. This is the Unix epoch
 *  of midnight, January 1st, 1970.<br>
 *  ------<br>
 *  <b>Throws</b><br>
 *  &nbsp; N/A<br>
 */
+ (uint64_t) mffDateTimeToMicroseconds: (NSString *)dateTime :(int *)timeZone;

/**
 *  Converts microseconds since epoch to an MFF date time string.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Examples of an MFF date time string are:<br>
 *  &nbsp; &nbsp; i) 2011-09-12T10:53:36.140373-07:00<br>
 *  &nbsp; &nbsp; ii) 2012-01-10T14:23:45.140373+01:00<br>
 *  &nbsp; 2) A time zone of "-07:00" desired in the string should for example be passed in as
 *  timezone = (-7 * (the number of seconds in an hour)) = (-7 * 3600).<br>
 *  ------<br>
 *  <b>Arguments:</b><br>
 *  &nbsp; 1): microseconds: Microseconds since epoch. This is the Unix epoch
 *  of midnight, January 1st, 1970.<br>
 *  &nbsp; 2): timeZone: An int expressing the timezone.<br>
 *  ------<br>
 *  <b>Return:</b><br>
 *  &nbsp; 1); std::string: The resulting MFF data time string.<br>
 *  ------<br>
 *  <b>Throws</b><br>
 *  &nbsp; N/A<br>
 */
+ (NSString *) microsecondsToMFFDateTime: (uint64_t)microseconds :(int)timeZone;

/**
 *  Calculates the difference between two MFF date time strings in microseconds.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The difference is dateTime1 - dateTime2. Thus, if dateTime1 represents a time
 *  before dateTime2, the value will be negative.<br>
 *  ------<br>
 *  <b>Arguments:</b><br>
 *  &nbsp; 1): dateTime1: Date time string 1.<br>
 *  &nbsp; 2): dateTime2: Date time string 2, which is subtracted from date time string 1.<br>
 *  ------<br>
 *  <b>Return:</b><br>
 *  &nbsp; 1); uint64_t: The difference i microseconds.<br>
 *  ------<br>
 *  <b>Throws</b><br>
 *  &nbsp; N/A<br>
 */
+ (uint64_t) mffDateTimeDifferenceInMicroseconds: (NSString *)dateTime1 :(NSString *)dateTime2;

@end
