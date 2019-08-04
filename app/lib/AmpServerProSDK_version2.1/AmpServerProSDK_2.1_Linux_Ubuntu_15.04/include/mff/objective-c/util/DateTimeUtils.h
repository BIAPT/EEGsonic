
/**@file
 *  DateTimeUtils header.
 *  @author Robert Bell
 *  @date 09/13/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#define MFF_DATE_TIME_INITIALIZER {0, 0, 0, 0, 0, 0, 0, 0};

typedef struct {
    
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int millisecond;
    int microsecond;
    
} MFFDateTime, *MFFDateTimeRef;

const char *convertMFFDateTimeToMFFCStringTime(MFFDateTimeRef mffDateTime);

MFFDateTimeRef convertMFFCStringTimeToMFFDateTime(const char *time);

