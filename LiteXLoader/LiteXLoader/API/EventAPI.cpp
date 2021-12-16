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
#include <Global.hpp>
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
#include <AutoUpgrade.h>
#include <EventAPI.h>
#include <ScheduleAPI.h>
#include <MC/Player.hpp>
#include <MC/BlockSource.hpp>
#include <MC/Actor.hpp>
#include <MC/ActorDamageSource.hpp>
#include <MC/MobEffectInstance.hpp>
#include <MC/HashedString.hpp>
#include <MC/Objective.hpp>
#include <MC/BlockInstance.hpp>
using namespace std;



//////////////////// Listeners ////////////////////

enum class EVENT_TYPES : int
{
    onPreJoin=0, onJoin, onLeft, onPlayerCmd, onChat, onPlayerDie, 
    onRespawn, onChangeDim, onJump, onSneak, onAttack, onEat, onMove, onChangeSprinting, onSpawnProjectile,
    onFireworkShootWithCrossbow, onSetArmor, onRide, onStepOnPressurePlate,
    onUseItem, onTakeItem, onDropItem, onUseItemOn, onInventoryChange, onChangeArmorStand,
    onStartDestroyBlock, onDestroyBlock, onWitherBossDestroy, onPlaceBlock, onBedExplode, onRespawnAnchorExplode, onLiquidFlow,
    onOpenContainer, onCloseContainer, onContainerChange, onOpenContainerScreen, 
    onMobDie, onMobHurt, onExplode, onBlockExploded, onCmdBlockExecute, onRedStoneUpdate, onProjectileHitEntity,
    onProjectileHitBlock, onBlockInteracted, onUseRespawnAnchor, onFarmLandDecay, onUseFrameBlock,
    onPistonPush, onHopperSearchItem, onHopperPushOut, onFireSpread, onBlockChanged, onNpcCmd,
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
    {"onChangeSprinting",EVENT_TYPES::onChangeSprinting},
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
    {"onBlockChanged",EVENT_TYPES::onBlockChanged},
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
    script::Global<Function> func;
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
        logger.error("Event Callback Failed!"); \
        logger.error << e << logger.endl; \
        logger.error("In Event: " + EventTypeToString(TYPE)); \
        logger.error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
    } \
    catch (const std::exception& e) \
    { \
        logger.error("Event Callback Failed!"); \
        logger.error("C++ Uncaught Exception Detected!"); \
        logger.error(e.what()); \
        logger.error("In Event: " + EventTypeToString(TYPE)); \
        logger.error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
    } \
    catch (const seh_exception& e) \
    { \
        logger.error("Event Callback Failed!"); \
        logger.error("SEH Uncaught Exception Detected!"); \
        logger.error(e.what()); \
        logger.error("In Event: " + EventTypeToString(TYPE)); \
        logger.error("In Plugin: " + ENGINE_OWN_DATA()->pluginName); \
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
#define CallEvent(TYPE,...) \
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
    if(!passToBDS) { return false; } else { return true; }

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
        logger.error("Event Callback Failed!"); \
        logger.error("Uncaught Exception Detected!"); \
        logger.error("In Event: " + EventTypeToString(TYPE)); \
    } } return true;


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
        listenerList[eventId].push_back({ engine,script::Global<Function>(func) });
        return true;
    }
    catch (const std::logic_error& e)
    {
        logger.error("Event \"" + eventName + "\" No Found!\n");
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

    auto players = Level::getAllPlayers();
    for (auto& pl : players)
        FakeCallEvent(engine, EVENT_TYPES::onPreJoin, PlayerClass::newPlayer(pl));
    for(auto &pl : players)
        FakeCallEvent(engine, EVENT_TYPES::onJoin, PlayerClass::newPlayer(pl));

    return true;
}

bool LxlCallEventsOnHotUnload(ScriptEngine* engine)
{
    auto players = Level::getAllPlayers();
    for (auto& pl : players)
        FakeCallEvent(engine, EVENT_TYPES::onLeft, PlayerClass::newPlayer(pl));

    return true;
}

//////////////////// Events ////////////////////

