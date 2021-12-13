#pragma once
#include <API/APIHelp.h>

////////////// Configs //////////////

// 后端宏
#define LXL_LANG_JS "Js"
#define LXL_LANG_LUA "Lua"

#if defined(SCRIPTX_LANG_JAVASCRIPT)
	#define LXL_SCRIPT_LANG_TYPE LXL_LANG_JS
	#define LXL_PLUGINS_SUFFIX ".js"
#elif defined(SCRIPTX_LANG_LUA)
	#define LXL_SCRIPT_LANG_TYPE LXL_LANG_LUA
	#define LXL_PLUGINS_SUFFIX ".lua"
#endif

// 插件注册信息
#if defined(SCRIPTX_LANG_JAVASCRIPT)
	#define LXL_LOADER_NAME "LiteXLoader-Js"
	#define LXL_LOADER_DESCRIPTION "LiteXLoader Script Plugin Loader For Javascript"
#elif defined(SCRIPTX_LANG_LUA)
	#define LXL_LOADER_NAME "LiteXLoader-Lua"
	#define LXL_LOADER_DESCRIPTION "LiteXLoader Script Plugin Loader For Lua"
#endif

#define LXL_MODULE_TYPE LXL_SCRIPT_LANG_TYPE

// 配置文件
#define LXL_PLUGINS_LOAD_DIR "./plugins"
#define LXL_PLUGINS_CACHE "./plugins/LiteXLoader/PluginCache/"
#define LXL_LANGPACK_DIR "./plugins/LiteXLoader/LangPack/"
#define LXL_CONFIG_PATH "./plugins/LiteXLoader/config.ini"

// 基础库 & 依赖库
#define LXL_DEPENDS_DIR "./plugins/lib"

// 全局调试
#if defined(SCRIPTX_LANG_JAVASCRIPT)
	#define LXL_DEBUG_CMD "jsdebug"
#elif defined(SCRIPTX_LANG_LUA)
	#define LXL_DEBUG_CMD "luadebug"
#endif
#define LXL_DEBUG_ENGINE_NAME "__LXL_DEBUG_ENGINE__"

// 全局通信
#define LXL_GLOBAL_DATA_NAME L"LITEXLOADER_GLOBAL_DATA_SECTION"
#define LXL_REMOTE_CALL_EVENT_NAME L"LITEXLOADER_REMOTE_CALL_EVENT"
#define LXL_MESSAGE_SYSTEM_WAIT_CHECK_INTERVAL 5

//超时
#define LXL_MAXWAIT_REMOTE_LOAD 10*1000
#define LXL_MAXWAIT_REMOTE_CALL 60*1000

//线程池
#define LXL_POOL_THREAD_COUNT 4

/////////////////////// LXL AutoUpgrade ///////////////////////

#define LXL_RELAY_INDEX "https://upgrade.litebds.com/id.json"
#define LXL_UPDATE_URL_PREFIX "https://cdn.jsdelivr.net/gh/LiteLDev/Upgrade"
#define LXL_UPDATE_URL_PATH "/LXL/LXL.json"

#define LXL_UPDATE_CHECK_INTERVAL (10 * 60)
#define LXL_UPDATE_CONNECTION_TIMEOUT 60

#define LXL_UPDATE_PROGRAM "plugins/LiteXLoader/LXLAutoUpdate.dll"
#define LXL_UPDATE_CHECK_PRELOAD "plugins/preload.conf"

#define LXL_UPDATE_CACHE_PATH "plugins/LiteXLoader/Update/"
#define LXL_UPDATE_INFO_RECORD "plugins/LiteXLoader/Update/Update.ini"

#define LXL_UPDATE_OTHER_FILES_RECORD "plugins/LiteXLoader/Versions.ini"