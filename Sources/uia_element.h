#ifndef UIA_ELEMENT_H
#define UIA_ELEMENT_H

#include <uiautomationcore.h>
#include "uia_client.h"
// if not MSVC Compiler
#ifndef _MSC_VER
#include "uia_core.h"

#ifndef __IUIAutomationElement_INTERFACE_DEFINED__
#define __IUIAutomationElement_INTERFACE_DEFINED__

/* interface IUIAutomationElement */
/* [unique][uuid][object] */


EXTERN_C const IID IID_IUIAutomationElement;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("d22108aa-8ac5-49a5-837b-37bbb3d7591e")
    IUIAutomationElement : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFocus( void) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetRuntimeId(
            /* [retval][out] */ __RPC__deref_out_opt SAFEARRAY * *runtimeId) = 0;

        virtual HRESULT STDMETHODCALLTYPE FindFirst(
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **found) = 0;

        virtual HRESULT STDMETHODCALLTYPE FindAll(
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **found) = 0;

        virtual HRESULT STDMETHODCALLTYPE FindFirstBuildCache(
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **found) = 0;

        virtual HRESULT STDMETHODCALLTYPE FindAllBuildCache(
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **found) = 0;

        virtual HRESULT STDMETHODCALLTYPE BuildUpdatedCache(
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **updatedElement) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCurrentPropertyValue(
            /* [in] */ PROPERTYID propertyId,
            /* [retval][out] */ __RPC__out VARIANT *retVal) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCurrentPropertyValueEx(
            /* [in] */ PROPERTYID propertyId,
            /* [in] */ BOOL ignoreDefaultValue,
            /* [retval][out] */ __RPC__out VARIANT *retVal) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCachedPropertyValue(
            /* [in] */ PROPERTYID propertyId,
            /* [retval][out] */ __RPC__out VARIANT *retVal) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCachedPropertyValueEx(
            /* [in] */ PROPERTYID propertyId,
            /* [in] */ BOOL ignoreDefaultValue,
            /* [retval][out] */ __RPC__out VARIANT *retVal) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCurrentPatternAs(
            /* [in] */ PATTERNID patternId,
            /* [in] */ __RPC__in REFIID riid,
            /* [retval][iid_is][out] */ __RPC__deref_out_opt void **patternObject) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCachedPatternAs(
            /* [in] */ PATTERNID patternId,
            /* [in] */ __RPC__in REFIID riid,
            /* [retval][iid_is][out] */ __RPC__deref_out_opt void **patternObject) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCurrentPattern(
            /* [in] */ PATTERNID patternId,
            /* [retval][out] */ __RPC__deref_out_opt IUnknown **patternObject) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCachedPattern(
            /* [in] */ PATTERNID patternId,
            /* [retval][out] */ __RPC__deref_out_opt IUnknown **patternObject) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCachedParent(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **parent) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCachedChildren(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **children) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentProcessId(
            /* [retval][out] */ __RPC__out int *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentControlType(
            /* [retval][out] */ __RPC__out CONTROLTYPEID *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentLocalizedControlType(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentName(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentAcceleratorKey(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentAccessKey(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentHasKeyboardFocus(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentIsKeyboardFocusable(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentIsEnabled(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentAutomationId(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentClassName(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentHelpText(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentCulture(
            /* [retval][out] */ __RPC__out int *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentIsControlElement(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentIsContentElement(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentIsPassword(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentNativeWindowHandle(
            /* [retval][out] */ __RPC__deref_out_opt UIA_HWND *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentItemType(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentIsOffscreen(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentOrientation(
            /* [retval][out] */ __RPC__out enum OrientationType *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentFrameworkId(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentIsRequiredForForm(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentItemStatus(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentBoundingRectangle(
            /* [retval][out] */ __RPC__out RECT *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentLabeledBy(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentAriaRole(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentAriaProperties(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentIsDataValidForForm(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentControllerFor(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentDescribedBy(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentFlowsTo(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentProviderDescription(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedProcessId(
            /* [retval][out] */ __RPC__out int *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedControlType(
            /* [retval][out] */ __RPC__out CONTROLTYPEID *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedLocalizedControlType(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedName(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedAcceleratorKey(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedAccessKey(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedHasKeyboardFocus(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedIsKeyboardFocusable(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedIsEnabled(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedAutomationId(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedClassName(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedHelpText(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedCulture(
            /* [retval][out] */ __RPC__out int *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedIsControlElement(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedIsContentElement(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedIsPassword(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedNativeWindowHandle(
            /* [retval][out] */ __RPC__deref_out_opt UIA_HWND *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedItemType(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedIsOffscreen(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedOrientation(
            /* [retval][out] */ __RPC__out enum OrientationType *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedFrameworkId(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedIsRequiredForForm(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedItemStatus(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedBoundingRectangle(
            /* [retval][out] */ __RPC__out RECT *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedLabeledBy(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedAriaRole(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedAriaProperties(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedIsDataValidForForm(
            /* [retval][out] */ __RPC__out BOOL *retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedControllerFor(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedDescribedBy(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedFlowsTo(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CachedProviderDescription(
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetClickablePoint(
            /* [out] */ __RPC__out POINT *clickable,
            /* [retval][out] */ __RPC__out BOOL *gotClickable) = 0;

    };


#else 	/* C style interface */

    typedef struct IUIAutomationElementVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */
            _COM_Outptr_  void **ppvObject);

        ULONG ( STDMETHODCALLTYPE *AddRef )(
            __RPC__in IUIAutomationElement * This);

        ULONG ( STDMETHODCALLTYPE *Release )(
            __RPC__in IUIAutomationElement * This);

        HRESULT ( STDMETHODCALLTYPE *SetFocus )(
            __RPC__in IUIAutomationElement * This);

        HRESULT ( STDMETHODCALLTYPE *GetRuntimeId )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt SAFEARRAY * *runtimeId);

        HRESULT ( STDMETHODCALLTYPE *FindFirst )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **found);

        HRESULT ( STDMETHODCALLTYPE *FindAll )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **found);

        HRESULT ( STDMETHODCALLTYPE *FindFirstBuildCache )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **found);

        HRESULT ( STDMETHODCALLTYPE *FindAllBuildCache )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **found);

        HRESULT ( STDMETHODCALLTYPE *BuildUpdatedCache )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **updatedElement);

        HRESULT ( STDMETHODCALLTYPE *GetCurrentPropertyValue )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ PROPERTYID propertyId,
            /* [retval][out] */ __RPC__out VARIANT *retVal);

        HRESULT ( STDMETHODCALLTYPE *GetCurrentPropertyValueEx )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ PROPERTYID propertyId,
            /* [in] */ BOOL ignoreDefaultValue,
            /* [retval][out] */ __RPC__out VARIANT *retVal);

        HRESULT ( STDMETHODCALLTYPE *GetCachedPropertyValue )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ PROPERTYID propertyId,
            /* [retval][out] */ __RPC__out VARIANT *retVal);

        HRESULT ( STDMETHODCALLTYPE *GetCachedPropertyValueEx )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ PROPERTYID propertyId,
            /* [in] */ BOOL ignoreDefaultValue,
            /* [retval][out] */ __RPC__out VARIANT *retVal);

        HRESULT ( STDMETHODCALLTYPE *GetCurrentPatternAs )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ PATTERNID patternId,
            /* [in] */ __RPC__in REFIID riid,
            /* [retval][iid_is][out] */ __RPC__deref_out_opt void **patternObject);

        HRESULT ( STDMETHODCALLTYPE *GetCachedPatternAs )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ PATTERNID patternId,
            /* [in] */ __RPC__in REFIID riid,
            /* [retval][iid_is][out] */ __RPC__deref_out_opt void **patternObject);

        HRESULT ( STDMETHODCALLTYPE *GetCurrentPattern )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ PATTERNID patternId,
            /* [retval][out] */ __RPC__deref_out_opt IUnknown **patternObject);

        HRESULT ( STDMETHODCALLTYPE *GetCachedPattern )(
            __RPC__in IUIAutomationElement * This,
            /* [in] */ PATTERNID patternId,
            /* [retval][out] */ __RPC__deref_out_opt IUnknown **patternObject);

        HRESULT ( STDMETHODCALLTYPE *GetCachedParent )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **parent);

        HRESULT ( STDMETHODCALLTYPE *GetCachedChildren )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **children);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentProcessId )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out int *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentControlType )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out CONTROLTYPEID *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentLocalizedControlType )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentName )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentAcceleratorKey )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentAccessKey )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentHasKeyboardFocus )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentIsKeyboardFocusable )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentIsEnabled )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentAutomationId )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentClassName )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentHelpText )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentCulture )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out int *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentIsControlElement )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentIsContentElement )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentIsPassword )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentNativeWindowHandle )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt UIA_HWND *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentItemType )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentIsOffscreen )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentOrientation )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out enum OrientationType *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentFrameworkId )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentIsRequiredForForm )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentItemStatus )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentBoundingRectangle )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out RECT *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentLabeledBy )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentAriaRole )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentAriaProperties )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentIsDataValidForForm )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentControllerFor )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentDescribedBy )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentFlowsTo )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentProviderDescription )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedProcessId )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out int *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedControlType )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out CONTROLTYPEID *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedLocalizedControlType )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedName )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedAcceleratorKey )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedAccessKey )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedHasKeyboardFocus )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedIsKeyboardFocusable )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedIsEnabled )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedAutomationId )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedClassName )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedHelpText )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedCulture )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out int *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedIsControlElement )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedIsContentElement )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedIsPassword )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedNativeWindowHandle )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt UIA_HWND *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedItemType )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedIsOffscreen )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedOrientation )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out enum OrientationType *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedFrameworkId )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedIsRequiredForForm )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedItemStatus )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedBoundingRectangle )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out RECT *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedLabeledBy )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedAriaRole )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedAriaProperties )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedIsDataValidForForm )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__out BOOL *retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedControllerFor )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedDescribedBy )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedFlowsTo )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElementArray **retVal);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_CachedProviderDescription )(
            __RPC__in IUIAutomationElement * This,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *retVal);

        HRESULT ( STDMETHODCALLTYPE *GetClickablePoint )(
            __RPC__in IUIAutomationElement * This,
            /* [out] */ __RPC__out POINT *clickable,
            /* [retval][out] */ __RPC__out BOOL *gotClickable);

        END_INTERFACE
    } IUIAutomationElementVtbl;

    interface IUIAutomationElement
    {
        CONST_VTBL struct IUIAutomationElementVtbl *lpVtbl;
    };



