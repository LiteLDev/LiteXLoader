#include <API/APIHelp.h>
#include <API/EventAPI.h>
#include <Engine/GlobalShareData.h>
#include <Engine/EngineOwnData.h>
#include <Engine/LocalShareData.h>
#include <Engine/RemoteCall.h>
#include <Engine/MessageSystem.h>
#include <SafeGuardRecord.h>
#include <windows.h>
#include <string>
#include <exception>
#include <thread>
#include <chrono>
#include <memory>
#include <filesystem>
#include <Configs.h>
#include <Version.h>
#include <LoggerAPI.h>
#include <Utils/FileHelper.h>
#include <Tools/IniHelper.h>
#include <TranslationAPI.h>
#include <EconomicSystem.h>

using namespace std;



//主引擎表
std::vector<ScriptEngine*> lxlModules;
// 配置文件
SimpleIni* iniConf;
// 日志等级
int lxlLogLevel = 1;

::Logger logger("LiteXLoader");

extern void LoadDepends();
extern void LoadMain();
extern void BindAPIs(ScriptEngine *engine);
extern void LoadDebugEngine();

void Welcome()
{
    cout << "\r" << R"(     _       _  _         __   __  _                        _             )" << endl
         << "\r" << R"(    | |     (_)| |        \ \ / / | |                      | |            )" << endl
         << "\r" << R"(    | |      _ | |_  ___   \ V /  | |      ___    __ _   __| |  ___  _ __ )" << endl
         << "\r" << R"(    | |     | || __|/ _ \   > <   | |     / _ \  / _` | / _` | / _ \| '__|)" << endl
         << "\r" << R"(    | |____ | || |_|  __/  / . \  | |____| (_) || (_| || (_| ||  __/| |   )" << endl
         << "\r" << R"(    |______||_| \__|\___| /_/ \_\ |______|\___/  \__,_| \__,_| \___||_|   )" << endl
         << "\r" << R"(                                                                          )" << endl
         << "\r" << R"(                                                                          )" << endl
         << "\r" << R"(        =========   LiteXLoader Script Plugin Loader   =========          )" << endl
         << "\r" << R"(                                                                          )" << endl;
}

void LoaderInfo()
{
    bool isNotRelease = LL::Version::Status::LXL_VERSION_STATUS != LL::Version::Status::Release;
    logger.info(std::string("LXL for ") + LXL_MODULE_TYPE + " loaded");
    logger.info(std::string("Version ") + to_string(LXL_VERSION_MAJOR) + "." + to_string(LXL_VERSION_MINOR) + "."
        + to_string(LXL_VERSION_REVISION) + (isNotRelease ? string(" ") + LXL_VERSION_STATUS_STRING : string("")));
}

void entry()
{
    //设置全局SEH处理
    _set_se_translator(seh_exception::TranslateSEHtoCE);

    LL::registerPlugin(LXL_LOADER_NAME, LXL_LOADER_DESCRIPTION,
        LL::Version(LXL_VERSION_MAJOR, LXL_VERSION_MINOR, LXL_VERSION_REVISION, LL::Version::LXL_VERSION_STATUS),
        "github.com/LiteLDev/LiteXLoader", "GPL-3", "www.litebds.com");

    //读取配置文件
    CreateDirs(std::filesystem::path(LXL_CONFIG_PATH).remove_filename().u8string());
    iniConf = SimpleIni::create(LXL_CONFIG_PATH,"");
    if (!iniConf)
        logger.error("Fail to Load config file of LiteXLoader! Default settings applied.");
    lxlLogLevel = iniConf->getInt("Main","LxlLogLevel",1);

    //国际化
    Translation::load(LXL_LANGPACK_DIR + iniConf->getString("Main", "Language", "en_US") + ".json");

    //初始化全局数据
    InitLocalShareData();
    InitGlobalShareData();
    InitSafeGuardRecord();

    //初始化消息系统
    InitMessageSystem();

    //欢迎
    if (localShareData->isFirstInstance)
        Welcome();
    LoaderInfo();

    //初始化经济系统
    EconomySystem::init(MoneyEventCallback);

    //预加载库
    LoadDepends();
    
    //加载插件
    LoadMain();

    //注册后台调试
    LoadDebugEngine();

    //初始化事件监听
    InitBasicEventListeners();

    //UnlockCmd
    extern bool isUnlockCmdEnabled;
    isUnlockCmdEnabled = iniConf->getBool("Modules", "BuiltInUnlockCmd", true);

    delete iniConf;
}