#pragma once
#include "APIHelp.h"

#include <MC/Tag.hpp>

extern struct Tag;
extern ClassDefine<void> NbtStaticBuilder;

//NBT Static
class NbtStatic : public ScriptClass
{
public:
    static Local<Value> newTag(const Arguments& args);
    static Local<Value> parseSNBT(const Arguments& args);
    static Local<Value> parseBinaryNBT(const Arguments& args);

    template<Tag::Type T>
    static Local<Value> getType()
    {
        return Number::newNumber((int)T);
    }
};
extern ClassDefine<void> NbtStaticBuilder;


//NBT End
class EndTag;
class NbtEndClass : public ScriptClass
{
public:
    EndTag* nbt;
    explicit NbtEndClass(const Local<Object>& scriptObj, EndTag* p, bool canDelete = false);
    explicit NbtEndClass(EndTag* p, bool canDelete = false);
    ~NbtEndClass() = default;
    static NbtEndClass* constructor(const Arguments& args);
    static EndTag* extract(Local<Value> v);
    static Local<Value> pack(EndTag* tag, bool canDelete = false);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtEndClass> NbtEndClassBuilder;


//NBT Byte
class NbtByteClass : public ScriptClass 
{
public:
    ByteTag* nbt;
    explicit NbtByteClass(const Local<Object>& scriptObj, ByteTag* p, bool canDelete = false);
    explicit NbtByteClass(ByteTag* p, bool canDelete = false);
    NbtByteClass() = default;
    static NbtByteClass* constructor(const Arguments& args);
    static ByteTag* extract(Local<Value> v);
    static Local<Value> pack(ByteTag* tag, bool canDelete = false);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtByteClass> NbtByteClassBuilder;


//NBT Short
class NbtShortClass : public ScriptClass
{
public:
    ShortTag* nbt;
    explicit NbtShortClass(const Local<Object>& scriptObj, ShortTag* p, bool canDelete = false);
    explicit NbtShortClass(ShortTag* p, bool canDelete = false);
    ~NbtShortClass() = default;
    static NbtShortClass* constructor(const Arguments& args);
    static ShortTag* extract(Local<Value> v);
    static Local<Value> pack(ShortTag* tag, bool canDelete = false);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtShortClass> NbtShortClassBuilder;


//NBT Int
class NbtIntClass : public ScriptClass
{
public:
    IntTag* nbt;
    explicit NbtIntClass(const Local<Object>& scriptObj, IntTag* p, bool canDelete = false);
    explicit NbtIntClass(IntTag* p, bool canDelete = false);
    ~NbtIntClass() = default;
    static NbtIntClass* constructor(const Arguments& args);
    static IntTag* extract(Local<Value> v);
    static Local<Value> pack(IntTag* tag, bool canDelete = false);
    
    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtIntClass> NbtIntClassBuilder;


//NBT Long
class NbtLongClass : public ScriptClass
{
public:
    Int64Tag* nbt;
    explicit NbtLongClass(const Local<Object>& scriptObj, Int64Tag* p, bool canDelete = false);
    explicit NbtLongClass(Int64Tag* p, bool canDelete = false);
    ~NbtLongClass() = default;
    static NbtLongClass* constructor(const Arguments& args);
    static Int64Tag* extract(Local<Value> v);
    static Local<Value> pack(Int64Tag* tag, bool canDelete = false);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtLongClass> NbtLongClassBuilder;


//NBT Float
class NbtFloatClass : public ScriptClass
{
public:
    FloatTag* nbt;
    explicit NbtFloatClass(const Local<Object>& scriptObj, FloatTag* p, bool canDelete = false);
    explicit NbtFloatClass(FloatTag* p, bool canDelete = false);
    ~NbtFloatClass() = default;
    static NbtFloatClass* constructor(const Arguments& args);
    static FloatTag* extract(Local<Value> v);
    static Local<Value> pack(FloatTag* tag, bool canDelete = false);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtFloatClass> NbtFloatClassBuilder;


//NBT Double
class NbtDoubleClass : public ScriptClass
{
public:
    DoubleTag* nbt;
    explicit NbtDoubleClass(const Local<Object>& scriptObj, DoubleTag* p, bool canDelete = false);
    explicit NbtDoubleClass(DoubleTag* p, bool canDelete = false);
    ~NbtDoubleClass() = default;
    static NbtDoubleClass* constructor(const Arguments& args);
    static DoubleTag* extract(Local<Value> v);
    static Local<Value> pack(DoubleTag* tag, bool canDelete = false);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtDoubleClass> NbtDoubleClassBuilder;


//NBT String
class NbtStringClass : public ScriptClass
{
public:
    StringTag* nbt;
    explicit NbtStringClass(const Local<Object>& scriptObj, StringTag* p, bool canDelete = false);
    explicit NbtStringClass(StringTag* p, bool canDelete = false);
    ~NbtStringClass() = default;
    static NbtStringClass* constructor(const Arguments& args);
    static StringTag* extract(Local<Value> v);
    static Local<Value> pack(StringTag* tag, bool canDelete = false);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtStringClass> NbtStringClassBuilder;


//NBT ByteArray
class NbtByteArrayClass : public ScriptClass
{
public:
    ByteArrayTag* nbt;
    explicit NbtByteArrayClass(const Local<Object>& scriptObj, ByteArrayTag* p, bool canDelete = false);
    explicit NbtByteArrayClass(ByteArrayTag* p, bool canDelete = false);
    ~NbtByteArrayClass() = default;
    static NbtByteArrayClass* constructor(const Arguments& args);
    static ByteArrayTag* extract(Local<Value> v);
    static Local<Value> pack(ByteArrayTag* tag, bool canDelete = false);