#ifdef COBJMACROS


#define IUIAutomationElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IUIAutomationElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) )

#define IUIAutomationElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) )


#define IUIAutomationElement_SetFocus(This)	\
    ( (This)->lpVtbl -> SetFocus(This) )

#define IUIAutomationElement_GetRuntimeId(This,runtimeId)	\
    ( (This)->lpVtbl -> GetRuntimeId(This,runtimeId) )

#define IUIAutomationElement_FindFirst(This,scope,condition,found)	\
    ( (This)->lpVtbl -> FindFirst(This,scope,condition,found) )

#define IUIAutomationElement_FindAll(This,scope,condition,found)	\
    ( (This)->lpVtbl -> FindAll(This,scope,condition,found) )

#define IUIAutomationElement_FindFirstBuildCache(This,scope,condition,cacheRequest,found)	\
    ( (This)->lpVtbl -> FindFirstBuildCache(This,scope,condition,cacheRequest,found) )

#define IUIAutomationElement_FindAllBuildCache(This,scope,condition,cacheRequest,found)	\
    ( (This)->lpVtbl -> FindAllBuildCache(This,scope,condition,cacheRequest,found) )

#define IUIAutomationElement_BuildUpdatedCache(This,cacheRequest,updatedElement)	\
    ( (This)->lpVtbl -> BuildUpdatedCache(This,cacheRequest,updatedElement) )

#define IUIAutomationElement_GetCurrentPropertyValue(This,propertyId,retVal)	\
    ( (This)->lpVtbl -> GetCurrentPropertyValue(This,propertyId,retVal) )

#define IUIAutomationElement_GetCurrentPropertyValueEx(This,propertyId,ignoreDefaultValue,retVal)	\
    ( (This)->lpVtbl -> GetCurrentPropertyValueEx(This,propertyId,ignoreDefaultValue,retVal) )

#define IUIAutomationElement_GetCachedPropertyValue(This,propertyId,retVal)	\
    ( (This)->lpVtbl -> GetCachedPropertyValue(This,propertyId,retVal) )

#define IUIAutomationElement_GetCachedPropertyValueEx(This,propertyId,ignoreDefaultValue,retVal)	\
    ( (This)->lpVtbl -> GetCachedPropertyValueEx(This,propertyId,ignoreDefaultValue,retVal) )

