#pragma once
#include <Kernel/ThirdParty.h>
#include <Kernel/Data.h>
#include <ScriptX/ScriptX.h>
#include <fstream>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <memory>

struct FormCallbackData
{
    script::ScriptEngine* engine;
    script::Global<script::Function> func;
    std::map<unsigned, script::Global<Function>> buttonCallbacks;
};

class Player;

struct EngineOwnData
{
    //基础信息
    std::string pluginName = "";
    std::string pluginPath = "";

    //表单回调
    std::map<unsigned, FormCallbackData> formCallbacks;

    //LoggerAPI
    bool toConsole = true;
    std::ofstream fout;
    Player *player = nullptr;
    std::string title = "";
    int maxLogLevel = 4;
    int consoleLogLevel = 4;
    int fileLogLevel = 4;
    int playerLogLevel = 4;

    //玩家绑定数据
    std::unordered_map<std::string,Global<Value>> playerDataDB;
};

// 引擎附加数据
#define ENGINE_GET_DATA(e) (std::static_pointer_cast<EngineOwnData>((e)->getData()))
#define ENGINE_OWN_DATA() (std::static_pointer_cast<EngineOwnData>(EngineScope::currentEngine()->getData()))