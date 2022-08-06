#include "Callback.h"

using namespace std;

void CALLPASCAL CALLBACK SrcEventProc2(NKREF refProc, ULONG ulEvent, NKPARAM data)
{
	BOOL bRet;
}
NKERROR CALLPASCAL CALLBACK DataProc4(NKREF ref, LPVOID pInfo, LPVOID pData)
{
    return kNkMAIDResult_NoError;
}

NKERROR CALLPASCAL CALLBACK DataProc3(NKREF ref, LPVOID pInfo, LPVOID pData)
{
	auto pDataInfo = (LPNkMAIDDataInfo)pInfo;
	auto pFileInfo = (LPNkMAIDFileInfo)pInfo;
	LPVOID pCurrentBuffer;
	auto xref = (ProcData*)ref;
	if (xref->pBuffer == NULL)
	{
		xref->pBuffer = malloc(pFileInfo->ulTotalLength);
	}
	if (pDataInfo->ulType & kNkMAIDDataObjType_File)
	{
		pCurrentBuffer = (char*)xref->pBuffer + xref->ulOffset;
		xref->ulOffset += pFileInfo->ulLength;
		memmove(pCurrentBuffer, pData, pFileInfo->ulLength);
		if (xref->ulOffset == pFileInfo->ulTotalLength)
		{
			char  Ext[16];
			switch (pFileInfo->ulFileDataType) {
			case kNkMAIDFileDataType_JPEG:
				strcpy(Ext, ".jpg");
				break;
			case kNkMAIDFileDataType_TIFF:
				strcpy(Ext, ".tif");
				break;
			case kNkMAIDFileDataType_NIF:
				strcpy(Ext, ".nef");
				break;
			case kNkMAIDFileDataType_NDF:
				strcpy(Ext, ".ndf");
				break;
			default:
				strcpy(Ext, ".dat");
			}
			string a = string(xref->path) + Ext;
			FILE* stream = fopen(a.c_str(), "wb");
			fwrite(
				xref->pBuffer,
				1,
				pFileInfo->ulTotalLength,
				stream
			);
			fclose(stream);
		}

	}
	return kNkMAIDResult_NoError;
}

NKERROR CALLPASCAL CALLBACK DataProc5(NKREF ref, LPVOID pInfo, LPVOID pData)
{
	auto pDataInfo = (LPNkMAIDDataInfo)pInfo;
	auto pFileInfo = (LPNkMAIDFileInfo)pInfo;
	LPVOID pCurrentBuffer;
	auto xref = (ProcData*)ref;
	if (xref->pBuffer == NULL)
	{
		xref->pBuffer = malloc(pFileInfo->ulTotalLength);
	}
	if (pDataInfo->ulType & kNkMAIDDataObjType_File)
	{
		pCurrentBuffer = (char*)xref->pBuffer + xref->ulOffset;
		xref->ulOffset += pFileInfo->ulLength;
		memmove(pCurrentBuffer, pData, pFileInfo->ulLength);
		if (xref->ulOffset == pFileInfo->ulTotalLength)
		{
			char * Ext = xref->suffix;
			switch (pFileInfo->ulFileDataType) {
			case kNkMAIDFileDataType_JPEG:
				strcpy(Ext, ".jpg");
				break;
			case kNkMAIDFileDataType_TIFF:
				strcpy(Ext, ".tif");
				break;
			case kNkMAIDFileDataType_NIF:
				strcpy(Ext, ".nef");
				break;
			case kNkMAIDFileDataType_NDF:
				strcpy(Ext, ".ndf");
				break;
			default:
				strcpy(Ext, ".dat");
			}
		}

	}
	return kNkMAIDResult_NoError;
}