#define IUIAutomationElement_GetCurrentPatternAs(This,patternId,riid,patternObject)	\
    ( (This)->lpVtbl -> GetCurrentPatternAs(This,patternId,riid,patternObject) )

#define IUIAutomationElement_GetCachedPatternAs(This,patternId,riid,patternObject)	\
    ( (This)->lpVtbl -> GetCachedPatternAs(This,patternId,riid,patternObject) )

#define IUIAutomationElement_GetCurrentPattern(This,patternId,patternObject)	\
    ( (This)->lpVtbl -> GetCurrentPattern(This,patternId,patternObject) )

#define IUIAutomationElement_GetCachedPattern(This,patternId,patternObject)	\
    ( (This)->lpVtbl -> GetCachedPattern(This,patternId,patternObject) )

#define IUIAutomationElement_GetCachedParent(This,parent)	\
    ( (This)->lpVtbl -> GetCachedParent(This,parent) )

#define IUIAutomationElement_GetCachedChildren(This,children)	\
    ( (This)->lpVtbl -> GetCachedChildren(This,children) )

#define IUIAutomationElement_get_CurrentProcessId(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentProcessId(This,retVal) )

#define IUIAutomationElement_get_CurrentControlType(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentControlType(This,retVal) )

#define IUIAutomationElement_get_CurrentLocalizedControlType(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentLocalizedControlType(This,retVal) )

#define IUIAutomationElement_get_CurrentName(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentName(This,retVal) )

#define IUIAutomationElement_get_CurrentAcceleratorKey(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentAcceleratorKey(This,retVal) )

#define IUIAutomationElement_get_CurrentAccessKey(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentAccessKey(This,retVal) )

#define IUIAutomationElement_get_CurrentHasKeyboardFocus(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentHasKeyboardFocus(This,retVal) )

#define IUIAutomationElement_get_CurrentIsKeyboardFocusable(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentIsKeyboardFocusable(This,retVal) )

#define IUIAutomationElement_get_CurrentIsEnabled(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentIsEnabled(This,retVal) )

#define IUIAutomationElement_get_CurrentAutomationId(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentAutomationId(This,retVal) )

#define IUIAutomationElement_get_CurrentClassName(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentClassName(This,retVal) )

#define IUIAutomationElement_get_CurrentHelpText(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentHelpText(This,retVal) )

#define IUIAutomationElement_get_CurrentCulture(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentCulture(This,retVal) )

#define IUIAutomationElement_get_CurrentIsControlElement(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentIsControlElement(This,retVal) )

#define IUIAutomationElement_get_CurrentIsContentElement(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentIsContentElement(This,retVal) )

#define IUIAutomationElement_get_CurrentIsPassword(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentIsPassword(This,retVal) )

#define IUIAutomationElement_get_CurrentNativeWindowHandle(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentNativeWindowHandle(This,retVal) )

#define IUIAutomationElement_get_CurrentItemType(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentItemType(This,retVal) )

#define IUIAutomationElement_get_CurrentIsOffscreen(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentIsOffscreen(This,retVal) )

#define IUIAutomationElement_get_CurrentOrientation(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentOrientation(This,retVal) )

#define IUIAutomationElement_get_CurrentFrameworkId(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentFrameworkId(This,retVal) )

#define IUIAutomationElement_get_CurrentIsRequiredForForm(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentIsRequiredForForm(This,retVal) )

#define IUIAutomationElement_get_CurrentItemStatus(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentItemStatus(This,retVal) )

#define IUIAutomationElement_get_CurrentBoundingRectangle(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentBoundingRectangle(This,retVal) )

#define IUIAutomationElement_get_CurrentLabeledBy(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentLabeledBy(This,retVal) )

#define IUIAutomationElement_get_CurrentAriaRole(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentAriaRole(This,retVal) )

#define IUIAutomationElement_get_CurrentAriaProperties(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentAriaProperties(This,retVal) )

#define IUIAutomationElement_get_CurrentIsDataValidForForm(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentIsDataValidForForm(This,retVal) )

#define IUIAutomationElement_get_CurrentControllerFor(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentControllerFor(This,retVal) )

#define IUIAutomationElement_get_CurrentDescribedBy(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentDescribedBy(This,retVal) )

#define IUIAutomationElement_get_CurrentFlowsTo(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentFlowsTo(This,retVal) )

#define IUIAutomationElement_get_CurrentProviderDescription(This,retVal)	\
    ( (This)->lpVtbl -> get_CurrentProviderDescription(This,retVal) )

#define IUIAutomationElement_get_CachedProcessId(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedProcessId(This,retVal) )

#define IUIAutomationElement_get_CachedControlType(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedControlType(This,retVal) )

#define IUIAutomationElement_get_CachedLocalizedControlType(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedLocalizedControlType(This,retVal) )

#define IUIAutomationElement_get_CachedName(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedName(This,retVal) )

#define IUIAutomationElement_get_CachedAcceleratorKey(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedAcceleratorKey(This,retVal) )

#define IUIAutomationElement_get_CachedAccessKey(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedAccessKey(This,retVal) )

#define IUIAutomationElement_get_CachedHasKeyboardFocus(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedHasKeyboardFocus(This,retVal) )

#define IUIAutomationElement_get_CachedIsKeyboardFocusable(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedIsKeyboardFocusable(This,retVal) )

#define IUIAutomationElement_get_CachedIsEnabled(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedIsEnabled(This,retVal) )

#define IUIAutomationElement_get_CachedAutomationId(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedAutomationId(This,retVal) )

#define IUIAutomationElement_get_CachedClassName(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedClassName(This,retVal) )

#define IUIAutomationElement_get_CachedHelpText(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedHelpText(This,retVal) )

#define IUIAutomationElement_get_CachedCulture(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedCulture(This,retVal) )

#define IUIAutomationElement_get_CachedIsControlElement(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedIsControlElement(This,retVal) )

#define IUIAutomationElement_get_CachedIsContentElement(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedIsContentElement(This,retVal) )

#define IUIAutomationElement_get_CachedIsPassword(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedIsPassword(This,retVal) )

#define IUIAutomationElement_get_CachedNativeWindowHandle(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedNativeWindowHandle(This,retVal) )

#define IUIAutomationElement_get_CachedItemType(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedItemType(This,retVal) )

#define IUIAutomationElement_get_CachedIsOffscreen(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedIsOffscreen(This,retVal) )

#define IUIAutomationElement_get_CachedOrientation(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedOrientation(This,retVal) )

