
/**@file
 *  MFFInfoN header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *
 *  The different types of MFFInfoN files.
 *
 */
typedef enum{
    kUnknownInfoNFileType   = -1,
    kEEG                    = 0,
    kSpectral               = 1,
    kSourceData             = 2,
    kPNSData                = 3,
    kJTF                    = 4,
    kTValues                = 5
} InfoNFileType;

/**
 *  MFFInfoN Class.
 *  @author Robert Bell.
 *  @remarks
 *  An MFF resource representing an info(n) resource in the MFF. Please see
 *  a description of handling "proper" MFF resources contained in the introduction
 *  to the MFF API.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2011-10-18: Added support for channels tag mirroring that in
 *  categories.xml.<br>
 *  ------<br>
 */
@interface MFFInfoN : MFFResource {
    
    InfoNFileType infoNFileType_;
    id fileTypeInformation_;
    NSString *continuationFrom_;
    NSString *continuationTo_;
    NSMutableArray *channels_;
    NSString *exclusion_;
    NSMutableArray *filters_;
    NSMutableArray *calibrations_;
	BOOL filterAdjusted_;
    uint64_t shiftValue_;

@private
    
}

@property (nonatomic, assign) InfoNFileType infoNFileType;
@property (nonatomic, retain) id fileTypeInformation;
@property (nonatomic, copy) NSString *continuationFrom;
@property (nonatomic, copy) NSString *continuationTo;
@property (nonatomic, retain) NSMutableArray *channels;
@property (nonatomic, copy) NSString *exclusion;
@property (nonatomic, retain) NSMutableArray *filters;
@property (nonatomic, retain) NSMutableArray *calibrations;

/**
 *	Whether the file has been adjusted for the hardware filter offset
 *  <b>Notes:</b><br>
 *  &nbsp; 1) YES means that the data has already been adjusted for the hardware filter offset, NO or absent means that it still needs updated
 **/

@property (nonatomic, assign) BOOL filterAdjusted;

/**
 *	The amount the data has been shifted to adjust for the anti alaising filter offset
 *  <b>Notes:</b><br>
 *  &nbsp; 1) the number of microseconds the data has been adjusted/
 **/
@property (nonatomic,assign)uint64_t shiftValue;


@end
