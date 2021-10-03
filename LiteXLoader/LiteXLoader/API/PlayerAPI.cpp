#include "APIHelp.h"
#include "BaseAPI.h"
#include "BlockAPI.h"
#include "DeviceAPI.h"
#include "PlayerAPI.h"
#include "McAPI.h"
#include "ContainerAPI.h"
#include "ItemAPI.h"
#include "GuiAPI.h"
#include "NbtAPI.h"
#include <API/PacketAPI.h>
#include <Engine/EngineOwnData.h>
#include <Engine/GlobalShareData.h>
#include <Kernel/Player.h>
#include <Kernel/Device.h>
#include <Kernel/Container.h>
#include <Kernel/Entity.h>
#include <Kernel/Gui.h>
#include <Kernel/Scoreboard.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <LiteXLoader/Kernel/Packet.h>
using namespace std;
using namespace script;

//////////////////// Class Definition ////////////////////

ClassDefine<PlayerClass> PlayerClassBuilder =
    defineClass<PlayerClass>("LXL_Player")
        .constructor(nullptr)
        .instanceFunction("getRawPtr", &PlayerClass::getRawPtr)

        .instanceProperty("name", &PlayerClass::getName)
        .instanceProperty("pos", &PlayerClass::getPos)
        .instanceProperty("blockPos", &PlayerClass::getBlockPos)
        .instanceProperty("realName", &PlayerClass::getRealName)
        .instanceProperty("xuid", &PlayerClass::getXuid)
        .instanceProperty("uuid", &PlayerClass::getUuid)
        .instanceProperty("permLevel", &PlayerClass::getPermLevel)
        .instanceProperty("gameMode", &PlayerClass::getGameMode)
        .instanceProperty("maxHealth", &PlayerClass::getMaxHealth)
        .instanceProperty("health", &PlayerClass::getHealth)
        .instanceProperty("inAir", &PlayerClass::getInAir)
        .instanceProperty("inWater", &PlayerClass::getInWater)
        .instanceProperty("sneaking", &PlayerClass::getSneaking)
        .instanceProperty("speed",&PlayerClass::getSpeed)
        .instanceProperty("direction", &PlayerClass::getDirection)
        .instanceProperty("uniqueId", &PlayerClass::getUniqueID)

        .instanceFunction("isOP", &PlayerClass::isOP)
        .instanceFunction("setPermLevel", &PlayerClass::setPermLevel)
        .instanceFunction("setGameMode", &PlayerClass::setGameMode)

        .instanceFunction("runcmd", &PlayerClass::runcmd)
        .instanceFunction("teleport", &PlayerClass::teleport)
        .instanceFunction("kill", &PlayerClass::kill)
        .instanceFunction("kick", &PlayerClass::kick)
        .instanceFunction("disconnect", &PlayerClass::kick)
        .instanceFunction("tell", &PlayerClass::tell)
        .instanceFunction("talkAs", &PlayerClass::talkAs)
        .instanceFunction("sendText", &PlayerClass::tell)
        .instanceFunction("rename", &PlayerClass::rename)
        .instanceFunction("addLevel", &PlayerClass::addLevel)
        .instanceFunction("setOnFire", &PlayerClass::setOnFire)
        .instanceFunction("transServer", &PlayerClass::transServer)
        .instanceFunction("crash", &PlayerClass::crash)
        .instanceFunction("hurt", &PlayerClass::hurt)
        .instanceFunction("setOnFire", &PlayerClass::setOnFire)
        .instanceFunction("refreshChunks", &PlayerClass::refreshChunks)
        .instanceFunction("giveItem", &PlayerClass::giveItem)
        .instanceFunction("clearItem", &PlayerClass::clearItem)

        .instanceFunction("getBlockStandingOn", &PlayerClass::getBlockStandingOn)
        .instanceFunction("getDevice", &PlayerClass::getDevice)
        .instanceFunction("getHand", &PlayerClass::getHand)
        .instanceFunction("getOffHand", &PlayerClass::getOffHand)
        .instanceFunction("getInventory", &PlayerClass::getInventory)
        .instanceFunction("getArmor", &PlayerClass::getArmor)
        .instanceFunction("getEnderChest", &PlayerClass::getEnderChest)
        .instanceFunction("refreshItems", &PlayerClass::refreshItems)

        .instanceFunction("getScore", &PlayerClass::getScore)
        .instanceFunction("setScore", &PlayerClass::setScore)
        .instanceFunction("addScore", &PlayerClass::addScore)
        .instanceFunction("reduceScore", &PlayerClass::reduceScore)
        .instanceFunction("deleteScore", &PlayerClass::deleteScore)
        .instanceFunction("setSidebar", &PlayerClass::setSidebar)
        .instanceFunction("removeSidebar", &PlayerClass::removeSidebar)
        .instanceFunction("setBossBar", &PlayerClass::setBossBar)
        .instanceFunction("removeBossBar", &PlayerClass::removeBossBar)

        .instanceFunction("sendSimpleForm", &PlayerClass::sendSimpleForm)
        .instanceFunction("sendModalForm", &PlayerClass::sendModalForm)
        .instanceFunction("sendCustomForm", &PlayerClass::sendCustomForm)
        .instanceFunction("sendForm", &PlayerClass::sendForm)
        .instanceFunction("sendPacket",&PlayerClass::sendPacket)

        .instanceFunction("setExtraData", &PlayerClass::setExtraData)
        .instanceFunction("getExtraData", &PlayerClass::getExtraData)
        .instanceFunction("delExtraData", &PlayerClass::delExtraData)

        .instanceFunction("setNbt", &PlayerClass::setNbt)
        .instanceFunction("getNbt", &PlayerClass::getNbt)
        .instanceFunction("addTag", &PlayerClass::addTag)
        .instanceFunction("removeTag", &PlayerClass::removeTag)
        .instanceFunction("hasTag", &PlayerClass::hasTag)
        .instanceFunction("getAllTags", &PlayerClass::getAllTags)
        .instanceFunction("getAbilities", &PlayerClass::getAbilities)
        .instanceFunction("getAttributes", &PlayerClass::getAttributes)

        //For Compatibility
        .instanceProperty("ip", &PlayerClass::getIP)
        .instanceFunction("setTag", &PlayerClass::setNbt)
        .instanceFunction("getTag", &PlayerClass::getNbt)
        .instanceFunction("removeItem", &PlayerClass::removeItem)
        .instanceFunction("getAllItems", &PlayerClass::getAllItems)
        .instanceFunction("removeScore", &PlayerClass::deleteScore)
        .build();