#define IUIAutomationElement_get_CachedFrameworkId(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedFrameworkId(This,retVal) )

#define IUIAutomationElement_get_CachedIsRequiredForForm(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedIsRequiredForForm(This,retVal) )

#define IUIAutomationElement_get_CachedItemStatus(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedItemStatus(This,retVal) )

#define IUIAutomationElement_get_CachedBoundingRectangle(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedBoundingRectangle(This,retVal) )

#define IUIAutomationElement_get_CachedLabeledBy(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedLabeledBy(This,retVal) )

#define IUIAutomationElement_get_CachedAriaRole(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedAriaRole(This,retVal) )

#define IUIAutomationElement_get_CachedAriaProperties(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedAriaProperties(This,retVal) )

#define IUIAutomationElement_get_CachedIsDataValidForForm(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedIsDataValidForForm(This,retVal) )

#define IUIAutomationElement_get_CachedControllerFor(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedControllerFor(This,retVal) )

#define IUIAutomationElement_get_CachedDescribedBy(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedDescribedBy(This,retVal) )

#define IUIAutomationElement_get_CachedFlowsTo(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedFlowsTo(This,retVal) )

#define IUIAutomationElement_get_CachedProviderDescription(This,retVal)	\
    ( (This)->lpVtbl -> get_CachedProviderDescription(This,retVal) )

#define IUIAutomationElement_GetClickablePoint(This,clickable,gotClickable)	\
    ( (This)->lpVtbl -> GetClickablePoint(This,clickable,gotClickable) )

#endif /* COBJMACROS */


#endif 	/* C style interface */

#endif 	/* __IUIAutomationElement_INTERFACE_DEFINED__ */


#ifndef __IUIAutomation_INTERFACE_DEFINED__
#define __IUIAutomation_INTERFACE_DEFINED__

/* interface IUIAutomation */
/* [unique][uuid][object] */


