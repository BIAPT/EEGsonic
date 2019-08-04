
/**@file
 *  MFFDipoleSet header.
 *  @author David Borland
 *  @date 4/16/2013
 *  @remarks
 *  Copyright 2013 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import "MFFResource.h"
/**
 *  MFFDipoleSet Class.
 *  @author David Borland
 *  @remarks
 *  This class wraps the concept of a dipole set detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2013-04-16: Class creation.<br>
 *  ------<br>
 */

@interface MFFDipoleSet : MFFResource {
	
	@private
	
	NSString		*name_;
	NSString		*type_;
	NSString		*subjectID_;
	NSMutableArray	*dipoles_;
	
}
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *type;
@property (nonatomic, copy) NSString *subjectID;
@property (nonatomic, retain) NSMutableArray *dipoles;

@end
