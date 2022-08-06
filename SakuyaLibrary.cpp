#include    "lib/Maid3.h"
#include    "lib/Maid3d1.h"
#include <ctime>
#include <string>

#include "Sakuya.h"

using namespace std;

extern "C" {
__declspec(dllexport) void Sakuya_init(char *path) { Sakuya::init(path); }
__declspec(dllexport) Sakuya *Sakuya_new(NkMAIDObject *parent, ULONG id) { return new Sakuya(parent, id); }
__declspec(dllexport) void Sakuya_getChildIds(Sakuya *sakuya, ULONG *arr) {
    memcpy(arr, sakuya->getChildIds().data(), sakuya->getChildIds().size() * sizeof(ULONG));
}
__declspec(dllexport) ULONG Sakuya_getChildIdsLen(Sakuya *sakuya) {
    return sakuya->getChildIdsLen();
}
__declspec(dllexport) Sakuya *Sakuya_getChild(Sakuya *sakuya, ULONG id) {
    return sakuya->getChildP(id);
}
__declspec(dllexport) void Sakuya_sc(Sakuya *sakuya) {
    sakuya->sc();
}
__declspec(dllexport) void Sakuya_close(Sakuya *sakuya) {
    sakuya->close();
}
__declspec(dllexport) void Sakuya_acquireFile(Sakuya *sakuya, char *buf) {
    sakuya->acquireFile(buf);
}
__declspec(dllexport) ULONG Sakuya_acquireLen(Sakuya *sakuya) {
    return sakuya->acquireLen();
}
__declspec(dllexport) void Sakuya_acquire(Sakuya *sakuya, char *path) {
    sakuya->acquire(path);
}
__declspec(dllexport) void Sakuya_acquire2(Sakuya *sakuya) {
    sakuya->acquire2();
}
__declspec(dllexport) void Sakuya_cap(Sakuya *sakuya) {
    sakuya->cap();
}
__declspec(dllexport) void Sakuya_deleteDram(Sakuya *sakuya) {
    sakuya->deleteDram();
}
}