//////////////////// Classes ////////////////////

//生成函数
PlayerClass::PlayerClass(Player* p)
    :ScriptClass(ScriptClass::ConstructFromCpp<PlayerClass>{})
{
    set(p);
}
Local<Object> PlayerClass::newPlayer(Player *p)
{
    auto newp = new PlayerClass(p);
    return newp->getScriptObject();
}
Local<Object> PlayerClass::newPlayer(WPlayer p)
{
    return PlayerClass::newPlayer(p.v);
}
Player* PlayerClass::extract(Local<Value> v)
{
    if(EngineScope::currentEngine()->isInstanceOf<PlayerClass>(v))
        return EngineScope::currentEngine()->getNativeInstance<PlayerClass>(v)->get();
    else
        return nullptr;
}

//公用API
Local<Value> McClass::getPlayer(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,1)
    CHECK_ARG_TYPE(args[0],ValueKind::kString)

    try{
        string target = args[0].toStr();
        if (target.empty())
            return Local<Value>();

        transform(target.begin(), target.end(), target.begin(), ::tolower);	//lower case the string
        auto playerList = Raw_GetOnlinePlayers();
        int delta = 2147483647;	//c++ int max
        Player* found = nullptr;

        for(Player *p : playerList)
        {
            if(Raw_GetXuid(p) == target)
                return PlayerClass::newPlayer(p);

            string pName = Raw_GetPlayerName(p);
            transform(pName.begin(), pName.end(), pName.begin(), ::tolower);

            if(pName.find(target) == 0)
            {	
                //0 ís the index where the "target" appear in "pName"
                int curDelta = pName.length() - target.length();
                if (curDelta == 0)
                    return PlayerClass::newPlayer(p);

                if(curDelta < delta){
                    found = p;
                    delta = curDelta;
                }
            }
        }
        return found ? PlayerClass::newPlayer(found) : Local<Value>();	//Player/Null
    }
    CATCH("Fail in GetPlayer!")
}

