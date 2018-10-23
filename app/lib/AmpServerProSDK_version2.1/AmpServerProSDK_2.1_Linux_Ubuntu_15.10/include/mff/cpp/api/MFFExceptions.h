
/**@file
 *  MFFExceptions Header File
 *  @author Robert Bell
 *  @date 04/28/2009
 *  @remarks
 *  Put notes here.
 */

#include "EGIExceptions.h"

#include <iostream>

#ifndef MFFExceptions_DEFINED
#define MFFExceptions_DEFINED

/**
 *  com namespace.
 */
namespace com{
    
	/**
	 *  egi namespace.
	 */
	namespace egi{
        
		/**
		 *  services namespace.
		 */
		namespace services{
            
			/**
			 *  mff namespace.
			 */
			namespace mff{
				
                /**
				 *  api namespace.
				 */
				namespace api{
                    
                    class Resource_MFFException : public EGIBase::EGIException{
                        
                    public:
                        
                        Resource_MFFException(std::string message) : EGIException(message){}
                        Resource_MFFException(std::string message, bool exitApplication, bool threadsafe) : EGIException(message, exitApplication, threadsafe){}
                        
                    };
                    
                }
                
            }
            
        }
        
    }
    
}

#endif // MFFExceptions_DEFINED
