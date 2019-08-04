
/**@file
 *  EGIException Header File
 *  @author Robert Bell
 *  @date 04/28/2009
 *  @remarks
 *  Put notes here.
 */

#ifndef EGIException_DEFINED
#define EGIException_DEFINED

#include "EGIObject.h"

/**
 *  EGIBase namespace.
 */
namespace EGIBase{
	
	/**
	 *  EGIException Class.
	 *  @author Robert Bell.
	 *  @remarks
	 *
	 *  ------<br>
	 *  Update: 2009-04-28: Class creation.<br>
	 *  ------<br>
	 */
	class EGIException : public EGIObject{
		
	public:
		//####################################
		// Constructor(s).
		//####################################
		
		/**
		 *  Default contructor.
		 *  Default contructor.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; message: Exception message.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; N/A<br>
		 */
		EGIException(std::string message);
		
		/**
		 *  Constructor.
		 *  Constructor.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; message: Exception message.<br>
		 *  &nbsp; exitApplication: true: handlers should call exit, false: handlers should not call exit.<br>
		 *  &nbsp; threadsafe: true: thread safe, false: not thread safe.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; N/A<br>
		 */
		EGIException(std::string message, bool exitApplication, bool threadsafe);
		
		//####################################
		// End - Constructor(s).
		//####################################
		
		//####################################
		// Destructor.
		//#################################### 
		
		/**
		 *  Destructor
		 *  Destructor
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual ~EGIException();
		
		//####################################
		// End - Destructor.
		//####################################
		
		/**
		 *  Gets the exception message.
		 *  Gets the exception message.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; std::string: N/A<br>
		 */
		virtual std::string getMessage();
		
		/**
		 *  Gets the exit application flag.
		 *  Gets the exit application flag.
		 *  <b>Notes:</b><br>
		 *  &nbsp; Handlers use this flag to determine whether or not to exit the application.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; std::string: N/A<br>
		 */
		bool getExitApplication();
		
		/**
		 *  The toString method.
		 *  The toString method.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; std::string: N/A<br>
		 */
		virtual std::string toString(){return EGIObject::toString() + "::EGIException";}
		
		//####################################
		// Class variables.
		//####################################
		
		/**
		 *  Class ID<br>
		 *  Specifies the class ID for instances of this class.
		 */
		static const ClassID classID = 'EXON';
		
		//####################################
		// End - Class variables.
		//####################################
		
		//####################################
		// Class methods.
		//####################################
		//####################################
		// End - Class methods.
		//####################################
		
		
		
	protected:
		
		//####################################
		//Inheritence tree variables.
		//####################################
		std::string mMessage;
		bool mExitApplication;
		//####################################
		//End - Inheritence tree variables.
		//####################################
		
	private:
		
		//####################################
		//Non-Inheritence tree variables.
		//####################################
		//####################################
		//End - Non-Inheritence tree variables.
		//####################################
	};
}

#endif // EGIException_DEFINED
