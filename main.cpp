#include    "lib/Maid3.h"
#include    "lib/Maid3d1.h"
#include <ctime>
#include <string>

#include "Sakuya.h"
using namespace std;

void Cap(Sakuya& sakuyaDevice)
{
    sakuyaDevice.capStart(kNkMAIDCapability_Capture);
    while (sakuyaDevice.getChildIds().empty())
    {
        Sleep(10);
    }
    auto sakuyaDataObject = sakuyaDevice.getChild(sakuyaDevice.getChildIds()[0]);
    auto sakuyaImage = sakuyaDataObject.getChild(1);
    auto path = string(R"(C:\Users\)");
    auto p1 = path + std::to_string(std::time(nullptr));
    sakuyaImage.acquire(const_cast<char *>(p1.c_str()));
    sakuyaImage.close();
    sakuyaDataObject.close();
    while (sakuyaDevice.getChildIds().empty())
    {
        Sleep(10);
    }
    auto sakuyaDataObject2 = sakuyaDevice.getChild(sakuyaDevice.getChildIds()[0]);
    auto sakuyaImage2 = sakuyaDataObject2.getChild(1);
    sakuyaImage2.acquire2();
    sakuyaDataObject2.deleteDram();
    sakuyaImage2.close();
//    auto sakuyaImage2 = sakuyaDataObject2.getChild(1);
//    auto p2 = path + std::to_string(std::time(nullptr));
//    sakuyaImage2.acquire(const_cast<char *>(p2.c_str()));
//    sakuyaImage2.close();
    sakuyaDataObject2.close();
}

int main()
{
    Sakuya::init((char *)R"(C:\Users\lambda\source\CLionProjects\sakuya\lib\Type0015.md3)");
    auto sakuyaRoot = Sakuya(nullptr, 0);
    {
        auto s = sakuyaRoot.getChildIds();
        if (s.empty())return 0;
    }
    auto sakuyaDevice = Sakuya(sakuyaRoot.pObject, 1);
    sakuyaDevice.setCallback(kNkMAIDCapability_EventProc,(LPNKFUNC)SrcEventProc2);
//    sakuyaDevice.capStart(kNkMAIDCapability_Capture);
    Cap(sakuyaDevice);
    Cap(sakuyaDevice);
    sakuyaDevice.close();
    return 0;
}
