
/**@file
 *  XMLNode header.
 *  @author Robert Bell
 *  @date 23/02/2015
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

class TiXmlNode;

@interface XMLNode : NSObject {

@private

    TiXmlNode *tinyXMLNode_;
    
}

/**
 *  The tinyxml node.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) TiXmlNode *tinyXMLNode;

/**
 * Gets the c-string representation of this node.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @return The c-string representation of this node.
 */
- (char *)getCStringRepresentation;

/**
 * Gets the string representation of this node.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @return The string representation of this node.
 */
- (NSString *)getStringRepresentation;

@end
