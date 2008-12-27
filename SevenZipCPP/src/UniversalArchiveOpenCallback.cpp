#include "StdAfx.h"

#include "jnitools.h"
#include "UniversalArchiveOpenCallback.h"

void UniversalArchiveOpencallback::Init(JNICallState * jniCallState, JNIEnv * initEnv, jobject archiveOpenCallbackImpl)
{
    TRACE_OBJECT_CALL("Init")
    
    CMyComPtr<IArchiveOpenCallback> archiveOpenCallbackComPtr = new CPPToJavaArchiveOpenCallback(jniCallState, initEnv, archiveOpenCallbackImpl);
    _archiveOpenCallback = archiveOpenCallbackComPtr.Detach();
    // _archiveOpenCallback->AddRef(); // TODO Remove
    
    _archiveOpenVolumeCallback = NULL;
    _cryptoGetTextPassword = NULL;
    
    jclass cryptoGetTextPasswordClass = initEnv->FindClass(CRYPTOGETTEXTPASSWORD_CLASS);
    FATALIF(cryptoGetTextPasswordClass == NULL,
            "Can't find class " CRYPTOGETTEXTPASSWORD_CLASS);

    jclass archiveOpenVolumeCallbackClass = initEnv->FindClass(ARCHIVEOPENVOLUMECALLBACK_CLASS);
    FATALIF(cryptoGetTextPasswordClass == NULL,
            "Can't find class " ARCHIVEOPENVOLUMECALLBACK_CLASS);

    if (initEnv->IsInstanceOf(archiveOpenCallbackImpl, cryptoGetTextPasswordClass))
    {
        CMyComPtr<ICryptoGetTextPassword> cryptoGetTextPasswordComPtr = 
            new CPPToJavaCryptoGetTextPassword(jniCallState, initEnv, archiveOpenCallbackImpl);
        _cryptoGetTextPassword = cryptoGetTextPasswordComPtr.Detach();
    }
    
    if (initEnv->IsInstanceOf(archiveOpenCallbackImpl, archiveOpenVolumeCallbackClass))
    {
        CMyComPtr<IArchiveOpenVolumeCallback> archiveOpenVolumeCallbackComPtr = 
            new CPPToJavaArchiveOpenVolumeCallback(jniCallState, initEnv, archiveOpenCallbackImpl);
        _archiveOpenVolumeCallback = archiveOpenVolumeCallbackComPtr.Detach();
    }
}

STDMETHODIMP(UniversalArchiveOpencallback::QueryInterface)(REFGUID iid, void **outObject)
{
    TRACE_OBJECT_CALL("QueryInterface")
    
    if (iid == IID_IArchiveOpenCallback)
    {
        *outObject = (void *)(IArchiveOpenCallback *)this;
        AddRef();
        return S_OK;
    }

    if (iid == IID_IArchiveOpenVolumeCallback && _archiveOpenVolumeCallback)
    {
        *outObject = (void *)(IArchiveOpenVolumeCallback *)this;
        AddRef();
        return S_OK;
    }

    if (iid == IID_ICryptoGetTextPassword && _cryptoGetTextPassword)
    {
        *outObject = (void *)(ICryptoGetTextPassword *)this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}