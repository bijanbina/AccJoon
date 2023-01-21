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

#ifndef __UIA_PatternIds_MODULE_DEFINED__
#define __UIA_PatternIds_MODULE_DEFINED__


/* module UIA_PatternIds */
/* [dllname] */

const long UIA_InvokePatternId	=	10000;

const long UIA_SelectionPatternId	=	10001;

const long UIA_ValuePatternId	=	10002;

const long UIA_RangeValuePatternId	=	10003;

const long UIA_ScrollPatternId	=	10004;

const long UIA_ExpandCollapsePatternId	=	10005;

const long UIA_GridPatternId	=	10006;

const long UIA_GridItemPatternId	=	10007;

const long UIA_MultipleViewPatternId	=	10008;

const long UIA_WindowPatternId	=	10009;

const long UIA_SelectionItemPatternId	=	10010;

const long UIA_DockPatternId	=	10011;

const long UIA_TablePatternId	=	10012;

const long UIA_TableItemPatternId	=	10013;

const long UIA_TextPatternId	=	10014;

const long UIA_TogglePatternId	=	10015;

const long UIA_TransformPatternId	=	10016;

const long UIA_ScrollItemPatternId	=	10017;

const long UIA_LegacyIAccessiblePatternId	=	10018;

const long UIA_ItemContainerPatternId	=	10019;

const long UIA_VirtualizedItemPatternId	=	10020;

const long UIA_SynchronizedInputPatternId	=	10021;

const long UIA_ObjectModelPatternId	=	10022;

const long UIA_AnnotationPatternId	=	10023;

const long UIA_TextPattern2Id	=	10024;

const long UIA_StylesPatternId	=	10025;

const long UIA_SpreadsheetPatternId	=	10026;

const long UIA_SpreadsheetItemPatternId	=	10027;

const long UIA_TransformPattern2Id	=	10028;

const long UIA_TextChildPatternId	=	10029;

const long UIA_DragPatternId	=	10030;

const long UIA_DropTargetPatternId	=	10031;

const long UIA_TextEditPatternId	=	10032;

const long UIA_CustomNavigationPatternId	=	10033;

const long UIA_SelectionPattern2Id	=	10034;

#endif /* __UIA_PatternIds_MODULE_DEFINED__ */


#endif // MSVC Compiler


#endif // UIA_CLIENT_H
