#include <string>
#include <vector>

class Player;
class Container;
class ItemStack;
class IntVec4;
class FloatVec4;
class ActorUniqueID;

std::string Raw_GetPlayerName(Player* player);
FloatVec4 Raw_GetPlayerPos(Player* player);
IntVec4 Raw_GetPlayerBlockPos(Player* player);
std::string Raw_GetXuid(Player* player);
std::string Raw_GetUuid(Player *player);
std::string Raw_GetRealName(Player* player);
int Raw_GetPlayerPermLevel(Player* player);
int Raw_GetGameMode(Player* player);
bool Raw_GetSneaking(Player *player);

bool Raw_RuncmdAs(Player *player, const std::string &cmd);
bool Raw_TeleportPlayer(Player* player, const FloatVec4 &pos);
bool Raw_KillPlayer(Player* player);
bool Raw_HurtPlayer(Player* player, int damage);
bool Raw_SetPlayerPermLevel(Player* player, int permLevel);
bool Raw_SetGameMode(Player* player, int gameMode);
bool Raw_KickPlayer(Player* player, const std::string &msg);
bool Raw_Tell(Player* player, const std::string &text, TextType type = TextType::RAW);
bool Raw_TalkAs(Player* player, const std::string& text);
bool Raw_Broadcast(const std::string& text, TextType type = TextType::RAW);
bool Raw_RenamePlayer(Player* player, const std::string &name);
bool Raw_AddLevel(Player* player, int level);
bool Raw_TransServer(Player* player, const std::string& server, short port);
bool Raw_CrashPlayer(Player* player);
bool Raw_RefreshChunks(Player* player);
bool Raw_GiveItem(Player* player, ItemStack* item);
int Raw_ClearItem(Player *player, std::string type);

ItemStack* Raw_GetHand(Player* player);
ItemStack* Raw_GetOffHand(Player* player);
Container* Raw_GetInventory(Player* pl);
Container* Raw_GetArmor(Player* pl);
Container* Raw_GetEnderChest(Player* pl);
bool Raw_RefreshItems(Player* pl);

bool Raw_SetSidebar(Player *player, std::string title, const std::vector<std::pair<std::string,int>> &data, int sortOrder);
bool Raw_RemoveSidebar(Player *player);
bool Raw_SetBossBar(Player *player, std::string title, float percent);
bool Raw_RemoveBossBar(Player *player);

std::vector<Player*> Raw_GetOnlinePlayers();
bool Raw_IsPlayerValid(Player *player);

int Raw_GetPlayerDimId(Player* player);
Player* Raw_GetPlayerByUniqueId(ActorUniqueID id);