Local<Value> McClass::getOnlinePlayers(const Arguments& args)
{
    try{
        auto players = Raw_GetOnlinePlayers();
        Local<Array> list = Array::newArray();
        for(auto p : players)
            list.add(PlayerClass::newPlayer(p));
        return list;
    }
    CATCH("Fail in GetOnlinePlayers!")
}

Local<Value> McClass::broadcast(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)

    try {
        TextType type = TextType::RAW;
        if (args.size() >= 2 && args[1].isNumber())
        {
            int newType = args[1].asNumber().toInt32();
            if (newType >= 0 && newType <= 9)
                type = (TextType)newType;
        }
        return Boolean::newBoolean(Raw_Broadcast(args[0].toStr(), type));
    }
    CATCH("Fail in Broadcast!")
}

//成员函数
void PlayerClass::set(Player* player)
{
    __try
    {
        id = ((Actor*)player)->getUniqueID();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        isValid = false;
    }
}

Player* PlayerClass::get()
{
    if (!isValid)
        return nullptr;
    else
        return Raw_GetPlayerByUniqueId(id);
}

Local<Value> PlayerClass::getName()
{ 
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return String::newString(Raw_GetPlayerName(player));
    }
    CATCH("Fail in getPlayerName!")
}

Local<Value> PlayerClass::getPos()
{ 
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return FloatPos::newPos(Raw_GetPlayerPos(player));
    }
    CATCH("Fail in getPlayerPos!")
}

Local<Value> PlayerClass::getBlockPos()
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return IntPos::newPos(Raw_GetPlayerBlockPos(player));
    }
    CATCH("Fail in getPlayerBlockPos!")
}

Local<Value> PlayerClass::getXuid()
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return String::newString(Raw_GetXuid(player));
    }
    CATCH("Fail in getXuid!")
}

Local<Value> PlayerClass::getUuid()
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return String::newString(Raw_GetUuid(player));
    }
    CATCH("Fail in getXuid!")
}

Local<Value> PlayerClass::getRealName()
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return String::newString(Raw_GetRealName(player));
    }
    CATCH("Fail in getRealName!")
}

Local<Value> PlayerClass::getIP()
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return String::newString(Raw_GetIP(player));
    }
    CATCH("Fail in GetIP!")
}

Local<Value> PlayerClass::getPermLevel()
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Number::newNumber(Raw_GetPlayerPermLevel(player));
    }
    CATCH("Fail in getPlayerPermLevel!")
}

Local<Value> PlayerClass::getGameMode()
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Number::newNumber(Raw_GetGameMode(player));
    }
    CATCH("Fail in getGameMode!")
}

Local<Value> PlayerClass::getSneaking()
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_GetSneaking(player));
    }
    CATCH("Fail in getSneaking!")
}

Local<Value> PlayerClass::getSpeed()
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Number::newNumber(Raw_GetSpeed((Actor*)player));
    }
    CATCH("Fail in getSpeed!")
}

Local<Value> PlayerClass::getDirection()
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();
        
        auto vec = Raw_GetDirction((Actor*)player);
        return DirectionAngle::newAngle(vec->x, vec->y);
    }
    CATCH("Fail in getDirection!")
}

