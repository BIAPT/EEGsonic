
/**@file
 *  AmpPropertiesTableDelegate Header File
 *  @author Robert Bell
 *  @date 2015/09/30
 *  @remarks
 *  Copyright (c) 2015 EGI. All rights reserved.<br>
 */

#import <Cocoa/Cocoa.h>

/**
 *  AmpPropertiesTableDelegate Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class is responsible for providing the amplifier's properties to the amplifier properties table
 *  in the UI. The class "AppController" is responsible for setting this delegate's data properties.<br>
 *
 *  <b> Important Notes: N/A</b><br>
 *
 *  ------<br>
 *  Update (001): 2015-09-30: Class creation.<br>
 *  ------<br>
 */
@interface AmpPropertiesTableDelegate : NSObject <NSTableViewDelegate, NSTableViewDataSource> {
    
    IBOutlet NSTableView *ampInformationTable_;
    IBOutlet NSTableColumn *ampPropertyColumn_;
    IBOutlet NSTableColumn *ampValueColumn_;
    
}

@property (nonatomic, copy) NSString *ampType;
@property (nonatomic, copy) NSString *ampSerialNumber;
@property (nonatomic, copy) NSString *ampSystemVersion;
@property (nonatomic, copy) NSString *ampPacketType;
@property (nonatomic, copy) NSString *ampNumberOfChannels;

@end