EXTERN_C const IID IID_IUIAutomation;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("30cbe57d-d9d0-452a-ab13-7ac5ac4825ee")
    IUIAutomation : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CompareElements(
            /* [in] */ __RPC__in_opt IUIAutomationElement *el1,
            /* [in] */ __RPC__in_opt IUIAutomationElement *el2,
            /* [retval][out] */ __RPC__out BOOL *areSame) = 0;

        virtual HRESULT STDMETHODCALLTYPE CompareRuntimeIds(
            /* [in] */ __RPC__in SAFEARRAY * runtimeId1,
            /* [in] */ __RPC__in SAFEARRAY * runtimeId2,
            /* [retval][out] */ __RPC__out BOOL *areSame) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetRootElement(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **root) = 0;

        virtual HRESULT STDMETHODCALLTYPE ElementFromHandle(
            /* [in] */ __RPC__in UIA_HWND hwnd,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element) = 0;

        virtual HRESULT STDMETHODCALLTYPE ElementFromPoint(
            /* [in] */ POINT pt,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetFocusedElement(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetRootElementBuildCache(
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **root) = 0;

        virtual HRESULT STDMETHODCALLTYPE ElementFromHandleBuildCache(
            /* [in] */ __RPC__in UIA_HWND hwnd,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element) = 0;

        virtual HRESULT STDMETHODCALLTYPE ElementFromPointBuildCache(
            /* [in] */ POINT pt,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetFocusedElementBuildCache(
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateTreeWalker(
            /* [in] */ __RPC__in_opt IUIAutomationCondition *pCondition,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationTreeWalker **walker) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ControlViewWalker(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationTreeWalker **walker) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ContentViewWalker(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationTreeWalker **walker) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RawViewWalker(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationTreeWalker **walker) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RawViewCondition(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **condition) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ControlViewCondition(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **condition) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ContentViewCondition(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **condition) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateCacheRequest(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCacheRequest **cacheRequest) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateTrueCondition(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateFalseCondition(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreatePropertyCondition(
            /* [in] */ PROPERTYID propertyId,
            /* [in] */ VARIANT value,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreatePropertyConditionEx(
            /* [in] */ PROPERTYID propertyId,
            /* [in] */ VARIANT value,
            /* [in] */ enum PropertyConditionFlags flags,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateAndCondition(
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition1,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition2,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateAndConditionFromArray(
            /* [in] */ __RPC__in_opt SAFEARRAY * conditions,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateAndConditionFromNativeArray(
            /* [size_is][in] */ __RPC__in_ecount_full(conditionCount) IUIAutomationCondition **conditions,
            /* [in] */ int conditionCount,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateOrCondition(
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition1,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition2,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateOrConditionFromArray(
            /* [in] */ __RPC__in_opt SAFEARRAY * conditions,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateOrConditionFromNativeArray(
            /* [size_is][in] */ __RPC__in_ecount_full(conditionCount) IUIAutomationCondition **conditions,
            /* [in] */ int conditionCount,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateNotCondition(
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition) = 0;

        virtual HRESULT STDMETHODCALLTYPE AddAutomationEventHandler(
            /* [in] */ EVENTID eventId,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [in] */ __RPC__in_opt IUIAutomationEventHandler *handler) = 0;

        virtual HRESULT STDMETHODCALLTYPE RemoveAutomationEventHandler(
            /* [in] */ EVENTID eventId,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationEventHandler *handler) = 0;

        virtual HRESULT STDMETHODCALLTYPE AddPropertyChangedEventHandlerNativeArray(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [in] */ __RPC__in_opt IUIAutomationPropertyChangedEventHandler *handler,
            /* [size_is][in] */ __RPC__in_ecount_full(propertyCount) PROPERTYID *propertyArray,
            /* [in] */ int propertyCount) = 0;

        virtual HRESULT STDMETHODCALLTYPE AddPropertyChangedEventHandler(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [in] */ __RPC__in_opt IUIAutomationPropertyChangedEventHandler *handler,
            /* [in] */ __RPC__in SAFEARRAY * propertyArray) = 0;

        virtual HRESULT STDMETHODCALLTYPE RemovePropertyChangedEventHandler(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationPropertyChangedEventHandler *handler) = 0;

        virtual HRESULT STDMETHODCALLTYPE AddStructureChangedEventHandler(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [in] */ __RPC__in_opt IUIAutomationStructureChangedEventHandler *handler) = 0;

        virtual HRESULT STDMETHODCALLTYPE RemoveStructureChangedEventHandler(
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationStructureChangedEventHandler *handler) = 0;

        virtual HRESULT STDMETHODCALLTYPE AddFocusChangedEventHandler(
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [in] */ __RPC__in_opt IUIAutomationFocusChangedEventHandler *handler) = 0;

        virtual HRESULT STDMETHODCALLTYPE RemoveFocusChangedEventHandler(
            /* [in] */ __RPC__in_opt IUIAutomationFocusChangedEventHandler *handler) = 0;

        virtual HRESULT STDMETHODCALLTYPE RemoveAllEventHandlers( void) = 0;

        virtual HRESULT STDMETHODCALLTYPE IntNativeArrayToSafeArray(
            /* [size_is][in] */ __RPC__in_ecount_full(arrayCount) int *array,
            /* [in] */ int arrayCount,
            /* [retval][out] */ __RPC__deref_out_opt SAFEARRAY * *safeArray) = 0;

        virtual HRESULT STDMETHODCALLTYPE IntSafeArrayToNativeArray(
            /* [in] */ __RPC__in SAFEARRAY * intArray,
            /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*arrayCount) int **array,
            /* [retval][out] */ __RPC__out int *arrayCount) = 0;

        virtual HRESULT STDMETHODCALLTYPE RectToVariant(
            /* [in] */ RECT rc,
            /* [retval][out] */ __RPC__out VARIANT *var) = 0;

        virtual HRESULT STDMETHODCALLTYPE VariantToRect(
            /* [in] */ VARIANT var,
            /* [retval][out] */ __RPC__out RECT *rc) = 0;

        virtual HRESULT STDMETHODCALLTYPE SafeArrayToRectNativeArray(
            /* [in] */ __RPC__in SAFEARRAY * rects,
            /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*rectArrayCount) RECT **rectArray,
            /* [retval][out] */ __RPC__out int *rectArrayCount) = 0;

        virtual HRESULT STDMETHODCALLTYPE CreateProxyFactoryEntry(
            /* [in] */ __RPC__in_opt IUIAutomationProxyFactory *factory,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationProxyFactoryEntry **factoryEntry) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ProxyFactoryMapping(
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationProxyFactoryMapping **factoryMapping) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetPropertyProgrammaticName(
            /* [in] */ PROPERTYID property,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *name) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetPatternProgrammaticName(
            /* [in] */ PATTERNID pattern,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *name) = 0;

        virtual HRESULT STDMETHODCALLTYPE PollForPotentialSupportedPatterns(
            /* [in] */ __RPC__in_opt IUIAutomationElement *pElement,
            /* [out] */ __RPC__deref_out_opt SAFEARRAY * *patternIds,
            /* [out] */ __RPC__deref_out_opt SAFEARRAY * *patternNames) = 0;

        virtual HRESULT STDMETHODCALLTYPE PollForPotentialSupportedProperties(
            /* [in] */ __RPC__in_opt IUIAutomationElement *pElement,
            /* [out] */ __RPC__deref_out_opt SAFEARRAY * *propertyIds,
            /* [out] */ __RPC__deref_out_opt SAFEARRAY * *propertyNames) = 0;

        virtual HRESULT STDMETHODCALLTYPE CheckNotSupported(
            /* [in] */ VARIANT value,
            /* [retval][out] */ __RPC__out BOOL *isNotSupported) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ReservedNotSupportedValue(
            /* [retval][out] */ __RPC__deref_out_opt IUnknown **notSupportedValue) = 0;

        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ReservedMixedAttributeValue(
            /* [retval][out] */ __RPC__deref_out_opt IUnknown **mixedAttributeValue) = 0;

        virtual HRESULT STDMETHODCALLTYPE ElementFromIAccessible(
            /* [in] */ __RPC__in_opt IAccessible *accessible,
            /* [in] */ int childId,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element) = 0;

        virtual HRESULT STDMETHODCALLTYPE ElementFromIAccessibleBuildCache(
            /* [in] */ __RPC__in_opt IAccessible *accessible,
            /* [in] */ int childId,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element) = 0;

    };


#else 	/* C style interface */

    typedef struct IUIAutomationVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */
            _COM_Outptr_  void **ppvObject);

        ULONG ( STDMETHODCALLTYPE *AddRef )(
            __RPC__in IUIAutomation * This);

        ULONG ( STDMETHODCALLTYPE *Release )(
            __RPC__in IUIAutomation * This);

        HRESULT ( STDMETHODCALLTYPE *CompareElements )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *el1,
            /* [in] */ __RPC__in_opt IUIAutomationElement *el2,
            /* [retval][out] */ __RPC__out BOOL *areSame);

        HRESULT ( STDMETHODCALLTYPE *CompareRuntimeIds )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in SAFEARRAY * runtimeId1,
            /* [in] */ __RPC__in SAFEARRAY * runtimeId2,
            /* [retval][out] */ __RPC__out BOOL *areSame);

        HRESULT ( STDMETHODCALLTYPE *GetRootElement )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **root);

        HRESULT ( STDMETHODCALLTYPE *ElementFromHandle )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in UIA_HWND hwnd,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element);

        HRESULT ( STDMETHODCALLTYPE *ElementFromPoint )(
            __RPC__in IUIAutomation * This,
            /* [in] */ POINT pt,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element);

        HRESULT ( STDMETHODCALLTYPE *GetFocusedElement )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element);

        HRESULT ( STDMETHODCALLTYPE *GetRootElementBuildCache )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **root);

        HRESULT ( STDMETHODCALLTYPE *ElementFromHandleBuildCache )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in UIA_HWND hwnd,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element);

        HRESULT ( STDMETHODCALLTYPE *ElementFromPointBuildCache )(
            __RPC__in IUIAutomation * This,
            /* [in] */ POINT pt,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element);

        HRESULT ( STDMETHODCALLTYPE *GetFocusedElementBuildCache )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element);

        HRESULT ( STDMETHODCALLTYPE *CreateTreeWalker )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *pCondition,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationTreeWalker **walker);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ControlViewWalker )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationTreeWalker **walker);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContentViewWalker )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationTreeWalker **walker);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RawViewWalker )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationTreeWalker **walker);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RawViewCondition )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **condition);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ControlViewCondition )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **condition);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContentViewCondition )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **condition);

        HRESULT ( STDMETHODCALLTYPE *CreateCacheRequest )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCacheRequest **cacheRequest);

        HRESULT ( STDMETHODCALLTYPE *CreateTrueCondition )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition);

        HRESULT ( STDMETHODCALLTYPE *CreateFalseCondition )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition);

        HRESULT ( STDMETHODCALLTYPE *CreatePropertyCondition )(
            __RPC__in IUIAutomation * This,
            /* [in] */ PROPERTYID propertyId,
            /* [in] */ VARIANT value,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition);

        HRESULT ( STDMETHODCALLTYPE *CreatePropertyConditionEx )(
            __RPC__in IUIAutomation * This,
            /* [in] */ PROPERTYID propertyId,
            /* [in] */ VARIANT value,
            /* [in] */ enum PropertyConditionFlags flags,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition);

        HRESULT ( STDMETHODCALLTYPE *CreateAndCondition )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition1,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition2,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition);

        HRESULT ( STDMETHODCALLTYPE *CreateAndConditionFromArray )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt SAFEARRAY * conditions,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition);

        HRESULT ( STDMETHODCALLTYPE *CreateAndConditionFromNativeArray )(
            __RPC__in IUIAutomation * This,
            /* [size_is][in] */ __RPC__in_ecount_full(conditionCount) IUIAutomationCondition **conditions,
            /* [in] */ int conditionCount,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition);

        HRESULT ( STDMETHODCALLTYPE *CreateOrCondition )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition1,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition2,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition);

        HRESULT ( STDMETHODCALLTYPE *CreateOrConditionFromArray )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt SAFEARRAY * conditions,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition);

        HRESULT ( STDMETHODCALLTYPE *CreateOrConditionFromNativeArray )(
            __RPC__in IUIAutomation * This,
            /* [size_is][in] */ __RPC__in_ecount_full(conditionCount) IUIAutomationCondition **conditions,
            /* [in] */ int conditionCount,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition);

        HRESULT ( STDMETHODCALLTYPE *CreateNotCondition )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationCondition *condition,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationCondition **newCondition);

        HRESULT ( STDMETHODCALLTYPE *AddAutomationEventHandler )(
            __RPC__in IUIAutomation * This,
            /* [in] */ EVENTID eventId,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [in] */ __RPC__in_opt IUIAutomationEventHandler *handler);

        HRESULT ( STDMETHODCALLTYPE *RemoveAutomationEventHandler )(
            __RPC__in IUIAutomation * This,
            /* [in] */ EVENTID eventId,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationEventHandler *handler);

        HRESULT ( STDMETHODCALLTYPE *AddPropertyChangedEventHandlerNativeArray )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [in] */ __RPC__in_opt IUIAutomationPropertyChangedEventHandler *handler,
            /* [size_is][in] */ __RPC__in_ecount_full(propertyCount) PROPERTYID *propertyArray,
            /* [in] */ int propertyCount);

        HRESULT ( STDMETHODCALLTYPE *AddPropertyChangedEventHandler )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [in] */ __RPC__in_opt IUIAutomationPropertyChangedEventHandler *handler,
            /* [in] */ __RPC__in SAFEARRAY * propertyArray);

        HRESULT ( STDMETHODCALLTYPE *RemovePropertyChangedEventHandler )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationPropertyChangedEventHandler *handler);

        HRESULT ( STDMETHODCALLTYPE *AddStructureChangedEventHandler )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ enum TreeScope scope,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [in] */ __RPC__in_opt IUIAutomationStructureChangedEventHandler *handler);

        HRESULT ( STDMETHODCALLTYPE *RemoveStructureChangedEventHandler )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *element,
            /* [in] */ __RPC__in_opt IUIAutomationStructureChangedEventHandler *handler);

        HRESULT ( STDMETHODCALLTYPE *AddFocusChangedEventHandler )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [in] */ __RPC__in_opt IUIAutomationFocusChangedEventHandler *handler);

        HRESULT ( STDMETHODCALLTYPE *RemoveFocusChangedEventHandler )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationFocusChangedEventHandler *handler);

        HRESULT ( STDMETHODCALLTYPE *RemoveAllEventHandlers )(
            __RPC__in IUIAutomation * This);

        HRESULT ( STDMETHODCALLTYPE *IntNativeArrayToSafeArray )(
            __RPC__in IUIAutomation * This,
            /* [size_is][in] */ __RPC__in_ecount_full(arrayCount) int *array,
            /* [in] */ int arrayCount,
            /* [retval][out] */ __RPC__deref_out_opt SAFEARRAY * *safeArray);

        HRESULT ( STDMETHODCALLTYPE *IntSafeArrayToNativeArray )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in SAFEARRAY * intArray,
            /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*arrayCount) int **array,
            /* [retval][out] */ __RPC__out int *arrayCount);

        HRESULT ( STDMETHODCALLTYPE *RectToVariant )(
            __RPC__in IUIAutomation * This,
            /* [in] */ RECT rc,
            /* [retval][out] */ __RPC__out VARIANT *var);

        HRESULT ( STDMETHODCALLTYPE *VariantToRect )(
            __RPC__in IUIAutomation * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ __RPC__out RECT *rc);

        HRESULT ( STDMETHODCALLTYPE *SafeArrayToRectNativeArray )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in SAFEARRAY * rects,
            /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*rectArrayCount) RECT **rectArray,
            /* [retval][out] */ __RPC__out int *rectArrayCount);

        HRESULT ( STDMETHODCALLTYPE *CreateProxyFactoryEntry )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationProxyFactory *factory,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationProxyFactoryEntry **factoryEntry);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProxyFactoryMapping )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationProxyFactoryMapping **factoryMapping);

        HRESULT ( STDMETHODCALLTYPE *GetPropertyProgrammaticName )(
            __RPC__in IUIAutomation * This,
            /* [in] */ PROPERTYID property,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *name);

        HRESULT ( STDMETHODCALLTYPE *GetPatternProgrammaticName )(
            __RPC__in IUIAutomation * This,
            /* [in] */ PATTERNID pattern,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *name);

        HRESULT ( STDMETHODCALLTYPE *PollForPotentialSupportedPatterns )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *pElement,
            /* [out] */ __RPC__deref_out_opt SAFEARRAY * *patternIds,
            /* [out] */ __RPC__deref_out_opt SAFEARRAY * *patternNames);

        HRESULT ( STDMETHODCALLTYPE *PollForPotentialSupportedProperties )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IUIAutomationElement *pElement,
            /* [out] */ __RPC__deref_out_opt SAFEARRAY * *propertyIds,
            /* [out] */ __RPC__deref_out_opt SAFEARRAY * *propertyNames);

        HRESULT ( STDMETHODCALLTYPE *CheckNotSupported )(
            __RPC__in IUIAutomation * This,
            /* [in] */ VARIANT value,
            /* [retval][out] */ __RPC__out BOOL *isNotSupported);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ReservedNotSupportedValue )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUnknown **notSupportedValue);

        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ReservedMixedAttributeValue )(
            __RPC__in IUIAutomation * This,
            /* [retval][out] */ __RPC__deref_out_opt IUnknown **mixedAttributeValue);

        HRESULT ( STDMETHODCALLTYPE *ElementFromIAccessible )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IAccessible *accessible,
            /* [in] */ int childId,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element);

        HRESULT ( STDMETHODCALLTYPE *ElementFromIAccessibleBuildCache )(
            __RPC__in IUIAutomation * This,
            /* [in] */ __RPC__in_opt IAccessible *accessible,
            /* [in] */ int childId,
            /* [in] */ __RPC__in_opt IUIAutomationCacheRequest *cacheRequest,
            /* [retval][out] */ __RPC__deref_out_opt IUIAutomationElement **element);

        END_INTERFACE
    } IUIAutomationVtbl;

    interface IUIAutomation
    {
        CONST_VTBL struct IUIAutomationVtbl *lpVtbl;
    };



