#include "APIHelp.h"
#include "NbtAPI.h"
#include <Kernel/NBT.h>
#include <vector>
#include <LiteXLoader/API/ItemAPI.h>
using namespace script;


ClassDefine<NBTClass> NBTClassBuilder =
    defineClass<NBTClass>("NBT")
        .constructor(nullptr)
        .instanceFunction("readInt", &NBTClass::readInt)
        .instanceFunction("readShort",&NBTClass::readShort)
        .instanceFunction("readLong", &NBTClass::readLong)
        .instanceFunction("readString", &NBTClass::readString)
        .instanceFunction("readFloat", &NBTClass::readFloat)
        .instanceFunction("readDouble", &NBTClass::readDouble)
        .instanceFunction("readBoolean", &NBTClass::readBoolean)
        .instanceFunction("readByte", &NBTClass::readByte)
        .instanceFunction("readList", &NBTClass::readList)
        .instanceFunction("readCompound", &NBTClass::readCompound)
        .instanceFunction("writeInt",&NBTClass::writeInt)
        .instanceFunction("writeInt", &NBTClass::writeInt)
        .instanceFunction("writeLong", &NBTClass::writeLong)
        .instanceFunction("writeString", &NBTClass::writeString)
        .instanceFunction("writeFloat", &NBTClass::writeFloat)
        .instanceFunction("writeBoolean", &NBTClass::writeBoolean)
        .instanceFunction("writeByte", &NBTClass::writeByte)
        .instanceFunction("writeList", &NBTClass::writeList)
        .instanceFunction("writeCompound", &NBTClass::writeCompound)
        .instanceFunction("getType", &NBTClass::getType)
        .instanceFunction("createNBT", &NBTClass::createTag)
        .instanceFunction("setItem",&NBTClass::setItem)
        .function("fromItem",&fromItem)
        .function("fromPtr", &fromPtr)
        .build();


constexpr unsigned int H(const char* str)
{
    unsigned int hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + (*str++); /* times 33 */
    }
    hash &= ~(1 << 31); /* strip the highest bit */
    return hash;
}

NBTClass::NBTClass(Tag* p) :ScriptClass(ScriptClass::ConstructFromCpp<NBTClass>{})
{
	this->nbt = p;
}

Tag* NBTClass::extractNBT(Local<Value> v)
{
    if (EngineScope::currentEngine()->isInstanceOf<NBTClass>(v))
        return EngineScope::currentEngine()->getNativeInstance<NBTClass>(v)->nbt;
    else
        return nullptr;
}

Local<Object> NBTClass::newNBT(Tag* p)
{
    auto tmp = new NBTClass(p);
    return tmp->getScriptObject();
}

Local<Value> NBTClass::readInt(const Arguments& args)
{
    try {
        auto v = nbt->getValue<int>();
        return Number::newNumber(v);
    }
    CATCH("Fail in NBTreadInt!")
}

Local<Value> NBTClass::readShort(const Arguments& args)
{
    try {
        auto v = nbt->getValue<short>();
        return Number::newNumber(v);
    }
    CATCH("Fail in NBTreadShort!")
}

Local<Value> NBTClass::readLong(const Arguments& args)
{
    try {
        auto v = nbt->getValue<__int64>();
        return Number::newNumber(v);
    }
    CATCH("Fail in NBTreadLong!")
}

Local<Value> NBTClass::readFloat(const Arguments& args)
{
    try {
        auto v = nbt->getValue<float>();
        return Number::newNumber(v);
    }
    CATCH("Fail in NBTreadFloat!")
}

Local<Value> NBTClass::readDouble(const Arguments& args)
{
    try {
        auto v = nbt->getValue<double>();
        return Number::newNumber(v);
    }
    CATCH("Fail in NBTreadDouble!")
}

Local<Value> NBTClass::readBoolean(const Arguments& args)
{
    try {
        auto v = nbt->getValue<char>();
        return Boolean::newBoolean(v);
    }
    CATCH("Fail in NBTreadBoolean!")
}

