
/**@file
 *  XMLMapping header.
 *  @author Robert Bell
 *  @date 25/02/2015
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

@class XMLNode;

@interface XMLMapping : NSObject {

@private

}

/**
 * Gets the XML node representation.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @return The XML node (or a derived type).
 */
- (XMLNode *)getXMLNode:(id)visitor
                       :(BOOL)useStatics;

@end