Local<Value> PlayerClass::getMaxHealth()
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Number::newNumber(Raw_GetMaxHealth((Actor*)player));
    }
    CATCH("Fail in GetMaxHealth!")
}

Local<Value> PlayerClass::getHealth()
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Number::newNumber(Raw_GetHealth((Actor*)player));
    }
    CATCH("Fail in GetHealth!")
}

Local<Value> PlayerClass::getInAir()
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_GetIsInAir((Actor*)player));
    }
    CATCH("Fail in GetInAir!")
}

Local<Value> PlayerClass::getInWater()
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_GetIsInWater((Actor*)player));
    }
    CATCH("Fail in getInWater!")
}

Local<Value> PlayerClass::getRawPtr(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();
        else
            return Number::newNumber((intptr_t)player);
    }
    CATCH("Fail in getRawPtr!")
}

Local<Value> PlayerClass::getUniqueID()
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();
        else
            return String::newString(std::to_string(player->getUniqueID().id));
    }
    CATCH("Fail in getUniqueID!")
}

Local<Value> PlayerClass::teleport(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,1)
    
    try{
        FloatVec4 pos;

        if (args.size() == 1)
        {
            if (IsInstanceOf<IntPos>(args[0]))
            {
                // IntPos
                IntPos* posObj = IntPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos.x = posObj->x;
                    pos.y = posObj->y;
                    pos.z = posObj->z;
                    pos.dim = posObj->dim;
                }
            }
            else if (IsInstanceOf<FloatPos>(args[0]))
            {
                // FloatPos
                FloatPos* posObj = FloatPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos = *posObj;
                }
            }
            else
            {
                ERROR("Wrong type of argument in teleport!");
                return Local<Value>();
            }
        }
        else if (args.size() == 4)
        {
            // number pos
            CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[2], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[3], ValueKind::kNumber);

            pos.x = args[0].asNumber().toFloat();
            pos.y = args[1].asNumber().toFloat();
            pos.z = args[2].asNumber().toFloat();
            pos.dim = args[3].toInt();
        }
        else
        {
            ERROR("Wrong type of argument in teleport!");
            return Local<Value>();
        }

        Player* player = get();
        if (!player)
            return Local<Value>();
        return Boolean::newBoolean(Raw_TeleportPlayer(player, pos));
    }
    CATCH("Fail in TeleportPlayer!")
}

Local<Value> PlayerClass::kill(const Arguments& args)
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_KillPlayer(player));
    }
    CATCH("Fail in KillPlayer!")
}

Local<Value> PlayerClass::isOP(const Arguments& args)
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_GetPlayerPermLevel(player) >= 1);
    }
    CATCH("Fail in IsOP!")
}

Local<Value> PlayerClass::setPermLevel(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
    
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        bool res = false;
        int newPerm = args[0].asNumber().toInt32();
        if(newPerm>=0 || newPerm<=4)
            res = Raw_SetPlayerPermLevel(player,newPerm);
        return Boolean::newBoolean(res);
    }
    CATCH("Fail in setPlayerPermLevel!");
}

Local<Value> PlayerClass::setGameMode(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        bool res = false;
        int newMode = args[0].asNumber().toInt32();
        if (newMode >= 0 || newMode <= 3)
            res = Raw_SetGameMode(player, newMode);
        return Boolean::newBoolean(res);
    }
    CATCH("Fail in setGameMode!");
}

Local<Value> PlayerClass::runcmd(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_RuncmdAs(player, args[0].toStr()));
    }
    CATCH("Fail in runcmd!");
}

Local<Value> PlayerClass::kick(const Arguments& args)
{
    if(args.size() >= 1)
        CHECK_ARG_TYPE(args[0],ValueKind::kString);

    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        string msg="正在从服务器断开连接";
        if(args.size() >= 1)
            msg = args[0].toStr();
        
        return Boolean::newBoolean(Raw_KickPlayer(player,msg));
    }
    CATCH("Fail in kickPlayer!");
}

