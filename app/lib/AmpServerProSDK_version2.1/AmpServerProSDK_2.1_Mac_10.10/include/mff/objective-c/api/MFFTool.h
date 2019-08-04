
/**@file
 *  MFFTool header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFTool Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a tool detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2012-01-31: Added comments for all the properties.<br>
 *  ------<br>
 */
@interface MFFTool : NSObject {

@private
    
    NSString *name_;
    NSString *kind_;
    NSString *method_;
    NSString *version_;
    NSString *beginTime_;
    NSString *endTime_;
    NSMutableArray *sourceFiles_;
    NSMutableArray *settings_;
    NSMutableArray *results_;
    
}

/**
 *  The tool name.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 **/
@property (nonatomic, copy) NSString *name;

/**
 *  The tool kind.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Indicates what kind of tool this is. For example, Transformation.<br>
 **/
@property (nonatomic, copy) NSString *kind;

/**
 *  The tool method.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The method used for the tool. For example, Artifact Detection.<br>
 **/
@property (nonatomic, copy) NSString *method;

/**
 *  The tool version.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 **/
@property (nonatomic, copy) NSString *version;

/**
 *  The tool begin time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is in MFF datetime format.<br>
 **/
@property (nonatomic, copy) NSString *beginTime;

/**
 *  The tool end time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is in MFF datetime format.<br>
 **/
@property (nonatomic, copy) NSString *endTime;

/**
 *  The list of source files used by this tool.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of MFFFilePath objects.<br>
 **/
@property (nonatomic, retain) NSMutableArray *sourceFiles;

/**
 *  The list of settings for this tool.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of NSString objects.<br>
 **/
@property (nonatomic, retain) NSMutableArray *settings;

/**
 *  The results list for this tool.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of NSString objects.<br>
 **/
@property (nonatomic, retain) NSMutableArray *results;

@end