void InitEventListeners()
{

    using namespace Event;

    Event::PlayerJoinEvent::subscribe([](const PlayerJoinEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onJoin)
        {
            CallEvent(EVENT_TYPES::onJoin, PlayerClass::newPlayer((Player*)ev.mPlayer));
        }
        IF_LISTENED_END(EVENT_TYPES::onJoin);
    });

    Event::PlayerPreJoinEvent::subscribe([](const PlayerPreJoinEvent& ev)
    {
        IF_LISTENED(EVENT_TYPES::onPreJoin)
        {
            CallEvent(EVENT_TYPES::onPreJoin, PlayerClass::newPlayer((Player*)ev.mPlayer));
        }
        IF_LISTENED_END(EVENT_TYPES::onPreJoin);
    });

    Event::PlayerLeftEvent::subscribe([](const PlayerLeftEvent& ev)
    {
        IF_LISTENED(EVENT_TYPES::onLeft)
        {
            CallEvent(EVENT_TYPES::onLeft, PlayerClass::newPlayer((Player*)ev.mPlayer));
        }
        IF_LISTENED_END(EVENT_TYPES::onLeft);
    });

    Event::PlayerChatEvent::subscribe([](const PlayerChatEvent& ev)
    {
        IF_LISTENED(EVENT_TYPES::onChat)
        {
            CallEvent(EVENT_TYPES::onChat, PlayerClass::newPlayer(ev.mPlayer), ev.mMessage);
        }
        IF_LISTENED_END(EVENT_TYPES::onChat);
    });

    Event::PlayerChangeDimEvent::subscribe([](const PlayerChangeDimEvent& ev)
    {
        IF_LISTENED(EVENT_TYPES::onChangeDim)
        {
            CallEvent(EVENT_TYPES::onChangeDim, PlayerClass::newPlayer(ev.mPlayer), Number::newNumber(ev.mToDimensionId));      //======???
        }
        IF_LISTENED_END(EVENT_TYPES::onChangeDim);
    });

    Event::PlayerAttackEvent::subscribe([](const PlayerAttackEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onAttack)
        {
            if (ev.mTarget)
            {
                CallEvent(EVENT_TYPES::onAttack, PlayerClass::newPlayer(ev.mPlayer), EntityClass::newEntity(ev.mTarget));
            }
        }
        IF_LISTENED_END(EVENT_TYPES::onAttack);
    });

    Event::PlayerDieEvent::subscribe([](const PlayerDieEvent& ev)
    {
        IF_LISTENED(EVENT_TYPES::onPlayerDie)
        {
            Actor* source = ev.mDamageSource->getEntity();
            CallEvent(EVENT_TYPES::onPlayerDie, PlayerClass::newPlayer(ev.mPlayer), 
                (source ? EntityClass::newEntity(source) : Local<Value>()));
        }
        IF_LISTENED_END(EVENT_TYPES::onPlayerDie);
    });

    Event::PlayerRespawnEvent::subscribe([](const PlayerRespawnEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onRespawn)
        {
            CallEvent(EVENT_TYPES::onRespawn, PlayerClass::newPlayer((Player*)ev.mPlayer));
        }
        IF_LISTENED_END(EVENT_TYPES::onRespawn)
    });

    Event::PlayerStartDestroyBlockEvent::subscribe([](const PlayerStartDestroyBlockEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onStartDestroyBlock)
        {
            CallEvent(EVENT_TYPES::onStartDestroyBlock, PlayerClass::newPlayer(ev.mPlayer),
                BlockClass::newBlock(ev.mBlockInstance));
        }
        IF_LISTENED_END(EVENT_TYPES::onStartDestroyBlock);
    });

    Event::PlayerDestroyBlockEvent::subscribe([](const PlayerDestroyBlockEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onDestroyBlock)
        {
            CallEvent(EVENT_TYPES::onDestroyBlock, PlayerClass::newPlayer(ev.mPlayer), BlockClass::newBlock(ev.mBlockInstance));
        }
        IF_LISTENED_END(EVENT_TYPES::onDestroyBlock);
    });

    Event::PlayerPlaceBlockEvent::subscribe([](const PlayerPlaceBlockEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onPlaceBlock)
        {
            CallEvent(EVENT_TYPES::onPlaceBlock, PlayerClass::newPlayer(ev.mPlayer), BlockClass::newBlock(ev.mBlockInstance));
        }
        IF_LISTENED_END(EVENT_TYPES::onPlaceBlock);
    });

    Event::PlayerMoveEvent::subscribe([](const PlayerMoveEvent& ev)
    {
        IF_LISTENED(EVENT_TYPES::onMove)
        {
            CallEvent(EVENT_TYPES::onMove, PlayerClass::newPlayer(ev.mPlayer), 
                FloatPos::newPos(ev.mPos,ev.mPlayer->getDimensionId()));
        }
        IF_LISTENED_END(EVENT_TYPES::onMove);
    });

    Event::PlayerJumpEvent::subscribe([](const PlayerJumpEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onJump)
        {
            CallEvent(EVENT_TYPES::onJump, PlayerClass::newPlayer(ev.mPlayer));
        }
        IF_LISTENED_END(EVENT_TYPES::onJump);
    });

    Event::PlayerDropItemEvent::subscribe([](const PlayerDropItemEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onDropItem)
        {
            CallEvent(EVENT_TYPES::onDropItem, PlayerClass::newPlayer(ev.mPlayer), ItemClass::newItem(ev.mItemStack));       //###### Q lost items ######
        }
        IF_LISTENED_END(EVENT_TYPES::onDropItem);
    });

    Event::PlayerTakeItemEvent::subscribe([](const PlayerTakeItemEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onTakeItem)
        {
            CallEvent(EVENT_TYPES::onTakeItem, PlayerClass::newPlayer(ev.mPlayer), 
                EntityClass::newEntity(ev.mItemEntity), ev.mItemStack ? ItemClass::newItem(ev.mItemStack) : Local<Value>());
        }
        IF_LISTENED_END(EVENT_TYPES::onTakeItem);
    });

    Event::PlayerOpenContainerEvent::subscribe([](const PlayerOpenContainerEvent &ev) {
        IF_LISTENED(EVENT_TYPES::onOpenContainer)
        {
            CallEvent(EVENT_TYPES::onOpenContainer, PlayerClass::newPlayer(ev.mPlayer), BlockClass::newBlock(ev.mBlockInstance));
        }
        IF_LISTENED_END(EVENT_TYPES::onOpenContainer);
    });

    Event::PlayerCloseContainerEvent::subscribe([](const PlayerCloseContainerEvent &ev) {
        IF_LISTENED(EVENT_TYPES::onCloseContainer)
        {
            CallEvent(EVENT_TYPES::onCloseContainer, PlayerClass::newPlayer(ev.mPlayer), BlockClass::newBlock(ev.mBlockInstance));
        }
        IF_LISTENED_END(EVENT_TYPES::onCloseContainer);
    });

    Event::PlayerInventoryChangeEvent::subscribe([](const PlayerInventoryChangeEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onInventoryChange)
        {
            CallEvent(EVENT_TYPES::onInventoryChange, PlayerClass::newPlayer(ev.mPlayer), ev.mSlot,
                ItemClass::newItem(ev.mPreviousItemStack), ItemClass::newItem(ev.mNewItemStack));
        }
        IF_LISTENED_END(EVENT_TYPES::onInventoryChange);
    });

    Event::PlayerUseItemEvent::subscribe([](const PlayerUseItemEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onUseItem)
        {
            CallEvent(EVENT_TYPES::onUseItem, PlayerClass::newPlayer((Player*)ev.mPlayer), ItemClass::newItem(ev.mItemStack));
        }
        IF_LISTENED_END(EVENT_TYPES::onUseItem);
    });

    Event::PlayerUseItemOnEvent::subscribe([](const PlayerUseItemOnEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onUseItemOn)
        {
            CallEvent(EVENT_TYPES::onUseItemOn, PlayerClass::newPlayer((Player*)ev.mPlayer), ItemClass::newItem(ev.mItemStack),
                BlockClass::newBlock(ev.mBlockInstance), Number::newNumber(ev.mFace));
        }
        IF_LISTENED_END(EVENT_TYPES::onUseItemOn);
    });

    Event::ContainerChangeEvent::subscribe([](const ContainerChangeEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onContainerChange)
        {
            CallEvent(EVENT_TYPES::onContainerChange, PlayerClass::newPlayer(ev.mPlayer), BlockClass::newBlock(ev.mBlockInstance),
                ev.mSlot, ItemClass::newItem(ev.mPerviousItemStack), ItemClass::newItem(ev.mNewItemStack));
        }
        IF_LISTENED_END(EVENT_TYPES::onContainerChange);
    });

    Event::ArmorStandChangeEvent::subscribe([](const ArmorStandChangeEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onChangeArmorStand)
        {
            CallEvent(EVENT_TYPES::onChangeArmorStand, EntityClass::newEntity((Actor*)ev.mArmorStand), 
                PlayerClass::newPlayer(ev.mPlayer), Number::newNumber(ev.mSlot));
        }
        IF_LISTENED_END(EVENT_TYPES::onChangeArmorStand);
    });

    Event::PlayerSprintEvent::subscribe([](const PlayerSprintEvent& ev)
    {
        IF_LISTENED(EVENT_TYPES::onChangeSprinting)
        {
            CallEvent(EVENT_TYPES::onChangeSprinting, PlayerClass::newPlayer(ev.mPlayer), 
                Boolean::newBoolean(ev.mIsSprinting));
        }
        IF_LISTENED_END(EVENT_TYPES::onChangeSprinting);
    });

    Event::PlayerSneakEvent::subscribe([](const PlayerSneakEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onSneak)
        {
            CallEvent(EVENT_TYPES::onSneak, PlayerClass::newPlayer(ev.mPlayer), Boolean::newBoolean(ev.mIsSneaking));
        }
        IF_LISTENED_END(EVENT_TYPES::onSneak);
    });

    Event::PlayerOpenContainerScreenEvent::subscribe([](const PlayerOpenContainerScreenEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onOpenContainerScreen)
        {
            CallEvent(EVENT_TYPES::onOpenContainerScreen, PlayerClass::newPlayer(ev.mPlayer));
        }
        IF_LISTENED_END(EVENT_TYPES::onOpenContainerScreen);
    });

    Event::PlayerSetArmorEvent::subscribe([](const PlayerSetArmorEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onSetArmor)
        {
            CallEvent(EVENT_TYPES::onSetArmor, PlayerClass::newPlayer(ev.mPlayer), Number::newNumber(ev.mSlot),
                ItemClass::newItem(ev.mArmorItem));
        }
        IF_LISTENED_END(EVENT_TYPES::onSetArmor);
    });

    Event::PlayerEatEvent::subscribe([](const PlayerEatEvent& ev)
    {
        IF_LISTENED(EVENT_TYPES::onEat)
        {
            CallEvent(EVENT_TYPES::onEat, PlayerClass::newPlayer(ev.mPlayer), ItemClass::newItem(ev.mFoodItem));
        }
        IF_LISTENED_END(EVENT_TYPES::onEat);
    });

    Event::PlayerConsumeTotemEvent::subscribe([](const PlayerConsumeTotemEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onConsumeTotem)
        {
            CallEvent(EVENT_TYPES::onConsumeTotem, PlayerClass::newPlayer(ev.mPlayer));
        }
        IF_LISTENED_END(EVENT_TYPES::onConsumeTotem);
    });

    Event::PlayerEffectChangedEvent::subscribe([](const PlayerEffectChangedEvent& ev) {
        if (ev.mEventType == PlayerEffectChangedEvent::EventType::Add)
        {
            IF_LISTENED(EVENT_TYPES::onEffectAdded)
            {
                CallEvent(EVENT_TYPES::onEffectAdded, PlayerClass::newPlayer(ev.mPlayer), 
                    String::newString(ev.mEffect->getComponentName().getString()));
            }
            IF_LISTENED_END(EVENT_TYPES::onEffectAdded);
        }
        else if (ev.mEventType == PlayerEffectChangedEvent::EventType::Remove)
        {
            IF_LISTENED(EVENT_TYPES::onEffectRemoved)
            {
                CallEvent(EVENT_TYPES::onEffectRemoved, PlayerClass::newPlayer(ev.mPlayer),
                    String::newString(ev.mEffect->getComponentName().getString()));
            }
            IF_LISTENED_END(EVENT_TYPES::onEffectRemoved);
        }
        else if (ev.mEventType == PlayerEffectChangedEvent::EventType::Update)
        {
            IF_LISTENED(EVENT_TYPES::onEffectUpdated)
            {
                CallEvent(EVENT_TYPES::onEffectUpdated, PlayerClass::newPlayer(ev.mPlayer),
                    String::newString(ev.mEffect->getComponentName().getString()));
            }
            IF_LISTENED_END(EVENT_TYPES::onEffectUpdated);
        }
        return true;
    });

    Event::PlayerUseRespawnAnchorEvent::subscribe([](const PlayerUseRespawnAnchorEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onUseRespawnAnchor)
        {
            BlockInstance bl(ev.mBlockInstance);
            CallEvent(EVENT_TYPES::onUseRespawnAnchor, PlayerClass::newPlayer(ev.mPlayer),
                IntPos::newPos(bl.getPosition(), bl.getDimensionId()));
        }
        IF_LISTENED_END(EVENT_TYPES::onUseRespawnAnchor);
    });

    Event::PlayerCmdEvent::subscribe([](const PlayerCmdEvent& ev)
    {
        try
        {
            string cmd = ev.mCommand;
            Player* player = ev.mPlayer;

            vector<string> paras;
            bool isFromOtherEngine = false;
            string prefix = LxlFindCmdReg(true, cmd, paras, &isFromOtherEngine);

            if (!prefix.empty())
            {
                //Lxl Registered Cmd
                int perm = localShareData->playerCmdCallbacks[prefix].perm;

                if (player->getCommandPermissionLevel() >= perm)
                {
                    bool callbackRes = CallPlayerCmdCallback(player, prefix, paras);
                    IF_LISTENED(EVENT_TYPES::onPlayerCmd)
                    {
                        CallEvent(EVENT_TYPES::onPlayerCmd, PlayerClass::newPlayer(player), String::newString(cmd));
                    }
                    IF_LISTENED_END(EVENT_TYPES::onPlayerCmd);
                    if (!callbackRes)
                        return false;
                }
            }
            else
            {
                if (isFromOtherEngine)
                    return false;

                //Other Cmd
                IF_LISTENED(EVENT_TYPES::onPlayerCmd)
                {
                    CallEvent(EVENT_TYPES::onPlayerCmd, PlayerClass::newPlayer(player), String::newString(cmd));
                }
                IF_LISTENED_END(EVENT_TYPES::onPlayerCmd);
            }
        }
        catch (...)
        {
            logger.error("Event Callback Failed!");
            logger.error("Uncaught Exception Detected!");
            logger.error("In Event: onPlayerCmd");
        }
        return true;
    });

    Event::EntityRideEvent::subscribe([](const EntityRideEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onRide)
        {
            CallEvent(EVENT_TYPES::onRide, EntityClass::newEntity(ev.mRider), EntityClass::newEntity(ev.mVehicle));
        }
        IF_LISTENED_END(EVENT_TYPES::onRide);
    });

    Event::EntityExplodeEvent::subscribe([](const EntityExplodeEvent &ev) {
        IF_LISTENED(EVENT_TYPES::onExplode)
        {
            CallEvent(EVENT_TYPES::onExplode, EntityClass::newEntity(ev.mActor),
                FloatPos::newPos(ev.mPos, ev.mDimensionId),
                Number::newNumber(ev.mRadius), Number::newNumber(ev.mRange),
                Boolean::newBoolean(ev.mIsDestroy), Boolean::newBoolean(ev.mIsFire));
        }
        IF_LISTENED_END(EVENT_TYPES::onExplode);
    });

    Event::CmdBlockExecuteEvent::subscribe([](const CmdBlockExecuteEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onCmdBlockExecute)
        {
            if (ev.mIsMinecart)
            {
                CallEvent(EVENT_TYPES::onCmdBlockExecute, String::newString(ev.mCommand),
                    FloatPos::newPos(ev.mMinecart->getPosition(), ev.mMinecart->getDimensionId()), true);
            }
            else
            {
                BlockInstance bl = ev.mBlockInstance;
                CallEvent(EVENT_TYPES::onCmdBlockExecute, String::newString(ev.mCommand),
                    FloatPos::newPos(bl.getPosition().toVec3(), bl.getDimensionId()), true);
            }
        }
        IF_LISTENED_END(EVENT_TYPES::onCmdBlockExecute);
    });

    Event::BlockExplodeEvent::subscribe([](const BlockExplodeEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onBedExplode)
        {
            BlockInstance bl(ev.mBlockInstance);
            CallEvent(EVENT_TYPES::onBedExplode, IntPos::newPos(bl.getPosition(), bl.getDimensionId()));
        }
        IF_LISTENED_END(EVENT_TYPES::onBedExplode);
    });

    Event::RedStoneUpdateEvent::subscribe([](const RedStoneUpdateEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onRedStoneUpdate)
        {
            CallEvent(EVENT_TYPES::onRedStoneUpdate, BlockClass::newBlock(ev.mBlockInstance),
                Number::newNumber(ev.mRedStonePower), Boolean::newBoolean(ev.mIsActivated));
        }
        IF_LISTENED_END(EVENT_TYPES::onRedStoneUpdate);
    });

    Event::RespawnAnchorExplodeEvent::subscribe([](const RespawnAnchorExplodeEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onRespawnAnchorExplode)
        {
            BlockInstance bl(ev.mBlockInstance);
            CallEvent(EVENT_TYPES::onRespawnAnchorExplode, IntPos::newPos(bl.getPosition(), bl.getDimensionId()),
                PlayerClass::newPlayer(ev.mPlayer));
        }
        IF_LISTENED_END(EVENT_TYPES::onRespawnAnchorExplode);
    });

    Event::WitherBossDestroyEvent::subscribe([](const WitherBossDestroyEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onWitherBossDestroy)
        {
            AABB range = ev.mDestroyRange;
            int dimId = ((Actor*)ev.mWitherBoss)->getDimensionId();
            CallEvent(EVENT_TYPES::onWitherBossDestroy, EntityClass::newEntity((Actor*)ev.mWitherBoss),
                IntPos::newPos(range.pointA.toBlockPos(),dimId), IntPos::newPos(range.pointB.toBlockPos(),dimId));
        }
        IF_LISTENED_END(EVENT_TYPES::onWitherBossDestroy);
    });

    Event::MobHurtEvent::subscribe([](const MobHurtEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onMobHurt)
        {
            Actor* source = nullptr;
            if (ev.mDamageSource->getCause() == ActorDamageCause::EntityAttack)
                source = Level::getEntity(ev.mDamageSource->getDamagingEntityUniqueID());

            CallEvent(EVENT_TYPES::onMobHurt, EntityClass::newEntity(ev.mMob),
                source ? EntityClass::newEntity(source) : Local<Value>(),
                Number::newNumber(ev.mDamage));
        }
        IF_LISTENED_END(EVENT_TYPES::onMobHurt)
    });

    Event::EntityStepOnPressurePlateEvent::subscribe([](const EntityStepOnPressurePlateEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onStepOnPressurePlate)
        {
            CallEvent(EVENT_TYPES::onStepOnPressurePlate, EntityClass::newEntity(ev.mActor), BlockClass::newBlock(ev.mBlockInstance));
        }
        IF_LISTENED_END(EVENT_TYPES::onStepOnPressurePlate);
    });

    Event::MobDieEvent::subscribe([](const MobDieEvent& ev)
    {
        IF_LISTENED(EVENT_TYPES::onMobDie)
        {
            Actor* source = nullptr;
            if (ev.mDamageSource->getCause() == ActorDamageCause::EntityAttack)
                source = Level::getEntity(ev.mDamageSource->getDamagingEntityUniqueID());

            CallEvent(EVENT_TYPES::onMobDie, EntityClass::newEntity((Actor*)ev.mMob),
                (source ? EntityClass::newEntity(source) : Local<Value>()));
        }
        IF_LISTENED_END(EVENT_TYPES::onMobDie);
    });

    Event::NpcCmdEvent::subscribe([](const NpcCmdEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onNpcCmd)
        {
            CallEvent(EVENT_TYPES::onNpcCmd, EntityClass::newEntity(ev.mNpc), PlayerClass::newPlayer(ev.mPlayer),
                String::newString(ev.mCommand));
        }
        IF_LISTENED_END(EVENT_TYPES::onNpcCmd);
    });

    Event::ProjectileSpawnEvent::subscribe([](const ProjectileSpawnEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onSpawnProjectile)
        {
            CallEvent(EVENT_TYPES::onSpawnProjectile, EntityClass::newEntity(ev.mShooter), String::newString(ev.mType));
        }
        IF_LISTENED_END(EVENT_TYPES::onSpawnProjectile);
    });

    Event::ProjectileHitEntityEvent::subscribe([](const ProjectileHitEntityEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onProjectileHitEntity)
        {
            CallEvent(EVENT_TYPES::onProjectileHitEntity, EntityClass::newEntity(ev.mTarget), EntityClass::newEntity(ev.mSource));
        }
        IF_LISTENED_END(EVENT_TYPES::onProjectileHitEntity);
    });

    Event::ProjectileHitBlockEvent::subscribe([](const ProjectileHitBlockEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onProjectileHitBlock)
        {
            CallEvent(EVENT_TYPES::onProjectileHitBlock, BlockClass::newBlock(ev.mBlockInstance),
                EntityClass::newEntity(ev.mSource));
        }
        IF_LISTENED_END(EVENT_TYPES::onProjectileHitBlock);
    });

    Event::LiquidSpreadEvent::subscribe([](const LiquidSpreadEvent &ev) {
        IF_LISTENED(EVENT_TYPES::onLiquidFlow)
        {
            CallEvent(EVENT_TYPES::onLiquidFlow, BlockClass::newBlock(ev.mBlockInstance), IntPos::newPos(ev.mTarget));
        }
        IF_LISTENED_END(EVENT_TYPES::onLiquidFlow);
    });

    Event::PlayerUseFrameBlockEvent::subscribe([](const PlayerUseFrameBlockEvent &ev) {
        IF_LISTENED(EVENT_TYPES::onUseFrameBlock)
        {
            CallEvent(EVENT_TYPES::onUseFrameBlock, PlayerClass::newPlayer(ev.mPlayer),
                BlockClass::newBlock(ev.mBlockInstance));
        }
        IF_LISTENED_END(EVENT_TYPES::onUseFrameBlock);
    });

    Event::BlockExplodedEvent::subscribe([](const BlockExplodedEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onBlockExploded)
        {
            CallEvent(EVENT_TYPES::onBlockExploded, BlockClass::newBlock(ev.mBlockInstance), 
                EntityClass::newEntity(ev.mExplodeSource));
        }
        IF_LISTENED_END(EVENT_TYPES::onBlockExploded);
    });

    Event::BlockInteractedEvent::subscribe([](const BlockInteractedEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onBlockInteracted)
        {
            CallEvent(EVENT_TYPES::onBlockInteracted, PlayerClass::newPlayer(ev.mPlayer),
                BlockClass::newBlock(ev.mBlockInstance));
        }
        IF_LISTENED_END(EVENT_TYPES::onBlockInteracted);
    });

    Event::FarmLandDecayEvent::subscribe([](const FarmLandDecayEvent &ev) {
        IF_LISTENED(EVENT_TYPES::onFarmLandDecay)
        {
            BlockInstance bl(ev.mBlockInstance);
            CallEvent(EVENT_TYPES::onFarmLandDecay, IntPos::newPos(bl.getPosition(),bl.getDimensionId()),
                EntityClass::newEntity(ev.mActor));
        }
        IF_LISTENED_END(EVENT_TYPES::onFarmLandDecay);
    });

    Event::PistonPushEvent::subscribe([](const PistonPushEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onPistonPush)
        {
            BlockInstance bl(ev.mPistonBlockInstance);
            CallEvent(EVENT_TYPES::onPistonPush, IntPos::newPos(bl.getPosition(), bl.getDimensionId()),
                BlockClass::newBlock(ev.mTargetBlockInstance));
        }
        IF_LISTENED_END(EVENT_TYPES::onPistonPush);
    });

    Event::HopperSearchItemEvent::subscribe([](const HopperSearchItemEvent &ev) {
        IF_LISTENED(EVENT_TYPES::onHopperSearchItem)
        {
            if (ev.isMinecart)
            {
                CallEvent(EVENT_TYPES::onHopperSearchItem, FloatPos::newPos(ev.mMinecartPos, ev.mDimensionId), ev.isMinecart);
            }
            else
            {
                BlockInstance bl = ev.mHopperBlock;
                CallEvent(EVENT_TYPES::onHopperSearchItem, FloatPos::newPos(bl.getPosition().toVec3(), ev.mDimensionId), ev.isMinecart);
            }
        }
        IF_LISTENED_END(EVENT_TYPES::onHopperSearchItem);
    });

    Event::HopperPushOutEvent::subscribe([](const HopperPushOutEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onHopperPushOut)
        {
            CallEvent(EVENT_TYPES::onHopperPushOut, FloatPos::newPos(ev.mPos, ev.mDimensionId));
        }
        IF_LISTENED_END(EVENT_TYPES::onHopperPushOut);
    });

    Event::FireSpreadEvent::subscribe([](const FireSpreadEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onFireSpread)
        {
            CallEvent(EVENT_TYPES::onFireSpread, IntPos::newPos(ev.mTarget,ev.mDimensionId));
        }
        IF_LISTENED_END(EVENT_TYPES::onFireSpread);
    });

    Event::BlockChangedEvent::subscribe([](const BlockChangedEvent& ev) {
        IF_LISTENED(EVENT_TYPES::onBlockChanged)
        {
            CallEvent(EVENT_TYPES::onBlockChanged, BlockClass::newBlock(ev.mPerviousBlockInstance),
                BlockClass::newBlock(ev.mNewBlockInstance));
        }
        IF_LISTENED_END(EVENT_TYPES::onBlockChanged);
    });

    Event::PlayerScoreChangedEvent::subscribe([](const PlayerScoreChangedEvent &ev) {
        IF_LISTENED(EVENT_TYPES::onScoreChanged)
        {
            CallEvent(EVENT_TYPES::onScoreChanged, PlayerClass::newPlayer(ev.mPlayer),
                Number::newNumber(ev.mScore),String::newString(ev.mObjective->getName()),
                String::newString(ev.mObjective->getDisplayName()));
        }
        IF_LISTENED_END(EVENT_TYPES::onScoreChanged);
    });

    Event::ConsoleOutputEvent::subscribe([](const ConsoleOutputEvent &ev) {
        IF_LISTENED(EVENT_TYPES::onConsoleOutput)
        {
            CallEvent(EVENT_TYPES::onConsoleOutput, String::newString(ev.mOutput));
        }
        IF_LISTENED_END(EVENT_TYPES::onConsoleOutput);
    });
    
    Event::ConsoleCmdEvent::subscribe([](const ConsoleCmdEvent& ev) {
        try
        {
            string cmd = ev.mCommand;

            // PreProcess
            if (!ProcessDebugEngine(cmd))
                return false;
            ProcessStopServer(cmd);
            if (!ProcessHotManageCmd(cmd))
                return false;

            //CallEvents
            vector<string> paras;
            bool isFromOtherEngine = false;
            string prefix = LxlFindCmdReg(false, cmd, paras, &isFromOtherEngine);

            if (!prefix.empty())
            {
                //Lxl Registered Cmd

                bool callbackRes = CallServerCmdCallback(prefix, paras);
                IF_LISTENED(EVENT_TYPES::onConsoleCmd)
                {
                    CallEvent(EVENT_TYPES::onConsoleCmd, String::newString(cmd));
                }
                IF_LISTENED_END(EVENT_TYPES::onConsoleCmd);
                if (!callbackRes)
                    return false;
            }
            else
            {
                if (isFromOtherEngine)
                    return false;

                //Other Cmd
                IF_LISTENED(EVENT_TYPES::onConsoleCmd)
                {
                    CallEvent(EVENT_TYPES::onConsoleCmd, String::newString(cmd));
                }
                IF_LISTENED_END(EVENT_TYPES::onConsoleCmd);
            }
        }
        catch (...)
        {
            logger.error("Event Callback Failed!");
            logger.error("Uncaught Exception Detected!");
            logger.error("In Event: onConsoleCmd");
        }
        return true;
    });

