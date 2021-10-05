#include "CommandAPI.h"
#include "APIHelp.h"
#include "McAPI.h"
#include "PlayerAPI.h"
#include <Kernel/Utils.h>
#include <Engine/GlobalShareData.h>
#include <Engine/LocalShareData.h>
#include <Engine/EngineOwnData.h>
#include <Engine/LoaderHelper.h>
#include <Kernel/Base.h>
#include <Kernel/Global.h>
#include <filesystem>
#include <Configs.h>
#include <vector>
#include <string>
using namespace std;

//////////////////// APIs ////////////////////

Local<Value> McClass::runcmd(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)

    try {
        return Boolean::newBoolean(Raw_Runcmd(args[0].asString().toString()));
    }
    CATCH("Fail in RunCmd!")
}

Local<Value> McClass::runcmdEx(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)

    try {
        std::pair<bool, string> result = Raw_RuncmdEx(args[0].asString().toString());
        Local<Object> resObj = Object::newObject();
        resObj.set("success", result.first);
        resObj.set("output", result.second);
        return resObj;
    }
    CATCH("Fail in RunCmdEx!")
}


// Helper
void LxlRegisterNewCmd(bool isPlayerCmd, string cmd, const string& describe, int level, Local<Function> func)
{
    if (cmd[0] == '/')
        cmd = cmd.erase(0, 1);

    if(isPlayerCmd)
        localShareData->playerCmdCallbacks[cmd] = { EngineScope::currentEngine(),level,Global<Function>(func) };
    else
        localShareData->consoleCmdCallbacks[cmd] = { EngineScope::currentEngine(),level,Global<Function>(func) };

    //延迟注册
    if (isCmdRegisterEnabled)
        Raw_RegisterCmd(cmd, describe, level);
    else
        toRegCmdQueue.push_back({ cmd, describe, level });
}

bool LxlRemoveCmdRegister(ScriptEngine* engine)
{
    for (auto& cmdData : localShareData->playerCmdCallbacks)
    {
        if (cmdData.second.fromEngine == engine)
            localShareData->playerCmdCallbacks.erase(cmdData.first);
    }

    for (auto& cmdData : localShareData->consoleCmdCallbacks)
    {
        if (cmdData.second.fromEngine == engine)
            localShareData->consoleCmdCallbacks.erase(cmdData.first);
    }
    return true;
}
// Helper

Local<Value> McClass::regPlayerCmd(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 3);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);
    CHECK_ARG_TYPE(args[2], ValueKind::kFunction);
    if (args.size() >= 4)
        CHECK_ARG_TYPE(args[3], ValueKind::kNumber);

    try {
        string cmd = args[0].asString().toString();
        string describe = args[1].asString().toString();
        int level = 0;

        if (args.size() >= 4)
        {
            int newLevel = args[3].asNumber().toInt32();
            if (newLevel >= 0 && newLevel <= 3)
                level = newLevel;
        }

        LxlRegisterNewCmd(true, cmd, describe, level, args[2].asFunction());
        return Boolean::newBoolean(true);
    }
    CATCH("Fail in RegisterPlayerCmd!");
}

Local<Value> McClass::regConsoleCmd(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 3);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);
    CHECK_ARG_TYPE(args[2], ValueKind::kFunction);

    try {
        string cmd = args[0].asString().toString();
        string describe = args[1].asString().toString();

        LxlRegisterNewCmd(false, cmd, describe, 4, args[2].asFunction());
        return Boolean::newBoolean(true);
    }
    CATCH("Fail in RegisterConsoleCmd!");
}

Local<Value> McClass::sendCmdOutput(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        return Boolean::newBoolean(Raw_SendCmdOutput(args[0].toStr()));
    }
    CATCH("Fail in SendCmdOutput!");
}


//////////////////// LXL Event Callbacks ////////////////////

void RegisterBuiltinCmds()
{
    //调试引擎
    Raw_RegisterCmd(LXL_DEBUG_CMD, "LXL " + string(LXL_MODULE_TYPE) + " Engine Real-time Debugging", 4);
    
    //热管理
    Raw_RegisterCmd("lxl list", "List current loaded LXL plugins", 4);
    Raw_RegisterCmd("lxl load", "Load a new LXL plugin", 4);
    Raw_RegisterCmd("lxl unload", "Unload an existing LXL plugin", 4);
    Raw_RegisterCmd("lxl reload", "Reload an existing LXL plugin / all LXL plugins", 4);
    Raw_RegisterCmd("lxl version", "Get the version of LiteXLoader", 4);

    INFO("Builtin Cmds Registered.");
}

