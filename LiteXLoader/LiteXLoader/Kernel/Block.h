#pragma once
#include <string>

class Block;
class Container;
class IntVec4;
class FloatVec4;
class Actor;

std::string Raw_GetBlockName(Block* block);
std::string Raw_GetBlockType(Block* block);
int Raw_GetBlockId(Block* block);

Block* Raw_NewBlockFromName(string str);
bool Raw_SetBlockByBlock(IntVec4 pos, Block* block);
bool Raw_SetBlockByName(IntVec4 pos, const string &name);
bool Raw_SpawnParticle(FloatVec4 pos, const string& type);

bool Raw_ResendBlocksAroundPlayer(Player* pl, IntVec4 pos);