#ifdef COBJMACROS


#define IUIAutomation_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IUIAutomation_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) )

#define IUIAutomation_Release(This)	\
    ( (This)->lpVtbl -> Release(This) )


#define IUIAutomation_CompareElements(This,el1,el2,areSame)	\
    ( (This)->lpVtbl -> CompareElements(This,el1,el2,areSame) )

#define IUIAutomation_CompareRuntimeIds(This,runtimeId1,runtimeId2,areSame)	\
    ( (This)->lpVtbl -> CompareRuntimeIds(This,runtimeId1,runtimeId2,areSame) )

#define IUIAutomation_GetRootElement(This,root)	\
    ( (This)->lpVtbl -> GetRootElement(This,root) )

#define IUIAutomation_ElementFromHandle(This,hwnd,element)	\
    ( (This)->lpVtbl -> ElementFromHandle(This,hwnd,element) )

#define IUIAutomation_ElementFromPoint(This,pt,element)	\
    ( (This)->lpVtbl -> ElementFromPoint(This,pt,element) )

#define IUIAutomation_GetFocusedElement(This,element)	\
    ( (This)->lpVtbl -> GetFocusedElement(This,element) )

#define IUIAutomation_GetRootElementBuildCache(This,cacheRequest,root)	\
    ( (This)->lpVtbl -> GetRootElementBuildCache(This,cacheRequest,root) )