Local<Value> NBTClass::readString(const Arguments& args)
{
    try {
        auto v = nbt->getValue<string>();
        return String::newString(v);
    }
    CATCH("Fail in NBTreadString!")
}

Local<Value> NBTClass::readList(const Arguments& args)
{
    try {
        auto v = nbt->getValue<std::vector<Tag*>>();
        auto arr = Array::newArray();
        for (auto i : v) {
            auto tmp = NBTClass::newNBT(i);
            arr.add(tmp);
        }
        return arr;
    }
    CATCH("Fail in NBTreadList!")
}

Local<Value> NBTClass::readCompound(const Arguments& args)
{
    try {
        auto v = nbt->getValue<std::map<string, Tag>>();
        auto obj = Object::newObject();
        for (auto& i : v) {
            auto k = String::newString(i.first);
            auto v = NBTClass::newNBT(&(i.second));
            obj.set(k, v);
        }
        return obj;
    }
    CATCH("Fail in NBTreadCompound!")
}


Local<Value> NBTClass::readByte(const Arguments& args)
{
    try {
        auto v = nbt->getValue<char>();
        return Number::newNumber(v);
    }
    CATCH("Fail in NBTreadByte!")
}

Local<Value> NBTClass::writeInt(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber)

    try {
        auto k = args[0].asString().toString();
        int v = args[1].asNumber().toInt32();
        nbt->put(k, v);

        return Boolean::newBoolean(true);
    }
    CATCH("Fail in NBTwriteInt!")
}

Local<Value> NBTClass::writeLong(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber)

    try {
        auto k = args[0].asString().toString();
        __int64 v = args[1].asNumber().toInt64();
        nbt->put(k, v);

        return Boolean::newBoolean(true);
    }
    CATCH("Fail in NBTwriteLong!")
}

Local<Value> NBTClass::writeFloat(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber)

    try {
        auto k = args[0].asString().toString();
        auto v = args[1].asNumber().toFloat();
        nbt->put(k, v);

        return Boolean::newBoolean(true);
    }
    CATCH("Fail in NBTwriteInt!")
}

Local<Value> NBTClass::writeBoolean(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)
    CHECK_ARG_TYPE(args[1], ValueKind::kBoolean)

    try {
        auto k = args[0].asString().toString();
        auto v = args[1].asBoolean().value();
        nbt->put(k, (char)v);

        return Boolean::newBoolean(true);
    }
    CATCH("Fail in NBTwriteInt!")
}

Local<Value> NBTClass::writeByte(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber)

    try {
        auto k = args[0].asString().toString();
        auto v = args[1].asNumber().toInt32();
        nbt->put(k, (char)v);

        return Boolean::newBoolean(true);
    }
    CATCH("Fail in NBTwriteInt!")
}

Local<Value> NBTClass::writeString(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)
    CHECK_ARG_TYPE(args[1], ValueKind::kString)

    try {
        auto k = args[0].asString().toString();
        auto v = args[1].asString().toString();
        nbt->put(k, v);

        return Boolean::newBoolean(true);
    }
    CATCH("Fail in NBTwriteInt!")
}

Local<Value> NBTClass::writeList(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)
    CHECK_ARG_TYPE(args[1], ValueKind::kArray)

    try {
        auto k = args[0].asString().toString();
        auto arr = args[1].asArray();
        auto v = Tag::createTag(TagType::List);
        for (int i = 0; i < arr.size(); ++i)
        {
            auto nbt = NBTClass::extractNBT(arr.get(i));
            v->addValue2List(nbt);
        }
        nbt->put(k, v);

        return Boolean::newBoolean(true);
    }
    CATCH("Fail in NBTwriteInt!")
}

Local<Value> NBTClass::writeCompound(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)
    CHECK_ARG_TYPE(args[1], ValueKind::kObject)

    try {
        auto k = args[0].asString().toString();
        auto tmp = args[1].asObject();
        auto keys = tmp.getKeys();
        auto v = Tag::createTag(TagType::Compound);
        for (auto& i : keys) {
            auto nbt = NBTClass::extractNBT(tmp.get(i));
            v->put(i.toString(), nbt);
        }
        nbt->put(k, &v);

        return Boolean::newBoolean(true);
    }
    CATCH("Fail in NBTwriteInt!")
}

