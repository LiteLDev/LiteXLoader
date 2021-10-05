#include "Global.h"
#include "Player.h"
#include "Packet.h"
#include "Entity.h"
#include "Item.h"
#include "Container.h"
#include "SymbolHelper.h"
#include "Scoreboard.h"
#include "ThirdParty.h"
#include "Global.h"
#include <bitset>
using namespace std;
class NetworkHandler;
string  Raw_GetPlayerName(Player* player)
{
    return player->getNameTag();
}

FloatVec4 Raw_GetPlayerPos(Player* player)
{
    return Raw_GetEntityPos((Actor*)player);
}

IntVec4 Raw_GetPlayerBlockPos(Player* player)
{
    return Raw_GetEntityBlockPos((Actor*)player);
}

string Raw_GetXuid(Player* player)
{
    return offPlayer::getXUIDString(player);
}

std::string Raw_GetUuid(Player *player)
{
    string uuid;
    SymCall("?asString@UUID@mce@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
        string *, void*, string *)((unsigned*)((uintptr_t)player+2976), &uuid);
    return uuid;
}

string  Raw_GetRealName(Player* player)
{
    return offPlayer::getRealName(player);
}

int Raw_GetPlayerPermLevel(Player* player)
{
    return (int)WPlayer(*player).getPermLvl();
}

int Raw_GetGameMode(Player* player)
{
    return SymCall("?getPlayerGameType@Player@@QEBA?AW4GameType@@XZ", unsigned short, Player*)(player);
}

bool Raw_GetSneaking(Player *player)
{
    return SymCall("?isSneaking@Actor@@QEBA_NXZ", bool, Player*)(player);
}

bool  Raw_RuncmdAs(Player *player, const string &cmd)
{
    //return liteloader::runcmdAs(player,cmd);
    return Raw_SendCommandRequestPacket(player, cmd);
}

bool Raw_TeleportPlayer(Player* player, const FloatVec4 &pos)
{
    WPlayer(*player).teleport({pos.x,pos.y,pos.z}  ,pos.dim);
    return true;
}

bool Raw_KillPlayer(Player* player)
{
    SymCall("?kill@Mob@@UEAAXXZ", void, void*)((Actor*)player);
    return true;
}

bool Raw_HurtPlayer(Player *player, int damage)
{
    char a[16];
    ActorDamageSource* ad = SymCall("??0ActorDamageSource@@QEAA@W4ActorDamageCause@@@Z",
        ActorDamageSource*, ActorDamageSource*, int)((ActorDamageSource*)a, 12);    //ActorDamageCause::Void
    return SymCall("?_hurt@Player@@MEAA_NAEBVActorDamageSource@@H_N1@Z",
        bool, Player*, ActorDamageSource*, int, bool, bool)(player, ad, damage, true, false);
}

bool Raw_SetPlayerPermLevel(Player* player, int permLevel)
{
    ((ServerPlayer*)player)->setPermissions((CommandPermissionLevel)permLevel);
    return true;
}

bool Raw_SetGameMode(Player* player, int gameMode)
{
    SymCall("?setPlayerGameType@Player@@UEAAXW4GameType@@@Z", void, Player*, unsigned short)(player, (unsigned short)gameMode);
    return true;        //############ 加上发包给客户端 ############
}

bool Raw_KickPlayer(Player* player, const string &msg)
{
    extern Minecraft *mc;
    auto nh = mc->getServerNetworkHandler();
    NetworkIdentifier* a = offPlayer::getNetworkIdentifier(player);
    nh->disconnectClient(*(NetworkIdentifier*)a, msg, 0);
    return true;
}

bool Raw_Tell(Player* player, const string &text, TextType type)
{
    WPlayer(*player).sendText(text,type);
    return true;
}

bool Raw_TalkAs(Player* player, const std::string& text)
{
    return Raw_SendTextTalkPacket(player, text);
}

bool Raw_Broadcast(const std::string& text, TextType type)
{
    auto playerList = Raw_GetOnlinePlayers();
    for (auto player : playerList)
        Raw_Tell(player, text, type);
    return true;
}

ItemStack* Raw_GetHand(Player* player)
{
    return (ItemStack*)&(player->getSelectedItem());
}

ItemStack* Raw_GetOffHand(Player* player)
{
    return SymCall("?getOffhandSlot@Actor@@QEBAAEBVItemStack@@XZ", ItemStack*, Player*)(player);
}

Container* Raw_GetInventory(Player* pl)
{
    return SymCall("?getInventory@Player@@QEAAAEAVContainer@@XZ", Container*, 
        Player*)(pl);
}

Container* Raw_GetArmor(Player* pl)
{
    return Raw_GetArmor((Actor*)pl);
}

Container* Raw_GetEnderChest(Player* pl)
{
    return dAccess<Container*>(pl, 4440);       //IDA ReplaceItemCommand::execute 1086 
}

