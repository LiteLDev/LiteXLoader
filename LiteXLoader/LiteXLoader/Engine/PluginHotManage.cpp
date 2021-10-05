#include "PluginHotManage.h"
#include <API/APIHelp.h>
#include <Kernel/Utils.h>
#include "LoaderHelper.h"
#include "MessageSystem.h"
#include "GlobalShareData.h"
#include <AutoUpdate.h>
#include <Configs.h>
#include <Version.h>
#include <string>
#include <thread>
using namespace std;

void HotManageMessageCallback(ModuleMessage& msg)
{
    string cmd = msg.getData();
    
    auto cmdList = SplitCmdLine(cmd);
    if (cmdList[1] == "list")
    {
        //list
        auto list = LxlListLocalAllPlugins();

        //多线程锁
        // ======================= Rewrite here =======================
        //lock_guard<mutex> lock(globalShareData->hotManageLock);

        for (auto& name : list)
            PRINT(name);
    }
    else if (cmdList[1] == "load" && cmdList.size() == 3)
    {
        //load
        if (!filesystem::exists(cmdList[2]))
            ERROR("Plugin no found!");
        if (filesystem::path(cmdList[2]).extension() == LXL_PLUGINS_SUFFIX)
            LxlLoadPlugin(cmdList[2], true);
    }
    else if (cmdList[1] == "unload" && cmdList.size() == 3)
    {
        //unload
        if (filesystem::path(cmdList[2]).extension() == LXL_PLUGINS_SUFFIX)
            if (LxlUnloadPlugin(cmdList[2]) == "")
                ERROR("Plugin no found!");
    }
    else if (cmdList[1] == "reload")
    {
        if (cmdList.size() == 2)
        {
            //reload all
            LxlReloadAllPlugins();
        }
        else if (cmdList.size() == 3)
        {
            //reload one
            if (filesystem::path(cmdList[2]).extension() == LXL_PLUGINS_SUFFIX)
                if (!LxlReloadPlugin(cmdList[2]))
                    ERROR("Plugin no found!");
        }
        else
            ERROR("Bad Command!");
    }
    else
        ERROR("Bad Command!");
}

bool ProcessHotManageCmd(const std::string& cmd)
{
    if (cmd.find("lxl") != 0)
        return true;
    if (cmd == "lxl version")
    {
        printf("LiteXLoader v%d.%d.%d\n", LXL_VERSION_MAJOR, LXL_VERSION_MINOR, LXL_VERSION_REVISION);
        return false;
    }
    else if (cmd == "lxl update")
    {
        std::thread([]
        {
            CheckAutoUpdate(true);
        }).detach();
        return false;
    }
    
    ModuleMessage msg(ModuleMessage::MessageType::LxlCommand, cmd);
    ModuleMessage::broadcastAll(msg);
    return false;
}