Local<Value> NBTClass::addValueToList(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1)
    CHECK_ARG_TYPE(args[0], ValueKind::kObject)

    try {
        auto tag = NBTClass::extractNBT(args[1].asValue());
        nbt->addValue2List(tag);

        return Boolean::newBoolean(true);
    }
    CATCH("Fail in NBTwriteInt!")
}

Local<Value> NBTClass::getType(const Arguments& args)
{
    try {
        auto type = nbt->getTagType();
        switch (type)
        {
        case TagType::End:
            return String::newString("End");
        case TagType::Byte:
            return String::newString("Byte/Boolean");
        case TagType::Short:
            return String::newString("Short");
        case TagType::Int:
            return String::newString("Int");
        case TagType::Int64:
            return String::newString("Long");
        case TagType::Float:
            return String::newString("Float");
        case TagType::Double:
            return String::newString("Double");
        case TagType::String:
            return String::newString("String");
        case TagType::ByteArray:
            return String::newString("ByteArray");
        case TagType::List:
            return String::newString("List");
        case TagType::Compound:
            return String::newString("Compound");
        default:
            return String::newString("Unknown");
        }

        return Boolean::newBoolean(true);
    }
    CATCH("Fail in NBTwriteInt!")
}

Local<Value> NBTClass::createTag(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1)
    CHECK_ARG_TYPE(args[0], ValueKind::kString)

    try {
        auto type = args[0].asString().toString();
        switch (H(type.c_str()))
        {
        case H("End"): {
            auto tag = Tag::createTag(TagType::End);
            return NBTClass::newNBT(tag);
        }
        case H("Byte"): {
            auto tag = Tag::createTag(TagType::Byte);
            return NBTClass::newNBT(tag);
        }
        case H("Short"): {
            auto tag = Tag::createTag(TagType::Short);
            return NBTClass::newNBT(tag);
        }
        case H("Int"): {
            auto tag = Tag::createTag(TagType::Int);
            return NBTClass::newNBT(tag);
        }
        case H("Long"): {
            auto tag = Tag::createTag(TagType::Int64);
            return NBTClass::newNBT(tag);
        }
        case H("Float"): {
            auto tag = Tag::createTag(TagType::Float);
            return NBTClass::newNBT(tag);
        }
        case H("Double"): {
            auto tag = Tag::createTag(TagType::Double);
            return NBTClass::newNBT(tag);
        }
        case H("String"): {
            auto tag = Tag::createTag(TagType::String);
            return NBTClass::newNBT(tag);
        }
        case H("ByteArray"): {
            auto tag = Tag::createTag(TagType::ByteArray);
            return NBTClass::newNBT(tag);
        }
        case H("List"): {
            auto tag = Tag::createTag(TagType::List);
            return NBTClass::newNBT(tag);
        }
        case H("Compound"): {
            auto tag = Tag::createTag(TagType::Compound);
            return NBTClass::newNBT(tag);
        }
        default:
            return String::newString("Unknown");
        }

        return Boolean::newBoolean(true);
    }
    CATCH("Fail in NBTwriteInt!")
}

Local<Value> NBTClass::setItem(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1)
    CHECK_ARG_TYPE(args[0], ValueKind::kObject)

    try {
        auto item = ItemClass::extractItem(args[0].asObject());
        nbt->setItem(item);
    }
    CATCH("Fail in NBT.setItem")
}

Local<Value> fromItem(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1)
    CHECK_ARG_TYPE(args[0], ValueKind::kObject)

    try {
        auto item = ItemClass::extractItem(args[0].asObject());
        auto nbt = Tag::fromItem(item);
        return NBTClass::newNBT(nbt);
    }
    CATCH("Fail in NBT.fromItem")
}

Local<Value> fromPtr(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1)
    CHECK_ARG_TYPE(args[0], ValueKind::kNumber)

    try {
        auto ptr = (Tag*)(args[0].asNumber().toInt64());
        return NBTClass::newNBT(ptr);
    }
    CATCH("Fail in NBT.fromPtt")
}
