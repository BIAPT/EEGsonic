
/**@file
 *  Observer header.
 *  @author Robert Bell
 *  @date 11/11/2005
 *  @remarks
 *  Copyright 2010 EGI. All rights reserved.<br>
 *  Utility Functions. This is just a list of some useful functions. None are particularly
 *  releated. All are static class members.
 */

#ifndef UtilityFunctions_DEFINED
#define UtilityFunctions_DEFINED

#include "EGIObject.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>

/**
 *  EGIBase namespace.
 */
namespace EGIBase{
	
	/** EGIObject Class.
	 *  @author Robert Bell.
	 *  @remarks
	 *  Utility Functions. This is just a list of some useful functions. None are particularly
	 *  releated. All are static class members.
	 *
	 *  ------<br>
	 *  Update (001): 2005-11-11: Class creation.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (002): 2010-09-28: Fixed an error in print bits. Bitwise and was too large.<br>getFileListing
	 *  ------<br>
     *
	 *  ------<br>
	 *  Update (003): 2012-12-20: Added getFileListing.<br>
	 *  ------<br>
     *
     *  ------<br>
	 *  Update (004): 2013-01-03: Added safeGetLine.<br>
	 *  ------<br>
	 */
	class UtilityFunctions : virtual public EGIBase::EGIObject{
		
		enum IOStreamBase{uF_Unknown, uF_Dec, uF_Hex, uF_Oct};
		
	public:
		
		//####################################
		//Class variables.
		//####################################
		static const std::string *IOStreamBaseStrings[4];
		//************************************
		//End - Class variables.
		//************************************
		
		//####################################
		//Class methods.
		//####################################
		
		/**
		 *  itoa.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; n: N/A<br>
		 *  &nbsp; output: N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; N/A<br>
		 */
		static void itoa(long long n, char * &output);
		
		/**
		 *  Reverses the string in place.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; s: The string to be reversed.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; N/A<br>
		 */
		static void reverse(char s[]);
		
		/**
		 *  Calculates the number of digits.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; number: The number.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; unsigned int: The number of digits.<br>
		 */
		static unsigned int numberOfDigits(unsigned long long number);
		
		/**
		 *  Prints the bits.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; bits: N/A<br>
		 *  &nbsp; numberOfBits: N/A<br>
		 *  &nbsp; grouping: N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; N/A<br>
		 */
		static void printBits(void *bits, unsigned short numberOfBits,  unsigned short grouping);
        
        /**
         *  Prints the bits to a string.
         *  <b>Notes:</b><br>
         *  &nbsp; N/A<br>
         *  ------<br>
         *  <b>Arguments:</b><br>
         *  &nbsp; bits: N/A<br>
         *  &nbsp; numberOfBits: N/A<br>
         *  &nbsp; grouping: N/A<br>
         *  ------<br>
         *  <b>Return:</b><br>
         *  &nbsp; std::string: The bits as a string.<br>
         */
        static std::string printBitsToString(void *bits, unsigned short numberOfBits,  unsigned short grouping);
        
        /**
		 *  Appends the given append string to the filename prior to the given extension.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) For example, the below converts test.xml to test_out.xml<br>
         *  &nbsp;&nbsp; UtilityFunctions::appendStringToFilenamePriorToExtention("test.xml", "xml", "out")<br>
         *  &nbsp; 2) If there is not "." in the filename, the append string is added to the end.<br>
         *  &nbsp; 3) If the extension does not match the given extension, nothing is done.
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; filename: The filename.<br>
		 *  &nbsp; extension: The extension (can be of an arbirary number of characters).<br>
		 *  &nbsp; appendString: The append string to use.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; std::string: The resulting string. If nothing was done, this string has a value of "not set".<br>
		 */
        static std::string appendStringToFilenamePriorToExtention(std::string filename,
                                                                  std::string extension,
                                                                  std::string appendString);
        
        /**
		 *  Converts the passed in string to a value of the type of "value".
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) value: The string is converted to the type of value (T).<br>
         *  &nbsp; 2) str: The string to be converted.<br>
         *  &nbsp; 3) f: For example: std::dec is a valid argument.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true = success; false = failure<br>
		 */
        template <class T> static bool from_string(T& value, const std::string& str, std::ios_base& (*f)(std::ios_base&));
        
