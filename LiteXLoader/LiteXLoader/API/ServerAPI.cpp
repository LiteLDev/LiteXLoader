#include "APIHelp.h"
#include <ScriptX/ScriptX.h>
#include <Kernel/Server.h>
#include "ServerAPI.h"
#include "McAPI.h"
using namespace script;

Local<Value> McClass::setMotd(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,1)
    CHECK_ARG_TYPE(args[0],ValueKind::kString)

    try{
        return Boolean::newBoolean(Raw_SetServerMotd(args[0].asString().toString()));
    }
    CATCH("Fail in SetServerMotd!")
}

Local<Value> McClass::crashBDS(const Arguments& args)
{
    DWORD tmp;
    long long* m = (long long*)GetModuleHandle(NULL);
    VirtualProtect((LPVOID)m, (SIZE_T)8, PAGE_READWRITE, &tmp);
    for (size_t a = 0; a < 0xfffff; a++)
    {
        VirtualProtect((LPVOID)((long long)m + a * 8), (SIZE_T)16, PAGE_READWRITE, &tmp);
        *(m + a) = 114514;
    }
    return Boolean::newBoolean(true);
}