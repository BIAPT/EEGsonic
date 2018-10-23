
/**@file
 *  TinyXMLWrappers header.
 *  @author Robert Bell
 *  @date 05/07/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

class TiXmlNode;
class TiXmlElement;

/**
 *  TinyXMLWrappers Class.
 *  @author Robert Bell.
 *  @remarks
 *  Conceptual wrapper of an MFF file.
 *
 *  ------<br>
 *  Update (001): 2011-07-05: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2012-02-08: UTF-8 enconding is now the default.<br>
 *  ------<br>
 */
@interface TinyXMLWrappers : NSObject {

@private
    
}

+ (NSString *)getText :(TiXmlElement *)element;
+ (NSString *)getAttribute :(TiXmlElement *)element :(const char *)name;

+ (TiXmlElement *)getTiXmlElementWithCStringName :(const char *)name
                                   andCStringText:(const char *)text
                                     alwaysCreate:(BOOL)alwaysCreate;

+ (TiXmlElement *)getTiXmlElementWithCStringName :(const char *)name
                                          andText:(NSString *)text
                                     alwaysCreate:(BOOL)alwaysCreate;

+ (TiXmlElement *)getTiXmlElementWithName :(NSString *)name
                            andCStringText:(const char *)text
                              alwaysCreate:(BOOL)alwaysCreate;

+ (TiXmlElement *)getTiXmlElementWithName :(NSString *)name
                                   andText:(NSString *)text
                              alwaysCreate:(BOOL)alwaysCreate;

+ (TiXmlElement *)setAttributeOnElement :(TiXmlElement *)element
                         withCStringName:(const char *)name
                        withCStringValue:(const char *)value
                            alwaysCreate:(BOOL)alwaysCreate;

+ (TiXmlElement *)setAttributeOnElement :(TiXmlElement *)element
                         withCStringName:(const char *)name
                               withValue:(NSString *)value
                            alwaysCreate:(BOOL)alwaysCreate;

+ (TiXmlElement *)setAttributeOnElement :(TiXmlElement *)element
                                withName:(NSString *)name
                        withCStringValue:(const char *)value
                            alwaysCreate:(BOOL)alwaysCreate;

+ (TiXmlElement *)setAttributeOnElement :(TiXmlElement *)element
                                withName:(NSString *)name
                               withValue:(NSString *)value
                            alwaysCreate:(BOOL)alwaysCreate;

+ (TiXmlNode *)linkChildToParent :(TiXmlElement *)parent :(TiXmlElement *)child;

+ (TiXmlNode *)linkChildToParentWithChildNameAndText:(TiXmlElement *)parent
                                       withChildName:(NSString *)name
                                        andChildText:(NSString *)text
                                        alwaysCreate:(BOOL)alwaysCreate;

+ (TiXmlNode *)linkChildToParentWithChildAndAttribute:(TiXmlElement *)parent
                                        withChildName:(NSString *)childName
                                         andChildText:(NSString *)childText
                                    alwaysCreateChild:(BOOL)alwaysCreateChild
                                    withAttributeName:(NSString *)attributeName
                                     andAttributeText:(NSString *)attributeValue
                               alwaysCreateAAttribute:(BOOL)alwaysCreateAttribute;

@end