#define IUIAutomation_ElementFromHandleBuildCache(This,hwnd,cacheRequest,element)	\
    ( (This)->lpVtbl -> ElementFromHandleBuildCache(This,hwnd,cacheRequest,element) )

#define IUIAutomation_ElementFromPointBuildCache(This,pt,cacheRequest,element)	\
    ( (This)->lpVtbl -> ElementFromPointBuildCache(This,pt,cacheRequest,element) )

#define IUIAutomation_GetFocusedElementBuildCache(This,cacheRequest,element)	\
    ( (This)->lpVtbl -> GetFocusedElementBuildCache(This,cacheRequest,element) )

#define IUIAutomation_CreateTreeWalker(This,pCondition,walker)	\
    ( (This)->lpVtbl -> CreateTreeWalker(This,pCondition,walker) )

#define IUIAutomation_get_ControlViewWalker(This,walker)	\
    ( (This)->lpVtbl -> get_ControlViewWalker(This,walker) )

#define IUIAutomation_get_ContentViewWalker(This,walker)	\
    ( (This)->lpVtbl -> get_ContentViewWalker(This,walker) )

#define IUIAutomation_get_RawViewWalker(This,walker)	\
    ( (This)->lpVtbl -> get_RawViewWalker(This,walker) )

#define IUIAutomation_get_RawViewCondition(This,condition)	\
    ( (This)->lpVtbl -> get_RawViewCondition(This,condition) )

#define IUIAutomation_get_ControlViewCondition(This,condition)	\
    ( (This)->lpVtbl -> get_ControlViewCondition(This,condition) )

#define IUIAutomation_get_ContentViewCondition(This,condition)	\
    ( (This)->lpVtbl -> get_ContentViewCondition(This,condition) )

#define IUIAutomation_CreateCacheRequest(This,cacheRequest)	\
    ( (This)->lpVtbl -> CreateCacheRequest(This,cacheRequest) )

#define IUIAutomation_CreateTrueCondition(This,newCondition)	\
    ( (This)->lpVtbl -> CreateTrueCondition(This,newCondition) )

#define IUIAutomation_CreateFalseCondition(This,newCondition)	\
    ( (This)->lpVtbl -> CreateFalseCondition(This,newCondition) )

#define IUIAutomation_CreatePropertyCondition(This,propertyId,value,newCondition)	\
    ( (This)->lpVtbl -> CreatePropertyCondition(This,propertyId,value,newCondition) )

#define IUIAutomation_CreatePropertyConditionEx(This,propertyId,value,flags,newCondition)	\
    ( (This)->lpVtbl -> CreatePropertyConditionEx(This,propertyId,value,flags,newCondition) )

#define IUIAutomation_CreateAndCondition(This,condition1,condition2,newCondition)	\
    ( (This)->lpVtbl -> CreateAndCondition(This,condition1,condition2,newCondition) )

#define IUIAutomation_CreateAndConditionFromArray(This,conditions,newCondition)	\
    ( (This)->lpVtbl -> CreateAndConditionFromArray(This,conditions,newCondition) )

#define IUIAutomation_CreateAndConditionFromNativeArray(This,conditions,conditionCount,newCondition)	\
    ( (This)->lpVtbl -> CreateAndConditionFromNativeArray(This,conditions,conditionCount,newCondition) )

#define IUIAutomation_CreateOrCondition(This,condition1,condition2,newCondition)	\
    ( (This)->lpVtbl -> CreateOrCondition(This,condition1,condition2,newCondition) )

#define IUIAutomation_CreateOrConditionFromArray(This,conditions,newCondition)	\
    ( (This)->lpVtbl -> CreateOrConditionFromArray(This,conditions,newCondition) )

#define IUIAutomation_CreateOrConditionFromNativeArray(This,conditions,conditionCount,newCondition)	\
    ( (This)->lpVtbl -> CreateOrConditionFromNativeArray(This,conditions,conditionCount,newCondition) )

