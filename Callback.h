#include    "lib/Maid3.h"
#include    "lib/Maid3d1.h"
#include <iostream>
#include <map>
#include <queue>
#include <list>
#include <string>
struct ProcData
{
	LPVOID	pBuffer;
	ULONG	ulOffset;
    char suffix[16] ;
	char *  path;
};
void CALLPASCAL CALLBACK SrcEventProc2(NKREF refProc, ULONG ulEvent, NKPARAM data);
NKERROR CALLPASCAL CALLBACK DataProc3(NKREF ref, LPVOID pInfo, LPVOID pData);
NKERROR CALLPASCAL CALLBACK DataProc4(NKREF ref, LPVOID pInfo, LPVOID pData);
NKERROR CALLPASCAL CALLBACK DataProc5(NKREF ref, LPVOID pInfo, LPVOID pData);