// For RegisterCmd...
    Event::RegCmdEvent::subscribe([](const RegCmdEvent& ev)
    {
        isCmdRegisterEnabled = true;

        //处理延迟注册
        ProcessRegCmdQueue();
        return true;
    });


// ===== onServerStarted =====
    Event::ServerStartedEvent::subscribe([](auto ev)
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
            }

            IF_LISTENED(EVENT_TYPES::onServerStarted)
            {
                CallEventDelayed(EVENT_TYPES::onServerStarted);
            }
            IF_LISTENED_END(EVENT_TYPES::onServerStarted);
        }
        return true;
    });
}

inline bool CallTickEvent()
{
    IF_LISTENED(EVENT_TYPES::onTick)
    {
        CallEvent(EVENT_TYPES::onTick);
    }
    IF_LISTENED_END(EVENT_TYPES::onTick);
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
            engine->messageQueue()->loopQueue(script::utils::MessageQueue::LoopType::kLoopOnce);
        }
    }
    catch (...)
    {
        logger.error("Error occurred in Engine Message Loop!");
        logger.error("Uncaught Exception Detected!");
    }

    CallTickEvent();
    return original(_this);
}

bool CallFireworkShootWithCrossbow(Player* pl)
{
    IF_LISTENED(EVENT_TYPES::onFireworkShootWithCrossbow)
    {
        CallEvent(EVENT_TYPES::onFireworkShootWithCrossbow, PlayerClass::newPlayer(pl));
    }
    IF_LISTENED_END(EVENT_TYPES::onFireworkShootWithCrossbow);
}