#define IUIAutomation_CreateNotCondition(This,condition,newCondition)	\
    ( (This)->lpVtbl -> CreateNotCondition(This,condition,newCondition) )

#define IUIAutomation_AddAutomationEventHandler(This,eventId,element,scope,cacheRequest,handler)	\
    ( (This)->lpVtbl -> AddAutomationEventHandler(This,eventId,element,scope,cacheRequest,handler) )

#define IUIAutomation_RemoveAutomationEventHandler(This,eventId,element,handler)	\
    ( (This)->lpVtbl -> RemoveAutomationEventHandler(This,eventId,element,handler) )

#define IUIAutomation_AddPropertyChangedEventHandlerNativeArray(This,element,scope,cacheRequest,handler,propertyArray,propertyCount)	\
    ( (This)->lpVtbl -> AddPropertyChangedEventHandlerNativeArray(This,element,scope,cacheRequest,handler,propertyArray,propertyCount) )

#define IUIAutomation_AddPropertyChangedEventHandler(This,element,scope,cacheRequest,handler,propertyArray)	\
    ( (This)->lpVtbl -> AddPropertyChangedEventHandler(This,element,scope,cacheRequest,handler,propertyArray) )

#define IUIAutomation_RemovePropertyChangedEventHandler(This,element,handler)	\
    ( (This)->lpVtbl -> RemovePropertyChangedEventHandler(This,element,handler) )

#define IUIAutomation_AddStructureChangedEventHandler(This,element,scope,cacheRequest,handler)	\
    ( (This)->lpVtbl -> AddStructureChangedEventHandler(This,element,scope,cacheRequest,handler) )

#define IUIAutomation_RemoveStructureChangedEventHandler(This,element,handler)	\
    ( (This)->lpVtbl -> RemoveStructureChangedEventHandler(This,element,handler) )

#define IUIAutomation_AddFocusChangedEventHandler(This,cacheRequest,handler)	\
    ( (This)->lpVtbl -> AddFocusChangedEventHandler(This,cacheRequest,handler) )

#define IUIAutomation_RemoveFocusChangedEventHandler(This,handler)	\
    ( (This)->lpVtbl -> RemoveFocusChangedEventHandler(This,handler) )

#define IUIAutomation_RemoveAllEventHandlers(This)	\
    ( (This)->lpVtbl -> RemoveAllEventHandlers(This) )

#define IUIAutomation_IntNativeArrayToSafeArray(This,array,arrayCount,safeArray)	\
    ( (This)->lpVtbl -> IntNativeArrayToSafeArray(This,array,arrayCount,safeArray) )

#define IUIAutomation_IntSafeArrayToNativeArray(This,intArray,array,arrayCount)	\
    ( (This)->lpVtbl -> IntSafeArrayToNativeArray(This,intArray,array,arrayCount) )

#define IUIAutomation_RectToVariant(This,rc,var)	\
    ( (This)->lpVtbl -> RectToVariant(This,rc,var) )

#define IUIAutomation_VariantToRect(This,var,rc)	\
    ( (This)->lpVtbl -> VariantToRect(This,var,rc) )

#define IUIAutomation_SafeArrayToRectNativeArray(This,rects,rectArray,rectArrayCount)	\
    ( (This)->lpVtbl -> SafeArrayToRectNativeArray(This,rects,rectArray,rectArrayCount) )

#define IUIAutomation_CreateProxyFactoryEntry(This,factory,factoryEntry)	\
    ( (This)->lpVtbl -> CreateProxyFactoryEntry(This,factory,factoryEntry) )

#define IUIAutomation_get_ProxyFactoryMapping(This,factoryMapping)	\
    ( (This)->lpVtbl -> get_ProxyFactoryMapping(This,factoryMapping) )

#define IUIAutomation_GetPropertyProgrammaticName(This,property,name)	\
    ( (This)->lpVtbl -> GetPropertyProgrammaticName(This,property,name) )

#define IUIAutomation_GetPatternProgrammaticName(This,pattern,name)	\
    ( (This)->lpVtbl -> GetPatternProgrammaticName(This,pattern,name) )

#define IUIAutomation_PollForPotentialSupportedPatterns(This,pElement,patternIds,patternNames)	\
    ( (This)->lpVtbl -> PollForPotentialSupportedPatterns(This,pElement,patternIds,patternNames) )

#define IUIAutomation_PollForPotentialSupportedProperties(This,pElement,propertyIds,propertyNames)	\
    ( (This)->lpVtbl -> PollForPotentialSupportedProperties(This,pElement,propertyIds,propertyNames) )

#define IUIAutomation_CheckNotSupported(This,value,isNotSupported)	\
    ( (This)->lpVtbl -> CheckNotSupported(This,value,isNotSupported) )

#define IUIAutomation_get_ReservedNotSupportedValue(This,notSupportedValue)	\
    ( (This)->lpVtbl -> get_ReservedNotSupportedValue(This,notSupportedValue) )

#define IUIAutomation_get_ReservedMixedAttributeValue(This,mixedAttributeValue)	\
    ( (This)->lpVtbl -> get_ReservedMixedAttributeValue(This,mixedAttributeValue) )

#define IUIAutomation_ElementFromIAccessible(This,accessible,childId,element)	\
    ( (This)->lpVtbl -> ElementFromIAccessible(This,accessible,childId,element) )

#define IUIAutomation_ElementFromIAccessibleBuildCache(This,accessible,childId,cacheRequest,element)	\
    ( (This)->lpVtbl -> ElementFromIAccessibleBuildCache(This,accessible,childId,cacheRequest,element) )

#endif /* COBJMACROS */


#endif 	/* C style interface */

#endif 	/* __IUIAutomation_INTERFACE_DEFINED__ */

EXTERN_C const CLSID CLSID_CUIAutomation;

#ifdef __cplusplus

class DECLSPEC_UUID("ff48dba4-60ef-4201-aa87-54103eef594e")
CUIAutomation;
#endif

#endif // MSVC Compiler
const CLSID UUID_CUIAutomation = {
    0xFF48DBA4, 0x60EF, 0x4201, {0xAA, 0x87, 0x54, 0x10, 0x3E, 0xEF, 0x59, 0x4E} };

const GUID UUID_IUIAutomation = {
    0x30CBE57D, 0xD9D0, 0x452A, {0xAB, 0x13, 0x7A, 0xC5, 0xAC, 0x48, 0x25, 0xEE} };

#endif // UIA_ELEMENT_H
