#include    "lib/Maid3.h"
#include    "lib/Maid3d1.h"
#include    "Callback.h"
#include <iostream>
#include <map>
#include <queue>
#include <list>

using namespace std;

class Sakuya {
public:
    static HMODULE g_hInstModule;
    static MAIDEntryPointProc *g_pMAIDEntryPoint;
    map<ULONG, NkMAIDCapInfo> capMap;
    NkMAIDObject *pObject;
    ProcData d;

    Sakuya(NkMAIDObject *pParentObj, ULONG ulChildID) {
        pObject = new NkMAIDObject;
        cout << pObject << endl;
        g_pMAIDEntryPoint(
                pParentObj,
                kNkMAIDCommand_Open,
                ulChildID,
                kNkMAIDDataType_ObjectPtr,
                reinterpret_cast<NKPARAM>(pObject),
                nullptr,
                nullptr
        );
    }

    Sakuya getChild(ULONG childId) {
        return {pObject, childId};
    }

    Sakuya *getChildP(ULONG childId) {
        return new Sakuya(pObject, childId);
    }

    NKERROR MAID(
            ULONG ulCommand,            // Command, one of eNkMAIDCommand
            ULONG ulParam,                // parameter for the command
            ULONG ulDataType,            // Data type, one of eNkMAIDDataType
            NKPARAM data,                    // Pointer or long integer
            LPNKFUNC pfnComplete,        // Completion function, may be NULL
            NKREF refComplete) {
//        cout<<g_pMAIDEntryPoint<<endl;
        return g_pMAIDEntryPoint(pObject, ulCommand, ulParam, ulDataType, data, pfnComplete, refComplete);
    }


    ULONG getCapCount() {
        ULONG a = 0;
        MAID(
                kNkMAIDCommand_GetCapCount,
                0,
                kNkMAIDDataType_UnsignedPtr,
                (NKPARAM) & a,
                nullptr,
                nullptr
        );
        return a;
    }

    NkMAIDCapInfo *getCapInfo(ULONG capCount) {
        auto static pCapArray = new NkMAIDCapInfo[capCount];
        MAID(
                kNkMAIDCommand_GetCapInfo,
                capCount,
                kNkMAIDDataType_CapInfoPtr,
                (NKPARAM)
        pCapArray,
                nullptr,
                nullptr
        );
        for (ULONG i = 0; i < capCount; i++) {
            auto pCapInfo = (LPNkMAIDCapInfo)(((char *) pCapArray) + (i * sizeof(NkMAIDCapInfo)));
            capMap.insert(std::pair<ULONG, NkMAIDCapInfo>{pCapInfo->ulID, *pCapInfo});
        }
        return pCapArray;
    }

    BOOL getCapOpa(ULONG ulID, ULONG ulOperations) {
        if (capMap.count(ulID)) {
            NkMAIDCapInfo pCapInfo = capMap.at(ulID);
            if (pCapInfo.ulOperations & ulOperations) {
                return true;
            } else {
                return false;
            }
        } else
            return false;
    }

    NKERROR setCap(ULONG ulParam, ULONG ulDataType, NKPARAM pData) {
        return MAID(
                kNkMAIDCommand_CapSet,
                ulParam,
                ulDataType,
                pData,
                nullptr,
                nullptr
        );
    }

    BOOL getCap(ULONG ulParam, ULONG ulDataType, NKPARAM pData) {
        SLONG nResult;
        nResult = MAID(
                kNkMAIDCommand_CapGet,
                ulParam,
                ulDataType,
                pData,
                nullptr,
                nullptr
        );
        return kNkMAIDResult_NoError == nResult;
    }

    BOOL getCapArray(ULONG ulParam, ULONG ulDataType, NKPARAM pData) {
        return kNkMAIDResult_NoError == MAID(
                kNkMAIDCommand_CapGetArray,
                ulParam,
                ulDataType,
                pData,
                nullptr,
                nullptr
        );
    }

    ULONG acquireLen() {
        NkMAIDCallback stProc;
        d = ProcData();
        stProc.refProc = &d;
        stProc.pProc = (LPNKFUNC)DataProc5;
        setCap(
                kNkMAIDCapability_DataProc,
                kNkMAIDDataType_CallbackPtr,
                (NKPARAM) & stProc
        );
        capStart(kNkMAIDCapability_Acquire);
        return d.ulOffset;
    }

