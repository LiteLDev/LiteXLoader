#include "EventAPI.h"
#include "McAPI.h"
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <exception>
#include <cstdarg>
#include <Kernel/Global.h>
#include <Kernel/Base.h>
#include <Kernel/Block.h>
#include <Kernel/BlockEntity.h>
#include <Kernel/Item.h>
#include <Kernel/Entity.h>
#include <Kernel/Player.h>
#include <Kernel/SymbolHelper.h>
#include <Kernel/Scoreboard.h>
#include <Kernel/Packet.h>
#include <Kernel/Global.h>
#include <Engine/TimeTaskSystem.h>
#include <Engine/PluginHotManage.h>
#include <Engine/EngineOwnData.h>
#include <Engine/GlobalShareData.h>
#include <Engine/LocalShareData.h>
#include "APIHelp.h"
#include "BaseAPI.h"
#include "BlockAPI.h"
#include "GuiAPI.h"
#include "CommandAPI.h"
#include "ItemAPI.h"
#include "EntityAPI.h"
#include "PlayerAPI.h"
#include <Loader.h>
#include <Configs.h>
#include <CheckNotice.h>
#include <AutoUpdate.h>
using namespace std;
using namespace script;

//////////////////// Listeners ////////////////////

enum class EVENT_TYPES : int
{
    onPreJoin=0, onJoin, onLeft, onPlayerCmd, onChat, onPlayerDie, 
    onRespawn, onChangeDim, onJump, onSneak, onAttack, onEat, onMove, onSpawnProjectile,
    onFireworkShootWithCrossbow, onSetArmor, onRide, onStepOnPressurePlate,
    onUseItem, onTakeItem, onDropItem, onUseItemOn, onInventoryChange, onChangeArmorStand,
    onStartDestroyBlock, onDestroyBlock, onWitherBossDestroy, onPlaceBlock, onBedExplode, onRespawnAnchorExplode, onLiquidFlow,
    onOpenContainer, onCloseContainer, onContainerChange, onOpenContainerScreen, 
    onMobDie, onMobHurt, onExplode, onBlockExploded, onCmdBlockExecute, onRedStoneUpdate, onProjectileHitEntity,
    onProjectileHitBlock, onBlockInteracted, onUseRespawnAnchor, onFarmLandDecay, onUseFrameBlock,
    onPistonPush, onHopperSearchItem, onHopperPushOut, onFireSpread, onNpcCmd,
    onScoreChanged, onServerStarted, onConsoleCmd, onFormSelected, onConsoleOutput, onTick,
    onMoneyAdd, onMoneyReduce, onMoneyTrans, onMoneySet, onConsumeTotem, onEffectAdded, onEffectUpdated, onEffectRemoved,
    EVENT_COUNT
};
static const std::unordered_map<string, EVENT_TYPES> EventsMap{
    {"onPreJoin",EVENT_TYPES::onPreJoin},
    {"onJoin",EVENT_TYPES::onJoin},
    {"onLeft",EVENT_TYPES::onLeft},
    {"onPlayerCmd",EVENT_TYPES::onPlayerCmd},
    {"onChat",EVENT_TYPES::onChat},
    {"onPlayerDie",EVENT_TYPES::onPlayerDie},
    {"onRespawn",EVENT_TYPES::onRespawn},
    {"onChangeDim",EVENT_TYPES::onChangeDim},
    {"onJump",EVENT_TYPES::onJump},
    {"onSneak",EVENT_TYPES::onSneak},
    {"onAttack",EVENT_TYPES::onAttack},
    {"onEat",EVENT_TYPES::onEat},
    {"onMove",EVENT_TYPES::onMove},
    {"onSpawnProjectile",EVENT_TYPES::onSpawnProjectile},
    {"onFireworkShootWithCrossbow",EVENT_TYPES::onFireworkShootWithCrossbow},
    {"onSetArmor",EVENT_TYPES::onSetArmor},
    {"onRide",EVENT_TYPES::onRide},
    {"onStepOnPressurePlate",EVENT_TYPES::onStepOnPressurePlate},
    {"onMobDie",EVENT_TYPES::onMobDie},
    {"onMobHurt",EVENT_TYPES::onMobHurt},
    {"onUseItem",EVENT_TYPES::onUseItem},
    {"onTakeItem",EVENT_TYPES::onTakeItem},
    {"onDropItem",EVENT_TYPES::onDropItem},
    {"onUseItemOn",EVENT_TYPES::onUseItemOn},
    {"onInventoryChange",EVENT_TYPES::onInventoryChange},
    {"onChangeArmorStand",EVENT_TYPES::onChangeArmorStand},
    {"onStartDestroyBlock",EVENT_TYPES::onStartDestroyBlock},
    {"onDestroyBlock",EVENT_TYPES::onDestroyBlock},
    {"onWitherBossDestroy",EVENT_TYPES::onWitherBossDestroy},
    {"onPlaceBlock",EVENT_TYPES::onPlaceBlock},
    {"onExplode",EVENT_TYPES::onExplode},
    {"onBedExplode",EVENT_TYPES::onBedExplode},
    {"onRespawnAnchorExplode",EVENT_TYPES::onRespawnAnchorExplode},
    {"onLiquidFlow",EVENT_TYPES::onLiquidFlow},
    {"onBlockExploded",EVENT_TYPES::onBlockExploded},
    {"onOpenContainer",EVENT_TYPES::onOpenContainer},
    {"onCloseContainer",EVENT_TYPES::onCloseContainer},
    {"onContainerChangeSlot",EVENT_TYPES::onContainerChange},
    {"onContainerChange",EVENT_TYPES::onContainerChange},
    {"onOpenContainerScreen",EVENT_TYPES::onOpenContainerScreen},
    {"onCmdBlockExecute",EVENT_TYPES::onCmdBlockExecute},
    {"onRedStoneUpdate",EVENT_TYPES::onRedStoneUpdate},
    {"onProjectileHitBlock",EVENT_TYPES::onProjectileHitBlock},
    {"onProjectileHitEntity",EVENT_TYPES::onProjectileHitEntity},
    {"onBlockInteracted",EVENT_TYPES::onBlockInteracted},
    {"onUseRespawnAnchor",EVENT_TYPES::onUseRespawnAnchor},
    {"onFarmLandDecay",EVENT_TYPES::onFarmLandDecay},
    {"onUseFrameBlock",EVENT_TYPES::onUseFrameBlock},
    {"onPistonPush",EVENT_TYPES::onPistonPush},
    {"onHopperSearchItem",EVENT_TYPES::onHopperSearchItem},
    {"onHopperPushOut",EVENT_TYPES::onHopperPushOut},
    {"onFireSpread",EVENT_TYPES::onFireSpread},
    {"onNpcCmd",EVENT_TYPES::onNpcCmd},
    {"onScoreChanged",EVENT_TYPES::onScoreChanged},
    {"onServerStarted",EVENT_TYPES::onServerStarted},
    {"onConsoleCmd",EVENT_TYPES::onConsoleCmd},
    {"onConsoleOutput",EVENT_TYPES::onConsoleOutput},
    {"onTick",EVENT_TYPES::onTick},
    {"onMoneyAdd",EVENT_TYPES::onMoneyAdd},
    {"onMoneyReduce",EVENT_TYPES::onMoneyReduce},
    {"onMoneyTrans",EVENT_TYPES::onMoneyTrans},
    {"onMoneySet",EVENT_TYPES::onMoneySet},
    {"onFormSelected",EVENT_TYPES::onFormSelected},
    {"onConsumeTotem",EVENT_TYPES::onConsumeTotem},
    {"onEffectAdded",EVENT_TYPES::onEffectAdded},
    {"onEffectRemoved",EVENT_TYPES::onEffectRemoved},
    {"onEffectUpdated",EVENT_TYPES::onEffectUpdated}
};
struct ListenerListType
{
    ScriptEngine *engine;
    Global<Function> func;
};
//监听器表
static std::list<ListenerListType> listenerList[int(EVENT_TYPES::EVENT_COUNT)];

//监听器异常拦截
string EventTypeToString(EVENT_TYPES e)
{
    for (auto& [k, v] : EventsMap)
        if (v == e)
            return k;
    return "Unknown";
}