Local<Value> PlayerClass::tell(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        TextType type = TextType::RAW;
        if(args.size() >= 2 && args[1].isNumber())
        {
            int newType = args[1].asNumber().toInt32();
            if(newType >= 0 && newType <= 9)
                type = (TextType)newType;
        }
        return Boolean::newBoolean(Raw_Tell(player,args[0].toStr(),type));
    }
    CATCH("Fail in tell!");
}

Local<Value> PlayerClass::talkAs(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_TalkAs(player, args[0].toStr()));
    }
    CATCH("Fail in talkAs!");
}

Local<Value> PlayerClass::getHand(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return ItemClass::newItem(Raw_GetHand(player));
    }
    CATCH("Fail in getHand!");
}

Local<Value> PlayerClass::getOffHand(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return ItemClass::newItem(Raw_GetOffHand(player));
    }
    CATCH("Fail in getOffHand!");
}

Local<Value> PlayerClass::getInventory(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return ContainerClass::newContainer(Raw_GetInventory(player));
    }
    CATCH("Fail in getInventory!");
}

Local<Value> PlayerClass::getArmor(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return ContainerClass::newContainer(Raw_GetArmor(player));
    }
    CATCH("Fail in getArmor!");
}

Local<Value> PlayerClass::getEnderChest(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return ContainerClass::newContainer(Raw_GetEnderChest(player));
    }
    CATCH("Fail in getEnderChest!");
}

Local<Value> PlayerClass::refreshItems(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_RefreshItems(player));
    }
    CATCH("Fail in refreshItems!");
}

Local<Value> PlayerClass::rename(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_RenamePlayer(player,args[0].toStr()));
    }
    CATCH("Fail in RenamePlayer!");
}

Local<Value> PlayerClass::addLevel(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_AddLevel(player, args[0].toInt()));
    }
    CATCH("Fail in addLevel!");
}

Local<Value> PlayerClass::transServer(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber)

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_TransServer(player, args[0].toStr(), (short) args[1].toInt()));
    }
    CATCH("Fail in transServer!");
}

Local<Value> PlayerClass::crash(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_CrashPlayer(player));
    }
    CATCH("Fail in crashPlayer!");
}

Local<Value> PlayerClass::getBlockStandingOn(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return BlockClass::newBlock(Raw_GetBlockStandingOn((Actor*)player));
    }
    CATCH("Fail in getBlockStandingOn!");
}

Local<Value> PlayerClass::getDevice(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return DeviceClass::newDevice(player);
    }
    CATCH("Fail in getDevice!");
}

Local<Value> PlayerClass::getScore(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Number::newNumber(Raw_GetScore(player, args[0].toStr()));
    }
    CATCH("Fail in getScore!");
}

Local<Value> PlayerClass::setScore(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
    
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_SetScore(player,args[0].toStr(), args[1].toInt()));
    }
    CATCH("Fail in getScore!");
}

Local<Value> PlayerClass::addScore(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
    
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_AddScore(player,args[0].toStr(), args[1].toInt()));
    }
    CATCH("Fail in addScore!");
}

Local<Value> PlayerClass::reduceScore(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
    
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_ReduceScore(player,args[0].toStr(), args[1].toInt()));
    }
    CATCH("Fail in removeScore!");
}

Local<Value> PlayerClass::deleteScore(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_DeleteScore(player, args[0].toStr()));
    }
    CATCH("Fail in removeScore!");
}

Local<Value> PlayerClass::setSidebar(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kObject);
    if (args.size() >= 3)
        CHECK_ARG_TYPE(args[2], ValueKind::kNumber);
    
    try
    {
        Player* player = get();
        if (!player)
            return Local<Value>();

        std::vector<std::pair<std::string, int>> data;
        auto source = args[1].asObject();
        auto keys = source.getKeyNames();
        for (auto& key : keys)
        {
            data.push_back(make_pair(key, source.get(key).toInt()));
        }

        int sortOrder = 1;
        if (args.size() >= 3)
            sortOrder = args[2].toInt();

        return Boolean::newBoolean(Raw_SetSidebar(player,args[0].toStr(),data,sortOrder));
    }
    CATCH("Fail in setSidebar!")
}

