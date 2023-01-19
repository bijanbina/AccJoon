#ifndef UIA_PATTERN_H
#define UIA_PATTERN_H

#include <uiautomationcore.h>
#include "uia_client.h"

/* Forward Declarations */

#ifndef _MSC_VER
#include "uia_core.h"

#ifndef __IUIAutomationValuePattern_INTERFACE_DEFINED__
#define __IUIAutomationValuePattern_INTERFACE_DEFINED__

/* interface IUIAutomationValuePattern */
/* [unique][uuid][object] */


EXTERN_C const IID IID_IUIAutomationValuePattern;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("a94cd8b1-0844-4cd6-9d2d-640537ab39e9")
    IUIAutomationValuePattern : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetValue(
            /* [in] */ __RPC__in BSTR val) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentValue(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentIsReadOnly(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedValue(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedIsReadOnly(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

    };


#else 	/* C style interface */

    typedef struct IUIAutomationValuePatternVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            __RPC__in IUIAutomationValuePattern * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */
            _COM_Outptr_  void **ppvObject);

        ULONG ( STDMETHODCALLTYPE *AddRef )(
            __RPC__in IUIAutomationValuePattern * This);

        ULONG ( STDMETHODCALLTYPE *Release )(
            __RPC__in IUIAutomationValuePattern * This);

        HRESULT ( STDMETHODCALLTYPE *SetValue )(
            __RPC__in IUIAutomationValuePattern * This,
            /* [in] */ __RPC__in BSTR val);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentValue )(
            __RPC__in IUIAutomationValuePattern * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentIsReadOnly )(
            __RPC__in IUIAutomationValuePattern * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedValue )(
            __RPC__in IUIAutomationValuePattern * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedIsReadOnly )(
            __RPC__in IUIAutomationValuePattern * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        END_INTERFACE
    } IUIAutomationValuePatternVtbl;

    interface IUIAutomationValuePattern
    {
        CONST_VTBL struct IUIAutomationValuePatternVtbl *lpVtbl;
    };



#ifdef COBJMACROS


#define IUIAutomationValuePattern_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IUIAutomationValuePattern_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) )

#define IUIAutomationValuePattern_Release(This)	\
    ( (This)->lpVtbl -> Release(This) )


#define IUIAutomationValuePattern_SetValue(This,val)	\
    ( (This)->lpVtbl -> SetValue(This,val) )

#define IUIAutomationValuePattern_get_CurrentValue(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentValue(This,retVal) )

#define IUIAutomationValuePattern_get_CurrentIsReadOnly(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentIsReadOnly(This,retVal) )

#define IUIAutomationValuePattern_get_CachedValue(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedValue(This,retVal) )

#define IUIAutomationValuePattern_get_CachedIsReadOnly(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedIsReadOnly(This,retVal) )

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUIAutomationValuePattern_INTERFACE_DEFINED__ */



#endif // MSVC Compiler


#endif // UIA_PATTERN_H
