
/**@file
 *  MFFMovieSync header.
 *  @author Robert Bell
 *  @date 02/02/2012
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFMovieSync Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a movie sync detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 02/20/2012: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 04/05/2013: Video file changed, added updates.<br>
 *  ------<br>

 */
@interface MFFMovieSync : NSObject {
    
@private
    NSString *fileName_;
    uint64_t sampleBeginTime_;
    uint64_t sampleEndTime_;	
    double videoBeginTime_;
    double videoEndTime_;	
    int64_t category_;
    int64_t segment_;    
}

+ (id)movieSync;

/**
 *  The file name for this video sync.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) What file this sync refers to.<br>
 **/

@property (nonatomic, copy) NSString *fileName;

/**
 *  The sample begin time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Microseconds since EEG recording began.<br>
 **/
@property (nonatomic, assign) uint64_t sampleBeginTime;

/**
 *  The sample end time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Microseconds since EEG recording began.<br>
 **/
@property (nonatomic, assign) uint64_t sampleEndTime;

/**
 *  The movie begin time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Seconds since video recording began.<br>
 **/
@property (nonatomic, assign) double videoBeginTime;

/**
 *  The movie end time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Seconds since video recording began.<br>
 **/

@property (nonatomic, assign) double videoEndTime;
/**
 *  The category.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 **/
@property (nonatomic, assign) int64_t category;

/**
 *  The segment.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 **/
@property (nonatomic, assign) int64_t segment;

@end