Local<Value> PlayerClass::removeSidebar(const Arguments& args)
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_RemoveSidebar(player));
    }
    CATCH("Fail in removeSidebar!")
}

Local<Value> PlayerClass::setBossBar(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
    
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        int percent = args[1].toInt();
        if(percent < 0)
            percent = 0;
        else if(percent > 100)
            percent = 100;
        
        float value = (float)percent / 100;
        return Boolean::newBoolean(Raw_SetBossBar(player,args[0].toStr(),value));
    }
    CATCH("Fail in setBossBar!")
}

Local<Value> PlayerClass::removeBossBar(const Arguments& args)
{
    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_RemoveBossBar(player));
    }
    CATCH("Fail in removeBossBar!")
}

Local<Value> PlayerClass::sendSimpleForm(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 4);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);
    CHECK_ARG_TYPE(args[2], ValueKind::kArray);
    CHECK_ARG_TYPE(args[3], ValueKind::kArray);
    CHECK_ARG_TYPE(args[4], ValueKind::kFunction);

    try
    {   
        Player* player = get();
        if (!player)
            return Local<Value>();

        // 普通格式
        auto textsArr = args[2].asArray();
        if (textsArr.size() == 0 || !textsArr.get(0).isString())
            return Local<Value>();
        auto imagesArr = args[3].asArray();
        if (imagesArr.size() != textsArr.size() || !imagesArr.get(0).isString())
            return Local<Value>();

        vector<string> texts, images;
        for (int i = 0; i < textsArr.size(); ++i)
        {
            texts.push_back(textsArr.get(i).toStr());
            images.push_back(imagesArr.get(i).toStr());
        }

        int formId = Raw_SendSimpleForm(player, args[0].toStr(), args[1].toStr(), texts, images);

        
        ENGINE_OWN_DATA()->formCallbacks[(unsigned)formId].engine = EngineScope::currentEngine();
        ENGINE_OWN_DATA()->formCallbacks[(unsigned)formId].func = args[4].asFunction();

        return Number::newNumber(formId);
    }
    CATCH("Fail in sendSimpleForm!");
}

Local<Value> PlayerClass::sendModalForm(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 5);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);
    CHECK_ARG_TYPE(args[2], ValueKind::kString);
    CHECK_ARG_TYPE(args[3], ValueKind::kString);
    CHECK_ARG_TYPE(args[4], ValueKind::kFunction);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        int formId = Raw_SendModalForm(player, args[0].toStr(), args[1].toStr(), args[2].toStr(), args[3].toStr());
        ENGINE_OWN_DATA()->formCallbacks[(unsigned)formId].engine = EngineScope::currentEngine();
        ENGINE_OWN_DATA()->formCallbacks[(unsigned)formId].func = args[4].asFunction();

        return Number::newNumber(formId);
    }
    CATCH("Fail in sendModalForm!");
}

Local<Value> PlayerClass::sendCustomForm(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kFunction);

    try{
        Player* player = get();
        if (!player)
            return Local<Value>();

        string data = JSON_VALUE::parse(args[0].toStr()).dump();
        int formId = Raw_SendCustomForm(player, data);
        
        ENGINE_OWN_DATA()->formCallbacks[(unsigned)formId].engine = EngineScope::currentEngine();
        ENGINE_OWN_DATA()->formCallbacks[(unsigned)formId].func = args[1].asFunction();
        
        return Number::newNumber(formId);
    }
    catch (const JSON_VALUE::exception& e)
    {
        ERROR("Fail to parse Json string in sendCustomForm!");
        ERRPRINT(e.what());

        return Local<Value>();
    }
    CATCH("Fail in sendCustomForm!");
}

