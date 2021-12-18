#include "PluginHotManage.h"
#include <API/APIHelp.h>
#include <Tools/Utils.h>
#include <Utils/StringHelper.h>
#include "LoaderHelper.h"
#include "MessageSystem.h"
#include "GlobalShareData.h"
#include <Engine/OperationCount.h>
#include <Utils/StringHelper.h>
#include <Utils/Hash.h>
#include <AutoUpgrade.h>
#include <Configs.h>
#include <Version.h>
#include <string>
#include <thread>
using namespace std;
#define H do_hash

void HotManageMessageCallback(ModuleMessage& msg)
{
    //Remove
    ;
}

bool ProcessHotManageCmd(const std::string& cmd)
{
    if (cmd.find("lxl ") != 0)
        return true;

    auto cmdList = SplitCmdLine(cmd);
    if (cmdList.size() <= 1)
    {
        logger.error("Command not found! Check your input again.");
        return false;
    }

    switch (H(cmdList[1].c_str()))
    {
    case H("version"):
        logger.info("LiteXLoader-{} v{}.{}.{}", LXL_SCRIPT_LANG_TYPE, LXL_VERSION_MAJOR, LXL_VERSION_MINOR, LXL_VERSION_REVISION);
        break;

    case H("list"):
    {
        logger.info("=== LiteXLoader-{} Plugins ===", LXL_SCRIPT_LANG_TYPE);
        auto list = LxlListLocalAllPlugins();
        for (auto& name : list)
            logger.info("{}", name);
        break;
    }

    case H("update"):
    {
        if (cmdList.size() == 3 && cmdList[2] == "force")
        {
            //Force Update
            OperationCount cnt("lxlcommand_update_force");
            if (cnt.hasReachMaxBackendCount())
            {
                cnt.clear();
                std::thread([]
                {
                    CheckAutoUpdate(true, true);
                }).detach();
            }
        }
        else if(cmdList.size() == 2)
        {
            //Common Update
            OperationCount cnt("lxlcommand_update");
            if (cnt.hasReachCount(LXL_BACKEND_TYPE_COUNT))
            {
                cnt.clear();
                std::thread([]
                    {
                        CheckAutoUpdate(true);
                    }).detach();
            }
        }
        else
            logger.error("Bad Command! Check your input again.");
        break;
    }
    
    case H("load"):
    {
        if (cmdList.size() == 3)
        {
            OperationCount cnt("lxlcommand_load");
            OperationCount succeeded("lxlcommand_load_succeeded", false);

            bool isPackage = EndsWith(cmdList[2], ".lxl");
            if (EndsWith(cmdList[2], LXL_PLUGINS_SUFFIX) || isPackage)
            {
                if (!filesystem::exists(cmdList[2]))
                    logger.error("Plugin no found! Check the path you input again.");
                else if (LxlLoadPlugin(cmdList[2], true, isPackage))
                    succeeded.done();
            }

            if (cnt.hasReachMaxBackendCount())
            {
                if(succeeded.get() == 0)
                    logger.error("Fail to load any plugin at <" + cmdList[2] + "> !");
                cnt.clear();
                succeeded.clear();
            }
        }
        else
            logger.error("Bad Command! Check your input again.");
        break;
    }

    case H("unload"):
    {
        if (cmdList.size() == 3)
        {
            OperationCount cnt("lxlcommand_unload");
            OperationCount succeeded("lxlcommand_unload_succeeded", false);

            if (EndsWith(cmdList[2], LXL_PLUGINS_SUFFIX) || EndsWith(cmdList[2], ".lxl"))
            {
                if (LxlUnloadPlugin(cmdList[2]) != "")
                    succeeded.done();
            }

            if (cnt.hasReachMaxBackendCount())
            {
                if (succeeded.get() == 0)
                {
                    logger.error("Fail to unload any plugin named <" + cmdList[2] + ">!");
                    logger.error("Use command \"lxl list\" to show plugins loaded currently.");
                }
                cnt.clear();
                succeeded.clear();
            }
        }
        else
            logger.error("Bad Command! Check your input again.");
        break;
    }

    case H("reload"):
    {
        if (cmdList.size() == 3)
        {
            //Reload specific plugin
            OperationCount cnt("lxlcommand_reload");
            OperationCount succeeded("lxlcommand_unload_succeeded", false);

            if (succeeded.get() == 1)
                break;

            if (EndsWith(cmdList[2], LXL_PLUGINS_SUFFIX) || EndsWith(cmdList[2],".lxl"))
            {
                if (!LxlReloadPlugin(cmdList[2]))
                    logger.error("Fail to reload plugin <" + cmdList[2] + ">!");
                else
                    succeeded.done();
            }

            if (cnt.hasReachMaxBackendCount())
            {
                if (succeeded.get() == 0)
                    logger.error("Fail to reload any plugin named <" + cmdList[2] + "> !");
                cnt.clear();
                succeeded.clear();
            }
        }
        else
        {
            //Reload All
            LxlReloadAllPlugins();
            logger.info("All plugins reloaded.", LXL_SCRIPT_LANG_TYPE);
        }
        break;
    }

    default:
        logger.error("Command not found! Check your input again.");
        break;
    }
    return false;
}