void ProcessRegCmdQueue()
{
    for (auto& cmdData : toRegCmdQueue)
    {
        Raw_RegisterCmd(cmdData.cmd, cmdData.describe, cmdData.level);
    }
    toRegCmdQueue.clear();
}

bool ProcessDebugEngine(const string& cmd)
{
#define OUTPUT_DEBUG_SIGN() std::cout << "LiteXLoader-" << LXL_MODULE_TYPE << ">" << std::flush
    extern bool globalDebug;
    extern ScriptEngine *debugEngine;

    if (cmd == LXL_DEBUG_CMD)
    {
        if (globalDebug)
        {
            //EndDebug
            INFO("Debug mode ended");
            globalDebug = false;
        }
        else
        {
            //StartDebug
            INFO("Debug mode begin");
            globalDebug = true;
            OUTPUT_DEBUG_SIGN();
        }
        return false;
    }
    if (globalDebug)
    {
        EngineScope enter(debugEngine);
        try
        {
            if (cmd == "stop")
            {
                WARN("请先退出Debug实时调试模式再使用stop！");
                return true;
            }
            else
            {
                auto result = debugEngine->eval(cmd);
                PrintValue(std::cout, result);
                cout << endl;
                OUTPUT_DEBUG_SIGN();
            }
        }
        catch (Exception& e)
        {
            ERRPRINT(e);
            OUTPUT_DEBUG_SIGN();
        }
        return false;
    }
    return true;
}

void ProcessStopServer(const string& cmd)
{
    if (cmd == "stop")
    {
        isServerStarted = false;
    }
}

string LxlFindCmdReg(bool isPlayerCmd, const string& cmd, vector<string> &receiveParas)
{
    std::map<std::string, CmdCallbackData, CmdCallbackMapCmp>& cmdMap =
        isPlayerCmd ? localShareData->playerCmdCallbacks : localShareData->consoleCmdCallbacks;

    for (auto& cmdData : cmdMap)
    {
        string prefix = cmdData.first;
        if (cmd == prefix || (cmd.find(prefix) == 0 && cmd[prefix.size()] == ' '))
            //如果命令与注册前缀全匹配，或者目标前缀后面为空格
        {
            //Matched
            if (cmd.size() > prefix.size())
            {
                //除了注册前缀之外还有额外参数
                receiveParas = SplitCmdLine(cmd.substr(prefix.size() + 1));
            }
            else
                receiveParas = vector<string>();

            return prefix;
        }
    }
    return string();
}

bool CallPlayerCmdCallback(Player* player, const string& cmdPrefix, const vector<string> &paras)
{
    EngineScope enter(localShareData->playerCmdCallbacks[cmdPrefix].fromEngine);
    auto cmdData = localShareData->playerCmdCallbacks[cmdPrefix];
    Local<Value> res{};
    try
    {
        Local<Array> args = Array::newArray();
        for (auto& para : paras)
            args.add(String::newString(para));
        res = cmdData.func.get().call({}, PlayerClass::newPlayer(player), args);
    }
    catch (const Exception& e)
    {
        ERROR("PlayerCmd Callback Failed!");
        ERRPRINT("[Error] In Plugin: " + ENGINE_OWN_DATA()->pluginName);
        ERRPRINT(e);
    }
    if (res.isNull() || (res.isBoolean() && res.asBoolean().value() == false))
        return false;

    return true;
}

bool CallServerCmdCallback(const string& cmdPrefix, const vector<string>& paras)
{
    EngineScope enter(localShareData->consoleCmdCallbacks[cmdPrefix].fromEngine);
    auto cmdData = localShareData->consoleCmdCallbacks[cmdPrefix];
    Local<Value> res{};
    try
    {
        Local<Array> args = Array::newArray();
        for (auto& para : paras)
            args.add(String::newString(para));
        res = cmdData.func.get().call({}, args);
    }
    catch (const Exception& e)
    {
        ERROR("ServerCmd Callback Failed!");
        ERRPRINT("[Error] In Plugin: " + ENGINE_OWN_DATA()->pluginName);
        ERRPRINT(e);
    }
    if (res.isNull() || (res.isBoolean() && res.asBoolean().value() == false))
        return false;

    return true;
}