Local<Value> PlayerClass::sendForm(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[1], ValueKind::kFunction);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        int formId = 0;
        auto jsonForm = SimpleFormClass::extract(args[0]);
        if(jsonForm == nullptr)
            jsonForm = CustomFormClass::extract(args[0]);

        if (jsonForm != nullptr)
        {
            int formId = Raw_SendRawForm(player, jsonForm->dump());
            ENGINE_OWN_DATA()->formCallbacks[(unsigned)formId] = { EngineScope::currentEngine(),Global<Function>(args[1].asFunction()) };

            return Number::newNumber(formId);
        }
        else
        {
            ERROR("Unknown Type of Form Parameter!");
            return Local<Value>();
        }
    }
    catch (const JSON_VALUE::exception& e)
    {
        ERROR("Fail to parse Json string in sendForm!");
        ERRPRINT(e.what());

        return Local<Value>();
    }
    CATCH("Fail in sendForm!");
}

Local<Value> PlayerClass::sendPacket(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kObject);

    try
    {
        Player* player = get();
        if (!player)
            return Local<Value>();
        auto id = PacketClass::_getPacketid(args[0]);
        auto wb = PacketClass::extractPacket(args[0]);
        auto pkt = MyPkt("", (MinecraftPacketIds)id);
        pkt.write(wb);
        Raw_SendPacket(player, &pkt);
    }
    CATCH("Fail in sendPacket");
    return Local<Value>();
}

Local<Value> PlayerClass::setExtraData(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        Player* player = get();
        if (!player)
            return Local<Value>();

        string key = args[0].toStr();
        if(key.empty())
            return Boolean::newBoolean(false);
    
        ENGINE_OWN_DATA()->playerDataDB[Raw_GetPlayerName(player) + "-" + key] = args[1];
        return Boolean::newBoolean(true);
    }
    CATCH("Fail in setExtraData!");
}

Local<Value> PlayerClass::getExtraData(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        Player* player = get();
        if (!player)
            return Local<Value>();

        string key = args[0].toStr();
        if (key.empty())
            return Boolean::newBoolean(false);

        return ENGINE_OWN_DATA()->playerDataDB.at(Raw_GetPlayerName(player) + "-" + key).get();
    }
    catch (const std::out_of_range& e)
    {
        return Local<Value>();
    }
    CATCH("Fail in getExtraData!");
}

Local<Value> PlayerClass::delExtraData(const Arguments& args)
{
    CHECK_ARGS_COUNT(args,1)
    CHECK_ARG_TYPE(args[0],ValueKind::kString)

    try
    {
        Player* player = get();
        if (!player)
            return Local<Value>();

        string key = args[0].toStr();
        if(key.empty())
            return Boolean::newBoolean(false);
    
        ENGINE_OWN_DATA()->playerDataDB.erase(Raw_GetPlayerName(player) + "-" + key);
        return Boolean::newBoolean(true);
    }
    CATCH("Fail in delExtraData!")
}

Local<Value> PlayerClass::hurt(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        int damage = args[0].toInt();
        return Boolean::newBoolean(Raw_HurtPlayer(player, damage));
    }
    CATCH("Fail in hurt!");
}

Local<Value> PlayerClass::setOnFire(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        int time = args[0].toInt();
        bool result = Raw_SetOnFire((Actor*)player, time);
        return Boolean::newBoolean(result);
    }
    CATCH("Fail in setOnFire!");
}

Local<Value> PlayerClass::refreshChunks(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_RefrashChunks(player));
    }
    CATCH("Fail in setOnFire!");
}

Local<Value> PlayerClass::giveItem(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        auto item = ItemClass::extract(args[0]);
        if (!item)
            return Local<Value>();    //Null

        return Boolean::newBoolean(Raw_GiveItem(player,item));
    }
    CATCH("Fail in giveItem!");
}

Local<Value> PlayerClass::clearItem(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Number::newNumber(Raw_ClearItem(player, args[0].toStr()));
    }
    CATCH("Fail in clearItem!");
}

