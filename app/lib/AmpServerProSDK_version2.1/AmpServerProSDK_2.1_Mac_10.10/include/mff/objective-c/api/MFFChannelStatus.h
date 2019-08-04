/**@file
 *  MFFChannelStatus header.
 *  @author David Borland
 *  @date 2/08/2013
 *  @remarks
 *  Copyright 2013 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFChannelStatus Class.
 *  @author David Borland
 *  @remarks
 *  This class wraps the concept of a channel status in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2013-02-08: Class creation.<br>
 *  ------<br>
 */
@interface MFFChannelStatus : NSObject {

	@private
	uint32_t		binIndex_;
	NSString		*exclusion_;
	NSMutableArray	*channels_;
}
/**
 *  A list of channels for this segment that have some attribute to take into
 *  account.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type NSNumber initialized by [NSNumber numberWithUnsignedInt: ...].<br>
 *  &nbsp; 2) The exclusion string for this segment (property exclusion) indicates what the
 *  attribute is. For example, "badChannels".<br>
 **/
@property (nonatomic, retain) NSMutableArray *channels;

/**
 *  The exclusion attribute for this segment's channel list.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The channels property (property channels) gives a list of channels for
 *  which some attribute is taken into account. This exclusion string indicates what
 *  that attribute is. For example, "badChannels" or "goodChannels".<br>
 **/
@property (nonatomic, copy) NSString *exclusion;

/**
 *  The signal bin that this channel status is for.
 *  <b>Notes:</b><br>
 *  &nbsp;A 1 based index, because the signal bin files are labeled 1 based, 
 *	describing which signal bin this status is for.<br>
 **/
@property (nonatomic, assign) uint32_t binIndex;

@end
