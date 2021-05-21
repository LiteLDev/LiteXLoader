#include "APIhelp.h"
#include "BlockAPI.h"
#include "../Kernel/Block.h"
using namespace script;

BlockClass::BlockClass(Block *p)
    :ScriptClass(ScriptClass::ConstructFromCpp<BlockClass>{}),block(p)
{
    name = Raw_GetBlockName(block);
    pos = {0,0,0,-1};
}

BlockClass::BlockClass(Block *p, BlockPos bp, int dim)
    :ScriptClass(ScriptClass::ConstructFromCpp<BlockClass>{}),block(p)
{
    name = Raw_GetBlockName(block);
    pos = {bp.x,bp.y,bp.z,dim};
}

//生成函数
Local<Object> BlockClass::newBlock(Block *p)
{
    auto newp = new BlockClass(p);
    return newp->getScriptObject();
}
Local<Object> BlockClass::newBlock(Block *p, BlockPos *pos)
{
    auto newp = new BlockClass(p,*pos,-1);
    return newp->getScriptObject();
}
Local<Object> BlockClass::newBlock(Block *p, BlockPos *pos, BlockSource *bs)
{
    auto newp = new BlockClass(p,*pos,Raw_GetBlockDimension(bs));
    return newp->getScriptObject();
}
Local<Object> BlockClass::newBlock(WBlock p)
{
    return BlockClass::newBlock(p.v);
}
Block* BlockClass::extractBlock(Local<Value> v)
{
    if(EngineScope::currentEngine()->isInstanceOf<BlockClass>(v))
        return EngineScope::currentEngine()->getNativeInstance<BlockClass>(v)->get();
    else
        return nullptr;
}

//成员函数
Local<Value> BlockClass::getName()
{
    try{
        //return String::newString(Raw_GetBlockName(block));
        return String::newString(name);
    }
    CATCH("Fail in GetBlockName!")
}

Local<Value> BlockClass::getPos()
{
    try{
        return IntPos::newPos(pos);
    }
    CATCH("Fail in GetBlockPos!")
}