        /**
		 *  Converts the passed in string to a value of the type of "T".
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) On failure, an attempt is made to convert "0" to the type T.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
         *  &nbsp; 1) str: The string to be converted.<br>
         *  &nbsp; 2) f: For example: std::dec is a valid argument.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; T: The converted value.<br>
		 */
        template <class T> static T from_string(const std::string& str, std::ios_base& (*f)(std::ios_base&));
        
        /**
		 *  Converts the passed in char string to a value of the type of "value".
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) value: The string is converted to the type of value (T).<br>
         *  &nbsp; 2) str: The char string to be converted.<br>
         *  &nbsp; 3) f: For example: std::dec is a valid argument.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true = success; false = failure<br>
		 */
        template <class T> static bool from_char_string(T& value, const char *str, std::ios_base& (*f)(std::ios_base&));
        
        /**
		 *  Converts the passed in char string to a value of the type of "T".
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) On failure, an attempt is made to convert "0" to the type T.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
         *  &nbsp; 1) str: The char string to be converted.<br>
         *  &nbsp; 2) f: For example: std::dec is a valid argument.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; T: The converted value.<br>
		 */
        template <class T> static T from_char_string(const char *str, std::ios_base& (*f)(std::ios_base&));
        
        /**
		 *  Converts the passed in value to a string.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) No statement is made about the underlying libstdc++ with regard
         *  to statics, however, this function will not use additional statics if called
         *  with statics set to false.<br>
         *  &nbsp; 2) If a particular precision is required, use the UtilityFunctions::to_string(...). 
		 *  ------<br>
		 *  <b>Arguments:</b><br>
         *  &nbsp; 1) value: The value to be converted.<br>
         *  &nbsp; 2) statics: Whether or not to use statics.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; std::string: The converted value.<br>
		 */
        template <class T> static std::string to_string_no_precision(T value, bool statics = true);
        
        /**
		 *  Converts the passed in value to a string.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) No statement is made about the underlying libstdc++ with regard
         *  to statics, however, this function will not use additional statics if called
         *  with statics set to false.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
         *  &nbsp; 1) value: The value to be converted.<br>
         *  &nbsp; 2) precision: The precision, if applicable. Default is 10.<br>
         *  &nbsp; 3) statics: Whether or not to use statics.<br>
		 *  &nbsp; 4) fixedPrecision: forces precision on decimal point.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; std::string: The converted value.<br>
		 */
        template <class T> static std::string to_string(T value, int precision = 10, bool statics = false ,bool fixedPrecision = false);
		
        /**
		 *  Swaps the byte order of a uint16_t.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Use this to switch between little and big endian.<br>
		 *  &nbsp; 2) The function always does the flip regardless of the platform.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; value: The value to be swapped.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; void: N/A<br>
		 */
		static void swapUINT16_t(uint16_t *value);
        
		/**
		 *  Swaps the byte order of a uint32_t.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Use this to switch between little and big endian.<br>
		 *  &nbsp; 2) The function always does the flip regardless of the platform.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; value: The value to be swapped.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; void: N/A<br>
		 */
		static void swapUINT32_t(uint32_t *value);
		
		/**
		 *  Swaps the byte order of a uint64_t.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  &nbsp; 1) Use this to switch between little and big endian.<br>
		 *  &nbsp; 2) The function always does the flip regardless of the platform.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; value: The value to be swapped.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; void: N/A<br>
		 */
		static void swapUINT64_t(uint64_t *value);
		
		/**
		 *  Gets current iostream base.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; IOStreamBase: The iostream base.<br>
		 */
		static IOStreamBase getCurrentIOStreamBase();
		
		/**
		 *  Gets current iostream base as a string.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; std::string: The iostream base as a string.<br>
		 */
		static const std::string *getCurrentIOStreamBaseStr();
        
