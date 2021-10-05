#include "Global.h"
#include "Packet.h"
#include "Player.h"
#include "SymbolHelper.h"
#include "Scoreboard.h"
#include <cstdlib>
using namespace std;

#define RAND_FORM_ID() (unsigned)((rand()<<16)+rand())

Packet* Raw_CreatePacket(int type)
{
    unsigned long long packet[2] = { 0 };
    SymCall("?createPacket@MinecraftPackets@@SA?AV?$shared_ptr@VPacket@@@std@@W4MinecraftPacketIds@@@Z",
        void*, void*, int)(packet, type);
    return (Packet*)*packet;
}

bool Raw_SendPacket(Player *player,void *packet)
{
    ((ServerPlayer*)player)->sendNetworkPacket(*(Packet*)packet);
    return true;
}

int Raw_SendFormPacket(Player* player, const string &data)
{
    unsigned id = RAND_FORM_ID();

    Packet *packet = Raw_CreatePacket(100);   //表单数据包
    dAccess<unsigned>(packet, 48) = id;
    dAccess<string>(packet, 56) = data;

    Raw_SendPacket(player,packet);
    return id;
}

bool Raw_SendTransferPacket(Player* player, const string& address, short port)
{
    Packet*packet = Raw_CreatePacket(85);    //跨服传送数据包
    dAccess<string>(packet, 48) = address;
    dAccess<short>(packet, 80) = port;

    Raw_SendPacket(player, packet);
    return true;
}

bool Raw_SendSetDisplayObjectivePacket(Player* player, const string& title, const string& name, char sortOrder)
{
    Packet* packet = Raw_CreatePacket(107);   //显示侧边栏数据包
    dAccess<string>(packet, 48) = "sidebar";
    dAccess<string>(packet, 80) = name;
    dAccess<string>(packet, 112) = title;
    dAccess<string>(packet, 144) = "dummy";
    dAccess<char>(packet, 176) = sortOrder;
    
    return Raw_SendPacket(player, packet);
}

bool Raw_SendSetScorePacket(Player* player, char type, const vector<ScorePacketInfo>& data)
{
    Packet* packet = Raw_CreatePacket(108);   //修改分数数据包
    dAccess<char>(packet, 48) = type;
    dAccess<vector<ScorePacketInfo>>(packet, 56) = data;

    return Raw_SendPacket(player, packet);
}

bool Raw_SendBossEventPacket(Player* player, string name, float percent, int type)
{
    Packet* packet = Raw_CreatePacket(74);   //Boss事件数据包
    dAccess<ActorUniqueID>(packet, 56) = dAccess<ActorUniqueID>(packet, 64) = player->getUniqueID();
    dAccess<int>(packet, 72) = type;    //0显示, 1更新, 2隐藏
    dAccess<string>(packet, 80) = name;
    dAccess<float>(packet, 112) = percent;
   
    return Raw_SendPacket(player, packet);
}

bool Raw_SendCrashClientPacket(Player* player)
{
    Packet* pkt = Raw_CreatePacket(58);
    dAccess<int, 14>(pkt) = 0;
    dAccess<int, 15>(pkt) = 0;
    dAccess<bool, 48>(pkt) = 1;

    return Raw_SendPacket(player, pkt);
}

bool Raw_SendCommandRequestPacket(Player* player,const string &cmd)
{
    Packet* pkt = Raw_CreatePacket(77);
    dAccess<string, 48>(pkt) = cmd;
    
    void* clientId = SymCall("?getClientId@Player@@QEBAAEBVNetworkIdentifier@@XZ",
        void*, Player*)(player);
    SymCall("?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVCommandRequestPacket@@@Z",
        void, ServerNetworkHandler*, void*, void*)(mc->getServerNetworkHandler(), clientId, pkt);
    return true;
}

bool Raw_SendTextTalkPacket(Player* player, const string& msg)
{
    Packet* pkt = Raw_CreatePacket(0x09);  //Text Packet
    dAccess<unsigned char, 48>(pkt) = 1;
    dAccess<string, 56>(pkt) = "";
    dAccess<string, 88>(pkt) = msg;

    void* clientId = SymCall("?getClientId@Player@@QEBAAEBVNetworkIdentifier@@XZ",
        void*, Player*)(player);
    SymCall("?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVTextPacket@@@Z",
        void, ServerNetworkHandler*, void*, void*)(mc->getServerNetworkHandler(), clientId, pkt);
    return true;
}

Player* Raw_GetPlayerFromPacket(ServerNetworkHandler* handler, NetworkIdentifier* id, Packet* packet)
{
    return SymCall("?_getServerPlayer@ServerNetworkHandler@@AEAAPEAVServerPlayer@@AEBVNetworkIdentifier@@E@Z",
        Player*, ServerNetworkHandler*, NetworkIdentifier*, char)(handler, id, dAccess<char>(packet,16));
}

Player* Raw_GetPlayerFromPacket(NetworkIdentifier* id, Packet* packet)
{
    return SymCall("?_getServerPlayer@ServerNetworkHandler@@AEAAPEAVServerPlayer@@AEBVNetworkIdentifier@@E@Z",
        Player*, ServerNetworkHandler*, NetworkIdentifier*, char)(mc->getServerNetworkHandler(), id, dAccess<char>(packet, 16));
}