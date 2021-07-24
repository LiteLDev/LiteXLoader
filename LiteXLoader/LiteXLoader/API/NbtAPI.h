#pragma once
#include <ScriptX/ScriptX.h>
using namespace script;

extern struct Tag;
class NBTClass : public ScriptClass
{
private:
    Tag* nbt;
public:
    explicit NBTClass(Tag* p);

    static Tag* extractNBT(Local<Value> v);
    static Local<Object> newNBT(Tag* p);

    Local<Value> readInt(const Arguments& args);
    Local<Value> readShort(const Arguments& args);
    Local<Value> readLong(const Arguments& args);
    Local<Value> readFloat(const Arguments& args);
    Local<Value> readDouble(const Arguments& args);
    Local<Value> readBoolean(const Arguments& args);
    Local<Value> readString(const Arguments& args);
    Local<Value> readList(const Arguments& args);
    Local<Value> readCompound(const Arguments& args);
    Local<Value> readByte(const Arguments& args);

    Local<Value> writeInt(const Arguments& args);
    Local<Value> writeLong(const Arguments& args);
    Local<Value> writeFloat(const Arguments& args);
    Local<Value> writeBoolean(const Arguments& args);
    Local<Value> writeString(const Arguments& args);
    Local<Value> writeByte(const Arguments& args);
    Local<Value> writeList(const Arguments& args);
    Local<Value> writeCompound(const Arguments& args);
    Local<Value> addValueToList(const Arguments& args);

    Local<Value> createTag(const Arguments& args);
    Local<Value> getType(const Arguments& args);

    Local<Value> setItem(const Arguments& args);
};

Local<Value> fromItem(const Arguments& args);
Local<Value> fromPtr(const Arguments& args);