        /**
		 *  Takes a string and tokenizes is based on the set of delimiters.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) stringToTokenize: The string to tokenize.<br>
         *  &nbsp; 2) delimiters: The deliminators to be used when tokenizing the string.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; std::vector<string> *: The tokens obtained. A non-null empty vector is returned
         *  if no tokens were found. Errors are indicated by exceptions.<br>
		 */
        static std::vector<std::string> *tokenize(const std::string& stringToTokenize,
                                                  const std::string& delimiters = " ");
        
        /**
		 *  Takes a string and tokenizes is based on the set of delimiters.
		 *  <b>Notes:</b><br>
         *  &nbsp; 1) Thread safe version of tokenize.<br>
		 *  &nbsp; 2) Uses new and delete as allocators and deallocators.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) stringToTokenize: The string to tokenize.<br>
         *  &nbsp; 2) delimiters: The deliminators to be used when tokenizing the string.<br>
         *  &nbsp; 3) numberOfTokens: Reference argument giving the number of tokens found (thus
         *  the effective length of the return array.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; char **: The tokens obtained. A null array is returned
         *  if no tokens were found, and the number of tokens found will be numberOfTokens. An error
         *  has occurred if numberOfTokens is less than zero.<br>
		 */
        static char **cTokenize(const char *stringToTokenize, const char *delimiters, int &numberOfTokens);
        
        /**
		 *  Gives a list files in the specified directory.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) directory: The directory.<br>
         *  &nbsp; 1) files: reference list into which the file names will be placed.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; 1) bool: true = sucess; false = failure.<br>
		 */
        static bool getFileListing(std::string directory, std::vector<std::string> &files);
		
		
		/**
		 *  Returns the string delimited by any of the three common end of line character
         *  combinations.<br>
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Example usage (which prevents the last line from being empty):<br>
         *  <br>
         *  &nbsp;&nbsp; while(! this->safeGetLine(fileStream , line).eof() ) { ... }<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; fileStream: the open file stream.<br>
		 *  &nbsp; line: the current line in the file.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; 1) std::istream &<br>
		 *  ------<br>
		 *  <b>Throws</b><br>
		 *  &nbsp; N/A<br>
		 */
		static std::istream& safeGetLine(std::istream& fileStream, std::string& line);
        
        /**
         *  Calls an external command.<br>
         *  <b>Notes:</b><br>
         *  &nbsp; 1) This call will block until the external command is done.<br>
         *  &nbsp; 2) Example shell command (which also redirects the standard error):<br>
         *  <br>
         *  &nbsp;&nbsp; "ntpq -p 2>&1"<br>
         *  ------<br>
         *  <b>Arguments:</b><br>
         *  &nbsp; command: the command to exectute.<br>
         *  &nbsp; results: the results will be placed here. Each result entry will correspond to
         *  a line of output generated by the external command.<br>
         *  ------<br>
         *  <b>Return:</b><br>
         *  &nbsp; 1) int: 0 = sucess; -1 = failure- command failed; -2 = warning- could not close resource.<br>
         *  ------<br>
         *  <b>Throws</b><br>
         *  &nbsp; N/A<br>
         */
        static int externalCommand(std::string command,
                                   std::vector<std::string>& results);
        
        /**
		 *  @name S-Expressions.
		 *  Various S-Expression utility funtions.
		 */
		//@{
		
        /**
		 *  Given an s-expression, search for (str a ...), and return "a" if "a" is a value.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) findValue(sx, "b"); on ((a (b c)) (d (b e))) will return "c".<br>
         *  &nbsp; 2) Uses new and delete as allocators and deallocators.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) exp: The s-expression.<br>
         *  &nbsp; 2) str: The identifier for which to associate a value.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; char *: The value associated with the identifier str.<br>
		 */
        static char *findValue(const char *exp, const char *str);
        
		//@}
		
		//####################################
		//End - Class methods.
		//####################################
		
	protected:
		
		//************************************
		//Inheritence tree variables.
		//************************************
		//************************************
		//End - Inheritence tree variables.
		//************************************
		
	private:
		
		//####################################
		//Constructor(s).
		//#################################### 	
		
		/**
		 *  Default contructor.
		 *  Default contructor.
		 */
		UtilityFunctions();
		
		//####################################
		//End - Constructor(s).
		//####################################
		
