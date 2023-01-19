#ifndef UIA_CLIENT_H
#define UIA_CLIENT_H

#include "rpc.h"
#include "rpcndr.h"

/* Forward Declarations */

#ifndef _MSC_VER

#ifndef __IUIAutomationElement_FWD_DEFINED__
#define __IUIAutomationElement_FWD_DEFINED__
typedef interface IUIAutomationElement IUIAutomationElement;

#endif 	/* __IUIAutomationElement_FWD_DEFINED__ */

#ifndef __IUIAutomationValuePattern_FWD_DEFINED__
#define __IUIAutomationValuePattern_FWD_DEFINED__
typedef interface IUIAutomationValuePattern IUIAutomationValuePattern;

#endif 	/* __IUIAutomationValuePattern_FWD_DEFINED__ */

#ifndef __IUIAutomation_FWD_DEFINED__
#define __IUIAutomation_FWD_DEFINED__
typedef interface IUIAutomation IUIAutomation;

#endif 	/* __IUIAutomation_FWD_DEFINED__ */

#ifndef __CUIAutomation_FWD_DEFINED__
#define __CUIAutomation_FWD_DEFINED__

#ifdef __cplusplus
typedef class CUIAutomation CUIAutomation;
#else
typedef struct CUIAutomation CUIAutomation;
#endif /* __cplusplus */

#endif 	/* __CUIAutomation_FWD_DEFINED__ */

#ifndef __IUIAutomationCondition_FWD_DEFINED__
#define __IUIAutomationCondition_FWD_DEFINED__
typedef interface IUIAutomationCondition IUIAutomationCondition;

#endif 	/* __IUIAutomationCondition_FWD_DEFINED__ */

#ifndef __IUIAutomationElementArray_FWD_DEFINED__
#define __IUIAutomationElementArray_FWD_DEFINED__
typedef interface IUIAutomationElementArray IUIAutomationElementArray;

#endif 	/* __IUIAutomationElementArray_FWD_DEFINED__ */

#ifndef __IUIAutomationCacheRequest_FWD_DEFINED__
#define __IUIAutomationCacheRequest_FWD_DEFINED__
typedef interface IUIAutomationCacheRequest IUIAutomationCacheRequest;

#endif 	/* __IUIAutomationCacheRequest_FWD_DEFINED__ */

#ifndef __IUIAutomationTreeWalker_FWD_DEFINED__
#define __IUIAutomationTreeWalker_FWD_DEFINED__
typedef interface IUIAutomationTreeWalker IUIAutomationTreeWalker;

#endif 	/* __IUIAutomationTreeWalker_FWD_DEFINED__ */

#ifndef __IUIAutomationEventHandler_FWD_DEFINED__
#define __IUIAutomationEventHandler_FWD_DEFINED__
typedef interface IUIAutomationEventHandler IUIAutomationEventHandler;

#endif 	/* __IUIAutomationEventHandler_FWD_DEFINED__ */

#ifndef __IUIAutomationPropertyChangedEventHandler_FWD_DEFINED__
#define __IUIAutomationPropertyChangedEventHandler_FWD_DEFINED__
typedef interface IUIAutomationPropertyChangedEventHandler IUIAutomationPropertyChangedEventHandler;

#endif 	/* __IUIAutomationPropertyChangedEventHandler_FWD_DEFINED__ */

#ifndef __IUIAutomationStructureChangedEventHandler_FWD_DEFINED__
#define __IUIAutomationStructureChangedEventHandler_FWD_DEFINED__
typedef interface IUIAutomationStructureChangedEventHandler IUIAutomationStructureChangedEventHandler;

#endif 	/* __IUIAutomationStructureChangedEventHandler_FWD_DEFINED__ */

#ifndef __IUIAutomationFocusChangedEventHandler_FWD_DEFINED__
#define __IUIAutomationFocusChangedEventHandler_FWD_DEFINED__
typedef interface IUIAutomationFocusChangedEventHandler IUIAutomationFocusChangedEventHandler;

#endif 	/* __IUIAutomationFocusChangedEventHandler_FWD_DEFINED__ */

#ifndef __IUIAutomationProxyFactory_FWD_DEFINED__
#define __IUIAutomationProxyFactory_FWD_DEFINED__
typedef interface IUIAutomationProxyFactory IUIAutomationProxyFactory;

#endif 	/* __IUIAutomationProxyFactory_FWD_DEFINED__ */


#ifndef __IUIAutomationProxyFactoryEntry_FWD_DEFINED__
#define __IUIAutomationProxyFactoryEntry_FWD_DEFINED__
typedef interface IUIAutomationProxyFactoryEntry IUIAutomationProxyFactoryEntry;

#endif 	/* __IUIAutomationProxyFactoryEntry_FWD_DEFINED__ */


#ifndef __IUIAutomationProxyFactoryMapping_FWD_DEFINED__
#define __IUIAutomationProxyFactoryMapping_FWD_DEFINED__
typedef interface IUIAutomationProxyFactoryMapping IUIAutomationProxyFactoryMapping;

#endif 	/* __IUIAutomationProxyFactoryMapping_FWD_DEFINED__ */

typedef void *UIA_HWND;

enum TreeScope
    {
        TreeScope_None	= 0,
        TreeScope_Element	= 0x1,
        TreeScope_Children	= 0x2,
        TreeScope_Descendants	= 0x4,
        TreeScope_Parent	= 0x8,
        TreeScope_Ancestors	= 0x10,
        TreeScope_Subtree	= ( ( TreeScope_Element | TreeScope_Children )  | TreeScope_Descendants )
    } ;

enum PropertyConditionFlags
    {
        PropertyConditionFlags_None	= 0,
        PropertyConditionFlags_IgnoreCase	= 0x1,
        PropertyConditionFlags_MatchSubstring	= 0x2
    } ;

#endif // MSVC Compiler


#endif // UIA_CLIENT_H