    BOOL acquireFile(char *buf) {
        memmove(buf, d.pBuffer, d.ulOffset);
        return true;
    }

    BOOL acquire(char *path) {
        NkMAIDCallback stProc;
        auto d = ProcData();
        d.path = path;
        stProc.refProc = &d;
        stProc.pProc = (LPNKFUNC) DataProc3;
        setCap(
                kNkMAIDCapability_DataProc,
                kNkMAIDDataType_CallbackPtr,
                (NKPARAM) & stProc
        );
        capStart(kNkMAIDCapability_Acquire);
        return true;
    }

    BOOL acquire2() {
        NkMAIDCallback stProc;
        stProc.pProc = (LPNKFUNC) DataProc4;
        setCap(
                kNkMAIDCapability_DataProc,
                kNkMAIDDataType_CallbackPtr,
                (NKPARAM) & stProc
        );
        capStart(kNkMAIDCapability_Acquire);
        return true;
    }

    ULONG getChildIdsLen() {
        vector<ULONG> list;
        NkMAIDEnum stEnum;
        getCap(
                kNkMAIDCapability_Children,
                kNkMAIDDataType_EnumPtr,
                (NKPARAM) & stEnum
        );
        return stEnum.ulElements;
    }

    vector<ULONG> getChildIds() {
        vector<ULONG> list;
        NkMAIDEnum stEnum;

        getCap(
                kNkMAIDCapability_Children,
                kNkMAIDDataType_EnumPtr,
                (NKPARAM) & stEnum
        );
        stEnum.pData = new ULONG[stEnum.ulElements];
        getCapArray(
                kNkMAIDCapability_Children,
                kNkMAIDDataType_EnumPtr,
                (NKPARAM) & stEnum
        );
        for (ULONG i = 0; i < stEnum.ulElements; i++)
            list.push_back(((ULONG * )
        stEnum.pData)[i]);
        if (list.empty())
            cout << "empty" << endl;
        else
            cout << list[0] << endl;
        return list;
    }

    BOOL cap() {
        return capStart(kNkMAIDCapability_Capture);
    }

    BOOL deleteDram() {
        return capStart(kNkMAIDCapability_DeleteDramImage);
    }


    BOOL capStart(ULONG ulParam) {

        SLONG nResult = MAID(
                kNkMAIDCommand_CapStart,
                ulParam,
                kNkMAIDDataType_Null,
                ulParam,
                nullptr,
                nullptr
        );

        return (nResult == kNkMAIDResult_NoError || nResult == kNkMAIDResult_Pending ||
                nResult == kNkMAIDResult_BulbReleaseBusy ||
                nResult == kNkMAIDResult_SilentReleaseBusy || nResult == kNkMAIDResult_MovieFrameReleaseBusy);

    }


    BOOL async() {
        SLONG lResult = MAID(
                kNkMAIDCommand_Async,
                0,
                kNkMAIDDataType_Null,
                (NKPARAM)
        NULL,
                (LPNKFUNC) NULL,
                (NKREF)
        NULL);
        return (lResult == kNkMAIDResult_NoError || lResult == kNkMAIDResult_Pending);
    }

    BOOL close() {
        SLONG nResult = MAID(kNkMAIDCommand_Close, 0, 0, 0, NULL, NULL);
        return nResult == kNkMAIDResult_NoError;
    }

    NKERROR setCallback(ULONG ulParam, LPNKFUNC f) {
        NkMAIDCallback stProc;
        stProc.pProc = f;
        return setCap(
                ulParam,
                kNkMAIDDataType_CallbackPtr,
                (NKPARAM) & stProc
        );

    }

    void sc() {
        setCallback(kNkMAIDCapability_EventProc, (LPNKFUNC) SrcEventProc2);
    }

    static void init(char *libPath) {
        g_hInstModule = LoadLibrary(
                libPath);
        g_pMAIDEntryPoint = reinterpret_cast<MAIDEntryPointProc *>(
                GetProcAddress(g_hInstModule, "MAIDEntryPoint"));
    }


};

HMODULE Sakuya::g_hInstModule;
MAIDEntryPointProc *Sakuya::g_pMAIDEntryPoint;