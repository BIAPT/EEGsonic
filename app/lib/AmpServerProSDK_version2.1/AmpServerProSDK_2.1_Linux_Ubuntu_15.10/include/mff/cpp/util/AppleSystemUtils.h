
/**@file
 *  AppleSystemUtils header.
 *  @author Robert Bell
 *  @date 05/09/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifdef __MACH__

#ifndef AppleSystemUtils_DEFINED
#define AppleSystemUtils_DEFINED

#include <string>
#include <vector>

/**
 *  Gets the resource size.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 *  ------<br>
 *  <b>Arguments:</b><br>
 *  &nbsp; 1) uri: The uri of the directory.<br>
 *  &nbsp; 2) encoding: The encoding. If no encoding is given, the default is used.
 *  At present, the "real" type of encoding is assumed to be NSStringEncoding *.<br>
 *  ------<br>
 *  <b>Return:</b><br>
 *  &nbsp; 1) uint64_t: The resource size.<br>
 *  ------<br>
 *  <b>Throws:</b><br>
 *  &nbsp; N/A<br>
 */
uint64_t resourceSize(std::string uri, void *encoding);

/**
 *  Determines whether the file exists at the given URI.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 *  ------<br>
 *  <b>Arguments:</b><br>
 *  &nbsp; 1) uri: The uri of the file.<br>
 *  &nbsp; 2) isDirectory: Reference argument indicating whether the uri is a directory
 *  or not.<br>
 *  ------<br>
 *  <b>Return:</b><br>
 *  &nbsp; 1) bool: true = resource exists; false = resource does not exist.<br>
 *  ------<br>
 *  <b>Throws:</b><br>
 *  &nbsp; N/A<br>
 */
bool fileExistsAtPath(std::string uri, bool &isDirectory);

/**
 *  Gets the contents of a directory at the specified uri.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 *  ------<br>
 *  <b>Arguments:</b><br>
 *  &nbsp; 1) uri: The uri of the directory.<br>
 *  &nbsp; 2) encoding: The encoding. If no encoding is given, the default is used.
 *  At present, the "real" type of encoding is assumed to be NSStringEncoding *.<br>
 *  ------<br>
 *  <b>Return:</b><br>
 *  &nbsp; 1) std::vector<std::string>: The directory contents; empty failure.<br>
 *  ------<br>
 *  <b>Throws:</b><br>
 *  &nbsp; N/A<br>
 */
std::vector<std::string> *contentsOfDirectoryAtURI(std::string uri, void *encoding);

/**
 *  Appends path component to base string.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 *  ------<br>
 *  <b>Arguments:</b><br>
 *  &nbsp; 1) baseString: The base string.<br>
 *  &nbsp; 2) pathComponent: The path component to append to the base string.<br>
 *  &nbsp; 3) encoding: The encoding. If no encoding is given, the default is used.
 *  At present, the "real" type of encoding is assumed to be NSStringEncoding *.<br>
 *  ------<br>
 *  <b>Return:</b><br>
 *  &nbsp; 1) std::string: The resulting string with path component appended
 *  to the base string.<br>
 *  ------<br>
 *  <b>Throws:</b><br>
 *  &nbsp; N/A<br>
 */
std::string stringByAppendingPathComponent(std::string baseString,
                                           std::string pathComponent,
                                           void *encoding);

/**
 *  Get's last path component.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 *  ------<br>
 *  <b>Arguments:</b><br>
 *  &nbsp; 1) path: The path.<br>
 *  &nbsp; 2) encoding: The encoding. If no encoding is given, the default is used.
 *  At present, the "real" type of encoding is assumed to be NSStringEncoding *.<br>
 *  ------<br>
 *  <b>Return:</b><br>
 *  &nbsp; 1) std::string: The last path component.<br>
 *  ------<br>
 *  <b>Throws:</b><br>
 *  &nbsp; N/A<br>
 */
std::string lastPathComponent(std::string path, void *encoding);

/**
 *  Deletes the last path component from the given path.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 *  ------<br>
 *  <b>Arguments:</b><br>
 *  &nbsp; 1) path: The path.<br>
 *  &nbsp; 2) encoding: The encoding. If no encoding is given, the default is used.
 *  At present, the "real" type of encoding is assumed to be NSStringEncoding *.<br>
 *  ------<br>
 *  <b>Return:</b><br>
 *  &nbsp; 1) std::string: The path obtained by deleting the last path component.<br>
 *  ------<br>
 *  <b>Throws:</b><br>
 *  &nbsp; N/A<br>
 */
std::string stringByDeletingLastPathComponent(std::string path, void *encoding);


#endif // AppleSystemUtils_DEFINED

#endif //__MACH__

