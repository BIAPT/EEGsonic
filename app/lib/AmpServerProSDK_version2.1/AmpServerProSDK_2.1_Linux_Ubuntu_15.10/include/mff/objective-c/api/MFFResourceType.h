
/**@file
 *  MFFResourceType header.
 *  @author Robert Bell
 *  @date 28/06/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *
 * Resource types for files in MFF.
 *
 */
typedef enum{
    
    //######
    // Resource types for files in MFF.
    //######
    
    // We don't understand the resource.
    kMFF_RT_Unknown         = -1,
    
    kMFF_RT_Any             = 0,
    kMFF_RT_MFFFile         = 1,
    kMFF_RT_Signal          = 2,
    kMFF_RT_EventTrack      = 3,
    kMFF_RT_Epochs          = 4,
    kMFF_RT_Subject         = 5,
    kMFF_RT_History         = 6,
    kMFF_RT_Info            = 7,
    kMFF_RT_InfoN           = 8,
    kMFF_RT_Categories      = 9,
    kMFF_RT_JTFCategories   = 10,
    kMFF_RT_SensorLayout    = 11,
    kMFF_RT_Coordinates     = 12,
    kMFF_RT_Photogrammetry  = 13,
    kMFF_RT_PNSSet          = 14,
    kMFF_RT_MovieSyncs      = 15,
    kMFF_RT_Fields          = 16,
    kMFF_RT_Notes           = 17,
    kMFF_RT_Montage         = 18,
	kMFF_RT_DipoleSet		= 19,
	kMFF_RT_PhoticStim      = 20,
    kMFF_RT_GTENModulationConfiguratonFile  = 21
    
} _MFFResourceType;

/**
 *  MFFResourceType Class.
 *  @author Robert Bell.
 *  @remarks
 *  A class wrapper of an MFF resource type.
 *
 *  ------<br>
 *  Update: 2011-06-28: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2012-01-26: Added JTF category type.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2012-01-26: Added movie syncs type.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2013-04-16: Added dipole set type. DFB<br>
 *  ------<br>

 */
@interface MFFResourceType : NSObject {

@private
    
    _MFFResourceType resourceType_;
    
}

@property (nonatomic, assign) _MFFResourceType resourceType;

-(id)initAsResourceType :(_MFFResourceType)resourceType;

+ (id)resource;
+ (id)asResourceType:(_MFFResourceType)resourceType;

@end