		//************************************
		//Non-Inheritence tree variables.
		//************************************
		//************************************
		//End - Non-Inheritence tree variables.
		//************************************
		
	};
    
    
    
    template <class T> inline bool UtilityFunctions::from_string(T& value,
                                                                 const std::string& str,
                                                                 std::ios_base& (*f)(std::ios_base&)){
        std::istringstream iss(str);
        return !(iss >> f >> value).fail();
    }
    
    template <class T> inline T UtilityFunctions::from_string(const std::string& str,
                                                              std::ios_base& (*f)(std::ios_base&)){
        T rVal = static_cast<T>(0);
        
        std::istringstream iss(str);
        
        if((iss >> f >> rVal).fail() == true){
            rVal = static_cast<T>(0);
        }
        
        return rVal;
        
    }
    
    template <class T> inline bool UtilityFunctions::from_char_string(T& value,
                                                                      const char *str,
                                                                      std::ios_base& (*f)(std::ios_base&)){
        if (str == NULL) {
            
            value = static_cast<T>(0);
            return false;
            
        } else {
            
            return UtilityFunctions::from_string<T>(value, str, f);
            
        }
        
    }
    
    template <class T> inline T UtilityFunctions::from_char_string(const char *str,
                                                                   std::ios_base& (*f)(std::ios_base&)){
        
        if (str == NULL) {
            
            return static_cast<T>(0);
            
        } else {
            
            return UtilityFunctions::from_string<T>(str, f);
            
        }
        
    }
    
    template <class T> inline std::string UtilityFunctions::to_string_no_precision(T value, bool statics){
        
        static std::ostringstream oss;
        
        if ( statics == true ) {
            
            oss.str("");
            oss << value;
            return oss.str();
            
        } else {
            
            std::ostringstream noStaticsOSS;
            noStaticsOSS.str("");
            noStaticsOSS <<  value;
            
            return noStaticsOSS.str();
            
        }
        
    }
    
    template <class T> inline std::string UtilityFunctions::to_string(T value, int precision, bool statics , bool fixedPrecision){
        
        static std::ostringstream oss;
		
		if(fixedPrecision == true){
		
			oss <<std::fixed;
        }
		
        if ( statics == true ) {
            
            oss.str("");
            oss << std::setprecision(precision) << value;
            return oss.str();
            
        } else {
            
            std::ostringstream noStaticsOSS;
			
			if(fixedPrecision == true){
			
				noStaticsOSS << std::fixed;
			}
			
            noStaticsOSS.str("");
            noStaticsOSS << std::setprecision(precision) << value;
            
            return noStaticsOSS.str();
            
        }
        
    }
    
    inline void UtilityFunctions::swapUINT16_t(uint16_t *value){
        
		uint8_t *byteArray = NULL;
		byteArray = reinterpret_cast<uint8_t *>(value);
		*value =
		static_cast<uint32_t>(byteArray[1])|
		static_cast<uint32_t>(byteArray[0])<<8;
        
	}
    
	inline void UtilityFunctions::swapUINT32_t(uint32_t *value){
        
		uint8_t *byteArray = NULL;
		byteArray = reinterpret_cast<uint8_t *>(value);
		*value =
		static_cast<uint32_t>(byteArray[3])|
		static_cast<uint32_t>(byteArray[2])<<8|
		static_cast<uint32_t>(byteArray[1])<<16|
		static_cast<uint32_t>(byteArray[0])<<24;
        
	}
	
	inline void UtilityFunctions::swapUINT64_t(uint64_t *value){
        
		uint8_t *byteArray = NULL;
		byteArray = reinterpret_cast<uint8_t *>(value);
		*value =
		static_cast<uint64_t>(byteArray[7])|
		static_cast<uint64_t>(byteArray[6])<<8|
		static_cast<uint64_t>(byteArray[5])<<16|
		static_cast<uint64_t>(byteArray[4])<<24|
		static_cast<uint64_t>(byteArray[3])<<32|
		static_cast<uint64_t>(byteArray[2])<<40|
		static_cast<uint64_t>(byteArray[1])<<48|
		static_cast<uint64_t>(byteArray[0])<<56;
        
	}
}

#endif // UtilityFunctions_DEFINED