    Local<Value> getType(const Arguments& args);
    Local<Value> set(const Arguments& args);
    Local<Value> get(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtByteArrayClass> NbtByteArrayClassBuilder;


//NBT List
class NbtListClass : public ScriptClass
{
public:
    ListTag* nbt;
    explicit NbtListClass(const Local<Object>& scriptObj, ListTag* p, bool canDelete = false);
    explicit NbtListClass(ListTag* p, bool canDelete = false);
    ~NbtListClass() = default;
    static NbtListClass* constructor(const Arguments& args);
    static ListTag* extract(Local<Value> v);
    static Local<Value> pack(ListTag* tag, bool canDelete = false);
    
    Local<Value> getType(const Arguments& args);
    Local<Value> getSize(const Arguments& args);
    Local<Value> getTypeOf(const Arguments& args);

    Local<Value> setEnd(const Arguments& args);
    Local<Value> setByte(const Arguments& args);
    Local<Value> setInt(const Arguments& args);
    Local<Value> setShort(const Arguments& args);
    Local<Value> setLong(const Arguments& args);
    Local<Value> setFloat(const Arguments& args);
    Local<Value> setDouble(const Arguments& args);
    Local<Value> setString(const Arguments& args);
    Local<Value> setByteArray(const Arguments& args);
    Local<Value> setTag(const Arguments& args);
    Local<Value> addTag(const Arguments& args);
    Local<Value> removeTag(const Arguments& args);

    Local<Value> getData(const Arguments& args);
    Local<Value> getTag(const Arguments& args);

    Local<Value> toArray(const Arguments& args);
    Local<Value> toString(const Arguments& args);
};
extern ClassDefine<NbtListClass> NbtListClassBuilder;


//NBT Compound
class NbtCompoundClass : public ScriptClass
{
public:
    CompoundTag* nbt;
    explicit NbtCompoundClass(const Local<Object>& scriptObj, CompoundTag* p, bool canDelete = false);
    explicit NbtCompoundClass(CompoundTag* p, bool canDelete = false);
    ~NbtCompoundClass() = default;
    static NbtCompoundClass* constructor(const Arguments& args);
    static CompoundTag* extract(Local<Value> v);
    static Local<Value> pack(CompoundTag* tag, bool canDelete = false);

    Local<Value> getType(const Arguments& args);
    Local<Value> getKeys(const Arguments& args);
    Local<Value> getTypeOf(const Arguments& args);

    Local<Value> setEnd(const Arguments& args);
    Local<Value> setByte(const Arguments& args);
    Local<Value> setInt(const Arguments& args);
    Local<Value> setShort(const Arguments& args);
    Local<Value> setLong(const Arguments& args);
    Local<Value> setFloat(const Arguments& args);
    Local<Value> setDouble(const Arguments& args);
    Local<Value> setString(const Arguments& args);
    Local<Value> setByteArray(const Arguments& args);
    Local<Value> setTag(const Arguments& args);
    Local<Value> removeTag(const Arguments& args);

    Local<Value> getData(const Arguments& args);
    Local<Value> getTag(const Arguments& args);

    Local<Value> toObject(const Arguments& args);
    Local<Value> toSNBT(const Arguments& args);
    Local<Value> toBinaryNBT(const Arguments& args);
    Local<Value> toString(const Arguments& args);

    Local<Value> destroy(const Arguments& args);
};
extern ClassDefine<NbtCompoundClass> NbtCompoundClassBuilder;


//Helper
bool IsNbtClass(Local<Value> value);
Local<Value> Tag2Value(Tag* nbt, bool autoExpansion = false);
bool TagSetValue(Tag::Type type, Tag* nbt, Local<Value> value = Local<Value>());