#define LISTENER_CATCH(TYPE) \
    catch(const Exception& e) \
    { \
        ERROR("Event Callback Failed!"); \
        ERRPRINT(e); \
        ERROR("In Event: " + EventTypeToString(TYPE)); \
        ERROR("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
    } \
    catch (const std::exception& e) \
    { \
        ERROR("Event Callback Failed!"); \
        ERROR("C++ Uncaught Exception Detected!"); \
        ERRPRINT(e.what()); \
        ERROR("In Event: " + EventTypeToString(TYPE)); \
        ERROR("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
    } \
    catch (const seh_exception& e) \
    { \
        ERROR("Event Callback Failed!"); \
        ERROR("SEH Uncaught Exception Detected!"); \
        ERRPRINT(e.what()); \
        ERROR("In Event: " + EventTypeToString(TYPE)); \
        ERROR("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
    } \

//调用事件监听函数，拦截不执行original
#define CallEventRtnVoid(TYPE,...) \
    std::list<ListenerListType> &nowList = listenerList[int(TYPE)]; \
    bool passToBDS = true; \
    for(auto &listener : nowList) { \
        EngineScope enter(listener.engine); \
        try{ \
            auto result = listener.func.get().call({},__VA_ARGS__); \
            if(result.isBoolean() && result.asBoolean().value() == false) \
                passToBDS = false; \
        } \
        LISTENER_CATCH(TYPE) \
    }\
    if(!passToBDS) { return; }

//调用事件监听函数，拦截返回false
#define CallEventRtnBool(TYPE,...) \
    std::list<ListenerListType> &nowList = listenerList[int(TYPE)]; \
    bool passToBDS = true; \
    for(auto &listener : nowList) { \
        EngineScope enter(listener.engine); \
        try{ \
            auto result = listener.func.get().call({},__VA_ARGS__); \
            if(result.isBoolean() && result.asBoolean().value() == false) \
                passToBDS = false; \
        } \
        LISTENER_CATCH(TYPE) \
    }\
    if(!passToBDS) { return false; }

//调用事件监听函数，拦截返回RETURN_VALUE
#define CallEventRtnValue(TYPE,RETURN_VALUE,...) \
    std::list<ListenerListType> &nowList = listenerList[int(TYPE)]; \
    bool passToBDS = true; \
    for(auto &listener : nowList) { \
        EngineScope enter(listener.engine); \
        try{ \
            auto result = listener.func.get().call({},__VA_ARGS__); \
            if(result.isBoolean() && result.asBoolean().value() == false) \
                passToBDS = false; \
        } \
        LISTENER_CATCH(TYPE) \
    }\
    if(!passToBDS) { return RETURN_VALUE; }

//模拟事件调用监听
#define FakeCallEvent(ENGINE,TYPE,...) \
    { \
        std::list<ListenerListType>& nowList = listenerList[int(TYPE)]; \
        for (auto &listener : nowList) { \
            if (listener.engine == ENGINE) { \
                EngineScope enter(listener.engine); \
                try { listener.func.get().call({},__VA_ARGS__); } \
                LISTENER_CATCH(TYPE) \
                break; \
            } \
        } \
    }

//延迟调用事件
#define CallEventDelayed(TYPE,...) \
    std::list<ListenerListType> &nowList = listenerList[int(TYPE)]; \
    for(auto &listener : nowList) { \
        EngineScope enter(listener.engine); \
        try{ \
            NewTimeout(listener.func.get(), { __VA_ARGS__ }, 5); \
        } \
        LISTENER_CATCH(TYPE) \
    }\

//异常检查
#define IF_LISTENED(TYPE) if(!listenerList[int(TYPE)].empty()) { try
#define IF_LISTENED_END(TYPE) \
    catch(...) \
    { \
        ERROR("Event Callback Failed!"); \
        ERROR("Uncaught Exception Detected!"); \
        ERROR("In Event: " + EventTypeToString(TYPE)); \
    } }


//////////////////// APIs ////////////////////

Local<Value> McClass::listen(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kFunction);

    try{
        return Boolean::newBoolean(LxlAddEventListener(EngineScope::currentEngine(),args[0].toStr(),args[1].asFunction()));
    }
    CATCH("Fail to Bind Listener!");
}


//////////////////// Funcs ////////////////////

bool LxlAddEventListener(ScriptEngine *engine, const string &eventName, const Local<Function> &func)
{
    try {
        int eventId = int(EventsMap.at(eventName));
        listenerList[eventId].push_back({ engine,Global<Function>(func) });
        return true;
    }
    catch (const std::logic_error& e)
    {
        ERROR("Event \"" + eventName + "\" No Found!\n");
        return false;
    }
}

bool LxlRemoveAllEventListeners(ScriptEngine* engine)
{
    for (auto& listeners : listenerList)
    {
        listeners.remove_if([engine](auto& listener) {
            return listener.engine == engine;
        });
    }
    return true;
}

bool LxlCallEventsOnHotLoad(ScriptEngine* engine)
{
    FakeCallEvent(engine, EVENT_TYPES::onServerStarted);

    auto players = Raw_GetOnlinePlayers();
    for (auto& pl : players)
        FakeCallEvent(engine, EVENT_TYPES::onPreJoin, PlayerClass::newPlayer(pl));
    for(auto &pl : players)
        FakeCallEvent(engine, EVENT_TYPES::onJoin, PlayerClass::newPlayer(pl));

    return true;
}

bool LxlCallEventsOnHotUnload(ScriptEngine* engine)
{
    auto players = Raw_GetOnlinePlayers();
    for (auto& pl : players)
        FakeCallEvent(engine, EVENT_TYPES::onLeft, PlayerClass::newPlayer(pl));

    return true;
}

//////////////////// Hook ////////////////////

void InitEventListeners()
{
// ===== onPreJoin =====
    Event::addEventListener([](JoinEV ev)
    {
        IF_LISTENED(EVENT_TYPES::onPreJoin)
        {
            CallEventRtnVoid(EVENT_TYPES::onPreJoin, PlayerClass::newPlayer(ev.Player));
        }
        IF_LISTENED_END(EVENT_TYPES::onPreJoin);
    });

// ===== onLeft =====
    Event::addEventListener([](LeftEV ev)
    {
        IF_LISTENED(EVENT_TYPES::onLeft)
        {
            CallEventRtnVoid(EVENT_TYPES::onLeft, PlayerClass::newPlayer(ev.Player));
        }
        IF_LISTENED_END(EVENT_TYPES::onLeft);
    });

// ===== onChat =====
    Event::addEventListener([](ChatEV ev)
    {
        IF_LISTENED(EVENT_TYPES::onChat)
        {
            CallEventRtnBool(EVENT_TYPES::onChat, PlayerClass::newPlayer(ev.pl), ev.msg);
        }
        IF_LISTENED_END(EVENT_TYPES::onChat);
        return true;
    });

// ===== onMobDie =====
    Event::addEventListener([](MobDieEV ev)
    {
        IF_LISTENED(EVENT_TYPES::onMobDie)
        {
            if (ev.mob)
            {
                CallEventRtnVoid(EVENT_TYPES::onMobDie, EntityClass::newEntity(ev.mob),
                    (ev.DamageSource ? EntityClass::newEntity(ev.DamageSource) : Local<Value>()));
            }
        }
        IF_LISTENED_END(EVENT_TYPES::onMobDie);
    });

// For RegisterCmd...
    Event::addEventListener([](RegCmdEV ev)
    {
        CmdReg = ev.CMDRg;
        isCmdRegisterEnabled = true;

        //处理延迟注册
        ProcessRegCmdQueue();
    });


// ===== onServerStarted =====
    Event::addEventListener([](ServerStartedEV ev)
    {
        //标记已启动
        if (!isServerStarted)
        {
            isServerStarted = true;

            //注册预置命令
            RegisterBuiltinCmds();

            //更新检查
            if (localShareData->isFirstInstance)
            {
                InitAutoUpdateCheck();
                CheckNotice();
            }

            IF_LISTENED(EVENT_TYPES::onServerStarted)
            {
                CallEventDelayed(EVENT_TYPES::onServerStarted);
            }
            IF_LISTENED_END(EVENT_TYPES::onServerStarted);
        }
    });
}

// 植入tick
THook(void, "?tick@ServerLevel@@UEAAXXZ",
    void* _this)
{
    try
    {
        for (auto engine : lxlModules)
        {
            EngineScope enter(engine);
            engine->messageQueue()->loopQueue(utils::MessageQueue::LoopType::kLoopOnce);
        }
    }
    catch (...)
    {
        ERROR("Error occurred in Engine Message Loop!");
        ERROR("Uncaught Exception Detected!");
    }

    IF_LISTENED(EVENT_TYPES::onTick)
    {
        CallEventRtnVoid(EVENT_TYPES::onTick);
    }
    IF_LISTENED_END(EVENT_TYPES::onTick);

    return original(_this);
}

// For device information
class ConnectionRequest;
THook(void, "?sendLoginMessageLocal@ServerNetworkHandler@@QEAAXAEBVNetworkIdentifier@@"
    "AEBVConnectionRequest@@AEAVServerPlayer@@@Z",
    ServerNetworkHandler* _this, NetworkIdentifier* ni, ConnectionRequest* cr, ServerPlayer* sp)
{
    try
    {
        string id = "", os = "";
        SymCall("?getDeviceId@ConnectionRequest@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
            void, ConnectionRequest*, string*)(cr, &id);
        int type = SymCall("?getDeviceOS@ConnectionRequest@@QEBA?AW4BuildPlatform@@XZ",
            int, ConnectionRequest*, string*)(cr, &os);

        localShareData->deviceInfoRecord[(uintptr_t)sp] = { id,type };
    }
    catch (const seh_exception& e)
    {
        ERROR("SEH Uncaught Exception Detected!");
        ERRPRINT(e.what());
        ERROR("In Getting Device Information");
    }
    catch (...)
    {
        ;
    }
    return original(_this, ni, cr, sp);
}


// ===== onJoin =====
THook(bool, "?setLocalPlayerAsInitialized@ServerPlayer@@QEAAXXZ",
    ServerPlayer* _this)
{
    IF_LISTENED(EVENT_TYPES::onJoin)
    {
        CallEventRtnBool(EVENT_TYPES::onJoin, PlayerClass::newPlayer(_this));
    }
    IF_LISTENED_END(EVENT_TYPES::onJoin);
    return original(_this);
}

// ===== onAttack =====
THook(bool, "?attack@Player@@UEAA_NAEAVActor@@AEBW4ActorDamageCause@@@Z",
    Player* _this, Actor* ac, int *damageCause)
{
    IF_LISTENED(EVENT_TYPES::onAttack)
    {
        if (ac)
        {
            CallEventRtnBool(EVENT_TYPES::onAttack, PlayerClass::newPlayer(_this), EntityClass::newEntity(ac));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onAttack);
    return original(_this, ac, damageCause);
}

// ===== onEat =====
THook(Item*, "?useTimeDepleted@FoodItemComponentLegacy@@UEAAPEBVItem@@AEAVItemStack@@AEAVPlayer@@AEAVLevel@@@Z",
    class FoodItemComponentLegacy* _this, ItemStack* eaten, Player* player, Level* level)
{
    if (Raw_GetItemTypeName(eaten) != "minecraft:suspicious_stew") {
        IF_LISTENED(EVENT_TYPES::onEat)
        {
            CallEventRtnValue(EVENT_TYPES::onEat, nullptr, PlayerClass::newPlayer(player), ItemClass::newItem(eaten));
        }
        IF_LISTENED_END(EVENT_TYPES::onEat);
    }
    return original(_this, eaten, player, level);
}

// ===== onEat_Unknown =====
THook(Item*, "?useTimeDepleted@FoodItemComponent@@UEAAPEBVItem@@AEAVItemStack@@AEAVPlayer@@AEAVLevel@@@Z",
    class FoodItemComponent* _this, ItemStack* eaten, Player* player, Level* level)
{
    IF_LISTENED(EVENT_TYPES::onEat)
    {
        CallEventRtnValue(EVENT_TYPES::onEat, nullptr, PlayerClass::newPlayer(player), ItemClass::newItem(eaten));
    }
    IF_LISTENED_END(EVENT_TYPES::onEat);
    return original(_this, eaten, player, level);
}

// ===== onEat_SuspiciousStew =====
THook(Item*, "?useTimeDepleted@SuspiciousStewItem@@UEBA?AW4ItemUseMethod@@AEAVItemStack@@PEAVLevel@@PEAVPlayer@@@Z",
    class SuspiciousStewItem* _this, ItemStack* eaten, Level* level, Player* player)
{
    IF_LISTENED(EVENT_TYPES::onEat)
    {
        CallEventRtnValue(EVENT_TYPES::onEat, nullptr, PlayerClass::newPlayer(player), ItemClass::newItem(eaten));
    }
    IF_LISTENED_END(EVENT_TYPES::onEat);
    return original(_this, eaten, level, player);
}

// ===== onEat_Potion =====
THook(Item*, "?useTimeDepleted@PotionItem@@UEBA?AW4ItemUseMethod@@AEAVItemStack@@PEAVLevel@@PEAVPlayer@@@Z",
    class PotionItem* _this, ItemStack* item, Level* level, Player* player)
{
    IF_LISTENED(EVENT_TYPES::onEat)
    {
        CallEventRtnValue(EVENT_TYPES::onEat, nullptr, PlayerClass::newPlayer(player), ItemClass::newItem(item));
    }
    IF_LISTENED_END(EVENT_TYPES::onEat);
    return original(_this, item, level, player);
}

// ===== onEat_Medicine =====
THook(Item*, "?useTimeDepleted@MedicineItem@@UEBA?AW4ItemUseMethod@@AEAVItemStack@@PEAVLevel@@PEAVPlayer@@@Z",
    class MedicineItem* _this, ItemStack* item, Level* level, Player* player)
{
    IF_LISTENED(EVENT_TYPES::onEat)
    {
        CallEventRtnValue(EVENT_TYPES::onEat, nullptr, PlayerClass::newPlayer(player), ItemClass::newItem(item));
    }
    IF_LISTENED_END(EVENT_TYPES::onEat);
    return original(_this, item, level, player);
}

// ===== onEat_Milk =====
THook(Item*, "?useTimeDepleted@BucketItem@@UEBA?AW4ItemUseMethod@@AEAVItemStack@@PEAVLevel@@PEAVPlayer@@@Z",
    class BucketItem* _this, ItemStack* item, Level* level, Player* player)
{
    IF_LISTENED(EVENT_TYPES::onEat)
    {
        CallEventRtnValue(EVENT_TYPES::onEat, nullptr, PlayerClass::newPlayer(player), ItemClass::newItem(item));
    }
    IF_LISTENED_END(EVENT_TYPES::onEat);
    return original(_this, item, level, player);
}

// ===== onMove =====
THook(void, "?sendPlayerMove@PlayerEventCoordinator@@QEAAXAEAVPlayer@@@Z",
    void *_this, Player* pl)
{
    IF_LISTENED(EVENT_TYPES::onMove)
    {
        if (Raw_EntityIsMoving((Actor*)pl))
        {
            CallEventRtnVoid(EVENT_TYPES::onMove, PlayerClass::newPlayer(pl), FloatPos::newPos(Raw_GetPlayerPos(pl)));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onMove);
    return original(_this, pl);
}

// ===== onChangeDim =====
THook(void*, "?changeDimension@ServerPlayer@@UEAAXV?$AutomaticID@VDimension@@H@@_N@Z",
    Actor* ac, unsigned int a3)
{
    IF_LISTENED(EVENT_TYPES::onChangeDim)
    {
        CallEventRtnValue(EVENT_TYPES::onChangeDim, original(ac, a3), PlayerClass::newPlayer((Player*)ac), Number::newNumber((int)a3));
    }
    IF_LISTENED_END(EVENT_TYPES::onChangeDim);
    return original(ac, a3);
}

// ===== onPlayerDie =====
THook(void, "?die@Player@@UEAAXAEBVActorDamageSource@@@Z",
    Player* _this, ActorDamageSource* src)
{
    IF_LISTENED(EVENT_TYPES::onPlayerDie)
    {
        if (_this)
        {
            Actor* source = Raw_GetDamageSourceEntity(src);
            CallEventRtnVoid(EVENT_TYPES::onPlayerDie, PlayerClass::newPlayer(_this),
                (source ? EntityClass::newEntity(source) : Local<Value>()));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onPlayerDie);
    return original(_this, src);
}

// ===== onSpawnProjectile =====
THook(Actor*, "?spawnProjectile@Spawner@@QEAAPEAVActor@@AEAVBlockSource@@AEBUActorDefinitionIdentifier@@PEAV2@AEBVVec3@@3@Z",
    void* _this, BlockSource* a2, ActorDefinitionIdentifier* a3, Actor* a4, Vec3* a5, Vec3* a6)
{
    IF_LISTENED(EVENT_TYPES::onSpawnProjectile)
    {
        string name = a3->fullname;
        CallEventRtnValue(EVENT_TYPES::onSpawnProjectile, nullptr, EntityClass::newEntity(a4), String::newString(name.substr(0,name.length()-2)));
    }
    IF_LISTENED_END(EVENT_TYPES::onSpawnProjectile);
    return original(_this, a2, a3, a4, a5, a6);
}

// ===== onFireworkShootWithCrossbow =====
THook(void, "?_shootFirework@CrossbowItem@@AEBAXAEBVItemInstance@@AEAVPlayer@@@Z",
    void* a1, void* a2, Player* a3)
{
    IF_LISTENED(EVENT_TYPES::onFireworkShootWithCrossbow)
    {
        CallEventRtnVoid(EVENT_TYPES::onFireworkShootWithCrossbow, PlayerClass::newPlayer(a3));
    }
    IF_LISTENED_END(EVENT_TYPES::onFireworkShootWithCrossbow);
    original(a1, a2, a3);
}

// ===== onSetArmor =====
THook(void, "?setArmor@Player@@UEAAXW4ArmorSlot@@AEBVItemStack@@@Z",
    Player* _this, unsigned slot, ItemStack* it)
{
    IF_LISTENED(EVENT_TYPES::onSetArmor)
    {
        if (Raw_IsPlayerValid(_this))
        {
            CallEventRtnVoid(EVENT_TYPES::onSetArmor, PlayerClass::newPlayer(_this), Number::newNumber((int)slot), ItemClass::newItem(it));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onSetArmor);
    return original(_this, slot, it);
}

// ===== onRide =====
THook(bool, "?canAddRider@Actor@@UEBA_NAEAV1@@Z",
    Actor* a1, Actor* a2)
{
    IF_LISTENED(EVENT_TYPES::onRide)
    {
        CallEventRtnBool(EVENT_TYPES::onRide, EntityClass::newEntity(a2), EntityClass::newEntity(a1));
    }
        IF_LISTENED_END(EVENT_TYPES::onRide);
    return original(a1, a2);
}

// ===== onStepOnPressurePlate =====
THook(void, "?entityInside@BasePressurePlateBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@AEAVActor@@@Z",
    void* _this, BlockSource* a2, BlockPos* a3, Actor* a4)
{
    IF_LISTENED(EVENT_TYPES::onStepOnPressurePlate)
    {
        Block* bl = Raw_GetBlockByPos(a3, a2);
        CallEventRtnVoid(EVENT_TYPES::onStepOnPressurePlate, EntityClass::newEntity(a4), BlockClass::newBlock(bl, a3, a2));
    }
    IF_LISTENED_END(EVENT_TYPES::onStepOnPressurePlate);
    original(_this, a2, a3, a4);
}


// ===== onRespawn =====
THook(bool, "?respawn@Player@@UEAAXXZ",
    Player* pl)
{
    IF_LISTENED(EVENT_TYPES::onRespawn)
    {
        CallEventRtnBool(EVENT_TYPES::onRespawn, PlayerClass::newPlayer(pl));
    }
    IF_LISTENED_END(EVENT_TYPES::onRespawn);
    return original(pl);
}

// ===== onJump =====
THook(void, "?jumpFromGround@Player@@UEAAXXZ",
    Player* pl)
{
    IF_LISTENED(EVENT_TYPES::onJump)
    {
        CallEventRtnVoid(EVENT_TYPES::onJump, PlayerClass::newPlayer(pl));
    }
    IF_LISTENED_END(EVENT_TYPES::onJump);
    return original(pl);
}

// ===== onSneak =====
THook(void, "?sendActorSneakChanged@ActorEventCoordinator@@QEAAXAEAVActor@@_N@Z",
    void* _this, Actor* ac, bool isSneaking)
{
    IF_LISTENED(EVENT_TYPES::onSneak)
    {
        CallEventRtnVoid(EVENT_TYPES::onSneak, PlayerClass::newPlayer((Player*)ac), Boolean::newBoolean(isSneaking));
    }
    IF_LISTENED_END(EVENT_TYPES::onSneak);
    return original(_this, ac, isSneaking);
}

// ===== onDropItem =====
THook(bool, "?drop@Player@@UEAA_NAEBVItemStack@@_N@Z",
    Player* _this, ItemStack* a2, bool a3)
{
    IF_LISTENED(EVENT_TYPES::onDropItem)
    {
        CallEventRtnBool(EVENT_TYPES::onDropItem, PlayerClass::newPlayer(_this), ItemClass::newItem(a2));       //###### Q lost items ######
    }
    IF_LISTENED_END(EVENT_TYPES::onDropItem);
    return original(_this, a2, a3);
}

// ===== onTakeItem =====
THook(bool, "?take@Player@@QEAA_NAEAVActor@@HH@Z",
    Player* _this, Actor* actor, int a2, int a3)
{
    IF_LISTENED(EVENT_TYPES::onTakeItem)
    {
        ItemStack* it = (ItemStack*)((uintptr_t)actor + 1856);      //IDA Player::take
        CallEventRtnBool(EVENT_TYPES::onTakeItem, PlayerClass::newPlayer(_this), EntityClass::newEntity(actor), ItemClass::newItem(it));
    }
    IF_LISTENED_END(EVENT_TYPES::onTakeItem);
    return original(_this, actor, a2, a3);
}

// ===== onUseItem =====
THook(bool, "?baseUseItem@GameMode@@QEAA_NAEAVItemStack@@@Z", void* _this, ItemStack& item)
{
    IF_LISTENED(EVENT_TYPES::onUseItem)
    {
        auto sp = dAccess<ServerPlayer*, 8>(_this);

        CallEventRtnBool(EVENT_TYPES::onUseItem, PlayerClass::newPlayer(sp), ItemClass::newItem(&item));
    }
    IF_LISTENED_END(EVENT_TYPES::onUseItem);
    return original(_this, item);
}

// ===== onUseItemOn =====
THook(bool, "?useItemOn@GameMode@@UEAA_NAEAVItemStack@@AEBVBlockPos@@EAEBVVec3@@PEBVBlock@@@Z",
    void* _this, ItemStack* item, BlockPos* bp, unsigned char side, Vec3* a5, Block* bl)
{
    IF_LISTENED(EVENT_TYPES::onUseItemOn)
    {
        auto sp = dAccess<ServerPlayer*, 8>(_this);

        CallEventRtnBool(EVENT_TYPES::onUseItemOn, PlayerClass::newPlayer(sp), ItemClass::newItem(item), BlockClass::newBlock(bl, bp, WPlayer(*sp).getDimID()), Number::newNumber(side));
    }
    IF_LISTENED_END(EVENT_TYPES::onUseItemOn);
    return original(_this, item, bp, side, a5, bl);
}

// ===== onConsumeTotem =====
THook(void, "?consumeTotem@Player@@UEAA_NXZ", Player* player)
{
    IF_LISTENED(EVENT_TYPES::onConsumeTotem)
    {
        CallEventRtnVoid(EVENT_TYPES::onConsumeTotem, PlayerClass::newPlayer(player));
    }
    IF_LISTENED_END(EVENT_TYPES::onConsumeTotem);
    return original(player);
}

// ===== onEffectAdded =====
THook(void, "?onEffectAdded@ServerPlayer@@MEAAXAEAVMobEffectInstance@@@Z", Player* player, void* effect)
{
    IF_LISTENED(EVENT_TYPES::onEffectAdded)
    {
        HashedString* effectName = SymCall("?getComponentName@MobEffectInstance@@QEBAAEBVHashedString@@XZ", HashedString*, void*)(effect);
        CallEventRtnVoid(EVENT_TYPES::onEffectAdded, PlayerClass::newPlayer(player) , effectName->getString());
    }
    IF_LISTENED_END(EVENT_TYPES::onEffectAdded);
    return original(player,effect);
}

// ===== onEffectRemoved =====
THook(void, "?onEffectRemoved@ServerPlayer@@MEAAXAEAVMobEffectInstance@@@Z", Player* player, void* effect)
{
    IF_LISTENED(EVENT_TYPES::onEffectRemoved)
    {
        HashedString* effectName = SymCall("?getComponentName@MobEffectInstance@@QEBAAEBVHashedString@@XZ", HashedString*, void*)(effect);
        CallEventRtnVoid(EVENT_TYPES::onEffectRemoved, PlayerClass::newPlayer(player), effectName->getString());
    }
    IF_LISTENED_END(EVENT_TYPES::onEffectRemoved);
    return original(player, effect);
}

// ===== onEffectUpdated =====
THook(void, "?onEffectUpdated@ServerPlayer@@MEAAXAEAVMobEffectInstance@@@Z", Player* player, void* effect)
{
    IF_LISTENED(EVENT_TYPES::onEffectUpdated)
    {
        HashedString* effectName = SymCall("?getComponentName@MobEffectInstance@@QEBAAEBVHashedString@@XZ", HashedString*, void*)(effect);
        CallEventRtnVoid(EVENT_TYPES::onEffectUpdated, PlayerClass::newPlayer(player), effectName->getString());
    }
    IF_LISTENED_END(EVENT_TYPES::onEffectUpdated);
    return original(player, effect);
}

/* onTurnLectern // 由于还是不能拦截掉书，暂时注释
THook(void, "?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVLecternUpdatePacket@@@Z",
    ServerNetworkHandler* handler, NetworkIdentifier* id, Packet* pkt)
{
    IF_LISTENED(EVENT_TYPES::onTurnLectern)
    {
        // Packet* pkt = *(Packet**)pPacket;
        Player* player = Raw_GetPlayerFromPacket(handler, id, pkt);
        if (!player)
            return;

        int page = *((DWORD*)pkt + 12);
        dAccess<bool>(pkt, 56) = false;
        bool shouldDropBook = *((BYTE*)pkt + 56);
        int totalPages = *((DWORD*)pkt + 13);
        auto* bp = new BlockPos;
        bp->x = *((DWORD*)pkt + 15);
        bp->y = *((DWORD*)pkt + 16);
        bp->z = *((DWORD*)pkt + 17);
        CallEventRtnVoid(EVENT_TYPES::onTurnLectern, PlayerClass::newPlayer(player), IntPos::newPos(bp, Raw_GetPlayerDimId(player)), page, totalPages, Boolean::newBoolean(shouldDropBook));
    }
    IF_LISTENED_END(EVENT_TYPES::onTurnLectern);
    original(handler,id,pkt);
}
*/

// ===== onInventoryChange =====
THook(void, "?inventoryChanged@Player@@UEAAXAEAVContainer@@HAEBVItemStack@@1_N@Z",
    Player* _this, void* container, int slotNumber, ItemStack* oldItem, ItemStack* newItem, bool is)
{
    IF_LISTENED(EVENT_TYPES::onInventoryChange)
    {
        if (Raw_IsPlayerValid(_this))
        {
            CallEventRtnVoid(EVENT_TYPES::onInventoryChange, PlayerClass::newPlayer((Player*)_this), slotNumber,
                ItemClass::newItem(oldItem), ItemClass::newItem(newItem));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onInventoryChange);

    return original(_this, container, slotNumber, oldItem, newItem, is);
}

// ===== onChangeArmorStand =====
THook(bool, "?_trySwapItem@ArmorStand@@AEAA_NAEAVPlayer@@W4EquipmentSlot@@@Z",
    Actor* _this, Player* a2, int a3)
{
    IF_LISTENED(EVENT_TYPES::onChangeArmorStand)
    {
        CallEventRtnBool(EVENT_TYPES::onChangeArmorStand, EntityClass::newEntity(_this), PlayerClass::newPlayer(a2), Number::newNumber(a3));
    }
    IF_LISTENED_END(EVENT_TYPES::onChangeArmorStand);
    return original(_this, a2, a3);
}

// ===== onStartDestroyBlock =====
THook(void, "?sendBlockDestructionStarted@BlockEventCoordinator@@QEAAXAEAVPlayer@@AEBVBlockPos@@@Z",
    void* _this, Player* pl, BlockPos* bp)
{
    IF_LISTENED(EVENT_TYPES::onStartDestroyBlock)
    {
        int dimid = Raw_GetPlayerDimId(pl);
        Block* bl = Raw_GetBlockByPos(bp, dimid);
        CallEventRtnVoid(EVENT_TYPES::onStartDestroyBlock, PlayerClass::newPlayer(pl), 
            BlockClass::newBlock(bl, bp, dimid));
    }
    IF_LISTENED_END(EVENT_TYPES::onStartDestroyBlock);
    return original(_this, pl, bp);
}

// ===== onDestroyBlock =====
THook(bool, "?checkBlockDestroyPermissions@BlockSource@@QEAA_NAEAVActor@@AEBVBlockPos@@AEBVItemStackBase@@_N@Z",
    BlockSource * _this, Actor* pl, BlockPos* pos, ItemStack* a3, bool a4)
{
    IF_LISTENED(EVENT_TYPES::onDestroyBlock)
    {
        auto block = Raw_GetBlockByPos(pos, _this);

        CallEventRtnBool(EVENT_TYPES::onDestroyBlock, PlayerClass::newPlayer((Player*)pl), BlockClass::newBlock(block,pos,_this));
    }
    IF_LISTENED_END(EVENT_TYPES::onDestroyBlock);
    return original(_this, pl, pos,a3, a4);
}

// ===== onWitherBossDestroy =====
THook(void, "?_destroyBlocks@WitherBoss@@AEAAXAEAVLevel@@AEBVAABB@@AEAVBlockSource@@H@Z",
    void* _this, Level* a2, AABB* a3, BlockSource* a4, int a5)
{
    IF_LISTENED(EVENT_TYPES::onWitherBossDestroy)
    {
        auto ac = (Actor*)_this;
        auto dimid = Raw_GetEntityDimId(ac);
        Vec3 posA = a3->p1;
        Vec3 posB = a3->p2;

        CallEventRtnVoid(EVENT_TYPES::onWitherBossDestroy, EntityClass::newEntity(ac), IntPos::newPos(posA.x, posA.y, posA.z, dimid), IntPos::newPos(posB.x, posB.y, posB.z, dimid));
    }
    IF_LISTENED_END(EVENT_TYPES::onWitherBossDestroy);

    original(_this, a2, a3, a4, a5);
}

// ===== onPlaceBlock =====
THook(bool, "?mayPlace@BlockSource@@QEAA_NAEBVBlock@@AEBVBlockPos@@EPEAVActor@@_N@Z",
    BlockSource* _this, Block* a2, BlockPos* a3, unsigned __int8 a4, Actor* a5, bool a6)
{
    IF_LISTENED(EVENT_TYPES::onPlaceBlock)
    {
        if (Raw_IsPlayer(a5))
        {
            CallEventRtnBool(EVENT_TYPES::onPlaceBlock, PlayerClass::newPlayer((Player*)a5), BlockClass::newBlock(a2, a3, _this));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onPlaceBlock);
    return original(_this, a2, a3, a4, a5, a6);
}

// ===== onOpenContainer =====
THook(__int64, "?onPlayerOpenContainer@VanillaServerGameplayEventListener@@UEAA?AW4EventResult@@AEBUPlayerOpenContainerEvent@@@Z",
    void* a1, void* a2)
{
    IF_LISTENED(EVENT_TYPES::onOpenContainer)
    {
        Player* pl = SymCall("??$tryUnwrap@VPlayer@@$$V@WeakEntityRef@@QEBAPEAVPlayer@@XZ", Player*, void*)(a2);
        BlockPos bp = dAccess<BlockPos>(a2, 28);        // IDA VanillaServerGameplayEventListener::onPlayerOpenContainer
        int dim = Raw_GetPlayerDimId(pl);

        CallEventRtnValue(EVENT_TYPES::onOpenContainer, 0, PlayerClass::newPlayer(pl), BlockClass::newBlock(&bp,dim));
    }
    IF_LISTENED_END(EVENT_TYPES::onOpenContainer);
    return original(a1, a2);
}

// ===== onCloseContainer_Chest =====
class ChestBlockActor;
THook(bool, "?stopOpen@ChestBlockActor@@UEAAXAEAVPlayer@@@Z",
    ChestBlockActor* _this, Player* pl)
{
    IF_LISTENED(EVENT_TYPES::onCloseContainer)
    {
        auto ba = (BlockActor*)((char*)_this - 240);        //IDA ChestBlockActor::stopOpen
        auto bp = Raw_GetBlockEntityPos(ba);
        int dim = Raw_GetPlayerDimId(pl);
        BlockSource* bs = Raw_GetBlockSourceByDim(dim);
        Block* bl = Raw_GetBlockByPos(&bp,bs);

        CallEventRtnBool(EVENT_TYPES::onCloseContainer, PlayerClass::newPlayer(pl), BlockClass::newBlock(bl, &bp, dim));
    }
    IF_LISTENED_END(EVENT_TYPES::onCloseContainer);
    return original(_this, pl);
}

// ===== onCloseContainer_Barrel =====
THook(bool, "?stopOpen@BarrelBlockActor@@UEAAXAEAVPlayer@@@Z",
    void* _this, Player* pl)
{
    IF_LISTENED(EVENT_TYPES::onCloseContainer)
    {
        auto ba = (BlockActor*)((char*)_this - 240);       //EventAPI onCloseContainer_Chest
        auto bp = Raw_GetBlockEntityPos(ba);
        int dim = Raw_GetPlayerDimId(pl);
        BlockSource* bs = Raw_GetBlockSourceByDim(dim);
        Block* bl = Raw_GetBlockByPos(&bp, bs);

        CallEventRtnBool(EVENT_TYPES::onCloseContainer, PlayerClass::newPlayer(pl), BlockClass::newBlock(bl, &bp, dim));
    }
    IF_LISTENED_END(EVENT_TYPES::onCloseContainer);
    return original(_this, pl);
}

// ===== onContainerChange =====
class LevelContainerModel;
THook(void, "?_onItemChanged@LevelContainerModel@@MEAAXHAEBVItemStack@@0@Z",
    LevelContainerModel* _this, int slotNumber, ItemStack* oldItem, ItemStack* newItem)
{
    IF_LISTENED(EVENT_TYPES::onContainerChange)
    {
        Player* pl = (Player*) dAccess<Actor*>(_this, 208);            //IDA LevelContainerModel::LevelContainerModel
        if (SymCall("?hasOpenContainer@Player@@QEBA_NXZ", bool, Player*)(pl))
        {
            BlockSource* bs = Raw_GetBlockSourceByActor(pl);
            BlockPos* bpos = (BlockPos*)((char*)_this + 216);
            Block* block = Raw_GetBlockByPos(bpos, bs);

            CallEventRtnVoid(EVENT_TYPES::onContainerChange, PlayerClass::newPlayer(pl), BlockClass::newBlock(block, bpos, bs),
                slotNumber, ItemClass::newItem(oldItem), ItemClass::newItem(newItem));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onContainerChange);
    return original(_this, slotNumber, oldItem, newItem);
}

// ===== onOpenContainerScreen =====
THook(bool, "?canOpenContainerScreen@Player@@UEAA_NXZ",
    Player* a1)
{
    IF_LISTENED(EVENT_TYPES::onOpenContainerScreen)
    {
        CallEventRtnBool(EVENT_TYPES::onOpenContainerScreen, PlayerClass::newPlayer(a1));
    }
    IF_LISTENED_END(EVENT_TYPES::onOpenContainerScreen);
    return original(a1);
}

// ===== onMobHurt =====
THook(bool, "?_hurt@Mob@@MEAA_NAEBVActorDamageSource@@H_N1@Z",
    Mob* ac, ActorDamageSource* ads, int damage, bool unk1_1, bool unk2_0)
{
    IF_LISTENED(EVENT_TYPES::onMobHurt)
    {
        if (ac)
        {
            auto level = offPlayer::getLevel(ac);
            void* v83;
            auto v6 = *VirtualCall<ActorUniqueID*>(ads, 0x40, &v83); //IDA ActorDamageSource::`vftable'
            auto src = Raw_GetEntityByUniqueId(v6);

            CallEventRtnBool(EVENT_TYPES::onMobHurt, EntityClass::newEntity(ac),
                src ? EntityClass::newEntity(src) : Local<Value>(),
                Number::newNumber(damage));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onMobHurt);
    return original(ac, ads, damage, unk1_1, unk2_0);
}

// ===== onExplode & onBedExplode =====
THook(void, "?explode@Level@@UEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
    Level* _this, BlockSource* bs, Actor* actor, Vec3* pos, float power, bool isFire, bool isDestroy, float range, bool a9)
{
    IF_LISTENED(EVENT_TYPES::onExplode)
    {
        if (actor)
        {
            CallEventRtnVoid(EVENT_TYPES::onExplode, EntityClass::newEntity(actor), 
                FloatPos::newPos(pos->x, pos->y, pos->z, Raw_GetBlockDimensionId(bs)),
                Number::newNumber(power), Number::newNumber(range),
                Boolean::newBoolean(isDestroy), Boolean::newBoolean(isFire) );
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onExplode);

    IF_LISTENED(EVENT_TYPES::onBedExplode)
    {
        if (!actor)
        {
            CallEventRtnVoid(EVENT_TYPES::onBedExplode, IntPos::newPos(pos->x, pos->y, pos->z, Raw_GetBlockDimensionId(bs)));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onBedExplode);
    original(_this, bs, actor, pos, power, isFire, isDestroy, range, a9);
}

// ===== onRespawnAnchorExplode =====
THook(void, "?explode@RespawnAnchorBlock@@CAXAEAVPlayer@@AEBVBlockPos@@AEAVBlockSource@@AEAVLevel@@@Z",
    Player* pl, BlockPos* bp, BlockSource* bs, Level* level)
{
    IF_LISTENED(EVENT_TYPES::onRespawnAnchorExplode)
    {
        CallEventRtnVoid(EVENT_TYPES::onRespawnAnchorExplode, IntPos::newPos(bp,bs),
            PlayerClass::newPlayer(pl));
    }
    IF_LISTENED_END(EVENT_TYPES::onRespawnAnchorExplode);
    return original(pl, bp, bs, level);
}

// ===== onLiquidFlow =====
THook(bool, "?_canSpreadTo@LiquidBlockDynamic@@AEBA_NAEAVBlockSource@@AEBVBlockPos@@1E@Z",
    void* _this, BlockSource* bs, BlockPos* to, BlockPos* from, char id)
{
    IF_LISTENED(EVENT_TYPES::onLiquidFlow)
    {
        auto fromBlock = Raw_GetBlockByPos(from, bs);
        CallEventRtnBool(EVENT_TYPES::onLiquidFlow, BlockClass::newBlock(fromBlock, from, bs), IntPos::newPos(to,bs));
    }
    IF_LISTENED_END(EVENT_TYPES::onLiquidFlow);
    return original(_this, bs, to, from, id);
}

// ===== onBlockExploded =====
THook(void, "?onExploded@Block@@QEBAXAEAVBlockSource@@AEBVBlockPos@@PEAVActor@@@Z",
    Block* _this, BlockSource *bs, BlockPos *bp, Actor * actor)
{
    IF_LISTENED(EVENT_TYPES::onBlockExploded)
    {
        if (actor)
        {
            CallEventRtnVoid(EVENT_TYPES::onBlockExploded, BlockClass::newBlock(_this, bp, bs), EntityClass::newEntity(actor));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onBlockExploded);
    return original(_this, bs, bp, actor);
}

// ===== onCmdBlockExecute =====
THook(bool, "?_performCommand@BaseCommandBlock@@AEAA_NAEAVBlockSource@@AEBVCommandOrigin@@AEA_N@Z",
    BaseCommandBlock* _this, BlockSource* a2, CommandOrigin* a3, bool* a4)
{
    IF_LISTENED(EVENT_TYPES::onCmdBlockExecute)
    {
        string cmd = offBaseCommandBlock::getCMD(_this);

        OriginType type = VirtualCall<OriginType>(a3, 0xB0); //IDA ScriptCommandOrigin::`vftable'
        bool isMinecart = type == OriginType::MinecartBlock;

        Vec3 pos;
        VirtualCall<BlockPos*>(a3, 0x20, &pos); //IDA BlockCommandOrigin::`vftable'
        int dim = Raw_GetBlockDimensionId(a2);

        CallEventRtnBool(EVENT_TYPES::onCmdBlockExecute, String::newString(cmd), 
            FloatPos::newPos(pos, dim), isMinecart);
    }
    IF_LISTENED_END(EVENT_TYPES::onCmdBlockExecute);
    return original(_this, a2, a3, a4);
}

// ===== onProjectileHitBlock =====
THook(void, "?onProjectileHit@Block@@QEBAXAEAVBlockSource@@AEBVBlockPos@@AEBVActor@@@Z",
    Block* _this, BlockSource* bs, BlockPos* bp, Actor* actor)
{
    IF_LISTENED(EVENT_TYPES::onProjectileHitBlock)
    {
        if (Raw_GetBlockType(_this) != "minecraft:air")
        {
            CallEventRtnVoid(EVENT_TYPES::onProjectileHitBlock, BlockClass::newBlock(_this, bp, bs), EntityClass::newEntity(actor));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onProjectileHitBlock);
    return original(_this, bs, bp, actor);
}

// ===== onProjectileHitEntity =====
class HitResult;
THook(void, "?onHit@ProjectileComponent@@QEAAXAEAVActor@@AEBVHitResult@@@Z",
    void* _this, Actor* item, HitResult* res)
{
    IF_LISTENED(EVENT_TYPES::onProjectileHitEntity)
    {
        Actor* actor = SymCall("?getEntity@HitResult@@QEBAPEAVActor@@XZ", Actor*, HitResult*)(res);
        if (actor)
        {
            CallEventRtnVoid(EVENT_TYPES::onProjectileHitEntity, EntityClass::newEntity(actor),EntityClass::newEntity(item));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onProjectileHitEntity);
    return original(_this, item, res);
}

// ===== onRedStoneUpdate =====
// 红石粉
THook(void, "?onRedstoneUpdate@RedStoneWireBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@H_N@Z",
    void* _this, BlockSource* bs, BlockPos* bp, int level, bool isActive)
{
    IF_LISTENED(EVENT_TYPES::onRedStoneUpdate)
    {
        CallEventRtnVoid(EVENT_TYPES::onRedStoneUpdate, BlockClass::newBlock(Raw_GetBlockByPos(bp,bs), bp, bs), 
            Number::newNumber(level),Boolean::newBoolean(level != 0));
    }
    IF_LISTENED_END(EVENT_TYPES::onRedStoneUpdate);
    return original(_this, bs, bp, level, isActive);
}

// 红石火把
THook(void, "?onRedstoneUpdate@RedstoneTorchBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@H_N@Z",
    void* _this, BlockSource* bs, BlockPos* bp, int level, bool isActive)
{
    IF_LISTENED(EVENT_TYPES::onRedStoneUpdate)
    {
        CallEventRtnVoid(EVENT_TYPES::onRedStoneUpdate, BlockClass::newBlock(Raw_GetBlockByPos(bp, bs), bp, bs),
            Number::newNumber(level), Boolean::newBoolean(level != 0));
    }
    IF_LISTENED_END(EVENT_TYPES::onRedStoneUpdate);
    return original(_this, bs, bp, level, isActive);
}

// 红石中继器
THook(void, "?onRedstoneUpdate@DiodeBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@H_N@Z",
    void* _this, BlockSource* bs, BlockPos* bp, int level, bool isActive)
{
    IF_LISTENED(EVENT_TYPES::onRedStoneUpdate)
    {
        CallEventRtnVoid(EVENT_TYPES::onRedStoneUpdate, BlockClass::newBlock(Raw_GetBlockByPos(bp, bs), bp, bs),
            Number::newNumber(level), Boolean::newBoolean(level != 0));
    }
    IF_LISTENED_END(EVENT_TYPES::onRedStoneUpdate);
    return original(_this, bs, bp, level, isActive);
}

// 红石比较器
THook(void, "?onRedstoneUpdate@ComparatorBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@H_N@Z",
    void* _this, BlockSource* bs, BlockPos* bp, int level, bool isActive)
{
    IF_LISTENED(EVENT_TYPES::onRedStoneUpdate)
    {
        CallEventRtnVoid(EVENT_TYPES::onRedStoneUpdate, BlockClass::newBlock(Raw_GetBlockByPos(bp, bs), bp, bs),
            Number::newNumber(level), Boolean::newBoolean(level != 0));
    }
    IF_LISTENED_END(EVENT_TYPES::onRedStoneUpdate);
    return original(_this, bs, bp, level, isActive);
}

/* ==== = onSplashPotionHitEffect ==== =
THook(void, "?doOnHitEffect@SplashPotionEffectSubcomponent@@UEAAXAEAVActor@@AEAVProjectileComponent@@@Z",
    void* _this, Actor* a2, ProjectileComponent* a3)
*/

// ===== onBlockInteracted =====
THook(unsigned short, "?onBlockInteractedWith@VanillaServerGameplayEventListener@@UEAA?AW4EventResult@@AEAVPlayer@@AEBVBlockPos@@@Z",
    void* _this, Player* pl, BlockPos* bp)
{
    IF_LISTENED(EVENT_TYPES::onBlockInteracted)
    {
        BlockSource* bs = Raw_GetBlockSourceByActor((Actor*)pl);
        Block* bl = Raw_GetBlockByPos(bp, bs);

        CallEventRtnValue(EVENT_TYPES::onBlockInteracted, 0, PlayerClass::newPlayer(pl),
            BlockClass::newBlock(bl, bp, bs));
    }
    IF_LISTENED_END(EVENT_TYPES::onBlockInteracted);
    return original(_this, pl, bp);
}

// ===== onUseRespawnAnchor =====
THook(bool, "?trySetSpawn@RespawnAnchorBlock@@CA_NAEAVPlayer@@AEBVBlockPos@@AEAVBlockSource@@AEAVLevel@@@Z",
    Player* pl, BlockPos* bp, BlockSource* bs, Level* a4)
{
    IF_LISTENED(EVENT_TYPES::onUseRespawnAnchor)
    {
        CallEventRtnBool(EVENT_TYPES::onUseRespawnAnchor,PlayerClass::newPlayer(pl),IntPos::newPos(bp, bs));
    }
    IF_LISTENED_END(EVENT_TYPES::onUseRespawnAnchor);
    return original(pl, bp, bs, a4);
}

// ===== onFarmLandDecay =====
THook(void, "?transformOnFall@FarmBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@PEAVActor@@M@Z",
    void *_this, BlockSource * bs, BlockPos * bp, Actor * ac, float a5)
{
    IF_LISTENED(EVENT_TYPES::onFarmLandDecay)
    {
        CallEventRtnVoid(EVENT_TYPES::onFarmLandDecay,IntPos::newPos(bp,bs),EntityClass::newEntity(ac));
    }
    IF_LISTENED_END(EVENT_TYPES::onFarmLandDecay);
    return original(_this,bs,bp,ac,a5);
}

// ===== onUseFrameBlock =====
THook(bool, "?use@ItemFrameBlock@@UEBA_NAEAVPlayer@@AEBVBlockPos@@E@Z",
    void* _this, Player* a2, BlockPos* a3)
{
    IF_LISTENED(EVENT_TYPES::onUseFrameBlock)
    {
        BlockSource * bs = Raw_GetBlockSourceByActor((Actor*)a2);
        Block* bl = Raw_GetBlockByPos(a3, bs);
        CallEventRtnBool(EVENT_TYPES::onUseFrameBlock, PlayerClass::newPlayer(a2), BlockClass::newBlock(bl, a3, bs));
    }
    IF_LISTENED_END(EVENT_TYPES::onUseFrameBlock);
    return original(_this, a2, a3);
}
THook(bool, "?attack@ItemFrameBlock@@UEBA_NPEAVPlayer@@AEBVBlockPos@@@Z",
    void* _this, Player* a2, BlockPos* a3)
{
    IF_LISTENED(EVENT_TYPES::onUseFrameBlock)
    {
        BlockSource* bs = Raw_GetBlockSourceByActor((Actor*)a2);
        Block* bl = Raw_GetBlockByPos(a3, bs);
        CallEventRtnBool(EVENT_TYPES::onUseFrameBlock, PlayerClass::newPlayer(a2), BlockClass::newBlock(bl, a3, bs));
    }
    IF_LISTENED_END(EVENT_TYPES::onUseFrameBlock);
    return original(_this, a2, a3);
}

// ===== onPistonPush =====
THook(bool, "?_attachedBlockWalker@PistonBlockActor@@AEAA_NAEAVBlockSource@@AEBVBlockPos@@EE@Z",
    BlockActor* _this, BlockSource* bs, BlockPos* bp, unsigned a3, unsigned a4)
{
    IF_LISTENED(EVENT_TYPES::onPistonPush)
    {
        int dim = Raw_GetBlockDimensionId(bs);
        BlockPos pistonPos = Raw_GetBlockEntityPos(_this);
        Block* pushedBlock = Raw_GetBlockByPos(bp, bs);
        if (Raw_GetBlockType(pushedBlock) == "minecraft:air")
            return original(_this, bs, bp, a3, a4);

        CallEventRtnBool(EVENT_TYPES::onPistonPush, IntPos::newPos(pistonPos, dim), BlockClass::newBlock(pushedBlock, bp, dim));
    }
    IF_LISTENED_END(EVENT_TYPES::onPistonPush);
    return original(_this, bs, bp, a3, a4);
}

// ===== onHopperSearchItem =====
THook(bool, "?_tryPullInItemsFromAboveContainer@Hopper@@IEAA_NAEAVBlockSource@@AEAVContainer@@AEBVVec3@@@Z",
    void* _this, BlockSource* bs, void* container, Vec3* pos)
{
    IF_LISTENED(EVENT_TYPES::onHopperSearchItem)
    {
        bool isMinecart = dAccess<bool>(_this, 5); // IDA Hopper::Hopper
        CallEventRtnBool(EVENT_TYPES::onHopperSearchItem, FloatPos::newPos(*pos, Raw_GetBlockDimensionId(bs)), isMinecart);
    }
    IF_LISTENED_END(EVENT_TYPES::onHopperSearchItem);
    return original(_this, bs, container, pos);
}

// ===== onHopperPushOut =====
THook(bool, "?_pushOutItems@Hopper@@IEAA_NAEAVBlockSource@@AEAVContainer@@AEBVVec3@@H@Z",
    void* _this, BlockSource* bs, void* container, Vec3* pos, int a5)
{
    IF_LISTENED(EVENT_TYPES::onHopperPushOut)
    {
        CallEventRtnBool(EVENT_TYPES::onHopperPushOut, FloatPos::newPos(*pos, Raw_GetBlockDimensionId(bs)));
    }
    IF_LISTENED_END(EVENT_TYPES::onHopperPushOut);
    return original(_this, bs, container, pos, a5);
}

// ===== onFireSpread =====
THook(bool, "?_trySpawnBlueFire@FireBlock@@AEBA_NAEAVBlockSource@@AEBVBlockPos@@@Z",
    void* _this, BlockSource* bs, BlockPos* bp)
{
    IF_LISTENED(EVENT_TYPES::onFireSpread)
    {
        CallEventRtnValue(EVENT_TYPES::onFireSpread, true, IntPos::newPos(bp, bs));
    }
    IF_LISTENED_END(EVENT_TYPES::onFireSpread);
    return original(_this, bs, bp);
}

/* ==== = onFishingHookRetrieve ==== =
THook(__int64, "?retrieve@FishingHook@@QEAAHXZ",
    FishingHook* _this)
*/


// ===== onNpcCmd =====
THook(bool, "?executeCommandAction@NpcComponent@@QEAAXAEAVActor@@AEBVPlayer@@HAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
    void* _this, Actor *ac, Player *pl, int a4, string &a5)
{
    IF_LISTENED(EVENT_TYPES::onNpcCmd)
    {
        CallEventRtnBool(EVENT_TYPES::onNpcCmd, EntityClass::newEntity(ac), PlayerClass::newPlayer(pl));
    }
    IF_LISTENED_END(EVENT_TYPES::onNpcCmd);
    return original(_this, ac, pl, a4, a5);
}


// ===== onPlayerCmd & onConsoleCmd =====
THook(bool, "?executeCommand@MinecraftCommands@@QEBA?AUMCRESULT@@V?$shared_ptr@VCommandContext@@@std@@_N@Z",
    MinecraftCommands* _this, unsigned int* a2, std::shared_ptr<CommandContext> x, char a4)
{
    try
    {
        Actor *ac = x->getOrigin().getEntity();
        Player* player = Raw_ToPlayer(ac);

        string cmd = x->getCmd();
        if (cmd.front() == '/')
            cmd = cmd.substr(1);
        if (!cmd.empty())
        {
            if (player)
            {
                // Player Command
                vector<string> paras;
                string prefix = LxlFindCmdReg(true, cmd, paras);

                if (!prefix.empty())
                {
                    //Lxl Registered Cmd
                    int perm = localShareData->playerCmdCallbacks[prefix].perm;

                    if (Raw_GetPlayerPermLevel(player) >= perm)
                    {
                        bool callbackRes = CallPlayerCmdCallback(player, prefix, paras);
                        IF_LISTENED(EVENT_TYPES::onPlayerCmd)
                        {
                            CallEventRtnBool(EVENT_TYPES::onPlayerCmd, PlayerClass::newPlayer(player), String::newString(cmd));
                        }
                        IF_LISTENED_END(EVENT_TYPES::onPlayerCmd);
                        if (!callbackRes)
                            return false;
                    }
                }
                else
                {
                    //Other Cmd
                    IF_LISTENED(EVENT_TYPES::onPlayerCmd)
                    {
                        CallEventRtnBool(EVENT_TYPES::onPlayerCmd, PlayerClass::newPlayer(player), String::newString(cmd));
                    }
                    IF_LISTENED_END(EVENT_TYPES::onPlayerCmd);
                }
            }
            else
            {
                // PreProcess
                if (!ProcessDebugEngine(cmd))
                    return false;
                ProcessStopServer(cmd);
                if (!ProcessHotManageCmd(cmd))
                    return false;

                //CallEvents
                vector<string> paras;
                string prefix = LxlFindCmdReg(false, cmd, paras);

                if (!prefix.empty())
                {
                    //Lxl Registered Cmd

                    bool callbackRes = CallServerCmdCallback(prefix, paras);
                    IF_LISTENED(EVENT_TYPES::onConsoleCmd)
                    {
                        CallEventRtnBool(EVENT_TYPES::onConsoleCmd, String::newString(cmd));
                    }
                    IF_LISTENED_END(EVENT_TYPES::onConsoleCmd);
                    if (!callbackRes)
                        return false;
                }
                else
                {
                    //Other Cmd
                    IF_LISTENED(EVENT_TYPES::onConsoleCmd)
                    {
                        CallEventRtnBool(EVENT_TYPES::onConsoleCmd, String::newString(cmd));
                    }
                    IF_LISTENED_END(EVENT_TYPES::onConsoleCmd);
                }
            }
        }
    }
    catch (const seh_exception& e)
    {
        ERROR("Event Callback Failed!"); 
        ERROR("SEH Uncaught Exception Detected!"); 
        ERRPRINT(e.what()); 
        ERROR("In Event: onPlayerCmd / onConsoleCmd");
    }
    catch (...) 
    { 
        ERROR("Event Callback Failed!"); 
        ERROR("Uncaught Exception Detected!"); 
        ERROR("In Event: onPlayerCmd / onConsoleCmd");
    }
    return original(_this, a2, x, a4);
}

// ===== onFormSelected =====
THook(void, "?handle@?$PacketHandlerDispatcherInstance@VModalFormResponsePacket@@$0A@@@UEBAXAEBVNetworkIdentifier@@AEAVNetEventCallback@@AEAV?$shared_ptr@VPacket@@@std@@@Z",
    void* _this, NetworkIdentifier* id, ServerNetworkHandler* handler, void* pPacket)
{
    try
    {
        //IF_LISTENED(EVENT_TYPES::onFormSelected)
        Packet* packet = *(Packet**)pPacket;
        Player* p = Raw_GetPlayerFromPacket(handler, id, packet);

        if (p)
        {
            unsigned formId = dAccess<unsigned>(packet, 48);
            string data = dAccess<string>(packet, 56);

            if (data.back() == '\n')
                data.pop_back();

            CallFormCallback(p, formId, data);
            // No CallEvent here
        }
    }
    catch (const seh_exception& e)
    {
        ERROR("Event Callback Failed!");
        ERROR("SEH Uncaught Exception Detected!");
        ERRPRINT(e.what());
        ERROR("In Event: onFormSelected");
    }
    catch (...)
    {
        ERROR("Event Callback Failed!");
        ERROR("Uncaught Exception Detected!");
        ERROR("In Event: onFormSelected");
    }

    original(_this, id, handler, pPacket);
}

// ===== onScoreChanged =====
THook(void, "?onScoreChanged@ServerScoreboard@@UEAAXAEBUScoreboardId@@AEBVObjective@@@Z",
    Scoreboard* _this, ScoreboardId* a1, Objective* a2)
{
    IF_LISTENED(EVENT_TYPES::onScoreChanged)
    {
        int id = a1->id;

        Player* player = nullptr;
        auto pls = Raw_GetOnlinePlayers();
        for (auto& pl : pls)
        {
            if (globalScoreBoard->getScoreboardId(pl)->id == id)
            {
                player = pl;
                break;
            }
        }

        if (player)
        {
            CallEventRtnVoid(EVENT_TYPES::onScoreChanged, PlayerClass::newPlayer(player), Number::newNumber(a2->getPlayerScore(*a1).getCount()),
                String::newString(a2->getName()), String::newString(a2->getDisplayName()));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onScoreChanged);

    return original(_this, a1, a2);
}

// ===== onConsoleOutput =====
THook(ostream&, "??$_Insert_string@DU?$char_traits@D@std@@_K@std@@YAAEAV?$basic_ostream@DU?$char_traits@D@std@@@0@AEAV10@QEBD_K@Z",
    ostream& _this, const char* str, unsigned size)
{
    IF_LISTENED(EVENT_TYPES::onConsoleOutput)
    {
        if (&_this == &cout)
        {
            CallEventRtnValue(EVENT_TYPES::onConsoleOutput, _this, String::newString(string(str)));
        }
    }
    IF_LISTENED_END(EVENT_TYPES::onConsoleOutput);
    return original(_this, str, size);
}

bool MoneyEventCallback(LLMoneyEvent type, xuid_t from, xuid_t to, money_t value)
{
    switch (type)
    {
        case LLMoneyEvent::Add:
        {
            IF_LISTENED(EVENT_TYPES::onMoneyAdd)
            {
                CallEventRtnBool(EVENT_TYPES::onMoneyAdd, String::newString(to_string(to)), Number::newNumber(value));
            }
            IF_LISTENED_END(EVENT_TYPES::onMoneyAdd);
            break;
        }
        case LLMoneyEvent::Reduce:
        {
            IF_LISTENED(EVENT_TYPES::onMoneyReduce)
            {
                CallEventRtnBool(EVENT_TYPES::onMoneyReduce, String::newString(to_string(to)), Number::newNumber(value));
            }
            IF_LISTENED_END(EVENT_TYPES::onMoneyReduce);
            break;
        }
        case LLMoneyEvent::Trans:
        {
            IF_LISTENED(EVENT_TYPES::onMoneyTrans)
            {
                CallEventRtnBool(EVENT_TYPES::onMoneyTrans, String::newString(to_string(from)), String::newString(to_string(to)), Number::newNumber(value));
            }
            IF_LISTENED_END(EVENT_TYPES::onMoneyTrans);
            break;
        }
        case LLMoneyEvent::Set:
        {
            IF_LISTENED(EVENT_TYPES::onMoneySet)
            {
                CallEventRtnBool(EVENT_TYPES::onMoneySet, String::newString(to_string(to)), Number::newNumber(value));
            }
            IF_LISTENED_END(EVENT_TYPES::onMoneySet);
            break;
        }
        default:
            break;
    }
    return true;
}

/*
class InventoryTransaction;
THook(void, "?handle@?$PacketHandlerDispatcherInstance@VInventoryTransactionPacket@@$0A@@@UEBAXAEBVNetworkIdentifier@@AEAVNetEventCallback@@AEAV?$shared_ptr@VPacket@@@std@@@Z",
    void* _this, NetworkIdentifier* id, ServerNetworkHandler* handler, void* pPacket)
{
    Packet* packet = *(Packet**)pPacket;
    Player* p = Raw_GetPlayerFromPacket(handler, id, packet);
    
    ///
        NORMAL = 0,
        MISMATCH = 1,
        USE_ITEM = 2,
        USE_ITEM_ON_ENTITY = 3,
        RELEASE_ITEM = 4
    ///

    auto type = *(DWORD*)(*((QWORD*)packet + 10) + 8i64);
    auto invts = (InventoryTransaction*)(*((QWORD*)packet + 10) + 16i64);
    cout << "PacketType: " << type << "\n";

    RBStream rb(packet,0);

    unsigned actionType;
    int bp_x;
    unsigned bp_y;
    int bp_z;
    int blockFace;
    int hotbarSlot;

    rb.apply(actionType, bp_x, bp_y, bp_z, blockFace, hotbarSlot);

    cout << actionType << "\n"
        << bp_x << "\n"
        << bp_y << "\n"
        << bp_z << "\n"
        << blockFace << "\n"
        << hotbarSlot << "\n";

    original(_this, id, handler, pPacket);
}
*/