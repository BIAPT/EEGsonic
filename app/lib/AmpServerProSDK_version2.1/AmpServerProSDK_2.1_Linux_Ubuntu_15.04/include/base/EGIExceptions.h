
/**@file
 *  EGIExceptions Header File
 *  @author Robert Bell
 *  @date 04/28/2009
 *  @remarks
 *  Put notes here.
 */

#include "EGIException.h"

#include <iostream>

#ifndef EGIExceptions_DEFINED
#define EGIExceptions_DEFINED

/**
 *  EGIBase namespace.
 */
namespace EGIBase{
	
#ifdef __USE_EXCEPTIONS__
	#define EGI_THROW(exception_type, message) throw exception_type(message);
	#define EGI_THROW_EXTENDED(exception_type, message, exitApplication, threadsafe) \
		throw exception_type(message, exitApplication, threadsafe);
#else
	#define EGI_THROW(exception_type, message) std::cout << message << std::endl;
	#define EGI_THROW_EXTENDED(exception_type, message, exitApplication, threadsafe) \
		std::cout << message << std::endl;	
#endif //__USE_EXCEPTIONS__	

	class Fatal_EGIException : public EGIException{
	public:
		Fatal_EGIException(std::string message) : EGIException(message){}
		Fatal_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class BadCast_EGIException : public EGIException{
	public:
		BadCast_EGIException(std::string message) : EGIException(message){}
		BadCast_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class Alloc_EGIException : public EGIException{
	public:
		Alloc_EGIException(std::string message) : EGIException(message){}
		Alloc_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class Free_EGIException : public EGIException{
	public:
		Free_EGIException(std::string message) : EGIException(message){}
		Free_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class Init_EGIException : public EGIException{
	public:
		Init_EGIException(std::string message) : EGIException(message){}
		Init_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class Retain_EGIException : public EGIException{
	public:
		Retain_EGIException(std::string message) : EGIException(message){}
		Retain_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class Release_EGIException : public EGIException{
	public:
		Release_EGIException(std::string message) : EGIException(message){}
		Release_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class AutoRelease_EGIException : public EGIException{
	public:
		AutoRelease_EGIException(std::string message) : EGIException(message){}
		AutoRelease_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class NULL_EGIException : public EGIException{
	public:
		NULL_EGIException(std::string message) : EGIException(message){}
		NULL_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
    
    class BadValue_EGIException : public EGIException{
	public:
		BadValue_EGIException(std::string message) : EGIException(message){}
		BadValue_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class MethodNotSupported_EGIException : public EGIException{
	public:
		MethodNotSupported_EGIException(std::string message) : EGIException(message){}
		MethodNotSupported_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class InvalidArgument_EGIException : public EGIException{
	public:
		InvalidArgument_EGIException(std::string message) : EGIException(message){}
		InvalidArgument_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class ResourceLock_EGIException : public EGIException{
	public:
		ResourceLock_EGIException(std::string message) : EGIException(message){}
		ResourceLock_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
	
	class ResourceUnlock_EGIException : public EGIException{
	public:
		ResourceUnlock_EGIException(std::string message) : EGIException(message){}
		ResourceUnlock_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
    
    class Error_EGIException : public EGIException{
	public:
		Error_EGIException(std::string message) : EGIException(message){}
		Error_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
	};
}

#endif // EGIExceptions_DEFINED