bool Raw_RefreshItems(Player* pl)
{
    SymCall("?sendInventory@ServerPlayer@@UEAAX_N@Z",void,ServerPlayer*,bool)((ServerPlayer*)pl, true);
    bitset<4> bits("1111");
    SymCall("?sendArmor@ServerPlayer@@UEAAXAEBV?$bitset@$03@std@@@Z", void, ServerPlayer*, bitset<4>*)((ServerPlayer*)pl, &bits);
    return true;
}

bool Raw_RenamePlayer(Player* player, const string &name)
{
    player->setNameTag(name);
    Raw_RefreshActorData((Actor*)player);
    return true;
}

bool Raw_AddLevel(Player* player, int level)
{
    SymCall("?addLevels@Player@@UEAAXH@Z", void, Player*, int)(player, level);
    return true;
}

bool Raw_TransServer(Player* player, const std::string& server, short port)
{
    return Raw_SendTransferPacket(player, server, port);
}

bool Raw_CrashPlayer(Player* player)
{
    return Raw_SendCrashClientPacket(player);
}

bool Raw_RefreshChunks(Player* player)
{
    SymCall("?resendAllChunks@ServerPlayer@@UEAAXXZ", void, Player*)(player);
    return true;
}

bool Raw_GiveItem(Player* player, ItemStack* item)
{
    bool res = SymCall("?add@Player@@UEAA_NAEAVItemStack@@@Z", bool, Player*, ItemStack*)(player, item);
    Raw_RefreshItems(player);
    return res;
}

int Raw_ClearItem(Player *player, std::string type)
{
    int res = 0;

    //Hand
    ItemStack* item = Raw_GetHand(player);
    if (Raw_GetItemTypeName(item) == type)
    {
        Raw_SetNull(item);
        ++res;
    }

    //OffHand
    item = Raw_GetOffHand(player);
    if (Raw_GetItemTypeName(item) == type)
    {
        Raw_SetNull(item);
        ++res;
    }

    //Inventory
    Container* container = Raw_GetInventory(player);
    auto items = Raw_GetAllSlots(container);
    for (int i = 0; i < Raw_GetContainerSize(container); ++i)
    {
        if (Raw_GetItemTypeName(items[i]) == type)
        {
            int cnt = Raw_GetCount(items[i]);
            Raw_RemoveItem(container, i, cnt);
            res += cnt;
        }
    }

    //Armor
    container = Raw_GetArmor(player);
    items = Raw_GetAllSlots(container);
    for (int i = 0; i < Raw_GetContainerSize(container); ++i)
    {
        if (Raw_GetItemTypeName(items[i]) == type)
        {
            int cnt = Raw_GetCount(items[i]);
            Raw_RemoveItem(container, i, cnt);
            res += cnt;
        }
    }

    Raw_RefreshItems(player);
    return res;
}

bool Raw_SetSidebar(Player *player, std::string title, const std::vector<std::pair<std::string,int>> &data, int sortOrder)
{
    Raw_SendSetDisplayObjectivePacket(player, title, "FakeScoreObj", (char)sortOrder);

    vector<ScorePacketInfo> info;
    for (auto& x : data)
    {
        ScoreboardId* id = SymCall("?createScoreboardId@ServerScoreboard@@UEAAAEBUScoreboardId@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
            ScoreboardId*, Scoreboard* ,const string*)(globalScoreBoard, &x.first);
        ScorePacketInfo i(id,x.second,x.first);
        info.emplace_back(i);
    }

    Raw_SendSetScorePacket(player, 0, info);    //set
    Raw_SendSetDisplayObjectivePacket(player, title, "FakeScoreObj", (char)sortOrder);
    return true;
}

bool Raw_RemoveSidebar(Player *player)
{
    return Raw_SendSetDisplayObjectivePacket(player, "", "", 0);
}

bool Raw_SetBossBar(Player *player, std::string title, float percent)
{
    return Raw_SendBossEventPacket(player, title, percent, 0);
}

bool Raw_RemoveBossBar(Player *player)
{
    return Raw_SendBossEventPacket(player, "", 0, 2);;
}

vector<Player*> Raw_GetOnlinePlayers()
{
    try
    {
        return isServerStarted ? liteloader::getAllPlayers() : vector<Player*>();
    }
    catch (const seh_exception& e)
    {
        return vector<Player*>();
    }
}

bool Raw_IsPlayerValid(Player *player)
{
    auto playerList = Raw_GetOnlinePlayers();
    for(auto p : playerList)
        if(p == player)
            return true;
    return false;
}

int Raw_GetPlayerDimId(Player* player)
{
    return WPlayer(*player).getDimID();
}

Player* Raw_GetPlayerByUniqueId(ActorUniqueID id) {
    return SymCall("?getPlayer@Level@@UEBAPEAVPlayer@@UActorUniqueID@@@Z"
        , Player*, Level*, ActorUniqueID)(mc->getLevel(), id);
}