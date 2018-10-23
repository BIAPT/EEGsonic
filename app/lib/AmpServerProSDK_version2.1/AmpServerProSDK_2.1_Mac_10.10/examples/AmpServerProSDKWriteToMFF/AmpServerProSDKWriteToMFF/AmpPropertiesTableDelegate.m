//
//  AmpPropertiesTableDelegate.m
//  AmpServerProSDKWriteToMFF
//
//  Created by Robert Bell on 01/10/2015.
//  Copyright (c) 2015 Robert Bell. All rights reserved.
//

#import "AmpPropertiesTableDelegate.h"

#define NUMBER_OF_TABLE_ROWS 5

typedef enum : NSUInteger {
    aptd_AmpType = 0,
    aptd_AmpSerialNumber = 1,
    aptd_AmpSystemVersion = 2,
    aptd_AmpPacketType = 3,
    aptd_AmpNumberOfChannels = 4
} AmpPropertiesTableDelegateRowType;

@implementation AmpPropertiesTableDelegate

@synthesize ampType=ampType_;
@synthesize ampSerialNumber=ampSerialNumber_;
@synthesize ampSystemVersion=ampSystemVersion_;
@synthesize ampPacketType=ampPacketType_;
@synthesize ampNumberOfChannels=ampNumberOfChannels_;

-(void)awakeFromNib {
    self.ampType = @"unknown";
    self.ampSerialNumber = @"unknown";
    self.ampSystemVersion = @"unknown";
    self.ampPacketType = @"unknown";
    self.ampNumberOfChannels = @"unknown";
}

- (void)dealloc {
    
    [super dealloc];
    
}

#pragma mark -
#pragma mark NSTableView delegate/datasource methods

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return NUMBER_OF_TABLE_ROWS;
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    
    id rVal = @"N/A";
    
    if ( tableColumn == self->ampPropertyColumn_) {
        
        switch (row) {
            case aptd_AmpType:
                rVal = @"Amp Type";
                break;
            case aptd_AmpSerialNumber:
                rVal = @"Amp Serial Number";
                break;
            case aptd_AmpSystemVersion:
                rVal = @"Amp System Version";
                break;
            case aptd_AmpPacketType:
                rVal = @"Amp Packet Type";
                break;
            case aptd_AmpNumberOfChannels:
                rVal = @"Number of Channels";
                break;
            default:
                break;
        }
        
    } else if ( tableColumn == self->ampValueColumn_) {
        
        switch (row) {
            case aptd_AmpType:
                rVal = self.ampType;
                break;
            case aptd_AmpSerialNumber:
                rVal = self.ampSerialNumber;
                break;
            case aptd_AmpSystemVersion:
                rVal = self.ampSystemVersion;
                break;
            case aptd_AmpPacketType:
                rVal = self.ampPacketType;
                break;
            case aptd_AmpNumberOfChannels:
                rVal = self.ampNumberOfChannels;
                break;
            default:
                break;
        }
        
    }
    
    return rVal;
    
}

#pragma mark -

@end
