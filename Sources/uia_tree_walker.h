#ifndef UIA_TREE_WALKER_H
#define UIA_TREE_WALKER_H

#include "uia_element.h"

/* Forward Declarations */

#ifndef _MSC_VER

#ifndef __IUIAutomationTreeWalker_INTERFACE_DEFINED__
#define __IUIAutomationTreeWalker_INTERFACE_DEFINED__

/* interface IUIAutomationTreeWalker */
/* [unique][uuid][object] */


EXTERN_C const IID IID_IUIAutomationTreeWalker;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4042c624-389c-4afc-a630-9df854a541fc")
    IUIAutomationTreeWalker : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetParentElement(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **parent) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetFirstChildElement(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **first) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetLastChildElement(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **last) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetNextSiblingElement(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **next) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetPreviousSiblingElement(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **previous) = 0;

        virtual HRESULT STDMETHODCALLTYPE NormalizeElement(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **normalized) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetParentElementBuildCache(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **parent) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetFirstChildElementBuildCache(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **first) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetLastChildElementBuildCache(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **last) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetNextSiblingElementBuildCache(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **next) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetPreviousSiblingElementBuildCache(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **previous) = 0;

        virtual HRESULT STDMETHODCALLTYPE NormalizeElementBuildCache(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **normalized) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Condition(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **condition) = 0;

    };


#else 	/* C style interface */

    typedef struct IUIAutomationTreeWalkerVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */
            _COM_Outptr_  void **ppvObject);

        ULONG ( STDMETHODCALLTYPE *AddRef )(
            __RPC__in IUIAutomationTreeWalker * This);

        ULONG ( STDMETHODCALLTYPE *Release )(
            __RPC__in IUIAutomationTreeWalker * This);

        HRESULT ( STDMETHODCALLTYPE *GetParentElement )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **parent);

        HRESULT ( STDMETHODCALLTYPE *GetFirstChildElement )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **first);

        HRESULT ( STDMETHODCALLTYPE *GetLastChildElement )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **last);

        HRESULT ( STDMETHODCALLTYPE *GetNextSiblingElement )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **next);

        HRESULT ( STDMETHODCALLTYPE *GetPreviousSiblingElement )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **previous);

        HRESULT ( STDMETHODCALLTYPE *NormalizeElement )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **normalized);

        HRESULT ( STDMETHODCALLTYPE *GetParentElementBuildCache )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **parent);

        HRESULT ( STDMETHODCALLTYPE *GetFirstChildElementBuildCache )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **first);

        HRESULT ( STDMETHODCALLTYPE *GetLastChildElementBuildCache )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **last);

        HRESULT ( STDMETHODCALLTYPE *GetNextSiblingElementBuildCache )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **next);

        HRESULT ( STDMETHODCALLTYPE *GetPreviousSiblingElementBuildCache )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **previous);

        HRESULT ( STDMETHODCALLTYPE *NormalizeElementBuildCache )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **normalized);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Condition )(
            __RPC__in IUIAutomationTreeWalker * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **condition);

        END_INTERFACE
    } IUIAutomationTreeWalkerVtbl;

    interface IUIAutomationTreeWalker
    {
        CONST_VTBL struct IUIAutomationTreeWalkerVtbl *lpVtbl;
    };



#ifdef COBJMACROS


#define IUIAutomationTreeWalker_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IUIAutomationTreeWalker_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) )

#define IUIAutomationTreeWalker_Release(This)	\
    ( (This)->lpVtbl -> Release(This) )


#define IUIAutomationTreeWalker_GetParentElement(This,element,parent)	\
    ( (This)->lpVtbl -> GetParentElement(This,element,parent) )

#define IUIAutomationTreeWalker_GetFirstChildElement(This,element,first)	\
    ( (This)->lpVtbl -> GetFirstChildElement(This,element,first) )

#define IUIAutomationTreeWalker_GetLastChildElement(This,element,last)	\
    ( (This)->lpVtbl -> GetLastChildElement(This,element,last) )

#define IUIAutomationTreeWalker_GetNextSiblingElement(This,element,next)	\
    ( (This)->lpVtbl -> GetNextSiblingElement(This,element,next) )

#define IUIAutomationTreeWalker_GetPreviousSiblingElement(This,element,previous)	\
    ( (This)->lpVtbl -> GetPreviousSiblingElement(This,element,previous) )

#define IUIAutomationTreeWalker_NormalizeElement(This,element,normalized)	\
    ( (This)->lpVtbl -> NormalizeElement(This,element,normalized) )

#define IUIAutomationTreeWalker_GetParentElementBuildCache(This,element,cacheRequest,parent)	\
    ( (This)->lpVtbl -> GetParentElementBuildCache(This,element,cacheRequest,parent) )

#define IUIAutomationTreeWalker_GetFirstChildElementBuildCache(This,element,cacheRequest,first)	\
    ( (This)->lpVtbl -> GetFirstChildElementBuildCache(This,element,cacheRequest,first) )

#define IUIAutomationTreeWalker_GetLastChildElementBuildCache(This,element,cacheRequest,last)	\
    ( (This)->lpVtbl -> GetLastChildElementBuildCache(This,element,cacheRequest,last) )

#define IUIAutomationTreeWalker_GetNextSiblingElementBuildCache(This,element,cacheRequest,next)	\
    ( (This)->lpVtbl -> GetNextSiblingElementBuildCache(This,element,cacheRequest,next) )

#define IUIAutomationTreeWalker_GetPreviousSiblingElementBuildCache(This,element,cacheRequest,previous)	\
    ( (This)->lpVtbl -> GetPreviousSiblingElementBuildCache(This,element,cacheRequest,previous) )

#define IUIAutomationTreeWalker_NormalizeElementBuildCache(This,element,cacheRequest,normalized)	\
    ( (This)->lpVtbl -> NormalizeElementBuildCache(This,element,cacheRequest,normalized) )

#define IUIAutomationTreeWalker_get_Condition(This,condition)	\
    ( (This)->lpVtbl -> get_Condition(This,condition) )

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUIAutomationTreeWalker_INTERFACE_DEFINED__ */


#endif // MSVC Compiler


#endif // UIA_TREE_WALKER_H