// ===== onFireworkShootWithCrossbow =====
THook(void, "?_shootFirework@CrossbowItem@@AEBAXAEBVItemInstance@@AEAVPlayer@@@Z",
    void* a1, void* a2, Player* a3)
{
    if (!CallFireworkShootWithCrossbow(a3))
        return;
    original(a1, a2, a3);
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

/* ==== = onSplashPotionHitEffect ==== =
THook(void, "?doOnHitEffect@SplashPotionEffectSubcomponent@@UEAAXAEAVActor@@AEAVProjectileComponent@@@Z",
    void* _this, Actor* a2, ProjectileComponent* a3)
*/

/* ==== = onFishingHookRetrieve ==== =
THook(__int64, "?retrieve@FishingHook@@QEAAHXZ",
    FishingHook* _this)
*/


bool MoneyEventCallback(LLMoneyEvent type, xuid_t from, xuid_t to, money_t value)
{
    switch (type)
    {
        case LLMoneyEvent::Add:
        {
            IF_LISTENED(EVENT_TYPES::onMoneyAdd)
            {
                CallEvent(EVENT_TYPES::onMoneyAdd, String::newString(to), Number::newNumber(value));
            }
            IF_LISTENED_END(EVENT_TYPES::onMoneyAdd);
            break;
        }
        case LLMoneyEvent::Reduce:
        {
            IF_LISTENED(EVENT_TYPES::onMoneyReduce)
            {
                CallEvent(EVENT_TYPES::onMoneyReduce, String::newString(to), Number::newNumber(value));
            }
            IF_LISTENED_END(EVENT_TYPES::onMoneyReduce);
            break;
        }
        case LLMoneyEvent::Trans:
        {
            IF_LISTENED(EVENT_TYPES::onMoneyTrans)
            {
                CallEvent(EVENT_TYPES::onMoneyTrans, String::newString(from), String::newString(to), Number::newNumber(value));
            }
            IF_LISTENED_END(EVENT_TYPES::onMoneyTrans);
            break;
        }
        case LLMoneyEvent::Set:
        {
            IF_LISTENED(EVENT_TYPES::onMoneySet)
            {
                CallEvent(EVENT_TYPES::onMoneySet, String::newString(to), Number::newNumber(value));
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