Local<Value> PlayerClass::getNbt(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return NbtCompoundClass::pack(Tag::fromActor((Actor*)player));
    }
    CATCH("Fail in getNbt!")
}

Local<Value> PlayerClass::setNbt(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        auto nbt = NbtCompoundClass::extract(args[0]);
        if (!nbt)
            return Local<Value>();    //Null

        return Boolean::newBoolean(nbt->setPlayer(player));
    }
    CATCH("Fail in setNbt!")
}

Local<Value> PlayerClass::addTag(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_AddTag(player, args[0].toStr()));
    }
    CATCH("Fail in addTag!");
}

Local<Value> PlayerClass::removeTag(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_RemoveTag(player, args[0].toStr()));
    }
    CATCH("Fail in removeTag!");
}

Local<Value> PlayerClass::hasTag(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        return Boolean::newBoolean(Raw_EntityHasTag((Actor*)player, args[0].toStr()));
    }
    CATCH("Fail in hasTag!");
}

Local<Value> PlayerClass::getAllTags(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        auto res = Raw_EntityGetAllTags((Actor*)player);
        Local<Array> arr = Array::newArray();
        for (auto& tag : res)
            arr.add(String::newString(tag));
        return arr;
    }
    CATCH("Fail in getAllTags!");
}

Local<Value> PlayerClass::getAbilities(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        auto list = Tag::fromActor(player)->asCompound();
        try
        {
            return Tag2Value(&list.at("abilities"), true);
        }
        catch (...)
        {
            return Object::newObject();
        }
    }
    CATCH("Fail in getAbilities!");
}

Local<Value> PlayerClass::getAttributes(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        Local<Array> res = Array::newArray();

        auto list = Tag::fromActor(player)->asCompound();
        try
        {
            auto attr = list.at("Attributes").asList();

            Local<Array> arr = Array::newArray();
            for (auto& tag : attr)
            {
                arr.add(Tag2Value(tag, true));
            }
            return arr;
        }
        catch (...)
        {
            return Array::newArray();
        }
    }
    CATCH("Fail in getAttributes!");
}


//////////////////// For Compatibility ////////////////////

Local<Value> PlayerClass::getAllItems(const Arguments& args)
{
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        ItemStack* hand = Raw_GetHand(player);
        ItemStack* offHand = Raw_GetOffHand(player);
        vector<ItemStack*> inventory = Raw_GetAllSlots(Raw_GetInventory(player));
        vector<ItemStack*> armor = Raw_GetAllSlots(Raw_GetArmor(player));
        vector<ItemStack*> endChest = Raw_GetAllSlots(Raw_GetEnderChest(player));

        Local<Object> result = Object::newObject();

        //hand
        result.set("hand", ItemClass::newItem(hand));

        //offHand
        result.set("offHand", ItemClass::newItem(offHand));

        //inventory
        Local<Array> inventoryArr = Array::newArray();
        for (ItemStack* item : inventory)
        {
            inventoryArr.add(ItemClass::newItem(item));
        }
        result.set("inventory", inventoryArr);

        //armor
        Local<Array> armorArr = Array::newArray();
        for (ItemStack* item : armor)
        {
            armorArr.add(ItemClass::newItem(item));
        }
        result.set("armor", armorArr);

        //endChest
        Local<Array> endChestArr = Array::newArray();
        for (ItemStack* item : endChest)
        {
            endChestArr.add(ItemClass::newItem(item));
        }
        result.set("endChest", endChestArr);

        return result;
    }
    CATCH("Fail in getAllItems!")
}

Local<Value> PlayerClass::removeItem(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    try {
        Player* player = get();
        if (!player)
            return Local<Value>();

        int inventoryId = args[0].toInt();
        int count = args[1].toInt();

        bool result = Raw_RemoveItem(Raw_GetInventory(player), inventoryId, count);
        return Boolean::newBoolean(result);
    }
    CATCH("Fail in removeItem!")
}