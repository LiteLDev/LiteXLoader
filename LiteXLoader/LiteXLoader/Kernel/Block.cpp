#include "Global.h"
#include "Block.h"
#include "Packet.h"
#include "Player.h"
#include "SymbolHelper.h"
using namespace std;

string Raw_GetBlockName(Block* block)
{
    HashedString* hashedstr = SymCall("?getName@Block@@QEBAAEBVHashedString@@XZ",
        HashedString*, void*)(block);

    return hashedstr->getString();
}

std::string Raw_GetBlockType(Block* block)
{
    BlockLegacy* blockLegacy = offBlock::getLegacyBlock(block);
    return offBlockLegacy::getFullName(blockLegacy);
}

int Raw_GetBlockId(Block* block)
{
    BlockLegacy* blockLegacy = offBlock::getLegacyBlock(block);
    return blockLegacy->getBlockItemId();
}

struct BlockPalette;
Block* Raw_NewBlockFromNameAndState(string name, unsigned short state)
{
    BlockPalette* generator = SymCall("?getBlockPalette@Level@@UEBAAEBVBlockPalette@@XZ", BlockPalette*, Level*)(mc->getLevel());
    BlockLegacy* blk = SymCall("?getBlockLegacy@BlockPalette@@QEBAPEBVBlockLegacy@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
        BlockLegacy*, void*, string*)(generator, &name);
    return SymCall("?getStateFromLegacyData@BlockLegacy@@UEBAAEBVBlock@@G@Z", Block*, BlockLegacy*, unsigned short)(blk, state);    //SetBlockCommand::execute
}

bool Raw_SetBlockByBlock(IntVec4 pos, Block* block)
{
    BlockSource* bs = Raw_GetBlockSourceByDim(pos.dim);

    if (!SymCall("?setBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@HPEBUActorBlockSyncMessage@@@Z", 
        bool, BlockSource*, BlockPos, Block*, int, void*) (bs, { pos.x, pos.y, pos.z }, block, 0, nullptr))
        return false;

    auto pls = Raw_GetOnlinePlayers();
    for (auto& pl : pls)
        Raw_ResendBlocksAroundPlayer(pl,pos);
    return true;
}

bool Raw_SetBlockByNameAndState(IntVec4 pos, const string& name, unsigned short state)
{
    Block* newBlock = Raw_NewBlockFromNameAndState(name, state);
    if (!newBlock)
        return false;
    return Raw_SetBlockByBlock(pos, newBlock);
}

bool Raw_SpawnParticle(FloatVec4 pos, const string& type)
{
    string name = type;
    Level* level = mc->getLevel();
    Dimension *dim = SymCall("?getDimension@Level@@UEBAPEAVDimension@@V?$AutomaticID@VDimension@@H@@@Z",
        Dimension*, void*, AutomaticID<Dimension, int>)(level, AutomaticID<Dimension, int>(pos.dim));

    SymCall("?spawnParticleEffect@Level@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVVec3@@PEAVDimension@@@Z",
        void, Level*, string&, const Vec3&, void*)
        (level, name, { pos.x,pos.y,pos.z }, dim);

    return true;
}

bool Raw_ResendBlocksAroundPlayer(Player* pl, IntVec4 pos)
{
    BlockPos bp{ pos.x,pos.y,pos.z };
    SymCall("?resendBlocksAroundArea@ItemUseInventoryTransaction@@QEBAXAEAVPlayer@@AEBVBlockPos@@E@Z",
        void, void*, Player*, BlockPos*, char)(nullptr, pl, &bp, 0);     // this* has not been used
    return true;
}