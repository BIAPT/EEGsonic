
/**@file
 *  ByteBuffer header.
 *  @author Robert Bell
 *  @date 14/06/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

@interface ByteBuffer : NSObject {

@private

    NSMutableData *data_;
    NSInteger capacity_;
    NSUInteger position_;
    BOOL expandable_;
    
}

@property (nonatomic, retain) NSMutableData *data;

- (id)initWithCapacity :(NSUInteger)capacity :(BOOL)expandable;
- (id)initWithLength:(NSUInteger)length :(BOOL)expandable;

+ (id)byteBufferWithCapacity:(NSUInteger)capacity :(BOOL)expandable;
+ (id)byteBufferWithLength:(NSUInteger)length :(BOOL)expandable;

/**
 *  @name Java's ByteBuffer interface.
 *  &nbsp; 1) This mirrors Java's ByteBuffer interface.
 */
//@{

//+ (ByteBuffer *)allocate :(NSUInteger)capacity :(BOOL)expandable;

- (NSMutableData *)array;

- (NSUInteger)position;

- (ByteBuffer *)position :(NSUInteger)position;

- (NSUInteger)capacity;

- (ByteBuffer *)put :(NSData *)src;

- (ByteBuffer *)put :(NSData *)src :(NSUInteger)offset :(NSUInteger)length;

- (ByteBuffer *)putInt8_T :(int8_t)value;

- (ByteBuffer *)putInt8_T :(NSUInteger)index :(int8_t)value;

- (ByteBuffer *)putInt16_T :(int16_t)value;

- (ByteBuffer *)putInt16_T :(NSUInteger)index :(int16_t)value;

- (ByteBuffer *)putInt32_T :(int32_t)value;

- (ByteBuffer *)putInt32_T :(NSUInteger)index :(int32_t)value;

- (ByteBuffer *)putInt64_T :(int64_t)value;

- (ByteBuffer *)putInt64_T :(NSUInteger)index :(int64_t)value;

//@}

@end
